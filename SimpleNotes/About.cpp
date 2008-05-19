//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "SNotes.h"
#include "inifiles.hpp"
#include "ShellAPI.h"
#include "stdio.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
AnsiString PrefFileAbout=ExtractFilePath(Application->ExeName)+"Preferences.ini";
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}

void ApplyLangAbout();
//---------------------------------------------------------------------
 void __fastcall TAboutBox::HomePageLabelClick(TObject *Sender)
{
   if (SNotesXMForm->RussianLangMenu->Checked)
      ShellExecute(0, NULL, "http://www.snotes.narod.ru", NULL,NULL,1);
   else
      ShellExecute(0, NULL, "http://www.snotes.narod.ru/index_en.htm", NULL,NULL,1);
   AboutBox->Close();
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::MailLabelClick(TObject *Sender)
{
   AboutBox->Close();
   ShellExecute(0, NULL, "mailto:xelfium@mail.ru", NULL,NULL,1);
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
   AboutBox->Close();
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::LogoAuthorLabelClick(TObject *Sender)
{
   AboutBox->Close();
   ShellExecute(0, NULL, "mailto:AB0@list.ru", NULL,NULL,1);
}
//---------------------------------------------------------------------------
void __fastcall TAboutBox::FormCreate(TObject *Sender)
{       
   ApplyLangAbout();
}
//---------------------------------------------------------------------------
void ApplyLangAbout()
{
         TIniFile *LangIni;
         if (SNotesXMForm->RussianLangMenu->Checked)
            LangIni = new TIniFile (ExtractFilePath(Application->ExeName)+"Languages\\Russian.lng");
         if (SNotesXMForm->EnglishLangMenu->Checked)
            LangIni = new TIniFile (ExtractFilePath(Application->ExeName)+"Languages\\English.lng");
         try
            {
               AboutBox->Caption=LangIni->ReadString("Language", "ABOUT_WINDOW_TITLE", "О программе...");
               AboutBox->LogoCreationLabel->Caption=LangIni->ReadString("Language", "ABOUT_LOGO_LABEL", "Создание логотипа:");
               if (SNotesXMForm->RussianLangMenu->Checked)
                  AboutBox->MainAuthorLabel->Caption="Сапрыкин Александр, 2004-2006 "+LangIni->ReadString("Language", "ABOUT_YEARS_LABEL", "года");
               else
                  AboutBox->MainAuthorLabel->Caption="Saprykin Alexander, 2004-2006 "+LangIni->ReadString("Language", "ABOUT_YEARS_LABEL", "years");
               if (SNotesXMForm->RussianLangMenu->Checked)
                  AboutBox->LogoAuthorLabel->Caption="Карпов Сергей";
               else
                  AboutBox->LogoAuthorLabel->Caption="Karpov Sergei";
               AboutBox->WarrantyLabel->Caption=LangIni->ReadString("Language", "ABOUT_WARRANTY_LABEL", "Эта программа распространяется по принципу freeware без всяких гарантий.");
            }
         catch (...)
            {
               Application->MessageBoxA("Error reading language file. Default language will be used", "Error", MB_OK+MB_ICONERROR);
            }
         delete LangIni;
}
//---------------------------------------------------------------------------





