//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SelLang.h"
#include "inifiles.hpp"
#include "stdio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLangForm* LangForm;
AnsiString Langes[10];
AnsiString PrefFileLang = ExtractFilePath(Application->ExeName) + "Preferences.ini";
//---------------------------------------------------------------------------
__fastcall TLangForm::TLangForm(TComponent* Owner)
  : TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLangForm::FormCreate(TObject* Sender) {
  Langes[0] = "English";
  Langes[1] = "Russian";
  Langs->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TLangForm::OKButtonClick(TObject* Sender) {
  if (!FileExists(PrefFileLang)) {
    FILE* F = fopen(PrefFileLang.c_str(), "w+");

    if (F == NULL) {
      char* MessText = new char [strlen(("File with preferences" + PrefFileLang + "\n" + "not found and cannot be created. Check your rights for writting.").c_str()) + 2];
      strcpy(MessText, "File with preferences");
      strcat(MessText, (" " + PrefFileLang + "\n" + "not found and cannot be created. Check your rights for writting.").c_str());
      Application->MessageBoxA(MessText, "Error", MB_OK + MB_ICONERROR);
      fclose(F);
      delete [] MessText;
      Application->Terminate();
    }

    fclose(F);
  }

  DWORD Attrs = GetFileAttributes(PrefFileLang.c_str());

  if (Attrs != INVALID_FILE_ATTRIBUTES)
    if (Attrs & FILE_ATTRIBUTE_READONLY)
      SetFileAttributes(PrefFileLang.c_str(), FILE_ATTRIBUTE_NORMAL);

  TIniFile* Ini = new TIniFile(PrefFileLang);
  int SelIndex = Langs->ItemIndex;

  try {
    if (SelIndex == 0)
      Ini->WriteString("Parameters", "Language", "English");

    if (SelIndex == 1)
      Ini->WriteString("Parameters", "Language", "Russian");
  } catch (...) {
    AnsiString tmp1 = "Error writting file with preferences";
    AnsiString tmp2 = "Check your access.";
    AnsiString full = tmp1 + " " + PrefFileLang + "\n" + tmp2;
    Application->MessageBoxA(full.c_str(), "Error", MB_OK + MB_ICONERROR);
  }

  delete Ini;
  Close();
}
//---------------------------------------------------------------------------

