//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Prefers.h"
#include "SNotes.h"
#include "inifiles.hpp"
#include "registry.hpp"
#include "stdio.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "RxCombos"
#pragma resource "*.dfm"
AnsiString PrefFileOpt = ExtractFilePath(Application->ExeName) + "Preferences.ini";
TPrefsForm* PrefsForm;
AnsiString OSopt;
int StyleIs = 0;
int TransIs;
bool WasTrayIcon;
bool WasTrans;
bool WasXPEffects;
bool WasMultiLine;
bool WasTop;
bool NeedOnClose = true;
struct L {
  char* HotExists;
  char* NoPrefsError;
  char* Error;
  char* WritePrefsError;
  char* ReadPrefsError;
  char* SelectFolder;
} LMessagesOpt;
//---------------------------------------------------------------------------
__fastcall TPrefsForm::TPrefsForm(TComponent* Owner)
  : TForm(Owner) {
}
//---------------------------------------------------------------------------
void ApplyLangOpt();
void OSdetectOpt();
void CheckPrefsInterOpt();
void CheckReadonlyOpt(AnsiString FileName);
//--------------------------------------------------------------------------
void __fastcall TPrefsForm::TransValueChange(TObject* Sender) {
  SNotesXMForm->AlphaBlendValue = TransValue->Position;
  TransparencyClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::ApplyButtonClick(TObject* Sender) {
  CheckPrefsInterOpt();
  CheckReadonlyOpt(PrefFileOpt);
  TRegistry* Reg = new TRegistry;
  TIniFile* Ini = new TIniFile(PrefFileOpt);

  try {
    Ini->WriteBool("Options", "FadeShow", FadeShow->Checked);
    Ini->WriteBool("Options", "URLDetect", URLDetect->Checked);
    Ini->WriteBool("Options", "MinOnClose", MinOnClose->Checked);
    Ini->WriteBool("Options", "StartWithWindows", StartWithWindows->Checked);
    Ini->WriteBool("Options", "TopPages", TopPages->Checked);
    Ini->WriteBool("Options", "Transparency", Transparency->Checked);
    Ini->WriteInteger("Options", "TransValue", TransValue->Position);
    Ini->WriteBool("Options", "MultiLines", MultiLines->Checked);
    Ini->WriteBool("Options", "WorkMode", NormalMode->Checked);
    Ini->WriteInteger("Options", "FadeSpeed", StrToInt(FadeSpeed->Text));
    Ini->WriteString("Options", "DefaultFont", FontComboBox1->FontName);
    Ini->WriteInteger("Options", "DefaultFontSize", StrToInt(DefaultSize->Text));
    Ini->WriteBool("Options", "FadeHide", FadeHide->Checked);
    Ini->WriteBool("Options", "XPEffects", XPEffects->Checked);
    Ini->WriteInteger("Options", "Style", StyleBox->ItemIndex);
    Ini->WriteBool("Options", "TaskbarIcon", TaskbarCheck->Checked);
    Ini->WriteBool("Options", "TrayIcon", IconInTray->Checked);
    Ini->WriteBool("Options", "HideWindow", HideWind->Checked);
    Ini->WriteInteger("Options", "HideTimeout", HideTimePosition->Position);
    Ini->WriteBool("Options", "AskOnFormatChange", AskFormat->Checked);

    if (FormatPageBox->ItemIndex == 0)
      Ini->WriteString("Options", "DefaultPageFormat", "RTF");
    else
      Ini->WriteString("Options", "DefaultPageFormat", "TXT");

    Reg->RootKey = HKEY_CURRENT_USER;
    Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);

    if (StartWithWindows->Checked) {
      AnsiString Path = Application->ExeName;
      Reg->WriteString("SimpleNotes", Path );
    } else {
      if (Reg->ValueExists("SimpleNotes") && (Reg->ReadString("SimpleNotes") == Application->ExeName))
        Reg->DeleteValue("SimpleNotes");
    }

    if (TopPages->Checked)
      SNotesXMForm->AllTabs->TabPosition = tpTop;
    else
      SNotesXMForm->AllTabs->TabPosition = tpBottom;

    SNotesXMForm->AllTabs->MultiLine = MultiLines->Checked;
    SNotesXMForm->RichEdit1->AutoURLDetect = URLDetect->Checked;

    if ((OSopt == "Win2K") || (OSopt == "WinXP") || (OSopt == "Win2003")) {
      SNotesXMForm->AlphaBlend = Transparency->Checked;
      SNotesXMForm->AlphaBlendValue = TransValue->Position;
    } else
      SNotesXMForm->AlphaBlend = false;

    switch (StyleBox->ItemIndex) {
      case 0:
        SNotesXMForm->TBXSwitcher1->Theme = "Default";
        break;

      case 1:
        SNotesXMForm->TBXSwitcher1->Theme = "OfficeXP";
        break;

      default:
        SNotesXMForm->TBXSwitcher1->Theme = "OfficeXP";
        break;
    }

    SNotesXMForm->TBXSwitcher1->EnableXPStyles = XPEffects->Checked;
    Ini->WriteString("Options", "BackUpPath", BackupPath->Text);
    WasTop = TopPages->Checked;
    WasXPEffects = SNotesXMForm->TBXSwitcher1->EnableXPStyles;
    WasMultiLine = SNotesXMForm->AllTabs->MultiLine;
    WasTrayIcon = SNotesXMForm->CoolTray->IconVisible;
    WasTrans = SNotesXMForm->AlphaBlend;
    TransIs = SNotesXMForm->AlphaBlendValue;
    StyleIs = StyleBox->ItemIndex;
    ApplyButton->Enabled = false;
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.WritePrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
  delete Reg;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::TransparencyClick(TObject* Sender) {
  if (Transparency->Checked) {
    SNotesXMForm->AlphaBlend = true;
    TransValue->Enabled = true;
    FadeShow->Enabled = true;
    FadeHide->Enabled = true;
    FadeShowClick(Sender);
  } else {
    SNotesXMForm->AlphaBlend = false;
    TransValue->Enabled = false;
    FadeShow->Enabled = false;
    FadeSpeed->Enabled = false;
    FadeSpeedPosition->Enabled = false;
    SpeedLabel->Enabled = false;
    FadeHide->Enabled = false;
  }

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FormShow(TObject* Sender) {
  CheckPrefsInterOpt();

  try {
    OSdetectOpt();
    TRegistry* Reg = new TRegistry;
    TIniFile* Ini = new TIniFile(PrefFileOpt);
    MinOnClose->Checked = Ini->ReadBool("Options", "MinOnClose", 1);

    if (Ini->ReadBool("Options", "TopPages", 1))
      TopPages->Checked = true;
    else
      BottomPages->Checked = true;

    if (Ini->ReadBool("Options", "WorkMode", 1))
      NormalMode->Checked = true;
    else
      HighMode->Checked = true;

    FontComboBox1->FontName = Ini->ReadString("Options", "DefaultFont", "MS Sans Serif");
    DefaultFontSizePosition->Position = Ini->ReadInteger("Options", "DefaultFontSize", 10);
    FadeShow->Checked = Ini->ReadBool("Options", "FadeShow", 1);
    URLDetect->Checked = Ini->ReadBool("Options", "URLDetect", 1);
    Transparency->Checked = Ini->ReadBool("Options", "Transparency", 0);
    TransValue->Position = Ini->ReadInteger("Options", "TransValue", 255);
    MultiLines->Checked = Ini->ReadBool("Options", "MultiLines", 0);
    FadeSpeedPosition->Position = Ini->ReadInteger("Options", "FadeSpeed", 2);
    FadeHide->Checked = Ini->ReadBool("Options", "FadeHide", 1);
    IconInTray->Checked = Ini->ReadBool("Options", "TrayIcon", 1);
    TaskbarCheck->Checked = Ini->ReadBool("Options", "TaskbarIcon", 1);
    XPEffects->Checked = Ini->ReadBool("Options", "XPEffects", 1);
    StyleBox->ItemIndex = Ini->ReadInteger("Options", "Style", 1);
    HideWind->Checked = Ini->ReadBool("Options", "HideWindow", 0);
    HideTimePosition->Position = Ini->ReadInteger("Options", "HideTimeout", 30);
    AskFormat->Checked = Ini->ReadBool("Options", "AskOnFormatChange", 1);

    if (Ini->ReadString("Options", "DefaultPageFormat", "RTF") == "RTF")
      FormatPageBox->ItemIndex = 0;
    else
      FormatPageBox->ItemIndex = 1;

    StyleIs = StyleBox->ItemIndex;
    FadeShowClick(Sender);
    TransparencyClick(Sender);
    HideWindClick(Sender);

    if ((OSopt != "WinXP") && (OSopt != "Win2K") && (OSopt != "Win2003")) {
      Transparency->Checked = false;
      Transparency->Enabled = false;
      TransValue->Position = 255;
      TransValue->Enabled = false;
      FadeShow->Checked = false;
      FadeShow->Enabled = false;
      FadeSpeed->Enabled = false;
      FadeSpeedPosition->Enabled = false;
      FadeHide->Enabled = false;
    }

    StyleBoxChange(Sender);
    Reg->RootKey = HKEY_CURRENT_USER;
    Reg->OpenKey("\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", true);

    if (Reg->ValueExists("SimpleNotes") && (Reg->ReadString("SimpleNotes") == Application->ExeName))
      StartWithWindows->Checked = true;
    else
      StartWithWindows->Checked = false;

    HotKeyComb->Modifiers.Clear();
    int Key = Ini->ReadInteger("Options", "Hot2", 145);
    HotKeyComb->HotKey = Key;

    if (Ini->ReadBool("Options", "Mod_Shift", 0))
      HotKeyComb->Modifiers << hkShift;

    if (Ini->ReadBool("Options", "Mod_Alt", 0))
      HotKeyComb->Modifiers << hkAlt;

    if (Ini->ReadBool("Options", "Mod_Ctrl", 0))
      HotKeyComb->Modifiers << hkCtrl;

    BackupPath->Text = Ini->ReadString("Options", "BackUpPath", "");
    WasTop = TopPages->Checked;
    WasXPEffects = SNotesXMForm->TBXSwitcher1->EnableXPStyles;
    WasMultiLine = SNotesXMForm->AllTabs->MultiLine;
    WasTrayIcon = SNotesXMForm->CoolTray->IconVisible;
    WasTrans = SNotesXMForm->AlphaBlend;
    TransIs = SNotesXMForm->AlphaBlendValue;
    ApplyButton->Enabled = false;
    SetHotkeyButton->Enabled = false;
    PagesTree->Items->operator [](0)->Selected = true;
    PagesTree->SetFocus();
    delete Ini;
    delete Reg;
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.ReadPrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::CancelButtonClick(TObject* Sender) {
  AnsiString StyleTx = StyleBox->Items->Strings[StyleIs];
  SNotesXMForm->TBXSwitcher1->Theme = StyleTx;
  SNotesXMForm->TBXSwitcher1->EnableXPStyles = WasXPEffects;
  SNotesXMForm->AllTabs->MultiLine = WasMultiLine;
  SNotesXMForm->CoolTray->IconVisible = WasTrayIcon;
  SNotesXMForm->AlphaBlend = WasTrans;
  SNotesXMForm->AlphaBlendValue = TransIs;

  if (WasTop)
    SNotesXMForm->AllTabs->TabPosition = tpTop;
  else
    SNotesXMForm->AllTabs->TabPosition = tpBottom;

  NeedOnClose = false;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::SetHotkeyButtonClick(TObject* Sender) {
  CheckPrefsInterOpt();
  CheckReadonlyOpt(PrefFileOpt);
  TIniFile* Ini = new TIniFile(PrefFileOpt);
  long int HotKey = HotKeyComb->HotKey;
  int Mods = 0;
  int Key = 0;

  if (HotKeyComb->Modifiers.Contains(hkShift))
    HotKey -= 8192;

  if (HotKeyComb->Modifiers.Contains(hkAlt))
    HotKey -= 32768;

  if (HotKeyComb->Modifiers.Contains(hkCtrl))
    HotKey -= 16384;

  try {
    if (HotKeyComb->Modifiers.Contains(hkShift))
      Ini->WriteBool("Options", "Mod_Shift", 1);
    else
      Ini->WriteBool("Options", "Mod_Shift", 0);

    if (HotKeyComb->Modifiers.Contains(hkAlt))
      Ini->WriteBool("Options", "Mod_Alt", 1);
    else
      Ini->WriteBool("Options", "Mod_Alt", 0);

    if (HotKeyComb->Modifiers.Contains(hkCtrl))
      Ini->WriteBool("Options", "Mod_Ctrl", 1);
    else
      Ini->WriteBool("Options", "Mod_Ctrl", 0);

    Ini->WriteInteger("Options", "HotKey", HotKey);
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.WritePrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }

  try {
    if (Ini->ReadBool("Options", "Mod_Shift", 0))
      Mods += MOD_SHIFT;

    if (Ini->ReadBool("Options", "Mod_Alt", 0))
      Mods += MOD_ALT;

    if (Ini->ReadBool("Options", "Mod_Ctrl", 0))
      Mods += MOD_CONTROL;

    Key = Ini->ReadInteger("Options", "HotKey", 165);
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.ReadPrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }

  try {
    Ini->WriteInteger("Options", "Hot2", HotKeyComb->HotKey);
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.WritePrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }

  if (HotKeyComb->HotKey != 0) {
    UnregisterHotKey(Application->Handle, 1);
    bool HotKey2 = RegisterHotKey(Application->Handle, 1, Mods, Key);

    if (!HotKey2)
      Application->MessageBoxA(LMessagesOpt.HotExists, LMessagesOpt.Error,  MB_OK + MB_ICONWARNING);
  }

  delete Ini;
  SetHotkeyButton->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FormClose(TObject* Sender, TCloseAction& Action) {
  CheckPrefsInterOpt();
  CheckReadonlyOpt(PrefFileOpt);
  TIniFile* Ini = new TIniFile(PrefFileOpt);

  try {
    if (HotKeyComb->HotKey != 0)
      Ini->WriteBool("Options", "HotKeyEn", 1);
    else
      Ini->WriteBool("Options", "HotKeyEn", 0);
  } catch (...) {
    Application->MessageBoxA(LMessagesOpt.WritePrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;

  if (NeedOnClose) {
    AnsiString StyleTx = StyleBox->Items->Strings[StyleIs];
    SNotesXMForm->TBXSwitcher1->Theme = StyleTx;
    SNotesXMForm->TBXSwitcher1->EnableXPStyles = WasXPEffects;
    SNotesXMForm->AllTabs->MultiLine = WasMultiLine;
    SNotesXMForm->CoolTray->IconVisible = WasTrayIcon;
    SNotesXMForm->AlphaBlend = WasTrans;
    SNotesXMForm->AlphaBlendValue = TransIs;

    if (WasTop)
      SNotesXMForm->AllTabs->TabPosition = tpTop;
    else
      SNotesXMForm->AllTabs->TabPosition = tpBottom;
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FadeShowClick(TObject* Sender) {
  if (FadeShow->Checked) {
    SpeedLabel->Enabled = true;
    FadeSpeed->Enabled = true;
    FadeSpeedPosition->Enabled = true;
  } else {
    SpeedLabel->Enabled = false;
    FadeSpeed->Enabled = false;
    FadeSpeedPosition->Enabled = false;
  }

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FadeSpeedKeyPress(TObject* Sender, char& Key) {
  Set <char, '0', '9'> Dig;
  Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';

  if ((! Dig.Contains(Key)) && (Key != VK_BACK))
    Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::OKButtonClick(TObject* Sender) {
  ApplyButtonClick(Sender);
  NeedOnClose = false;
  Close();
}
//---------------------------------------------------------------------------
void ApplyLangOpt() {
  TIniFile* LangIni;

  if (SNotesXMForm->RussianLangMenu->Checked)
    LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\Russian.lng");

  if (SNotesXMForm->EnglishLangMenu->Checked)
    LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\English.lng");

  PrefsForm->Caption = LangIni->ReadString("Language", "OPTIONS_WINDOW_TITLE", "Настройки");
  PrefsForm->PagesTree->Items->operator [](0)->Text = LangIni->ReadString("Language", "OPTIONS_PAGE_GENERAL", "Общие");
  PrefsForm->PagesTree->Items->operator [](1)->Text = LangIni->ReadString("Language", "OPTIONS_PAGE_VIEW", "Вид");
  PrefsForm->PagesTree->Items->operator [](2)->Text = LangIni->ReadString("Language", "OPTIONS_PAGE_OPTIMIZATION", "Оптимизация");
  PrefsForm->PagesTree->Items->operator [](3)->Text = LangIni->ReadString("Language", "OPTIONS_PAGE_HOTKEY", "Горячая клавиша");
  PrefsForm->PagesTree->Items->operator [](4)->Text = LangIni->ReadString("Language", "OPTIONS_PAGE_DEFAULT", "По умолчанию");
  PrefsForm->OKButton->Caption = LangIni->ReadString("Language", "OPTIONS_OK_BUTTON", "OK");
  PrefsForm->CancelButton->Caption = LangIni->ReadString("Language", "OPTIONS_CANCEL_BUTTON", "О&тмена");
  PrefsForm->ApplyButton->Caption = LangIni->ReadString("Language", "OPTIONS_APPLY_BUTTON", "П&рименить");

  PrefsForm->GeneralGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_GENERAL_LABEL", "Общие настройки");
  PrefsForm->MinOnClose->Caption = LangIni->ReadString("Language", "OPTIONS_CLOSE_AS_MIN_CHECKBOX", "ЗАКРЫТЬ работает как СВЕРНУТЬ");
  PrefsForm->StartWithWindows->Caption = LangIni->ReadString("Language", "OPTIONS_AUTORUN_CHECKBOX", "Запускаться с Windows");
  PrefsForm->StorePagesGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_STORE_PAGES_LABEL", "Располагать названия страниц");
  PrefsForm->TopPages->Caption = LangIni->ReadString("Language", "OPTIONS_ON_TOP_RADIO", "Вверху");
  PrefsForm->BottomPages->Caption = LangIni->ReadString("Language", "OPTIONS_BOTTOM_RADIO", "Внизу");
  PrefsForm->SelectBackupFolderLabel->Caption = LangIni->ReadString("Language", "OPTIONS_BACKUP_FOLDER_LABEL", "Выберите папку для резервного копирования:");
  PrefsForm->IconInTray->Caption = LangIni->ReadString("Language", "OPTIONS_TRAY_ICON_CHECKBOX", "Значок в системном трее");
  PrefsForm->TaskbarCheck->Caption = LangIni->ReadString("Language", "OPTIONS_TASKBAR_ICON_CHECKBOX", "Значок в панели задач (перезапустите программу)");
  PrefsForm->HideWind->Caption = LangIni->ReadString("Language", "OPTIONS_HIDE_WINDOW_CHECKBOX", "Скрывать окно, если оно неактивно");
  PrefsForm->HideLabel->Caption = LangIni->ReadString("Language", "OPTIONS_SECONDS_LABEL", "сек.");

  PrefsForm->ViewGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_VIEW_LABEL", "Вид");
  PrefsForm->Transparency->Caption = LangIni->ReadString("Language", "OPTIONS_TRANS_CHECKBOX", "Эффект полупрозрачности (WinXP/2K/2003)");
  PrefsForm->MultiLines->Caption = LangIni->ReadString("Language", "OPTIONS_MULTILINE_CHECKBOX", "Многострочные закладки");
  PrefsForm->URLDetect->Caption = LangIni->ReadString("Language", "OPTIONS_AUTO_URL_CHECKBOX", "Автоопределение ссылок (перезапустите программу)");
  PrefsForm->FadeShow->Caption = LangIni->ReadString("Language", "OPTIONS_FADE_SHOW_CHECKBOX", "Плавное появление");
  PrefsForm->SpeedLabel->Caption = LangIni->ReadString("Language", "OPTIONS_SPEED_LABEL", "Скорость");
  PrefsForm->StyleLabel->Caption = LangIni->ReadString("Language", "OPTIONS_STYLE_LABEL", "Стиль:");
  PrefsForm->StyleBox->Items->Strings[0] = LangIni->ReadString("Language", "OPTIONS_DEFAULT_STYLE", "Стандартный");
  PrefsForm->XPEffects->Caption = LangIni->ReadString("Language", "OPTIONS_XP_EFECTS_CHECKBOX", "Включить оформление XP");

  PrefsForm->ProgramModeGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_PROGRAM_MODE_LABEL", "Выберите режим работы программы");
  PrefsForm->NormalMode->Caption = LangIni->ReadString("Language", "OPTIONS_NORMAL_RADIO", "Обычный");
  PrefsForm->HighMode->Caption = LangIni->ReadString("Language", "OPTIONS_SECURITY_RADIO", "Надежный");
  PrefsForm->NormalModeLabel->Caption = LangIni->ReadString("Language", "OPTIONS_NORMAL_MODE_LABEL", "Программа сохраняет текст при смене страниц, сворачивании и закрытии. Работает быстро даже на слабых машинах.");
  PrefsForm->SecurityModeLabel->Caption = LangIni->ReadString("Language", "OPTIONS_SECURITY_MODE_LABEL", "Программа сохраняет каждый введенный символ. Занимает меньше места в RAM на 0.5 Мб, но работает медленно при высокой загрузке процессора.");

  PrefsForm->HotkeyGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_SEY_HOTKEY_LABEL", "Установите горячую клавишу");
  PrefsForm->HotkeyLabel->Caption = LangIni->ReadString("Language", "OPTIONS_HOTKEY_LABEL", "Горячая клавиша для свертывания/восстановления SimpleNotes");
  PrefsForm->SetHotkeyButton->Caption = LangIni->ReadString("Language", "OPTIONS_SET_HOTKEY_BUTTON", "Задействовать!");
  PrefsForm->FadeHide->Caption = LangIni->ReadString("Language", "OPTIONS_FADE_HIDE_CHECKBOX", "Плавное исчезновение при нажатии");

  PrefsForm->DefaultGroupBox->Caption = LangIni->ReadString("Language", "OPTIONS_DEFAULT_LABEL", "Настройки по умолчанию");
  PrefsForm->DefaultFontLabel->Caption = LangIni->ReadString("Language", "OPTIONS_DEFAULT_FONT_LABEL", "Шрифт по умолчанию:");
  PrefsForm->DefaultPageColorLabel->Caption = LangIni->ReadString("Language", "OPTIONS_DEFAULT_COLOR_LABEL", "Цвет фона страницы по умолчанию:");
  PrefsForm->DefaultFontSizeLabel->Caption = LangIni->ReadString("Language", "OPTIONS_DEFAULT_FONT_SIZE_LABEL", "Размер шрифта по умолчанию:");
  PrefsForm->PageFormatLabel->Caption = LangIni->ReadString("Language", "OPTIONS_DEFAULT_FORMAT_LABEL", "Формат страницы при создании:");
  PrefsForm->FormatPageBox->Items->Strings[0] = LangIni->ReadString("Language", "OPTIONS_DEFAULT_RTF_FORMAT", "rtf-формат");
  PrefsForm->FormatPageBox->Items->Strings[1] = LangIni->ReadString("Language", "OPTIONS_DEFAULT_TXT_FORMAT", "txt-формат");
  PrefsForm->AttentionLabel->Caption = LangIni->ReadString("Language", "OPTIONS_FORMAT_WARNING_LABEL", "Внимание!!! В txt-формате Вы НЕ сможете вставлять объекты и изображения, менять фоматирование отдельных частей текста, менять цвет текста и т.д.");
  PrefsForm->AskFormat->Caption = LangIni->ReadString("Language", "OPTIONS_CONFIRM_FORMAT_CHANGE_CHECKBOX", "Подтверждать смену формата страницы из rtf в txt");

  LMessagesOpt.Error = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str()) + 1];
  LMessagesOpt.HotExists = new char [strlen((LangIni->ReadString("Language", "OPTIONS_MESSAGE_ERROR_HOTKEY_ALREADY_REGISTERED", "Эта клавиша уже зарегистрирована!")).c_str()) + 1];
  LMessagesOpt.NoPrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str()) + 1];
  LMessagesOpt.WritePrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_1", "Ошибка при записи в файл настроек") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно получить к нему доступ, файл или диск защищены (переполнены)") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_3", "от записи, другой пользователь производит запись в данный файл.")).c_str()) + 1];
  LMessagesOpt.ReadPrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str()) + 1];
  LMessagesOpt.SelectFolder = new char [strlen((LangIni->ReadString("Language", "OPTIONS_SELECT_FOLDER_DIALOG_LABEL", "Выберите папку для резервного копирования:")).c_str()) + 1];


  strcpy(LMessagesOpt.Error, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str());
  strcpy(LMessagesOpt.HotExists, (LangIni->ReadString("Language", "OPTIONS_MESSAGE_ERROR_HOTKEY_ALREADY_REGISTERED", "Эта клавиша уже зарегистрирована!")).c_str());
  strcpy(LMessagesOpt.NoPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str());
  strcpy(LMessagesOpt.WritePrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_1", "Ошибка при записи в файл настроек") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно получить к нему доступ, файл или диск защищены (переполнены)") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_3", "от записи, другой пользователь производит запись в данный файл.")).c_str());
  strcpy(LMessagesOpt.ReadPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек") + " " + PrefFileOpt + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str());
  strcpy(LMessagesOpt.SelectFolder, (LangIni->ReadString("Language", "OPTIONS_SELECT_FOLDER_DIALOG_LABEL", "Выберите папку для резервного копирования:")).c_str());
  delete LangIni;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FormCreate(TObject* Sender) {
  try {
    ApplyLangOpt();
  } catch (...) {
    Application->MessageBoxA("Error reading language file. Default language will be used.", "Error", MB_OK + MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::DefaultColorClick(TObject* Sender) {
  CheckPrefsInterOpt();
  CheckReadonlyOpt(PrefFileOpt);

  if (ColorDialog1->Execute()) {
    TIniFile* Ini = new TIniFile(PrefFileOpt);

    try {
      Ini->WriteInteger("Options", "DefaultColor", ColorDialog1->Color);
    } catch (...) {
      Application->MessageBoxA(LMessagesOpt.WritePrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
    }

    delete Ini;
  }
}
//---------------------------------------------------------------------------
void OSdetectOpt() {
  OSVERSIONINFO OsInfo;
  int Win32Platform, Win32MajorVersion, Win32MinorVersion;
  OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&OsInfo);
  Win32Platform = OsInfo.dwPlatformId;
  Win32MajorVersion = OsInfo.dwMajorVersion;
  Win32MinorVersion = OsInfo.dwMinorVersion;

  if (Win32Platform == VER_PLATFORM_WIN32s)
    OSopt = "Win3x";

  if (Win32Platform == VER_PLATFORM_WIN32_WINDOWS) {
    if (Win32MajorVersion == 4) {
      if (Win32MinorVersion >= 0)
        OSopt = "Win95";

      if (Win32MinorVersion >= 10)
        OSopt = "Win98";

      if (Win32MinorVersion >= 90)
        OSopt = "WinMe";
    }
  }

  if (Win32Platform == VER_PLATFORM_WIN32_NT) {
    if (Win32MajorVersion <= 4)
      OSopt = "WinNT";

    if (Win32MajorVersion == 5) {
      if (Win32MinorVersion >= 0)
        OSopt = "Win2K";

      if (Win32MinorVersion >= 1)
        OSopt = "WinXP";

      if (Win32MinorVersion >= 2)
        OSopt = "Win2003";
    }
  }
}
//------------------------------------------------------------------------------
void __fastcall TPrefsForm::BrowseButtonClick(TObject* Sender) {
  BROWSEINFO    info;
  char          szDir[MAX_PATH];
  char          szDisplayName[MAX_PATH];
  LPITEMIDLIST  pidl;
  LPMALLOC      pShellMalloc;

  if(SHGetMalloc(&pShellMalloc) == NO_ERROR) {
    memset(&info, 0x00, sizeof(info));
    info.hwndOwner = Handle;
    info.pidlRoot  = 0;
    info.pszDisplayName = szDisplayName;
    info.lpszTitle = LMessagesOpt.SelectFolder;
    info.ulFlags = BIF_NEWDIALOGSTYLE; //BIF_RETURNONLYFSDIRS;
    info.lpfn = 0;
    pidl = SHBrowseForFolder(&info);

    if(pidl) {
      if(SHGetPathFromIDList(pidl, szDir))
        BackupPath->Text = szDir;

      pShellMalloc->Free(pidl);
    }

    pShellMalloc->Release();
  }
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::StyleBoxChange(TObject* Sender) {
  switch (StyleBox->ItemIndex) {
    case 0:
      SNotesXMForm->TBXSwitcher1->Theme = "Default";
      XPEffects->Enabled = true;
      break;

    case 1:
      SNotesXMForm->TBXSwitcher1->Theme = "OfficeXP";
      XPEffects->Enabled = false;
      break;

    default:
      SNotesXMForm->TBXSwitcher1->Theme = "OfficeXP";
      XPEffects->Enabled = false;
      break;
  }

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::BackupPathChange(TObject* Sender) {
  BackupPath->Text = IncludeTrailingBackslash(BackupPath->Text);
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::MinOnCloseClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::StartWithWindowsClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::TaskbarCheckClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::TopPagesClick(TObject* Sender) {
  if (TopPages->Checked)
    SNotesXMForm->AllTabs->TabPosition = tpTop;

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::BottomPagesClick(TObject* Sender) {
  if (BottomPages->Checked)
    SNotesXMForm->AllTabs->TabPosition = tpBottom;

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::MultiLinesClick(TObject* Sender) {
  SNotesXMForm->AllTabs->MultiLine = MultiLines->Checked;
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::URLDetectClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FadeSpeedChange(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::XPEffectsClick(TObject* Sender) {
  SNotesXMForm->TBXSwitcher1->EnableXPStyles = XPEffects->Checked;
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::NormalModeClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::HighModeClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::HotKeyCombChange(TObject* Sender) {
  SetHotkeyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FadeHideClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FontComboBox1Change(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::DefaultSizeChange(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::HideWindClick(TObject* Sender) {
  if (HideWind->Checked) {
    HideTime->Enabled = true;
    HideTimePosition->Enabled = true;
    HideLabel->Enabled = true;
  } else {
    HideTime->Enabled = false;
    HideTimePosition->Enabled = false;
    HideLabel->Enabled = false;
  }

  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::HideTimeChange(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::FormatPageBoxChange(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::AskFormatClick(TObject* Sender) {
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::IconInTrayClick(TObject* Sender) {
  SNotesXMForm->CoolTray->IconVisible = IconInTray->Checked;
  ApplyButton->Enabled = true;
}
//---------------------------------------------------------------------------
void CheckPrefsInterOpt() {
  if (!FileExists(PrefFileOpt)) {
    FILE* F = fopen(PrefFileOpt.c_str(), "w+");

    if (F == NULL) {
      Application->MessageBoxA(LMessagesOpt.NoPrefsError, LMessagesOpt.Error, MB_OK + MB_ICONERROR);
      fclose(F);
      Application->Terminate();
    }

    fclose(F);
  }
}
//---------------------------------------------------------------------------
void CheckReadonlyOpt(AnsiString FileName) {
  DWORD Attrs = GetFileAttributes(FileName.c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES)
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      SetFileAttributes(FileName.c_str(), FILE_ATTRIBUTE_NORMAL);

}
//---------------------------------------------------------------------------
void __fastcall TPrefsForm::PagesTreeChange(TObject* Sender,
    TTreeNode* Node) {
  TTreeNode* Index = PagesTree->Selected;

  if (Index->SelectedIndex == 0) {
    GeneralGroupBox->Visible = true;
    ViewGroupBox->Visible = false;
    ProgramModeGroupBox->Visible = false;
    HotkeyGroupBox->Visible = false;
    DefaultGroupBox->Visible = false;
  }

  if (Index->SelectedIndex == 1) {
    ViewGroupBox->Visible = true;
    GeneralGroupBox->Visible = false;
    ProgramModeGroupBox->Visible = false;
    HotkeyGroupBox->Visible = false;
    DefaultGroupBox->Visible = false;
  }

  if (Index->SelectedIndex == 2) {
    ProgramModeGroupBox->Visible = true;
    GeneralGroupBox->Visible = false;
    ViewGroupBox->Visible = false;
    HotkeyGroupBox->Visible = false;
    DefaultGroupBox->Visible = false;
  }

  if (Index->SelectedIndex == 3) {
    HotkeyGroupBox->Visible = true;
    GeneralGroupBox->Visible = false;
    ViewGroupBox->Visible = false;
    ProgramModeGroupBox->Visible = false;
    DefaultGroupBox->Visible = false;
  }

  if (Index->SelectedIndex == 4) {
    DefaultGroupBox->Visible = true;
    GeneralGroupBox->Visible = false;
    ViewGroupBox->Visible = false;
    ProgramModeGroupBox->Visible = false;
    HotkeyGroupBox->Visible = false;

  }
}
//---------------------------------------------------------------------------

