//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "SNotes.h"
#include "About.h"
#include "Prefers.h"
#include "SelLang.h"
#include "ProgressForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TBXOfficeXPTheme"
#pragma include "TBXOfficeXPTheme.pas"
#pragma link "RxCombos"
#pragma link "RXShell"
#pragma link "CoolTrayIcon"
#pragma link "TB2Dock"
#pragma link "TB2Item"
#pragma link "TB2Toolbar"
#pragma link "TBX"
#pragma link "TBXSwitcher"
#pragma link "ThemeMgr"
#pragma link "TBXToolPals"
#pragma link "TBXDkPanels"
#pragma link "TBXToolPals"
#pragma link "JvRichEdit"
#pragma resource "*.dfm"
#include "inifiles.hpp"
#include "stdio.h"
#include "registry.hpp"
#include "clipbrd.hpp"
#include "RxGif.hpp"
AnsiString PrefFile = ExtractFilePath(Application->ExeName) + "Preferences.ini";
TSNotesXMForm* SNotesXMForm;
int ShowCounter = 0;
int LangCounter = 0;
bool OSXP = false;
bool WasCreateFunc = false;
AnsiString OS;
AnsiString HyperLink;
struct L {
  AnsiString PrintPage;
  AnsiString BackupTitle;
  AnsiString BackupText;
  char* Error;
  char* NoPrefsError;
  char* NoPageError;
  char* OtherHotKeyError;
  char* EmptyError;
  char* PrefsError;
  char* PageCreateError;
  char* PageCreateErrorTitle;
  char* ConfirmDelete;
  char* ConfirmDeleteTitle;
  char* OnePageError;
  char* OnePageErrorTitle;
  char* SelectFolderError;
  char* SelectFolderErrorTitle;
  char* Message;
  char* FolderNotExistsError1;
  char* FolderNotExistsError2;
  char* FolderNotExistsErrorTitle;
  char* NewPageTitle;
  char* EnterName;
  char* RenamePageTitle;
  char* NewName;
  char* CopyTempOK;
  char* CopyTempFail;
  char* WritePrefsError;
  char* ReadPrefsError;
  char* ReadPageLockedError1;
  char* ReadPageLockedError2;
  char* WritePageLockedError1;
  char* WritePageLockedError2;
  char* WritePageProtectError1;
  char* WritePageProtectError2;
  char* WritePageDiskFullError1;
  char* WritePageDiskFullError2;
  char* InsImageError;
  char* ConfirmFormatChange;
  char* ConfirmSaveToTemp;
  char* SelectTempFolderTitle;
  char* ConfirmReadonlyOff;
  char* RemoveReadonlyFail;
  char* CreateFolderFail;
  char* RestoreNotFound1;
  char* RestoreNotFound2;
  char* ConfirmRestore1;
  char* ConfirmRestore2;
  char* RestoreBroken;
  char* NoRestoreFolder;
  char* NoPrinter;
} LMessages;
bool ShowCopyLink = false;
bool AllowQuestion;
int Pos = -1;
//---------------------------------------------------------------------------
__fastcall TSNotesXMForm::TSNotesXMForm(TComponent* Owner)
  : TForm(Owner) {
}
//---------------------------------------------------------------------------
void FreeLang();
void ApplyLang();
void OSdetect();
AnsiString CheckAccess(AnsiString FileName);
void DisplayError(AnsiString Type, AnsiString WriteRead, AnsiString PageName, bool Quest);
void CheckPrefs();
void CheckPrefsInter();
bool CreateNewPage(AnsiString PageName);
AnsiString GetBrowsePath();
void SaveToTemp(char* ErrorStr, bool Quest, bool Cat);
void CheckReadonly(AnsiString PageName, bool Quest);
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormClose(TObject* Sender, TCloseAction& Action) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  if (Ini->ReadBool("Options", "MinOnClose", 0)) {
    Application->Minimize();
    Abort();
  } else {
    UnregisterHotKey(SNotesXMForm->Handle, 1);
    CheckReadonly(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);

    try {
      RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
    } catch (...) {
      DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
    }

    try {
      Ini->WriteInteger("Parameters", "PageCount", AllTabs->Tabs->Count);
      Ini->WriteInteger("Parameters", "PageIndex", AllTabs->TabIndex);
      Ini->WriteInteger("Parameters", "Top", SNotesXMForm->Top);
      Ini->WriteInteger("Parameters", "Left", SNotesXMForm->Left);
      Ini->WriteInteger("Parameters", "Height", SNotesXMForm->Height);
      Ini->WriteInteger("Parameters", "Width", SNotesXMForm->Width);
      Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart);
      TBIniSavePositions(SNotesXMForm, PrefFile, "");
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsChanging(TObject* Sender, bool& AllowChange) {
  AllTabs->OnMouseDown = NULL;

  if (!FileExists(PrefFile)) {
    FILE* F = fopen(PrefFile.c_str(), "w+");

    if (F == NULL) {
      Application->MessageBoxA(LMessages.NoPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      fclose(F);
      AllTabs->OnEndDrag = NULL;
      Application->Terminate();
    }

    fclose(F);
  }

  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  CheckReadonly(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);

  try {
    RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
  } catch (...) {
    DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
  }

  try {
    if (RichEdit1->SelStart == 0)
      Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart + 1);
    else
      Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsChange(TObject* Sender) {
  if (FileExists(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn")) {
    CheckPrefsInter();
    TIniFile* Ini = new TIniFile(PrefFile);
    RichEdit1->OnSelectionChange = NULL;
    AnsiString Format = "RTF";

    try {
      Format = Ini->ReadString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "RTF");
    } catch (...) {
      Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    if (Format == "TXT") {
      AllowQuestion = false;
      TXTFormatClick(Sender);
    } else
      RTFFormatClick(Sender);

    try {
      RichEdit1->Color = Ini->ReadInteger("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex], -2147483643);
    } catch (...) {
      Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    try {
      RichEdit1->Lines->LoadFromFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
    } catch (...) {
      DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Read", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", false);
    }

    try {
      RichEdit1->SelStart = Ini->ReadInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], 0);
    } catch (...) {
      Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
    FontNameBox->FontName = RichEdit1->SelAttributes->Name;
    FontSizeBox->Text = IntToStr(RichEdit1->SelAttributes->Size);
    delete Ini;
  } else {
    char* ErrorStr = new char[strlen((ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn").c_str()) + strlen(LMessages.NoPageError) + 2];
    strcpy(ErrorStr, LMessages.NoPageError);
    strcat(ErrorStr, "\n");
    strcat(ErrorStr, (ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn").c_str());
    Application->MessageBoxA(ErrorStr, LMessages.Error, MB_OK + MB_ICONERROR);
    RichEdit1->Lines->Clear();
    delete ErrorStr;
  }

  MouseEventTimer->Interval = 100;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontMenuClick(TObject* Sender) {
  FontDialog1->Font->Name = RichEdit1->SelAttributes->Name;
  FontDialog1->Font->Size = RichEdit1->SelAttributes->Size;
  FontDialog1->Font->Style = RichEdit1->SelAttributes->Style;
  FontDialog1->Font->Color = RichEdit1->SelAttributes->Color;

  if (FontDialog1->Execute())
    RichEdit1->SelAttributes->Assign(FontDialog1->Font);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::NewPageMenuClick(TObject* Sender) {
  NewPageButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ExitMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  CheckReadonly(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);

  try {
    RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
  } catch (...) {
    DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
  }

  try {
    Ini->WriteInteger("Parameters", "PageIndex", AllTabs->TabIndex);
    Ini->WriteInteger("Parameters", "Top", SNotesXMForm->Top);
    Ini->WriteInteger("Parameters", "Left", SNotesXMForm->Left);
    Ini->WriteInteger("Parameters", "Height", SNotesXMForm->Height);
    Ini->WriteInteger("Parameters", "Width", SNotesXMForm->Width);
    Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart);
    TBIniSavePositions(SNotesXMForm, PrefFile, "");
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
  UnregisterHotKey(SNotesXMForm->Handle, 1);
  Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AlignLeftButtonClick(TObject* Sender) {
  RichEdit1->Paragraph->Alignment = taLeftJustify;
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AlignCenterButtonClick(TObject* Sender) {
  RichEdit1->Paragraph->Alignment = taCenter;
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AlignRightButtonClick(TObject* Sender) {
  RichEdit1->Paragraph->Alignment = taRightJustify;
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RichEdit1SelectionChange(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  AlignLeftButton->OnClick = NULL;
  AlignCenterButton->OnClick = NULL;
  AlignRightButton->OnClick = NULL;

  if (RichEdit1->Paragraph->Alignment == taLeftJustify)
    AlignLeftButton->Checked = true;

  if (RichEdit1->Paragraph->Alignment == taCenter)
    AlignCenterButton->Checked = true;

  if (RichEdit1->Paragraph->Alignment == taRightJustify)
    AlignRightButton->Checked = true;

  FontSizeBox->Text = IntToStr(RichEdit1->SelAttributes->Size);
  FontNameBox->OnChange = NULL;
  FontNameBox->FontName = RichEdit1->SelAttributes->Name;
  FontNameBox->OnChange = FontNameBoxChange;
  AlignLeftButton->OnClick = AlignLeftButtonClick;
  AlignCenterButton->OnClick = AlignCenterButtonClick;
  AlignRightButton->OnClick = AlignRightButtonClick;
  bool WorkMode = false;

  try {
    WorkMode = Ini->ReadBool("Options", "WorkMode", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (!WorkMode) {
    CheckReadonly(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);

    try {
      RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
    } catch (...) {
      DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
    }
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::SaveAsPageMenuClick(TObject* Sender) {
  if (SaveDialog1->Execute())
    RichEdit1->Lines->SaveToFile(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontPopClick(TObject* Sender) {
  FontMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FindPopClick(TObject* Sender) {
  RichEdit1->FindDialog(RichEdit1->SelText);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ReplacePopClick(TObject* Sender) {
  RichEdit1->ReplaceDialog(RichEdit1->SelText, RichEdit1->SelText);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FindMenuClick(TObject* Sender) {
  FindPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ReplaceMenuClick(TObject* Sender) {
  ReplacePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PrintPageMenuClick(TObject* Sender) {
  int PagesCount = 0;

  try {
    if (PrintDialog1->Execute())
      PagesCount = PrintDialog1->Copies;
  } catch (...) {
    Application->MessageBoxA(LMessages.NoPrinter, LMessages.Message, MB_OK + MB_ICONWARNING);
  }

  for (int i = 0; i < PagesCount; i++)
    RichEdit1->Print(LMessages.PrintPage + " SimpleNotes #" + IntToStr(i + 1));
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::SearchButtonClick(TObject* Sender) {
  FindPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::WordWrapMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  RichEdit1->WordWrap = WordWrapMenu->Checked;

  try {
    Ini->WriteBool("Parameters", "WordWrap", WordWrapMenu->Checked);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::StayOnTopMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  try {
    Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (StayOnTopMenu->Checked) {
    try {
      Ini->WriteBool("Parameters", "OnTop", 1);
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    SNotesXMForm->FormStyle = fsStayOnTop;

    if ((OSXP) && (SNotesXMForm->AlphaBlend))
      try {
        SNotesXMForm->AlphaBlendValue = Ini->ReadInteger("Options", "TransValue", 255);
      } catch (...) {
        Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
  } else {
    try {
      Ini->WriteBool("Parameters", "OnTop", 0);
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    SNotesXMForm->FormStyle = fsNormal;

    if ((OSXP) && (SNotesXMForm->AlphaBlend))
      try {
        SNotesXMForm->AlphaBlendValue = Ini->ReadInteger("Options", "TransValue", 255);
      } catch (...) {
        Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
  }

  RichEdit1->SetFocus();

  try {
    RichEdit1->SelStart = Ini->ReadInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], 0);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ExitPopClick(TObject* Sender) {
  ExitMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormCreate(TObject* Sender) {
  CheckPrefs();
  DWORD Attrs = GetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES)
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      SetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str(), FILE_ATTRIBUTE_NORMAL);

  try {
    TIniFile* Ini = new TIniFile(PrefFile);

    if (!IfBackup->Checked) {
      AnsiString FromCopy = IncludeTrailingBackslash(Ini->ReadString("Options", "BackUpPath", ""));
      delete Ini;
      CopyFile((FromCopy + "Preferences.ini").c_str(), (ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str(), false);
      Ini = new TIniFile(PrefFile);
    }

    TBImageList1->AddImages(ImageList1);
    TBImageList1->DisabledImages = ImageList1;
    MainMenuBar->Images = TBImageList1;
    EditorPopupMenu->Images = TBImageList1;
    TrayPopupMenu->Images = TBImageList1;
    PagePopupMenu->Images = TBImageList1;
    RichEdit1->OnSelectionChange = NULL;
    CoolTray->IconVisible = Ini->ReadBool("Options", "TrayIcon", 1);

    if (!Ini->ReadBool("Options", "TaskbarIcon", 1)) {
      DWORD StyleEx = GetWindowLong(Application->Handle, GWL_EXSTYLE);
      StyleEx |= WS_EX_TOOLWINDOW;
      SetWindowLong(Application->Handle, GWL_EXSTYLE, StyleEx);
    } else {
      DWORD StyleEx = GetWindowLong(Application->Handle, GWL_EXSTYLE);
      StyleEx |= WS_EX_APPWINDOW;
      SetWindowLong(Application->Handle, GWL_EXSTYLE, StyleEx);
    }

    OSdetect();

    if ((OS == "WinXP") || (OS == "Win2K") || (OS == "Win2003")) {
      OSXP = true;
      SNotesXMForm->AlphaBlend = Ini->ReadBool("Options", "Transparency", 0);

      if (SNotesXMForm->AlphaBlend)
        SNotesXMForm->AlphaBlendValue = Ini->ReadInteger("Options", "TransValue", 255);
    } else
      SNotesXMForm->AlphaBlend = false;

    AnsiString Lang = Ini->ReadString("Parameters", "Language", "English");

    if (Lang == "Russian")
      RussianLangMenu->Checked = true;

    if (Lang == "English")
      EnglishLangMenu->Checked = true;

    ApplyLang();
    SNotesXMForm->Top = Ini->ReadInteger("Parameters", "Top", 210);
    SNotesXMForm->Left = Ini->ReadInteger("Parameters", "Left", 400);
    SNotesXMForm->Height = Ini->ReadInteger("Parameters", "Height", 480);
    SNotesXMForm->Width = Ini->ReadInteger("Parameters", "Width", 380);

    if (Ini->ReadBool("Parameters", "OnTop", 0)) {
      StayOnTopMenu->Checked = true;
      SNotesXMForm->FormStyle = fsStayOnTop;
    } else
      SNotesXMForm->FormStyle = fsNormal;

    if (Ini->ReadBool("Options", "HotKeyEn", 1)) {
      int Mods = 0;

      if (Ini->ReadBool("Options", "Mod_Shift", 0))
        Mods += MOD_SHIFT;

      if (Ini->ReadBool("Options", "Mod_Alt", 0))
        Mods += MOD_ALT;

      if (Ini->ReadBool("Options", "Mod_Ctrl", 0))
        Mods += MOD_CONTROL;

      int Key = Ini->ReadInteger("Options", "HotKey", 145);
      bool HotKey = RegisterHotKey(SNotesXMForm->Handle, 1, Mods, Key);

      if ((!HotKey) && (IfBackup->Checked))
        Application->MessageBoxA(LMessages.OtherHotKeyError, LMessages.Error,  MB_OK + MB_ICONWARNING);
    }

    int Style = Ini->ReadInteger("Options", "Style", 1);

    if (Style == 0)
      TBXSwitcher1->Theme = "Default";

    if (Style == 1)
      TBXSwitcher1->Theme = "OfficeXP";

    TBXSwitcher1->EnableXPStyles = Ini->ReadBool("Options", "XPEffects", 1);
    AllTabs->MultiLine = Ini->ReadBool("Options", "MultiLines", 0);
    RichEdit1->DefAttributes->Name = Ini->ReadString("Options", "DefaultFont", "MS Sans Serif");
    RichEdit1->DefAttributes->Size = Ini->ReadInteger("Options", "DefaultFontSize", 10);
    RichEdit1->AutoURLDetect = Ini->ReadBool("Options", "URLDetect", 1);
    ColorPalette->Color = Ini->ReadInteger("Parameters", "FontColor", 0);

    if (Ini->ReadBool("Options", "TopPages", 1))
      AllTabs->TabPosition = tpTop;
    else
      AllTabs->TabPosition = tpBottom;

    RichEdit1->WordWrap = Ini->ReadBool("Parameters", "WordWrap", 1);
    WordWrapMenu->Checked = RichEdit1->WordWrap;
    int PCount = Ini->ReadInteger("Parameters", "PageCount", 1);
    AllTabs->Tabs->Clear();

    for (int i = 0; i < PCount; i++)
      AllTabs->Tabs->Add(Ini->ReadString("Pages", IntToStr(i), "SimpleNotes" + IntToStr(i)));

    AllTabs->TabIndex = Ini->ReadInteger("Parameters", "PageIndex", 0);

    if (Ini->ReadString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "RTF") == "TXT") {
      AllowQuestion = false;
      TXTFormatClick(Sender);
    } else
      RTFFormatClick(Sender);

    if (FileExists(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn")) {
      RichEdit1->Color = Ini->ReadInteger("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex], -2147483643);

      try {
        RichEdit1->Lines->LoadFromFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
      } catch (...) {
        DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Read", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", false);
      }

      RichEdit1->SelStart = Ini->ReadInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], 0);
    } else {
      char* ErrorStr = new char[strlen((ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn").c_str()) + strlen(LMessages.NoPageError) + 2];
      strcpy(ErrorStr, LMessages.NoPageError);
      strcat(ErrorStr, "\n");
      strcat(ErrorStr, (ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn").c_str());
      Application->MessageBoxA(ErrorStr, LMessages.Error, MB_OK + MB_ICONERROR);
      RichEdit1->Lines->Clear();
      delete ErrorStr;
    }

    char WinDir[255];
    GetSystemDirectory(WinDir, 255);
    char SysDir[255];
    GetWindowsDirectory(SysDir, 255);

    if ((!FileExists((String)WinDir + "\\calc.exe")) && (!FileExists((String)SysDir + "\\calc.exe"))) {
      CalcMenu->Enabled = false;
      CalculatorButton->Visible = false;
      CalcPop->Enabled = false;
    }

    RichEdit1->SelectionBar = Ini->ReadBool("Parameters", "LeftMargin", 1);
    LeftMarginMenu->Checked = RichEdit1->SelectionBar;
    FormatBar->Visible = Ini->ReadBool("FormatBar", "Visible", 1);
    ServiceBar->Visible = Ini->ReadBool("ServiceBar", "Visible", 1);
    MainMenuBar->Visible = Ini->ReadBool("MainMenuBar", "Visible", 1);
    FormatBarMenu->Checked = FormatBar->Visible;
    ServiceBarMenu->Checked = ServiceBar->Visible;
    MainMenuMenu->Checked = MainMenuBar->Visible;
    TBIniLoadPositions(SNotesXMForm, PrefFile, "");

    for (int i = 0; i < AllTabs->Tabs->Count; i++)
      Ini->WriteString("Pages", IntToStr(i), AllTabs->Tabs->Strings[i]);

    Ini->WriteInteger("Parameters", "PageCount", AllTabs->Tabs->Count);
    RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
    RichEdit1SelectionChange(Sender);
    delete Ini;
  } catch (...) {
    char* MessText = new char [strlen(("Error in file with preferences" + PrefFile + "\n" + "Application will be closed.").c_str()) + 2];
    strcpy(MessText, "Error in file with preferences");
    strcat(MessText, (" " + PrefFile + "\n" + "Application will be closed.").c_str());
    Application->MessageBoxA(MessText, "Error", MB_OK + MB_ICONERROR);
    delete [] MessText;
    Application->Terminate();
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AboutMenuClick(TObject* Sender) {
  Application->CreateForm(__classid(TAboutBox), &AboutBox);
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::BackColorClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  if (ColorDialog1->Execute())
    RichEdit1->Color = ColorDialog1->Color;

  try {
    Ini->WriteInteger("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->Color);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CalcMenuClick(TObject* Sender) {
  ShellExecute (Handle, "open", "Calc", NULL, NULL, SW_RESTORE);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CalculatorButtonClick(TObject* Sender) {
  CalcMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CalcPopClick(TObject* Sender) {
  CalcMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::Timer1Timer(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  bool WorkMode = false;

  try {
    WorkMode = Ini->ReadBool("Options", "WorkMode", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (!WorkMode)
    RichEdit1->OnSelectionChange = NULL;

  SNotesXMForm->OnShow = NULL;
  SNotesXMForm->AlphaBlendValue = 0;
  CoolTray->ShowMainForm();
  SNotesXMForm->OnShow = TSNotesXMForm::FormShow;
  TSNotesXMForm::FormShow(NULL);
  RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
  RichEdit1SelectionChange(NULL);
  Timer1->Interval = 0;
  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::NewPageButtonClick(TObject* Sender) {
  CreateNewPage("");
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::DeletePageButtonClick(TObject* Sender) {
  if ((Application->MessageBoxA(LMessages.ConfirmDelete, LMessages.ConfirmDeleteTitle, MB_YESNO + MB_ICONQUESTION) == IDYES)) {
    if (AllTabs->Tabs->Count > 1) {
      CheckPrefsInter();
      CheckReadonly("Preferences.ini", false);
      TIniFile* Ini = new TIniFile(PrefFile);

      try {
        DeleteFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
        Ini->DeleteKey("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        Ini->DeleteKey("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        Ini->DeleteKey("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        Ini->EraseSection("Pages");
      } catch (...) {
        Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      AllTabs->Tabs->Delete(AllTabs->TabIndex);

      try {
        int PC = AllTabs->Tabs->Count;

        for (int i = 0; i < PC; i++)
          Ini->WriteString("Pages", IntToStr(i), AllTabs->Tabs->Strings[i]);

        Ini->WriteInteger("Parameters", "PageCount", AllTabs->Tabs->Count);
      } catch (...) {
        Application->MessageBoxA(LMessages.PrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      RichEdit1->OnSelectionChange = NULL;
      AllTabs->TabIndex = 0;
      AllTabsChange(Sender);
      RichEdit1->SetFocus();
      RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
      delete Ini;
    } else
      Application->MessageBoxA(LMessages.OnePageError, LMessages.OnePageErrorTitle, MB_OK + MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontSizeBoxKeyPress(TObject* Sender, char& Key) {
  Set <char, '0', '9'> Dig;
  Dig << '0' << '1' << '2' << '3' << '4' << '5' << '6' << '7' << '8' << '9';

  if ((! Dig.Contains(Key)) && (Key != VK_BACK) && (Key != VK_RETURN))
    Key = 0;

  if (Key == VK_RETURN)
    FontSizeBoxSelect(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontButtonClick(TObject* Sender) {
  FontMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsMouseUp(TObject* Sender,
    TMouseButton Button, TShiftState Shift, int X, int Y) {
  if (!FileExists(PrefFile)) {
    FILE* F = fopen(PrefFile.c_str(), "w+");

    if (F == NULL) {
      Application->MessageBoxA(LMessages.NoPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      fclose(F);
      AllTabs->OnEndDrag = NULL;
      Application->Terminate();
    }

    fclose(F);
  }

  if (Button == mbRight) {
    int Index = AllTabs->IndexOfTabAt(X, Y);

    if (Index != AllTabs->TabIndex) {
      AllTabsChanging(Sender, true);
      AllTabs->TabIndex = Index;
      AllTabsChange(Sender);
    }

    PagePopupMenu->Popup(Mouse->CursorPos.x, Mouse->CursorPos.y - 60);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RenamePagePopClick(TObject* Sender) {
  AnsiString PageName = AllTabs->Tabs->Strings[AllTabs->TabIndex];
  bool Flag = InputQuery(LMessages.RenamePageTitle, LMessages.NewName, PageName);

  if (Flag) {
    bool counter = false;

    for (int i = 0; i < (AllTabs->Tabs->Count); i++) {
      if (FileExists(ExtractFilePath(Application->ExeName) + PageName + ".spn"))
        counter = true;

      if (PageName == (AllTabs->Tabs->Strings[i]))
        counter = true;
    }

    if (counter)
      Application->MessageBoxA(LMessages.PageCreateError, LMessages.PageCreateErrorTitle, MB_OK + MB_ICONWARNING);
    else {
      CheckPrefsInter();
      CheckReadonly("Preferences.ini", false);
      TIniFile* Ini = new TIniFile(PrefFile);
      int OldName = 0;

      try {
        OldName = Ini->ReadInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], 0);
      } catch (...) {
        Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      try {
        RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + PageName + ".spn");
      } catch (...) {
        DisplayError(CheckAccess(ExtractFilePath(Application->ExeName) + PageName + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
      }

      try {
        Ini->DeleteKey("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        Ini->DeleteKey("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        Ini->DeleteKey("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex]);
        DeleteFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
        AllTabs->Tabs->Strings[AllTabs->TabIndex] = PageName;
        Ini->WriteString("Pages", IntToStr(AllTabs->TabIndex), PageName);
        Ini->WriteInteger("PageColour", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->Color);
        Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], OldName);

        if (RichEdit1->PlainText)
          Ini->WriteString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "TXT");
        else
          Ini->WriteString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "RTF");
      } catch (...) {
        Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      delete Ini;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::NewPagePopClick(TObject* Sender) {
  NewPageButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::DeletePagePopClick(TObject* Sender) {
  DeletePageButtonClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::SavePageButtonClick(TObject* Sender) {
  SaveAsPageMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PrintPageButtonClick(TObject* Sender) {
  PrintPageMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ApplicationEvents1Message(tagMSG& Msg,
    bool& Handled) {
  try {
    TIniFile* Ini = new TIniFile(PrefFile);

    if ((Msg.message == WM_HOTKEY) && (Ini->ReadBool("Options", "HotKeyEn", 1))) {
      if (Msg.wParam == 1) {
        CheckPrefsInter();

        if (SNotesXMForm->Visible) {
          if ((Ini->ReadBool("Options", "Transparency", 0)) && OSXP && (Ini->ReadBool("Options", "FadeHide", 0))) {
            int count = Ini->ReadInteger("Options", "FadeSpeed", 2);

            for (int i = 1; i < SNotesXMForm->AlphaBlendValue / Ini->ReadInteger("Options", "FadeSpeed", 2); i++) {
              SNotesXMForm->AlphaBlendValue -= count;
              SNotesXMForm->Repaint();
            }
          }

          SNotesXMForm->Visible = false;
          Application->Minimize();
        } else {
          if (!Ini->ReadBool("Options", "WorkMode", 1))
            RichEdit1->OnSelectionChange = NULL;

          SNotesXMForm->OnShow = NULL;
          SNotesXMForm->AlphaBlendValue = 0;
          CoolTray->ShowMainForm();
          SNotesXMForm->OnShow = TSNotesXMForm::FormShow;
          TSNotesXMForm::FormShow(NULL);
          RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
          RichEdit1SelectionChange(NULL);
        }

        Handled = true;
      }
    }

    delete Ini;
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if ((Msg.message == WM_LBUTTONDBLCLK) && (SNotesXMForm->Active) && (!FontNameBox->DroppedDown) && (!FontSizeBox->DroppedDown)) {
    int tabx = Mouse->CursorPos.x - AllTabs->ClientOrigin.x;
    int taby = Mouse->CursorPos.y - AllTabs->ClientOrigin.y;
    int pos = AllTabs->IndexOfTabAt(tabx, taby);

    if (pos >= 0) {
      RenamePagePopClick(NULL);
      Handled = true;
    }
  }

  if ((Msg.message == WM_QUERYENDSESSION) && (SNotesXMForm->Visible)) {
    ExitMenuClick(NULL);
    Handled = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ApplicationEvents1Minimize(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  bool WorkMode = true;

  try {
    WorkMode = Ini->ReadBool("Options", "WorkMode", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (WorkMode) {
    CheckReadonly(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);

    try {
      RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
    } catch (...) {
      DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
    }
  }

  try {
    Ini->WriteInteger("Parameters", "PageIndex", AllTabs->TabIndex);
    Ini->WriteInteger("Parameters", "Top", SNotesXMForm->Top);
    Ini->WriteInteger("Parameters", "Left", SNotesXMForm->Left);
    Ini->WriteInteger("Parameters", "Height", SNotesXMForm->Height);
    Ini->WriteInteger("Parameters", "Width", SNotesXMForm->Width);
    Ini->WriteInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], RichEdit1->SelStart);
    TBIniSavePositions(SNotesXMForm, PrefFile, "");
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
  CoolTray->HideMainForm();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PreferencesMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  Application->CreateForm(__classid(TPrefsForm), &PrefsForm);

  try {
    Ini->DeleteKey("Options", "FlatMenus");
    Ini->WriteBool("Options", "HotKeyEn", 0);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  PrefsForm->ShowModal();
  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontSizeBoxSelect(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  RichEdit1->OnSelectionChange = NULL;
  RichEdit1->SetFocus();

  try {
    RichEdit1->SelStart = Ini->ReadInteger("Parameters", "SelStart", 0);
    RichEdit1->SelLength = Ini->ReadInteger("Parameters", "SelLen", 0);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  RichEdit1->SelAttributes->Size = StrToInt(FontSizeBox->Text);
  RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
  RichEdit1SelectionChange(Sender);
  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontSizeBoxClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  try {
    Ini->WriteInteger("Parameters", "SelStart", RichEdit1->SelStart);
    Ini->WriteInteger("Parameters", "SelLen", RichEdit1->SelLength);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RichEdit1URLClick(TObject* Sender, const AnsiString URLText, TMouseButton Button) {
  if (Button == mbLeft) {
    char* HLink = new char [strlen(URLText.c_str()) + 1];
    strcpy(HLink, URLText.c_str());
    ShellExecute(0, NULL, HLink , NULL, NULL, 1);
    delete [] HLink;
  }

  if (Button == mbRight) {
    ShowCopyLink = true;
    HyperLink = URLText;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontBoldPopClick(TObject* Sender) {
  if (RichEdit1->SelAttributes->Style == RichEdit1->SelAttributes->Style << fsBold)
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsBold;
  else
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsBold;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontItalicPopClick(TObject* Sender) {
  if (RichEdit1->SelAttributes->Style == RichEdit1->SelAttributes->Style << fsItalic)
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsItalic;
  else
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsItalic;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontUnderlinePopClick(TObject* Sender) {
  if (RichEdit1->SelAttributes->Style == RichEdit1->SelAttributes->Style << fsUnderline)
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsUnderline;
  else
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsUnderline;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontStrikeoutPopClick(TObject* Sender) {
  if (RichEdit1->SelAttributes->Style == RichEdit1->SelAttributes->Style << fsStrikeOut)
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style >> fsStrikeOut;
  else
    RichEdit1->SelAttributes->Style = RichEdit1->SelAttributes->Style << fsStrikeOut;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontNameBoxClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  try {
    Ini->WriteInteger("Parameters", "FontSelStart", RichEdit1->SelStart);
    Ini->WriteInteger("Parameters", "FontSelLen", RichEdit1->SelLength);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontNameBoxChange(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  RichEdit1->OnSelectionChange = NULL;
  RichEdit1->SetFocus();

  try {
    RichEdit1->SelStart = Ini->ReadInteger("Parameters", "FontSelStart", 0);
    RichEdit1->SelLength = Ini->ReadInteger("Parameters", "FontSelLen", 0);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  RichEdit1->SelAttributes->Name = FontNameBox->FontName;
  RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
  RichEdit1SelectionChange(Sender);
  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RestorePopClick(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  bool WorkMode = false;

  try {
    WorkMode = Ini->ReadBool("Options", "WorkMode", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (!WorkMode)
    RichEdit1->OnSelectionChange = NULL;

  SNotesXMForm->OnShow = NULL;
  SNotesXMForm->AlphaBlendValue = 0;
  CoolTray->ShowMainForm();
  SNotesXMForm->OnShow = TSNotesXMForm::FormShow;
  TSNotesXMForm::FormShow(NULL);
  RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
  RichEdit1SelectionChange(NULL);
  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormShow(TObject* Sender) {
  CheckPrefs();
  DWORD Attrs = GetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES)
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      SetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str(), FILE_ATTRIBUTE_NORMAL);

  TIniFile* Ini = new TIniFile(PrefFile);

  try {
    bool Changed = false;
    bool FirstStart = Ini->ReadBool("Parameters", "FirstStart", 0);

    if (!FirstStart) {
      Ini->WriteString("Parameters", "FirstStart", 1);
      Application->CreateForm(__classid(TLangForm), &LangForm);
      LangForm->ShowModal();
      Changed = true;
    }

    if (Changed) {
      AnsiString Lang = Ini->ReadString("Parameters", "Language", "English");

      if (Lang == "Russian")
        RussianLangMenu->Checked = true;

      if (Lang == "English")
        EnglishLangMenu->Checked = true;

      ApplyLang();
    }

    SNotesXMForm->BringToFront();

    if (ShowCounter == 0) {
      RichEdit1->SetFocus();
      RichEdit1->SelStart = Ini->ReadInteger("PageCursors", AllTabs->Tabs->Strings[AllTabs->TabIndex], 0);
    }

    ++ShowCounter;

    if (OSXP && (Ini->ReadBool("Options", "FadeShow", 0)) && (Ini->ReadBool("Options", "Transparency", 0)) && (FirstStart)) {
      int counter = Ini->ReadInteger("Options", "FadeSpeed", 2);

      for (int i = 0; i < (Ini->ReadInteger("Options", "TransValue", 255) / counter); i++) {
        SNotesXMForm->AlphaBlendValue += counter;
        SNotesXMForm->Repaint();
      }
    } else if (OSXP) {
      SNotesXMForm->AlphaBlend = Ini->ReadBool("Options", "Transparency", 0);
      SNotesXMForm->AlphaBlendValue = Ini->ReadInteger("Options", "TransValue", 255);
    } else if (!OSXP) {
      SNotesXMForm->AlphaBlendValue = 255;
      SNotesXMForm->AlphaBlend = false;
    }

    delete Ini;
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorBlackPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorWhitePopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clWhite;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorRedPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clRed;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorGreenPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clGreen;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorBluePopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clBlue;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorYellowPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clYellow;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorPinkPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clFuchsia;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorDarkRedPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clMaroon;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorDarkBluePopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clNavy;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorAquaPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clAqua;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorLimePopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clLime;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorPurplePopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clPurple;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorGrayPopClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = clGray;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CoolTrayClick(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  bool WorkMode = false;

  try {
    WorkMode = Ini->ReadBool("Options", "WorkMode", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (SNotesXMForm->Visible == false) {
    if (!WorkMode)
      RichEdit1->OnSelectionChange = NULL;

    SNotesXMForm->OnShow = NULL;
    SNotesXMForm->AlphaBlendValue = 0;
    CoolTray->ShowMainForm();
    SNotesXMForm->OnShow = TSNotesXMForm::FormShow;
    TSNotesXMForm::FormShow(NULL);
    RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
    RichEdit1SelectionChange(NULL);
  } else
    Application->Minimize();

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontMarkersPopClick(TObject* Sender) {
  RichEdit1->Paragraph->Numbering = !RichEdit1->Paragraph->Numbering;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::BackupMenuClick(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  AnsiString Path = "";

  try {
    Path = Ini->ReadString("Options", "BackUpPath", "");
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;

  if (Path == "")
    Application->MessageBoxA(LMessages.SelectFolderError, LMessages.SelectFolderErrorTitle, MB_OK + MB_ICONINFORMATION);
  else {
    bool WasCreate = false;

    if (!DirectoryExists(Path) && (OS == "WinMe" || OS == "Win2K" || OS == "WinXP" || OS == "Win2003")) {
      char* Msg = new char[strlen(LMessages.FolderNotExistsError1) + strlen(LMessages.FolderNotExistsError2) + strlen(Path.c_str()) + 4];
      strcpy(Msg, LMessages.FolderNotExistsError1);
      strcat(Msg, "\n");
      strcat(Msg, LMessages.FolderNotExistsError2);
      strcat(Msg, " ");
      strcat(Msg, Path.c_str());
      strcat(Msg, "?");

      if (Application->MessageBoxA(Msg, LMessages.FolderNotExistsErrorTitle, MB_YESNO + MB_ICONQUESTION) == IDYES)
        if (SHCreateDirectoryEx(Application->Handle, Path.c_str(), NULL) != ERROR_SUCCESS)
          Application->MessageBoxA(LMessages.CreateFolderFail, LMessages.Error, MB_OK + MB_ICONERROR);

      delete [] Msg;
      WasCreate = true;
    }

    if (DirectoryExists(Path) && (Path != "\\")) {
      IfBackup->Checked = true;

      try {
        RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn");
      } catch (...) {
        DisplayError(CheckAccess(AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn"), "Write", AllTabs->Tabs->Strings[AllTabs->TabIndex] + ".spn", true);
      }

      Application->CreateForm(__classid(TBackupProgressForm), &BackupProgressForm);
      BackupProgressForm->ShowModal();
      CoolTray->ShowBalloonHint(LMessages.BackupTitle, LMessages.BackupText, bitInfo, 1);
      HintTimer->Interval = 4000;
    } else if (!WasCreate)
      Application->MessageBoxA(LMessages.FolderNotExistsError1, LMessages.FolderNotExistsErrorTitle, MB_OK + MB_ICONWARNING);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RussianLangMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  if (RussianLangMenu->Checked)
    try {
      Ini->WriteString("Parameters", "Language", "Russian");
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

  RussianLangMenu->Checked = true;
  delete Ini;
  ApplyLang();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::EnglishLangMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  if (EnglishLangMenu->Checked)
    try {
      Ini->WriteString("Parameters", "Language", "English");
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

  EnglishLangMenu->Checked = true;
  delete Ini;
  ApplyLang();
}
//---------------------------------------------------------------------------
void FreeLang() {
  delete [] LMessages.Error;
  delete [] LMessages.NoPrefsError;
  delete [] LMessages.NoPageError;
  delete [] LMessages.OtherHotKeyError;
  delete [] LMessages.EmptyError;
  delete [] LMessages.PrefsError;
  delete [] LMessages.PageCreateError;
  delete [] LMessages.PageCreateErrorTitle;
  delete [] LMessages.ConfirmDelete;
  delete [] LMessages.ConfirmDeleteTitle;
  delete [] LMessages.OnePageError;
  delete [] LMessages.OnePageErrorTitle;
  delete [] LMessages.SelectFolderError;
  delete [] LMessages.SelectFolderErrorTitle;
  delete [] LMessages.Message;
  delete [] LMessages.FolderNotExistsError1;
  delete [] LMessages.FolderNotExistsError2;
  delete [] LMessages.FolderNotExistsErrorTitle;
  delete [] LMessages.ConfirmFormatChange;
  delete [] LMessages.WritePrefsError;
  delete [] LMessages.ReadPrefsError;
  delete [] LMessages.ReadPageLockedError1;
  delete [] LMessages.ReadPageLockedError2;
  delete [] LMessages.WritePageLockedError1;
  delete [] LMessages.WritePageLockedError2;
  delete [] LMessages.WritePageProtectError1;
  delete [] LMessages.WritePageProtectError2;
  delete [] LMessages.WritePageDiskFullError1;
  delete [] LMessages.WritePageDiskFullError2;
  delete [] LMessages.InsImageError;
  delete [] LMessages.NewPageTitle;
  delete [] LMessages.EnterName;
  delete [] LMessages.RenamePageTitle;
  delete [] LMessages.NewName;
  delete [] LMessages.CopyTempOK;
  delete [] LMessages.CopyTempFail;
  delete [] LMessages.ConfirmSaveToTemp;
  delete [] LMessages.SelectTempFolderTitle;
  delete [] LMessages.ConfirmReadonlyOff;
  delete [] LMessages.RemoveReadonlyFail;
  delete [] LMessages.CreateFolderFail;
  delete [] LMessages.RestoreNotFound1;
  delete [] LMessages.RestoreNotFound2;
  delete [] LMessages.ConfirmRestore1;
  delete [] LMessages.ConfirmRestore2;
  delete [] LMessages.RestoreBroken;
  delete [] LMessages.NoRestoreFolder;
  delete [] LMessages.NoPrinter;
}
//---------------------------------------------------------------------------
void ApplyLang () {
  CheckPrefs();
  DWORD Attrs = GetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES)
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      SetFileAttributes((ExtractFilePath(Application->ExeName) + "Preferences.ini").c_str(), FILE_ATTRIBUTE_NORMAL);

  try {
    TIniFile* Ini = new TIniFile(PrefFile);
    TIniFile* LangIni;
    AnsiString Lang = Ini->ReadString("Parameters", "Language", "English");
    delete Ini;

    if (Lang == "Russian")
      LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\Russian.lng");

    if (Lang == "English")
      LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\English.lng");

    SNotesXMForm->FileMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_FILE", "&Файл");
    SNotesXMForm->EditMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_EDIT", "&Правка");
    SNotesXMForm->ViewMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_VIEW", "&Вид");
    SNotesXMForm->FormatMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_FORMAT", "Фо&рмат");
    SNotesXMForm->LanguageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_LANGUAGE", "Язы&к");
    SNotesXMForm->ToolsMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_TOOLS", "&Сервис");
    SNotesXMForm->HelpMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_HELP", "По&мощь");

    SNotesXMForm->NewPageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_NEW", "&Создать");
    SNotesXMForm->OpenPageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_OPEN", "&Открыть...");
    SNotesXMForm->SaveAsPageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_SAVE_AS", "Со&хранить как..");
    SNotesXMForm->PrintPageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_PRINT", "&Печать");
    SNotesXMForm->ExitMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_EXIT", "&Выход");

    SNotesXMForm->UndoMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_UNDO", "&Отменить");
    SNotesXMForm->RedoMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_REDO", "Повто&рить");
    SNotesXMForm->CutMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_CUT", "&Вырезать");
    SNotesXMForm->CopyMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_COPY", "&Копировать");
    SNotesXMForm->PasteMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_PASTE", "Встав&ить");
    SNotesXMForm->PasteTextMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_PASTE_TEXT", "Вс&тавить (только текст)");
    SNotesXMForm->SelectAllMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_SELECT_ALL", "Вы&делить все");
    SNotesXMForm->FindMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_FIND", "&Найти");
    SNotesXMForm->ReplaceMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_REPLACE", "&Заменить");
    SNotesXMForm->PasteSpecialMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_PASTE_SPECIAL", "Спе&циальная вставка");
    SNotesXMForm->InsertObjectMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_INSERT_OBJECT", "Вставить &объект");
    SNotesXMForm->InsertImageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_INSERT_IMAGE", "Вставить и&зображение");

    SNotesXMForm->ToolbarsMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_TOOLBARS", "Па&нели инструментов");
    SNotesXMForm->FormatBarMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_FORMAT_BAR", "Панель &форматирования");
    SNotesXMForm->ServiceBarMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_SERVICE_BAR", "Панель &сервиса");
    SNotesXMForm->MainMenuMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_MENU_BAR", "Главное &меню");
    SNotesXMForm->WordWrapMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_WORD_WRAP", "&Переносить по словам");
    SNotesXMForm->StayOnTopMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_ON_TOP", "&Поверх всех окон");
    SNotesXMForm->LeftMarginMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_LEFT_MARGIN", "Поле &слева");

    SNotesXMForm->FontMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_FONT", "&Шрифт");
    SNotesXMForm->BackColor->Caption = LangIni->ReadString("Language", "MAIN_MENU_COLOR", "Ц&вет фона");

    SNotesXMForm->CalcMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_CALC", "&Калькулятор");
    SNotesXMForm->PreferencesMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_PREFERENCES", "&Настройки");
    SNotesXMForm->BackupMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_BACKUP", "&Резервное копирование");
    SNotesXMForm->RestoreMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_RESTORE", "&Восстановление");

    SNotesXMForm->AboutMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_ABOUT", "О &программе...");
    SNotesXMForm->HomePageMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_HOME_PAGE", "&Домашняя web-страница");
    SNotesXMForm->WriteLetterMenu->Caption = LangIni->ReadString("Language", "MAIN_MENU_TO_AUTHOR", "Письмо &автору");

    SNotesXMForm->RTFFormat->Caption = LangIni->ReadString("Language", "MAIN_MENU_RTF_FORMAT", "rtf-формат");
    SNotesXMForm->TXTFormat->Caption = LangIni->ReadString("Language", "MAIN_MENU_TXT_FORMAT", "txt-формат");

    SNotesXMForm->NewPagePop->Caption = LangIni->ReadString("Language", "MAIN_PAGE_POPUP_NEW", "Создать страницу");
    SNotesXMForm->DeletePagePop->Caption = LangIni->ReadString("Language", "MAIN_PAGE_POPUP_DELETE", "Удалить страницу");
    SNotesXMForm->RenamePagePop->Caption = LangIni->ReadString("Language", "MAIN_PAGE_POPUP_RENAME", "Переименовать страницу");

    SNotesXMForm->AutoColor->Caption = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_FONT_COLOR_AUTO", "&Авто");
    SNotesXMForm->MoreColors->Caption = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_FONT_COLOR_OTHER", "&Другие...");

    SNotesXMForm->CalcPop->Caption = LangIni->ReadString("Language", "TRAY_POPUP_CALC", "Калькулятор");
    SNotesXMForm->RestorePop->Caption = LangIni->ReadString("Language", "TRAY_POPUP_RESTORE", "Восстановить");
    SNotesXMForm->ExitPop->Caption = LangIni->ReadString("Language", "TRAY_POPUP_EXIT", "Выход");
    SNotesXMForm->HomePagePop->Caption = LangIni->ReadString("Language", "TRAY_POPUP_HOME_PAGE", "Домашняя web-страница");
    SNotesXMForm->WriteLetterPop->Caption = LangIni->ReadString("Language", "TRAY_POPUP_TO_AUTHOR", "Письмо автору");

    SNotesXMForm->FormatPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT", "Формат шрифта");
    SNotesXMForm->FontBoldPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_BOLD", "Жирный");
    SNotesXMForm->FontItalicPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_ITALIC", "Курсив");
    SNotesXMForm->FontUnderlinePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_UNDERLINE", "Подчеркнутый");
    SNotesXMForm->FontStrikeoutPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_STRIKEOUT", "Зачеркнутый");
    SNotesXMForm->FontMarkersPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_MARKERS", "Маркеры");
    SNotesXMForm->UpCase->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_UP_LETTERS", "Все прописные");
    SNotesXMForm->LowCase->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_LOW_LETTERS", "Все строчные");
    SNotesXMForm->Indent->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_INDENT", "Отступ");
    SNotesXMForm->Unindent->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FORMAT_UNINDENT", "Выступ");
    SNotesXMForm->ColorPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR", "Цвет шрифта");
    SNotesXMForm->ColorBlackPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_BLACK", "Черный");
    SNotesXMForm->ColorWhitePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_WHITE", "Белый");
    SNotesXMForm->ColorRedPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_RED", "Красный");
    SNotesXMForm->ColorGreenPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_GREEN", "Зеленый");
    SNotesXMForm->ColorBluePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_BLUE", "Синий");
    SNotesXMForm->ColorYellowPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_YELLOW", "Желтый");
    SNotesXMForm->ColorPinkPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_PINK", "Розовый");
    SNotesXMForm->ColorDarkRedPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_DARK_RED", "Темно-бордовый");
    SNotesXMForm->ColorDarkBluePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_DARK_BLUE", "Темно-синий");
    SNotesXMForm->ColorAquaPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_AQUA", "Голубой");
    SNotesXMForm->ColorLimePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_LIME", "Салатовый");
    SNotesXMForm->ColorPurplePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_PURPLE", "Пурпурный");
    SNotesXMForm->ColorGrayPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COLOR_GRAY", "Серый");
    SNotesXMForm->FontPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FONT", "Шрифт");
    SNotesXMForm->UndoPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_UNDO", "Отменить");
    SNotesXMForm->RedoPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_REDO", "Восстановить");
    SNotesXMForm->CutPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_CUT", "Вырезать");
    SNotesXMForm->CopyPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COPY", "Копировать");
    SNotesXMForm->PastePopSm->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_PASTE", "Вставить");
    SNotesXMForm->PastePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_PASTE_TEXT", "Вставить (только текст)");
    SNotesXMForm->SelectAllPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_SELECT_ALL", "Выделить все");
    SNotesXMForm->FindPop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_FIND", "Найти...");
    SNotesXMForm->ReplacePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_REPLACE", "Заменить");
    SNotesXMForm->InsertDatePop->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_INSERT_DATE", "Вставить дату");
    SNotesXMForm->CopyURL->Caption = LangIni->ReadString("Language", "MAIN_EDITOR_POPUP_COPY_LINK", "Копировать ссылку");

    SNotesXMForm->NewPageButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_NEW_HINT", "Создать страницу (Ctrl+N)");
    SNotesXMForm->DeletePageButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_DELETE_HINT", "Удалить страницу (Ctrl+D)");
    SNotesXMForm->SavePageButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_SAVE_AS_HINT", "Сохранить как... (Ctrl+S)");
    SNotesXMForm->PrintPageButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_PRINT_HINT", "Печать (Ctrl+P)");
    SNotesXMForm->SearchButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_FIND_HINT", "Найти (Ctrl+F)");
    SNotesXMForm->CalculatorButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_CALC_HINT", "Калькулятор (F3)");
    SNotesXMForm->BackupButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_BACKUP_HINT", "Резервное копирование (F4)");
    SNotesXMForm->AlignLeftButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_ALIGN_LEFT_HINT", "Выравнивание слева");
    SNotesXMForm->AlignCenterButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_ALIGN_CENTER_HINT", "Выравнивание по центру");
    SNotesXMForm->AlignRightButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_ALIGN_RIGHT_HINT", "Выравнивание справа");
    SNotesXMForm->FontColorButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_FONT_COLOR_HINT", "Цвет шрифта");
    SNotesXMForm->PrefButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_PREFERENCES_HINT", "Настройки (F2)");
    SNotesXMForm->InsertImageButton->Hint = LangIni->ReadString("Language", "MAIN_TOOLBUTTON_INSERT_IMAGE_HINT", "Вставить изображение");

    SNotesXMForm->SaveDialog1->Title = LangIni->ReadString("Language", "MAIN_SAVE_PAGE_DIALOG_TITLE", "Сохранение страницы");
    SNotesXMForm->OpenDialog1->Title = LangIni->ReadString("Language", "MAIN_INSERT_IMAGE_DIALOG_TITLE", "Выберите изображение для вставки");
    SNotesXMForm->OpenDialog2->Title = LangIni->ReadString("Language", "MAIN_OPEN_FILE_DIALOG_TITLE", "Выберите файл для открытия");

    SNotesXMForm->MainMenuBar->Caption = LangIni->ReadString("Language", "MAIN_MENU_BAR_CAPTION", "Главное меню");
    SNotesXMForm->FormatBar->Caption = LangIni->ReadString("Language", "MAIN_FORMAT_BAR_CAPTION", "Панель форматирования");
    SNotesXMForm->ServiceBar->Caption = LangIni->ReadString("Language", "MAIN_SERVICE_BAR_CAPTION", "Панель сервиса");

    if (LangCounter++)
      FreeLang();

    LMessages.Error = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str()) + 1];
    LMessages.NoPrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str()) + 1];
    LMessages.NoPageError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_NOT_FOUND", "Отсутствует файл с содержимым данной страницы:")).c_str()) + 1];
    LMessages.OtherHotKeyError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_HOTKEY_ALREADY_USING", "Сторонняя программа использует горячую клавишу SimpleNotes!")).c_str()) + 1];
    LMessages.EmptyError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_EMPTY", "Пусто")).c_str()) + 1];
    LMessages.PrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_IN_PREFERENCES", "Ошибка в файле настроек") + " " + PrefFile).c_str()) + 1];
    LMessages.PageCreateError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_EXISTS", "Страница с таким именем уже существует!")).c_str()) + 1];
    LMessages.PageCreateErrorTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_EXISTS_TITLE", "Ошибка при создании страницы")).c_str()) + 1];
    LMessages.ConfirmDelete = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_PAGE_DELETE", "Вы действительно хотите удалить текущую страницу? Информация будет утеряна.")).c_str()) + 1];
    LMessages.ConfirmDeleteTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_PAGE_DELETE_TITLE", "Подтвердите удаление")).c_str()) + 1];
    LMessages.OnePageError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_ONE_PAGE", "Должна остаться хотя бы одна страница!")).c_str()) + 1];
    LMessages.OnePageErrorTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_ONE_PAGE_TITLE", "Ошибка при удалении")).c_str()) + 1];
    LMessages.SelectFolderError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SELECT_BACKUP_FOLDER", "Задайте папку для резервного копирования в Настройках!")).c_str()) + 1];
    LMessages.SelectFolderErrorTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SELECT_BACKUP_FOLDER_TITLE", "Не задана папка для резервного копирования")).c_str()) + 1];
    LMessages.Message = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_SIMPLE_MESSAGE", "Сообщение")).c_str()) + 1];
    LMessages.FolderNotExistsError1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_1", "Указанная Вами в Настройках папка для резервного копирования не существует!")).c_str()) + 1];
    LMessages.FolderNotExistsError2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_2", "Создать эту папку:")).c_str()) + 1];
    LMessages.FolderNotExistsErrorTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_TITLE", "Неверная папка")).c_str()) + 1];
    LMessages.ConfirmFormatChange = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_FORMAT_CHANGE_1", "Вы действительно хотите сменить формат страницы на txt?") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_FORMAT_CHANGE_2", "Форматирование текста станет невозможным.")).c_str()) + 1];
    LMessages.WritePrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_1", "Ошибка при записи в файл настроек") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно получить к нему доступ, файл или диск защищены (переполнены)") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_3", "от записи, другой пользователь производит запись в данный файл.")).c_str()) + 1];
    LMessages.ReadPrefsError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str()) + 1];
    LMessages.ReadPageLockedError1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_1", "Ошибка при загрузке страницы. Файл")).c_str()) + 1];
    LMessages.ReadPageLockedError2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_2", "с содержимым данной страницы блокирован другим процессом и не может быть прочитан. SimpleNotes") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_3", "никогда не блокирует файлы, поэтому это сделало другое приложение. Переключитесь на другую") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_4", " страницу SimpleNotes, отключите блокировку и попытайтесь снова.")).c_str()) + 1];
    LMessages.WritePageLockedError1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_1", "Ошибка при сохранении страницы. Файл")).c_str()) + 1];
    LMessages.WritePageLockedError2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_2", "с содержимым данной страницы блокирован другим процессом и не может быть прочитан. SimpleNotes") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_3", "никогда не блокирует файлы, поэтому это сделало другое приложение. Найдите его и отключите блокировку.")).c_str()) + 1];
    LMessages.WritePageProtectError1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_1", "Ошибка при сохранении страницы. Файл")).c_str()) + 1];
    LMessages.WritePageProtectError2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_2", "с содержимым данной страницы защищен от записи. Или другой пользователь") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_3", "производит в него запись.")).c_str()) + 1];
    LMessages.WritePageDiskFullError1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_DISK_FULL_1", "Ошибка при сохранении страницы в")).c_str()) + 1];
    LMessages.WritePageDiskFullError2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_DISK_FULL_2", "Диск может быть защищен от записи или переполнен. Либо у Вас нет прав для записи файлов на данный диск.")).c_str()) + 1];
    LMessages.InsImageError = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_INSERT_IMAGE_1", "Ошибка при вставке изображения. Возможно, у файла неверный формат.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_INSERT_IMAGE_2", "SimpleNotes работает с изображениями форматов BMP, JPG и GIF.")).c_str()) + 1];
    LMessages.NewPageTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_NEW_PAGE_DIALOG_TITLE", "Создание страницы")).c_str()) + 1];
    LMessages.EnterName = new char [strlen((LangIni->ReadString("Language", "MAIN_NEW_PAGE_DIALOG_LABEL", "Введите имя новой страницы:")).c_str()) + 1];
    LMessages.RenamePageTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_RENAME_PAGE_DIALOG_TITLE", "Переименование страницы")).c_str()) + 1];
    LMessages.NewName = new char [strlen((LangIni->ReadString("Language", "MAIN_RENAME_PAGE_DIALOG_LABEL", "Введите новое имя страницы:")).c_str()) + 1];
    LMessages.CopyTempOK = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_TEMP_COPY_OK", "Страница успешно сохранена во временную папку:")).c_str()) + 1];
    LMessages.CopyTempFail = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_TEMP_COPY_FAIL", "Сохранение во временную папку не удалось!")).c_str()) + 1];
    LMessages.ConfirmSaveToTemp = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_SAVE_TO_TEMP", "Сохранить страницу в другую папку?")).c_str()) + 1];
    LMessages.SelectTempFolderTitle = new char [strlen((LangIni->ReadString("Language", "MAIN_OPEN_TEMP_FOLDER_DIALOG_TITLE", "Выберите папку для сохранения страницы:")).c_str()) + 1];
    LMessages.ConfirmReadonlyOff = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_READONLY_OFF", "Снять атрибут 'Только чтение' с файла?")).c_str()) + 1];
    LMessages.RemoveReadonlyFail = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_REMOVE_READONLY_FAIL", "Изменить атрибуты файла не удалось!")).c_str()) + 1];
    LMessages.CreateFolderFail = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CREATE_FOLDER_FAIL", "Не удалось создать папку для резервного копирования!")).c_str()) + 1];
    LMessages.RestoreNotFound1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_EMPTY_FOLDER_1", "Резервная копия не найдена! Проверьте папку")).c_str()) + 1];
    LMessages.RestoreNotFound2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_EMPTY_FOLDER_2", "или укажите другую папку с резервной копией в Настройках.")).c_str()) + 1];
    LMessages.ConfirmRestore1 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_1", "Вы действительно хотите восстановить информацию из")).c_str()) + 1];
    LMessages.ConfirmRestore2 = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_2", "Вся информация новее будет удалена!")).c_str()) + 1];
    LMessages.RestoreBroken = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_BROKEN_1", "Возможно, в резервной копии не хватает нескольких файлов.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_BROKEN_2", "Все равно продолжить восстановление?")).c_str()) + 1];
    LMessages.NoRestoreFolder = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_NO_FOLDER", "Укажите в Настройках папку с резервной копией.")).c_str()) + 1];
    LMessages.NoPrinter = new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_NO_PRINTER", "Нет установленного по умолчанию принтера. Печать невозможна.")).c_str()) + 1];

    strcpy(LMessages.Error, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str());
    strcpy(LMessages.NoPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str());
    strcpy(LMessages.NoPageError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_NOT_FOUND", "Отсутствует файл с содержимым данной страницы:")).c_str());
    strcpy(LMessages.OtherHotKeyError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_HOTKEY_ALREADY_USING", "Сторонняя программа использует горячую клавишу SimpleNotes!")).c_str());
    strcpy(LMessages.EmptyError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_EMPTY", "Пусто")).c_str());
    strcpy(LMessages.PrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_IN_PREFERENCES", "Ошибка в файле настроек") + " " + PrefFile).c_str());
    strcpy(LMessages.PageCreateError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_EXISTS", "Страница с таким именем уже существует!")).c_str());
    strcpy(LMessages.PageCreateErrorTitle, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PAGE_EXISTS_TITLE", "Ошибка при создании страницы")).c_str());
    strcpy(LMessages.ConfirmDelete, (LangIni->ReadString("Language", "MAIN_MESSAGE_PAGE_DELETE", "Вы действительно хотите удалить текущую страницу? Информация будет утеряна.")).c_str());
    strcpy(LMessages.ConfirmDeleteTitle, (LangIni->ReadString("Language", "MAIN_MESSAGE_PAGE_DELETE_TITLE", "Подтвердите удаление")).c_str());
    strcpy(LMessages.OnePageError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_ONE_PAGE", "Должна остаться хотя бы одна страница!")).c_str());
    strcpy(LMessages.OnePageErrorTitle, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_ONE_PAGE_TITLE", "Ошибка при удалении")).c_str());
    strcpy(LMessages.SelectFolderError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SELECT_BACKUP_FOLDER", "Задайте папку для сохранения в Настройках!")).c_str());
    strcpy(LMessages.SelectFolderErrorTitle, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SELECT_BACKUP_FOLDER_TITLE", "Не задана папка для сохранения")).c_str());
    strcpy(LMessages.Message, (LangIni->ReadString("Language", "MAIN_MESSAGE_SIMPLE_MESSAGE", "Сообщение")).c_str());
    strcpy(LMessages.FolderNotExistsError1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_1", "Указанная Вами в Настройках папка для резервного копирования не существует!")).c_str());
    strcpy(LMessages.FolderNotExistsError2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_2", "Создать эту папку:")).c_str());
    strcpy(LMessages.FolderNotExistsErrorTitle, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_FOLDER_NOT_EXISTS_TITLE", "Неверная папка")).c_str());
    strcpy(LMessages.ConfirmFormatChange, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_FORMAT_CHANGE_1", "Вы действительно хотите сменить формат страницы на txt?") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_FORMAT_CHANGE_2", "Форматирование текста станет невозможным.")).c_str());
    strcpy(LMessages.WritePrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_1", "Ошибка при записи в файл настроек") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно получить к нему доступ, файл или диск защищены (переполнены)") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_WRITE_PREFERENCES_3", "от записи, другой пользователь производит запись в данный файл.")).c_str());
    strcpy(LMessages.ReadPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек") + " " + PrefFile + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str());
    strcpy(LMessages.ReadPageLockedError1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_1", "Ошибка при загрузке страницы. Файл")).c_str());
    strcpy(LMessages.ReadPageLockedError2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_2", "с содержимым данной страницы блокирован другим процессом и не может быть прочитан. SimpleNotes") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_3", "никогда не блокирует файлы, поэтому это сделало другое приложение. Переключитесь на другую") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_LOAD_LOCKED_4", "страницу SimpleNotes, отключите блокировку и попытайтесь снова.")).c_str());
    strcpy(LMessages.WritePageLockedError1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_1", "Ошибка при сохранении страницы. Файл")).c_str());
    strcpy(LMessages.WritePageLockedError2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_2", "с содержимым данной страницы блокирован другим процессом и не может быть прочитан. SimpleNotes") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_LOCKED_3", "никогда не блокирует файлы, поэтому это сделало другое приложение. Найдите его и отключите блокировку.")).c_str());
    strcpy(LMessages.WritePageProtectError1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_1", "Ошибка при сохранении страницы. Файл")).c_str());
    strcpy(LMessages.WritePageProtectError2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_2", "с содержимым данной страницы защищен от записи. Или другой пользователь") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_WRITE_PROTECTED_3", "производит в него запись.")).c_str());
    strcpy(LMessages.WritePageDiskFullError1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_DISK_FULL_1", "Ошибка при сохранении страницы в")).c_str());
    strcpy(LMessages.WritePageDiskFullError2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_SAVE_DISK_FULL_2", "Диск может быть защищен от записи или переполнен. Либо у Вас нет прав для записи файлов на данный диск.")).c_str());
    strcpy(LMessages.InsImageError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_INSERT_IMAGE_1", "Ошибка при вставке изображения. Возможно, у файла неверный формат.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_INSERT_IMAGE_2", "SimpleNotes работает с изображениями форматов BMP, JPG и GIF.")).c_str());
    strcpy(LMessages.NewPageTitle, (LangIni->ReadString("Language", "MAIN_NEW_PAGE_DIALOG_TITLE", "Создание страницы")).c_str());
    strcpy(LMessages.EnterName, (LangIni->ReadString("Language", "MAIN_NEW_PAGE_DIALOG_LABEL", "Введите имя новой страницы:")).c_str());
    strcpy(LMessages.RenamePageTitle, (LangIni->ReadString("Language", "MAIN_RENAME_PAGE_DIALOG_TITLE", "Переименование страницы")).c_str());
    strcpy(LMessages.NewName, (LangIni->ReadString("Language", "MAIN_RENAME_PAGE_DIALOG_LABEL", "Введите новое имя страницы:")).c_str());
    strcpy(LMessages.CopyTempOK, (LangIni->ReadString("Language", "MAIN_MESSAGE_TEMP_COPY_OK", "Страница успешно сохранена во временную папку:")).c_str());
    strcpy(LMessages.CopyTempFail, (LangIni->ReadString("Language", "MAIN_MESSAGE_TEMP_COPY_FAIL", "Сохранение во временную папку не удалось!")).c_str());
    strcpy(LMessages.ConfirmSaveToTemp, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_SAVE_TO_TEMP", "Сохранить страницу в другую папку?")).c_str());
    strcpy(LMessages.SelectTempFolderTitle, (LangIni->ReadString("Language", "MAIN_OPEN_TEMP_FOLDER_DIALOG_TITLE", "Выберите папку для сохранения страницы:")).c_str());
    strcpy(LMessages.ConfirmReadonlyOff, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_READONLY_OFF", "Снять атрибут 'Только чтение' с файла?")).c_str());
    strcpy(LMessages.RemoveReadonlyFail, (LangIni->ReadString("Language", "MAIN_MESSAGE_REMOVE_READONLY_FAIL", "Изменить атрибуты файла не удалось!")).c_str());
    strcpy(LMessages.CreateFolderFail, (LangIni->ReadString("Language", "MAIN_MESSAGE_CREATE_FOLDER_FAIL", "Не удалось создать папку для резервного копирования!")).c_str());
    strcpy(LMessages.RestoreNotFound1, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_EMPTY_FOLDER_1", "Резервная копия не найдена! Проверьте папку")).c_str());
    strcpy(LMessages.RestoreNotFound2, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_EMPTY_FOLDER_2", "или укажите другую папку с резервной копией в Настройках.")).c_str());
    strcpy(LMessages.ConfirmRestore1, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_1", "Вы действительно хотите восстановить информацию из")).c_str());
    strcpy(LMessages.ConfirmRestore2, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_2", "Вся информация новее будет удалена!")).c_str());
    strcpy(LMessages.RestoreBroken, (LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_BROKEN_1", "Возможно, в резервной копии не хватает нескольких файлов.") + "\n" + LangIni->ReadString("Language", "MAIN_MESSAGE_CONFIRM_RESTORE_BROKEN_2", "Все равно продолжить восстановление?")).c_str());
    strcpy(LMessages.NoRestoreFolder, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_RESTORE_NO_FOLDER", "Укажите в Настройках папку с резервной копией.")).c_str());
    strcpy(LMessages.NoPrinter, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_NO_PRINTER", "Нет установленного по умолчанию принтера. Печать невозможна.")).c_str());

    LMessages.PrintPage = LangIni->ReadString("Language", "MAIN_MESSAGE_PRINT_PAGE", "Страница");
    LMessages.BackupTitle = LangIni->ReadString("Language", "TRAY_MESSAGE_BACKUP_RECOMMEND_TITLE", "Не забывайте делать резервные копии!");
    LMessages.BackupText = LangIni->ReadString("Language", "TRAY_MESSAGE_BACKUP_RECOMMEND", "Рекомендуется делать резервную копию Вашей информации хотя бы раз в неделю!");
    delete LangIni;
  } catch (...) {
    Application->MessageBoxA("Error reading language file. Default language will be used.", "Error", MB_OK + MB_ICONERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::BackupButtonClick(TObject* Sender) {
  BackupMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CoolTrayStartup(TObject* Sender,
    bool& ShowMainForm) {
  if (!FileExists(PrefFile)) {
    FILE* F = fopen(PrefFile.c_str(), "w+");

    if (F == NULL) {
      CoolTray->OnClick = NULL;
      CoolTray->PopupMenu = NULL;
      char* MessText = new char [strlen(("File with preferences" + PrefFile + "\n" + "not found and cannot be created. Check your rights for writting.").c_str()) + 2];
      strcpy(MessText, "File with preferences");
      strcat(MessText, (" " + PrefFile + "\n" + "not found and cannot be created. Check your rights for writting.").c_str());
      Application->MessageBoxA(MessText, "Error", MB_OK + MB_ICONERROR);
      fclose(F);
      delete [] MessText;
      Application->Terminate();
    }

    fclose(F);
  }

  TIniFile* Ini = new TIniFile(PrefFile);
  TIniFile* LangIni;
  AnsiString Lang;

  try {
    Lang = Ini->ReadString("Parameters", "Language", "English");
    RichEdit1->SelectionBar = Ini->ReadBool("Parameters", "LeftMargin", 1);
  } catch (...) {
    char* MessText = new char [strlen(("Error reading file with preferences" + PrefFile + "\n" + "Maybe file is blocked by another process.").c_str()) + 2];
    strcpy(MessText, "Error reading file with preferences");
    strcat(MessText, (" " + PrefFile + "\n" + "Maybe file is blocked by another process.").c_str());
    Application->MessageBoxA(MessText, "Error", MB_OK + MB_ICONERROR);
    delete [] MessText;
  }

  if (Lang == "Russian")
    LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\Russian.lng");

  if (Lang == "English")
    LangIni = new TIniFile (ExtractFilePath(Application->ExeName) + "Languages\\English.lng");

  try {
    SNotesXMForm->CalcPop->Caption = LangIni->ReadString("Tray", "0", "Калькулятор");
    SNotesXMForm->RestorePop->Caption = LangIni->ReadString("Tray", "2", "Восстановить");
    SNotesXMForm->ExitPop->Caption = LangIni->ReadString("Tray", "3", "Выход");
    SNotesXMForm->HomePagePop->Caption = LangIni->ReadString("Tray", "4", "Домашняя web-страница");
    SNotesXMForm->WriteLetterPop->Caption = LangIni->ReadString("Tray", "5", "Письмо автору");
  } catch (...) {
    AnsiString LangPath = ExtractFilePath(Application->ExeName) + "Languages\\" + Lang + ".lng";
    char* LangStr = new char [strlen(("Error reading language file" + LangPath + "\n" + "Default language will be used.").c_str()) + 2];
    strcpy(LangStr, "Error reading language file");
    strcat(LangStr, (" " + LangPath + "\n" + "Default language will be used.").c_str());
    Application->MessageBoxA(LangStr, "Error", MB_OK + MB_ICONERROR);
    delete [] LangStr;
  }

  LeftMarginMenu->Checked = RichEdit1->SelectionBar;
  delete Ini;
  delete LangIni;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::InsertDatePopClick(TObject* Sender) {
  AnsiString Str = DateToStr(Date()) + ' ' + TimeToStr(Time());
  RichEdit1->SelText = Str;
  RichEdit1->SelStart = RichEdit1->SelStart + Str.Length();
}
//---------------------------------------------------------------------------
void OSdetect () {
  OSVERSIONINFO OsInfo;
  int Win32Platform, Win32MajorVersion, Win32MinorVersion;
  OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&OsInfo);
  Win32Platform = OsInfo.dwPlatformId;
  Win32MajorVersion = OsInfo.dwMajorVersion;
  Win32MinorVersion = OsInfo.dwMinorVersion;

  if (Win32Platform == VER_PLATFORM_WIN32s)
    OS = "Win3x";

  if (Win32Platform == VER_PLATFORM_WIN32_WINDOWS) {
    if (Win32MajorVersion == 4) {
      if (Win32MinorVersion >= 0)
        OS = "Win95";

      if (Win32MinorVersion >= 10)
        OS = "Win98";

      if (Win32MinorVersion >= 90)
        OS = "WinMe";
    }
  }

  if (Win32Platform == VER_PLATFORM_WIN32_NT) {
    if (Win32MajorVersion <= 4)
      OS = "WinNT";

    if (Win32MajorVersion == 5) {
      if (Win32MinorVersion >= 0)
        OS = "Win2K";

      if (Win32MinorVersion >= 1)
        OS = "WinXP";

      if (Win32MinorVersion >= 2)
        OS = "Win2003";
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RedoPopClick(TObject* Sender) {
  RichEdit1->Redo();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RedoMenuClick(TObject* Sender) {
  RichEdit1->Redo();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsMouseDown(TObject* Sender,
    TMouseButton Button, TShiftState Shift, int X, int Y) {
  Pos = AllTabs->IndexOfTabAt(X, Y);

  if (Button == mbLeft) {
    if (Pos >= 0)
      AllTabs->BeginDrag(false, 5);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsDragOver(TObject* Sender, TObject* Source,
    int X, int Y, TDragState State, bool& Accept) {
  if (Source == AllTabs)
    Accept = true;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AllTabsEndDrag(TObject* Sender, TObject* Target,
    int X, int Y) {
  RichEdit1->OnSelectionChange = NULL;
  AllTabs->OnChange = NULL;
  AllTabs->OnChanging = NULL;
  Pos = AllTabs->IndexOfTabAt(X, Y); //куда переносим
  int OldIndex = AllTabs->TabIndex;
  AnsiString OldName = AllTabs->Tabs->Strings[AllTabs->TabIndex];

  if (Pos >= 0) {
    CheckPrefsInter();
    CheckReadonly("Preferences.ini", false);
    TIniFile* Ini = new TIniFile(PrefFile);

    if (AllTabs->TabIndex < Pos) { //переносим слева на право
      for (int i = OldIndex + 1; i <= Pos; i++)
        AllTabs->Tabs->Strings[i - 1] = AllTabs->Tabs->Strings[i];

      AllTabs->Tabs->Strings[Pos] = OldName;
      AllTabs->TabIndex = Pos;

      try {
        for (int i = 0; i <= AllTabs->Tabs->Count - 1; i++)
          Ini->WriteString("Pages", i, AllTabs->Tabs->Strings[i]);
      } catch (...) {
        Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
    }

    if (AllTabs->TabIndex > Pos) { //переносим наоборот
      for (int i = AllTabs->TabIndex - 1; i >= Pos; i--)
        AllTabs->Tabs->Strings[i + 1] = AllTabs->Tabs->Strings[i];

      AllTabs->Tabs->Strings[Pos] = OldName;
      AllTabs->TabIndex = Pos;

      try {
        for (int i = 0; i <= AllTabs->Tabs->Count - 1; i++)
          Ini->WriteString("Pages", i, AllTabs->Tabs->Strings[i]);
      } catch (...) {
        Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
    }

    delete Ini;
  }

  RichEdit1->OnSelectionChange = RichEdit1SelectionChange;
  AllTabs->OnChange = AllTabsChange;
  AllTabs->OnChanging = AllTabsChanging;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ServiceBarMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  ServiceBar->Visible = ServiceBarMenu->Checked;

  try {
    Ini->WriteBool("ServiceBar", "Visible", ServiceBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormatBarMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  FormatBar->Visible = FormatBarMenu->Checked;

  try {
    Ini->WriteBool("FormatBar", "Visible", FormatBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormatBarVisibleChanged(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  FormatBarMenu->Checked = FormatBar->Visible;

  try {
    Ini->WriteBool("FormatBar", "Visible", FormatBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ServiceBarVisibleChanged(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  ServiceBarMenu->Checked = ServiceBar->Visible;

  try {
    Ini->WriteBool("ServiceBar", "Visible", ServiceBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RichEdit1KeyDown(TObject* Sender, WORD& Key,
    TShiftState Shift) {
  if ((!Shift.Contains(ssCtrl)) && (Shift.Contains(ssAlt)) && (!Shift.Contains(ssShift)) && (Key == 88))
    ExitMenuClick(Sender);

  if ((Shift.Contains(ssCtrl)) && (!Shift.Contains(ssAlt)) && (!Shift.Contains(ssShift)) && (Key == 107)) {
    RichEdit1->SelAttributes->Size += 1;
    FontSizeBox->Text = IntToStr(StrToInt(FontSizeBox->Text) + 1);
  }

  if ((Shift.Contains(ssCtrl)) && (!Shift.Contains(ssAlt)) && (!Shift.Contains(ssShift)) && (Key == 109)) {
    RichEdit1->SelAttributes->Size -= 1;
    FontSizeBox->Text = IntToStr(StrToInt(FontSizeBox->Text) - 1);
  }

  if ((!Shift.Contains(ssCtrl)) && (!Shift.Contains(ssAlt)) && (!Shift.Contains(ssShift)) && (Key == 27))
    Application->Minimize();

  if ((!Shift.Contains(ssCtrl)) && (Shift.Contains(ssAlt)) && (!Shift.Contains(ssShift)) && (Key >= 49) && (Key <= 57)) {
    if (AllTabs->Tabs->Count >= (Key - 48)) {
      AllTabsChanging(Sender, true);
      AllTabs->TabIndex = Key - 49;
      AllTabsChange(Sender);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::BoldNotClick(TObject* Sender) {
  FontBoldPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ItalickNotClick(TObject* Sender) {
  FontItalicPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::UnderlineNotClick(TObject* Sender) {
  FontUnderlinePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::StrikeNotClick(TObject* Sender) {
  FontStrikeoutPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::MarkersNotClick(TObject* Sender) {
  FontMarkersPopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::DateNotClick(TObject* Sender) {
  InsertDatePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::LeftNotClick(TObject* Sender) {
  AlignLeftButtonClick(Sender);
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CenterNotClick(TObject* Sender) {
  AlignCenterButtonClick(Sender);
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RightNotClick(TObject* Sender) {
  AlignRightButtonClick(Sender);
  RichEdit1SelectionChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::DeleteNotClick(TObject* Sender) {
  DeletePagePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RenameNotClick(TObject* Sender) {
  RenamePagePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::HomePageMenuClick(TObject* Sender) {
  if (RussianLangMenu->Checked)
    ShellExecute(0, NULL, "http://www.snotes.narod.ru", NULL, NULL, 1);
  else
    ShellExecute(0, NULL, "http://www.snotes.narod.ru/index_en.htm", NULL, NULL, 1);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::WriteLetterMenuClick(TObject* Sender) {
  ShellExecute(0, NULL, "mailto:xelfium@mail.ru", NULL, NULL, 1);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::HomePagePopClick(TObject* Sender) {
  if (RussianLangMenu->Checked)
    ShellExecute(0, NULL, "http://www.snotes.narod.ru", NULL, NULL, 1);
  else
    ShellExecute(0, NULL, "http://www.snotes.narod.ru/index_en.htm", NULL, NULL, 1);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::WriteLetterPopClick(TObject* Sender) {
  ShellExecute(0, NULL, "mailto:xelfium@mail.ru", NULL, NULL, 1);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PrefButtonClick(TObject* Sender) {
  PreferencesMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::UpCaseClick(TObject* Sender) {
  RichEdit1->SelText = RichEdit1->SelText.UpperCase();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::LowCaseClick(TObject* Sender) {
  RichEdit1->SelText = RichEdit1->SelText.LowerCase();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::IndentClick(TObject* Sender) {
  RichEdit1->Paragraph->FirstIndent += 10;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::UnindentClick(TObject* Sender) {
  RichEdit1->Paragraph->FirstIndent -= 10;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::InsertObjectMenuClick(TObject* Sender) {
  RichEdit1->InsertObjectDialog();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RichEdit1MouseUp(TObject* Sender,
    TMouseButton Button, TShiftState Shift, int X, int Y) {
  if (Button == mbRight) {
    if ((RichEdit1->SelectionType.Contains(stObject)) && (!RichEdit1->SelectionType.Contains(stMultiObject)) && (!RichEdit1->SelectionType.Contains(stText)) )
      RichEdit1->ObjectPropertiesDialog();
    else if ( (!RichEdit1->SelectionType.Contains(stObject)) && (!RichEdit1->SelectionType.Contains(stMultiObject)) && (RichEdit1->SelectionType.Contains(stText)) )
      EditorPopupMenu->Popup(Mouse->CursorPos.x, Mouse->CursorPos.y);
    else
      EditorPopupMenu->Popup(Mouse->CursorPos.x, Mouse->CursorPos.y);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::EditorPopupMenuPopup(TObject* Sender) {
  CopyURL->Visible = ShowCopyLink;
  CopyURLSep->Visible = ShowCopyLink;
  ShowCopyLink = false;
  UndoPop->Enabled = RichEdit1->CanUndo;
  RedoPop->Enabled = RichEdit1->CanRedo;
  PastePopSm->Enabled = RichEdit1->CanPaste;
  CutPop->Enabled = (RichEdit1->SelLength > 0);
  CopyPop->Enabled = (RichEdit1->SelLength > 0);
  TClipboard* MyClipBoard = new TClipboard;
  MyClipBoard->Open();
  PastePop->Enabled = MyClipBoard->HasFormat(CF_TEXT);
  MyClipBoard->Close();
  MyClipBoard->Free();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CopyURLClick(TObject* Sender) {
  char* HLink = new char [strlen(HyperLink.c_str()) + 1];
  strcpy(HLink, HyperLink.c_str());
  TClipboard* MyClipBoard = new TClipboard;
  MyClipBoard->Open();
  MyClipBoard->Clear();
  MyClipBoard->SetTextBuf(HLink);
  MyClipBoard->Close();
  MyClipBoard->Free();
  delete [] HLink;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CopyPopClick(TObject* Sender) {
  RichEdit1->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PastePopClick(TObject* Sender) {
  TClipboard* MyClipBoard = new TClipboard;
  MyClipBoard->Open();

  if (MyClipBoard->HasFormat(CF_TEXT))
    RichEdit1->SelText = MyClipBoard->AsText;

  MyClipBoard->Close();
  MyClipBoard->Free();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::SelectAllPopClick(TObject* Sender) {
  RichEdit1->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CutPopClick(TObject* Sender) {
  RichEdit1->CopyToClipboard();
  RichEdit1->SelText = "";
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::UndoPopClick(TObject* Sender) {
  RichEdit1->Undo();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::UndoMenuClick(TObject* Sender) {
  RichEdit1->Undo();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CutMenuClick(TObject* Sender) {
  RichEdit1->CopyToClipboard();
  RichEdit1->SelText = "";
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::CopyMenuClick(TObject* Sender) {
  RichEdit1->CopyToClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PasteTextMenuClick(TObject* Sender) {
  PastePopClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::SelectAllMenuClick(TObject* Sender) {
  RichEdit1->SelectAll();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::EditMenuPopup(TTBCustomItem* Sender, bool FromLink) {
  UndoMenu->Enabled = RichEdit1->CanUndo;
  RedoMenu->Enabled = RichEdit1->CanRedo;
  PasteMenu->Enabled = RichEdit1->CanPaste;
  PasteSpecialMenu->Enabled = RichEdit1->CanPaste;
  CutMenu->Enabled = (RichEdit1->SelLength > 0);
  CopyMenu->Enabled = (RichEdit1->SelLength > 0);
  TClipboard* MyClipBoard = new TClipboard;
  MyClipBoard->Open();
  PasteTextMenu->Enabled = MyClipBoard->HasFormat(CF_TEXT);
  MyClipBoard->Close();
  MyClipBoard->Free();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PastePopSmClick(TObject* Sender) {
  RichEdit1->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PasteMenuClick(TObject* Sender) {
  RichEdit1->PasteFromClipboard();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::HintTimerTimer(TObject* Sender) {
  CoolTray->HideBalloonHint();
  HintTimer->Interval = 0;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormMouseWheelDown(TObject* Sender,
    TShiftState Shift, TPoint& MousePos, bool& Handled) {
  if ((SNotesXMForm->Active) && (!FontNameBox->DroppedDown) && (!FontSizeBox->DroppedDown)) {
    int x = MousePos.x - AllTabs->ClientOrigin.x;
    int y = MousePos.y - AllTabs->ClientOrigin.y;
    int pos = AllTabs->IndexOfTabAt(x, y);

    if (pos >= 0) {
      if (AllTabs->TabIndex < (AllTabs->Tabs->Count - 1)) {
        AllTabsChanging(Sender, true);
        AllTabs->TabIndex += 1;
        AllTabsChange(Sender);
      } else {
        AllTabsChanging(Sender, true);
        AllTabs->TabIndex = 0;
        AllTabsChange(Sender);
      }

      Handled = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormMouseWheelUp(TObject* Sender,
    TShiftState Shift, TPoint& MousePos, bool& Handled) {
  if ((SNotesXMForm->Active) && (!FontNameBox->DroppedDown) && (!FontSizeBox->DroppedDown)) {
    int x = MousePos.x - AllTabs->ClientOrigin.x;
    int y = MousePos.y - AllTabs->ClientOrigin.y;
    int pos = AllTabs->IndexOfTabAt(x, y);

    if (pos >= 0) {
      if (AllTabs->TabIndex > 0) {
        AllTabsChanging(Sender, true);
        AllTabs->TabIndex -= 1;
        AllTabsChange(Sender);
      } else {
        AllTabsChanging(Sender, true);
        AllTabs->TabIndex = AllTabs->Tabs->Count - 1;
        AllTabsChange(Sender);
      }

      Handled = true;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::PasteSpecialMenuClick(TObject* Sender) {
  RichEdit1->PasteSpecialDialog();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ApplicationEvents1Deactivate(
  TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  bool HideWindow = true;

  try {
    HideWindow = Ini->ReadBool("Options", "HideWindow", 0);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (HideWindow) {
    int Seconds = 30;

    try {
      Seconds = Ini->ReadInteger("Options", "HideTimeout", 30);
    } catch (...) {
      Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    HideWindTimer->Interval = Seconds * 1000;
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ApplicationEvents1Activate(TObject* Sender) {
  HideWindTimer->Interval = 0;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::HideWindTimerTimer(TObject* Sender) {
  HideWindTimer->Interval = 0;
  Application->Minimize();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::InsertImageMenuClick(TObject* Sender) {
  if (OpenDialog1->Execute()) {
    bool isError = false;
    Graphics::TPicture* Picture = new Graphics::TPicture();
    Graphics::TBitmap* BMP = new Graphics::TBitmap();
    TGIFImage* GIF = new TGIFImage;
    AnsiString GFile = OpenDialog1->FileName;

    if (GFile[GFile.Length()] == 'f') {
      try {
        GIF->LoadFromFile(GFile);
        BMP->Assign(GIF);
        RichEdit1->InsertGraphic(BMP, true);

      } catch (...) {
        isError = true;
        Application->MessageBoxA(LMessages.InsImageError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
    } else {
      try {
        Picture->LoadFromFile(GFile);
        BMP->Assign(Picture->Graphic);
        RichEdit1->InsertGraphic(BMP, true);

      } catch (...) {
        isError = true;
        Application->MessageBoxA(LMessages.InsImageError, LMessages.Error, MB_OK + MB_ICONERROR);
      }
    }

    Picture->Free();
    GIF->Free();

    if (!isError) {
      AllTabsChanging(Sender, true);
      AllTabsChange(Sender);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::InsertImageButtonClick(TObject* Sender) {
  InsertImageMenuClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::TXTFormatClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  bool Quest = true;

  try {
    Quest = Ini->ReadBool("Options", "AskOnFormatChange", 1);
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  if (!AllowQuestion)
    Quest = false;

  if (!Quest) {
    FormatSelector->Caption = "txt";
    RichEdit1->PlainText = true;
    TXTFormat->Checked = true;
    SaveDialog1->Filter = "(*.txt)|*.txt";
    FontColorButton->Visible = false;
    InsertObjectMenu->Enabled = false;
    InsertImageMenu->Enabled = false;
    FontBoldPop->Enabled = false;
    FontItalicPop->Enabled = false;
    FontUnderlinePop->Enabled = false;
    FontStrikeoutPop->Enabled = false;
    FontMarkersPop->Enabled = false;
    ColorPop->Enabled = false;
    Indent->Enabled = false;
    Unindent->Enabled = false;
    InsertImageButton->Visible = false;

    try {
      Ini->WriteString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "TXT");
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    AllowQuestion = false;
  } else if (Application->MessageBoxA(LMessages.ConfirmFormatChange, LMessages.Message, MB_YESNO + MB_ICONQUESTION) == IDYES) {
    FormatSelector->Caption = "txt";
    RichEdit1->PlainText = true;
    TXTFormat->Checked = true;
    RichEdit1->PlainText = true;
    TXTFormat->Checked = true;
    SaveDialog1->Filter = "(*.txt)|*.txt";
    FontColorButton->Visible = false;
    InsertObjectMenu->Enabled = false;
    InsertImageMenu->Enabled = false;
    FontBoldPop->Enabled = false;
    FontItalicPop->Enabled = false;
    FontUnderlinePop->Enabled = false;
    FontStrikeoutPop->Enabled = false;
    FontMarkersPop->Enabled = false;
    ColorPop->Enabled = false;
    Indent->Enabled = false;
    Unindent->Enabled = false;
    InsertImageButton->Visible = false;

    try {
      Ini->WriteString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "TXT");
    } catch (...) {
      Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
    }

    AllowQuestion = false;
  } else {
    RTFFormat->Checked = true;
    AllowQuestion = true;
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RTFFormatClick(TObject* Sender) {
  FormatSelector->Caption = "rtf";
  RichEdit1->PlainText = false;
  RTFFormat->Checked = true;
  SaveDialog1->Filter = "(*.rtf)|*.rtf";
  FontColorButton->Visible = true;
  InsertObjectMenu->Enabled = true;
  InsertImageMenu->Enabled = true;
  FontBoldPop->Enabled = true;
  FontItalicPop->Enabled = true;
  FontUnderlinePop->Enabled = true;
  FontStrikeoutPop->Enabled = true;
  FontMarkersPop->Enabled = true;
  ColorPop->Enabled = true;
  Indent->Enabled = true;
  Unindent->Enabled = true;
  InsertImageButton->Visible = true;
  AllowQuestion = true;
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);

  try {
    Ini->WriteString("PageFormat", AllTabs->Tabs->Strings[AllTabs->TabIndex], "RTF");
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
AnsiString CheckAccess(AnsiString FileName) {
  int Identy;
  Identy = FileOpen(FileName, fmShareExclusive);

  if (Identy == -1) {
    FileClose(Identy);
    return "Locked";
  } else
    FileClose(Identy);

  DWORD Attrs = GetFileAttributes(FileName.c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES) {
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      return "ReadOnly";
  } else
    return "ReadOnly";

  return "OK";
}
//---------------------------------------------------------------------------
void DisplayError(AnsiString Type, AnsiString WriteRead, AnsiString PageName, bool Quest) {
  if ((Type == "Locked") && (WriteRead == "Write")) {
    char* ErrorStr = new char [strlen((LMessages.WritePageLockedError1 + ExtractFilePath(Application->ExeName) + PageName + "\n" + LMessages.WritePageLockedError2 + "\n" + LMessages.ConfirmSaveToTemp).c_str()) + 2];
    strcpy(ErrorStr, LMessages.WritePageLockedError1);
    strcat(ErrorStr, (" " + ExtractFilePath(Application->ExeName) + PageName + "\n").c_str());
    strcat(ErrorStr, LMessages.WritePageLockedError2);
    SaveToTemp(ErrorStr, Quest, true);
    delete [] ErrorStr;
  }

  if ((Type == "Locked") && (WriteRead == "Read")) {
    char* ErrorStr = new char [strlen((LMessages.ReadPageLockedError1 + ExtractFilePath(Application->ExeName) + PageName + "\n" + LMessages.ReadPageLockedError2).c_str()) + 2];
    strcpy(ErrorStr, LMessages.ReadPageLockedError1);
    strcat(ErrorStr, (" " + ExtractFilePath(Application->ExeName) + PageName + "\n").c_str());
    strcat(ErrorStr, LMessages.ReadPageLockedError2);
    Application->MessageBoxA(ErrorStr, LMessages.Error, MB_OK + MB_ICONERROR);
    delete [] ErrorStr;
  }

  if (Type == "ReadOnly") {
    char* ErrorStr = new char [strlen(LMessages.ConfirmSaveToTemp)];
    SaveToTemp(ErrorStr, Quest, false);
    delete [] ErrorStr;
  }

  if (Type == "OK") {
    char* ErrorStr = new char [strlen((LMessages.WritePageDiskFullError1 + ExtractFilePath(Application->ExeName) + PageName + "\n" + LMessages.WritePageDiskFullError2 + "\n" + LMessages.ConfirmSaveToTemp).c_str()) + 2];
    strcpy(ErrorStr, LMessages.WritePageDiskFullError1);
    strcat(ErrorStr, (" " + ExtractFilePath(Application->ExeName) + PageName + "\n").c_str());
    strcat(ErrorStr, LMessages.WritePageDiskFullError2);
    SaveToTemp(ErrorStr, Quest, true);
    delete [] ErrorStr;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontColorButtonDrawImage(
  TTBCustomItem* Item, TTBItemViewer* Viewer, TCanvas* Canvas,
  TRect& ImageRect, TPoint& ImageOffset, int StateFlags) {
  TColor Color;

  if (!Boolean(StateFlags && ISF_DISABLED)) {
    Color = ColorPalette->Color;
    OffsetRect(ImageRect, ImageOffset.x , ImageOffset.y);
    ImageRect.Top = ImageRect.Bottom - 4;

    if (Color != clNone) {
      Canvas->Brush->Color = Color;
      Canvas->FillRect(ImageRect);
    } else {
      Canvas->Brush->Color = clNone;
      Canvas->FillRect(ImageRect);
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::AutoColorClick(TObject* Sender) {
  ColorPalette->Color = clBlack;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::MoreColorsClick(TObject* Sender) {
  if (ColorDialog1->Execute())
    ColorPalette->Color = ColorDialog1->Color;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FontColorButtonClick(TObject* Sender) {
  RichEdit1->SelAttributes->Color = ColorPalette->Color;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::ColorPaletteChange(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  RichEdit1->SelAttributes->Color = ColorPalette->Color;

  try {
    Ini->WriteInteger("Parameters", "FontColor", ColorPalette->Color);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONWARNING);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::MouseEventTimerTimer(TObject* Sender) {
  MouseEventTimer->Interval = 0;
  AllTabs->OnMouseDown = AllTabsMouseDown;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::MainMenuMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  MainMenuBar->Visible = MainMenuMenu->Checked;

  try {
    Ini->WriteBool("MainMenuBar", "Visible", MainMenuBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void CheckPrefs() {
  if (!FileExists(PrefFile)) {
    FILE* F = fopen(PrefFile.c_str(), "w+");

    if (F == NULL) {
      char* MessText = new char [strlen(("File with preferences" + PrefFile + "\n" + "not found and cannot be created. Check your rights for writting.").c_str()) + 2];
      strcpy(MessText, "File with preferences");
      strcat(MessText, (" " + PrefFile + "\n" + "not found and cannot be created. Check your rights for writting.").c_str());
      Application->MessageBoxA(MessText, "Error", MB_OK + MB_ICONERROR);
      fclose(F);
      delete [] MessText;
      Application->Terminate();
    }

    fclose(F);
  }
}
//---------------------------------------------------------------------------
void CheckPrefsInter() {
  if (!FileExists(PrefFile)) {
    FILE* F = fopen(PrefFile.c_str(), "w+");

    if (F == NULL) {
      Application->MessageBoxA(LMessages.NoPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      fclose(F);
      Application->Terminate();
    }

    fclose(F);
  }
}
//---------------------------------------------------------------------------
void CheckReadonly(AnsiString PageName, bool Quest) {
  AnsiString Path = ExtractFilePath(Application->ExeName) + PageName;
  DWORD Attrs = GetFileAttributes(Path.c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES) {
    if (Attrs & FILE_ATTRIBUTE_READONLY) {
      if (Quest) {
        char* ErrorStr = new char [strlen((LMessages.WritePageProtectError1 + ExtractFilePath(Application->ExeName) + PageName + "\n" + LMessages.WritePageProtectError2 + " " + LMessages.ConfirmReadonlyOff).c_str()) + 2];
        strcpy(ErrorStr, LMessages.WritePageProtectError1);
        strcat(ErrorStr, (" " + ExtractFilePath(Application->ExeName) + PageName + "\n").c_str());
        strcat(ErrorStr, LMessages.WritePageProtectError2);
        strcat(ErrorStr, " ");
        strcat(ErrorStr, LMessages.ConfirmReadonlyOff);

        if (Application->MessageBoxA(ErrorStr, LMessages.Error, MB_YESNO + MB_ICONERROR) == IDYES)
          if (!SetFileAttributes(Path.c_str(), FILE_ATTRIBUTE_NORMAL))
            Application->MessageBoxA(LMessages.RemoveReadonlyFail, LMessages.Error, MB_OK + MB_ICONERROR);

        delete [] ErrorStr;
      } else
        SetFileAttributes(Path.c_str(), FILE_ATTRIBUTE_NORMAL);
    }
  } else if ((Quest) && (FileExists(Path))) {
    char* ErrorStr = new char [strlen((LMessages.WritePageProtectError1 + ExtractFilePath(Application->ExeName) + PageName + "\n" + LMessages.WritePageProtectError2).c_str()) + 2];
    strcpy(ErrorStr, LMessages.WritePageProtectError1);
    strcat(ErrorStr, (" " + ExtractFilePath(Application->ExeName) + PageName + "\n").c_str());
    strcat(ErrorStr, LMessages.WritePageProtectError2);
    Application->MessageBoxA(ErrorStr, LMessages.Error, MB_OK + MB_ICONERROR);
    delete [] ErrorStr;
  }
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::MainMenuBarVisibleChanged(TObject* Sender) {
  CheckReadonly("Preferences.ini", false);
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  MainMenuMenu->Checked = MainMenuBar->Visible;

  try {
    Ini->WriteBool("MainMenuBar", "Visible", MainMenuBar->Visible);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::OpenPageMenuClick(TObject* Sender) {
  if (OpenDialog2->Execute()) {
    AnsiString PageName = "";
    int Start, End;
    char* tmp = (OpenDialog2->FileName).c_str();

    for (int j = strlen(tmp); j >= 0; j--)
      if (*(tmp + j) == '\\') {
        Start = j;
        break;
      }

    End = strlen(tmp) + 1;

    for (int j = strlen(tmp); j > Start; j--)
      if (*(tmp + j) == '.') {
        End = j;
        break;
      }

    char FileName [255];
    char TempChar;

    for (int j = Start + 1; j < End; j++) {
      TempChar = *(tmp + j);
      FileName[j - Start - 1] = TempChar;
      FileName[j - Start] = '\0';
    }

    PageName = FileName;

    if (CreateNewPage(PageName))
      RichEdit1->Lines->LoadFromFile(OpenDialog2->FileName);
  }
}
//---------------------------------------------------------------------------
bool CreateNewPage(AnsiString PageName) {
  CheckReadonly(SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn", true);

  try {
    SNotesXMForm->RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn");
  } catch (...) {
    DisplayError(CheckAccess(SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn"), "Write", SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn", true);
  }

  AnsiString Title = "---";
  bool Flag;

  if (PageName == "")
    Flag = InputQuery(LMessages.NewPageTitle, LMessages.EnterName, Title);
  else {
    Title = PageName;
    Flag = true;
  }

  if (Flag) {
    bool counter = false;

    for (int i = 0; i < (SNotesXMForm->AllTabs->Tabs->Count); i++) {
      if (FileExists(ExtractFilePath(Application->ExeName) + Title + ".spn"))
        counter = true;

      if (Title == (SNotesXMForm->AllTabs->Tabs->Strings[i]))
        counter = true;
    }

    if ((counter) && (PageName == ""))
      Application->MessageBoxA(LMessages.PageCreateError, LMessages.PageCreateErrorTitle, MB_OK + MB_ICONWARNING);
    else {
      if ((counter) && (PageName != "")) {
        int i = 2;

        do {
          PageName += IntToStr(i);
          i++;
          Title = PageName;
        } while (FileExists(ExtractFilePath(Application->ExeName) + Title + ".spn"));
      }

      CheckPrefsInter();
      CheckReadonly("Preferences.ini", false);
      TIniFile* Ini = new TIniFile(PrefFile);
      SNotesXMForm->AllTabsChanging(NULL, true);
      FILE* F = fopen((ExtractFilePath(Application->ExeName) + Title + ".spn").c_str(), "w+");
      fclose(F);
      int PC = SNotesXMForm->AllTabs->Tabs->Count;
      SNotesXMForm->AllTabs->Tabs->Add(Title);
      SNotesXMForm->AllTabs->TabIndex = PC;
      SNotesXMForm->RichEdit1->Lines->Clear();
      SNotesXMForm->RichEdit1->SetFocus();

      try {
        SNotesXMForm->RichEdit1->Color = Ini->ReadInteger("Options", "DefaultColor", 16777215);
        SNotesXMForm->RichEdit1->Font->Name = Ini->ReadString("Options", "DefaultFont", "MS Sans Serif");
        SNotesXMForm->RichEdit1->Font->Size = Ini->ReadInteger("Options", "DefaultFontSize", 10);
      } catch (...) {
        Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      AnsiString Format = "RTF";

      try {
        Format = Ini->ReadString("Options", "DefaultPageFormat", "RTF");
      } catch (...) {
        Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      if (Format == "TXT") {
        AllowQuestion = false;
        SNotesXMForm->TXTFormatClick(NULL);
      } else
        SNotesXMForm->RTFFormatClick(NULL);

      try {
        Ini->WriteInteger("PageCursors", SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex], SNotesXMForm->RichEdit1->SelStart);
        Ini->WriteInteger("PageColour", SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex], SNotesXMForm->RichEdit1->Color);
      } catch (...) {
        Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      SNotesXMForm->FontNameBox->FontName = SNotesXMForm->RichEdit1->Font->Name;
      SNotesXMForm->FontSizeBox->Text = IntToStr(SNotesXMForm->RichEdit1->Font->Size);

      try {
        int PC = SNotesXMForm->AllTabs->Tabs->Count;

        for (int i = 0; i < PC; i++)
          Ini->WriteString("Pages", IntToStr(i), SNotesXMForm->AllTabs->Tabs->Strings[i]);

        Ini->WriteInteger("Parameters", "PageCount", SNotesXMForm->AllTabs->Tabs->Count);
      } catch (...) {
        Application->MessageBoxA(LMessages.PrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
      }

      try {
        SNotesXMForm->RichEdit1->Lines->SaveToFile(ExtractFilePath(Application->ExeName) + SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn");
      } catch (...) {
        DisplayError(CheckAccess(SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn"), "Write", SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn", false);
      }

      delete Ini;
      return 1;
    }
  }

  return 0;
}
//--------------------------------------------------------------------------
AnsiString GetBrowsePath() {
  AnsiString Path = "";
  BROWSEINFO    info;
  char          szDir[MAX_PATH];
  char          szDisplayName[MAX_PATH];
  LPITEMIDLIST  pidl;
  LPMALLOC      pShellMalloc;

  if(SHGetMalloc(&pShellMalloc) == NO_ERROR) {
    memset(&info, 0x00, sizeof(info));
    info.hwndOwner = Application->Handle;
    info.pidlRoot  = 0;
    info.pszDisplayName = szDisplayName;
    info.lpszTitle = LMessages.SelectTempFolderTitle;
    info.ulFlags = BIF_NEWDIALOGSTYLE; //BIF_RETURNONLYFSDIRS;
    info.lpfn = 0;
    pidl = SHBrowseForFolder(&info);

    if(pidl) {
      if(SHGetPathFromIDList(pidl, szDir))
        Path = szDir;

      pShellMalloc->Free(pidl);
    }

    pShellMalloc->Release();
  }

  return Path;
}
//--------------------------------------------------------------------------
void SaveToTemp(char* ErrorStr, bool Quest, bool Cat) {
  if (!Quest)
    Application->MessageBoxA(ErrorStr, LMessages.Error, MB_OK + MB_ICONERROR);
  else {
    if (Cat) {
      strcat(ErrorStr, "\n");
      strcat(ErrorStr, LMessages.ConfirmSaveToTemp);
    } else
      strcpy(ErrorStr, LMessages.ConfirmSaveToTemp);

    DWORD MsButtons;

    if (Cat)
      MsButtons = MB_YESNO + MB_ICONERROR;
    else
      MsButtons = MB_YESNO + MB_ICONQUESTION;

    if (Application->MessageBoxA(ErrorStr, LMessages.Error, MsButtons) == IDYES) {
      AnsiString Path = IncludeTrailingBackslash(GetBrowsePath());
      bool OK = true;

      try {
        if (Path != "\\")
          SNotesXMForm->RichEdit1->Lines->SaveToFile(Path + SNotesXMForm->AllTabs->Tabs->Strings[SNotesXMForm->AllTabs->TabIndex] + ".spn");
      } catch (...) {
        OK = false;
      }

      if ((OK) && (Path != "\\")) {
        char* TmpStr = new char [strlen((LMessages.CopyTempOK + Path).c_str()) + 2];
        strcpy(TmpStr, LMessages.CopyTempOK);
        strcat(TmpStr, " ");
        strcat(TmpStr, Path.c_str());
        Application->MessageBoxA(TmpStr, LMessages.Message, MB_OK + MB_ICONINFORMATION);
        delete [] TmpStr;
      } else if ((!OK) && (Path != "\\"))
        Application->MessageBoxA(LMessages.CopyTempFail, LMessages.Error, MB_OK + MB_ICONERROR);
    }
  }
}
//--------------------------------------------------------------------------
void __fastcall TSNotesXMForm::RestoreMenuClick(TObject* Sender) {
  CheckPrefsInter();
  TIniFile* Ini = new TIniFile(PrefFile);
  AnsiString Path = "";

  try {
    Path = Ini->ReadString("Options", "BackUpPath", "");
  } catch (...) {
    Application->MessageBoxA(LMessages.ReadPrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;

  if (Path == "")
    Application->MessageBoxA(LMessages.NoRestoreFolder, LMessages.Message, MB_OK + MB_ICONINFORMATION);
  else {
    if (!FileExists(Path + "Preferences.ini")) {
      char* Error = new char [strlen(LMessages.RestoreNotFound1) + strlen(LMessages.RestoreNotFound2) + strlen(Path.c_str()) + 3];
      strcpy(Error, LMessages.RestoreNotFound1);
      strcat(Error, " ");
      strcat(Error, Path.c_str());
      strcat(Error, "\n");
      strcat(Error, LMessages.RestoreNotFound2);
      Application->MessageBoxA(Error, LMessages.Message, MB_OK + MB_ICONWARNING);
      delete [] Error;
    } else {
      char* TmpStr = new char [strlen(LMessages.ConfirmRestore1) + strlen(LMessages.ConfirmRestore2) + strlen(Path.c_str()) + 4];
      strcpy(TmpStr, LMessages.ConfirmRestore1);
      strcat(TmpStr, " ");
      strcat(TmpStr, Path.c_str());
      strcat(TmpStr, "?\n");
      strcat(TmpStr, LMessages.ConfirmRestore2);

      if (Application->MessageBoxA(TmpStr, LMessages.Message, MB_YESNO + MB_ICONQUESTION) == IDYES) {
        TIniFile* Ini = new TIniFile(Path + "Preferences.ini");
        int RestCount = Ini->ReadInteger("Parameters", "PageCount", 0);
        int PagesFound = 0;

        for (int i = 0; i < RestCount; i++)
          if (FileExists(Path + Ini->ReadString("Pages", IntToStr(i), "") + ".spn"))
            ++PagesFound;

        if ((PagesFound != RestCount) || (RestCount == 0)) {
          if (Application->MessageBoxA(LMessages.RestoreBroken, LMessages.Message, MB_YESNO + MB_ICONQUESTION) == IDYES) {
            IfBackup->Checked = false;
            Application->CreateForm(__classid(TBackupProgressForm), &BackupProgressForm);
            BackupProgressForm->ShowModal();
          }
        } else {
          IfBackup->Checked = false;
          Application->CreateForm(__classid(TBackupProgressForm), &BackupProgressForm);
          BackupProgressForm->ShowModal();
        }

      }
    }
  }
}
//---------------------------------------------------------------------------
/*void __fastcall TSNotesXMForm::FindDialog1Find(TObject *Sender)
{
   int FoundAt, StartPos, ToEnd;
   TRichSearchTypes Option;
   StartPos=RichEdit1->SelStart;
   if (RichEdit1->SelLength)
      StartPos+=RichEdit1->SelLength;
   ToEnd=RichEdit1->Text.Length()-StartPos;
   if (FindDialog1->Options.Contains(frWholeWord))
      Option<<stWholeWord;
   else
      Option>>stWholeWord;
   if (FindDialog1->Options.Contains(frMatchCase))
      Option<<stMatchCase;
   else
      Option>>stMatchCase;
   FoundAt=RichEdit1->FindText(FindDialog1->FindText, StartPos, ToEnd, Option);
   if (FoundAt!=-1)
      {
         RichEdit1->SetFocus();
         RichEdit1->SelStart=FoundAt;
         RichEdit1->SelLength=FindDialog1->FindText.Length();
      }
} */
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::FormResize(TObject* Sender) {
  RichEdit1->Repaint();
}
//---------------------------------------------------------------------------
void __fastcall TSNotesXMForm::LeftMarginMenuClick(TObject* Sender) {
  CheckPrefsInter();
  CheckReadonly("Preferences.ini", false);
  TIniFile* Ini = new TIniFile(PrefFile);
  RichEdit1->SelectionBar = LeftMarginMenu->Checked;

  try {
    Ini->WriteBool("Parameters", "LeftMargin", LeftMarginMenu->Checked);
  } catch (...) {
    Application->MessageBoxA(LMessages.WritePrefsError, LMessages.Error, MB_OK + MB_ICONERROR);
  }

  delete Ini;
}
//---------------------------------------------------------------------------

