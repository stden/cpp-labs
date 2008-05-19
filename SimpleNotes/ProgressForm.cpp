//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgressForm.h"
#include "SNotes.h"
#include "inifiles.hpp"
#include "stdio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBackupProgressForm *BackupProgressForm;
AnsiString PrefFileProg=ExtractFilePath(Application->ExeName)+"Preferences.ini";
struct L
{
   AnsiString Copied;
   char *NoPrefsError;
   char *ReadPrefsError;
   char *Error;
   char *CopyError;
   char *ErrorCopyFile;
   char *RestoreError;
} LMessagesProg;
bool CanClose;
//---------------------------------------------------------------------------
__fastcall TBackupProgressForm::TBackupProgressForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBackupProgressForm::FormCreate(TObject *Sender)
{
   try
      {
         TIniFile *LangIni;
         CanClose=false;
         if (SNotesXMForm->RussianLangMenu->Checked)
            LangIni=new TIniFile(ExtractFilePath(Application->ExeName)+"Languages\\Russian.lng");
         if (SNotesXMForm->EnglishLangMenu->Checked)
            LangIni=new TIniFile(ExtractFilePath(Application->ExeName)+"Languages\\English.lng");
         if (SNotesXMForm->IfBackup->Checked)
            {
               BackupProgressForm->Caption=LangIni->ReadString("Language", "BACKUP_WINDOW_TITLE", "Резервное копирование");
               CopyLabel->Caption=LangIni->ReadString("Language", "BACKUP_COPYING_LABEL", "Копирование:");
               BackComplete->Caption=LangIni->ReadString("Language", "BACKUP_COMPLETE_LABEL", "Резервное копирование завершено!");
               LMessagesProg.Copied=LangIni->ReadString("Language", "BACKUP_FILES_COPIED_LABEL", "Файлов скопировано:");
            }
         else
            {
               BackupProgressForm->Caption=LangIni->ReadString("Language", "RESTORE_WINDOW_TITLE", "Восстановление");
               CopyLabel->Caption=LangIni->ReadString("Language", "RESTORE_COPYING_LABEL", "Восстановление:");
               BackComplete->Caption=LangIni->ReadString("Language", "RESTORE_COMPLETE_LABEL", "Восстановление данных завершено!");
               LMessagesProg.Copied=LangIni->ReadString("Language", "RESTORE_FILES_COPIED_LABEL", "Файлов восстановлено:");
            }
         LMessagesProg.NoPrefsError=new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками")+" "+PrefFileProg+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str())+1];
         LMessagesProg.ReadPrefsError=new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек")+" "+PrefFileProg+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.")+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str())+1];
         LMessagesProg.Error=new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str())+1];
         LMessagesProg.ErrorCopyFile=new char [strlen((LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_COPY_FILE", "Невозможно скопировать файл:")).c_str())+1];
         LMessagesProg.CopyError=new char [strlen((LangIni->ReadString("Language", "BACKUP_MESSAGE_ERROR_BACKUP_1", "Не все файлы были скопированы! Возможно, некоторые файлы блокированы другим процессом. Либо")+"\n"+LangIni->ReadString("Language", "BACKUP_MESSAGE_ERROR_BACKUP_2", "папка назначения переполнена или диск защищен от записи. Также проверьте сетевое соединение.")).c_str())+1];
         LMessagesProg.RestoreError=new char [strlen((LangIni->ReadString("Language", "RESTORE_MESSAGE_ERROR_RESTORE_1", "Не все файлы были восстановлены! Возможно, некоторые файлы блокированы другим процессом. Либо")+"\n"+LangIni->ReadString("Language", "RESTORE_MESSAGE_ERROR_RESTORE_2", "папка назначения переполнена или диск защищен от записи. Также проверьте сетевое соединение.")).c_str())+1];

         strcpy(LMessagesProg.NoPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_1", "Файл с настройками")+" "+PrefFileProg+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_PREFERENCES_NOT_FOUND_2", "не найден и не может быть создан. Проверьте Ваши права на запись.")).c_str());
         strcpy(LMessagesProg.ReadPrefsError, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_1", "Ошибка при чтении файла настроек")+" "+PrefFileProg+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_2", "Возможные причины: файл блокирован другим приложением и невозможно прочитать его. Найдите это приложение и отключите блокировку.")+"\n"+LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_READ_PREFERENCES_3", "Либо данные, записанные в этом файле, некорректны.")).c_str());
         strcpy(LMessagesProg.Error, (LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR", "Ошибка")).c_str());
         strcpy(LMessagesProg.ErrorCopyFile, LangIni->ReadString("Language", "MAIN_MESSAGE_ERROR_COPY_FILE", "Невозможно скопировать файл:").c_str());
         strcpy(LMessagesProg.CopyError, (LangIni->ReadString("Language", "BACKUP_MESSAGE_ERROR_BACKUP_1", "Не все файлы были скопированы! Возможно, некоторые файлы блокированы другим процессом. Либо")+"\n"+LangIni->ReadString("Language", "BACKUP_MESSAGE_ERROR_BACKUP_2", "папка назначения переполнена или диск защищен от записи. Также проверьте сетевое соединение.")).c_str());
         strcpy(LMessagesProg.RestoreError, (LangIni->ReadString("Language", "RESTORE_MESSAGE_ERROR_RESTORE_1", "Не все файлы были восстановлены! Возможно, некоторые файлы блокированы другим процессом. Либо")+"\n"+LangIni->ReadString("Language", "RESTORE_MESSAGE_ERROR_RESTORE_2", "папка назначения переполнена или диск защищен от записи. Также проверьте сетевое соединение.")).c_str());
         delete LangIni;
      }
   catch (...)
      {
         Application->MessageBoxA("Error reading language file. Default language will be used.", "Error", MB_OK+MB_ICONERROR);
      }
}
//---------------------------------------------------------------------------
void __fastcall TBackupProgressForm::FormShow(TObject *Sender)
{
   StartTimer->Interval=250;
}
//---------------------------------------------------------------------------
void __fastcall TBackupProgressForm::StartTimerTimer(TObject *Sender)
{
   StartTimer->Interval=0;
   if (!FileExists(PrefFileProg))
      {
         FILE *F=fopen(PrefFileProg.c_str(), "w+");
         if (F==NULL)
            {
               Application->MessageBoxA(LMessagesProg.NoPrefsError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
               fclose(F);
               Application->Terminate();
            }
         fclose(F);
      }
   TIniFile *Ini=new TIniFile(PrefFileProg);
   int Total=0;
   AnsiString Path, PathTemp, FromCopy;
   TSearchRec Srh;
   if (SNotesXMForm->IfBackup->Checked)
      {
         try
            {
               PathTemp=IncludeTrailingBackslash(Ini->ReadString("Options", "BackUpPath", ""));
            }
         catch (...)
            {
               Application->MessageBoxA(LMessagesProg.ReadPrefsError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
            }
      }
   else
      {
         PathTemp=ExtractFilePath(Application->ExeName);
         try
            {
               FromCopy=IncludeTrailingBackslash(Ini->ReadString("Options", "BackUpPath", ""));
            }
         catch (...)
            {
               Application->MessageBoxA(LMessagesProg.ReadPrefsError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
            }
      }
   if (FindFirst(PathTemp+"*.spn", faAnyFile, Srh)==0)
      {
         DeleteFile((PathTemp+Srh.Name).c_str());
         while (FindNext(Srh)==0)
            DeleteFile((PathTemp+Srh.Name).c_str());
      }
   if (SNotesXMForm->IfBackup->Checked)
      DeleteFile((PathTemp+"Preferences.ini").c_str());
   if (SNotesXMForm->IfBackup->Checked)
   {
      for (int i=0; i<=(SNotesXMForm->AllTabs->Tabs->Count-1); i++)
         {
            try
               {
                  Path=IncludeTrailingBackslash(Ini->ReadString("Options", "BackUpPath", ""))+SNotesXMForm->AllTabs->Tabs->Strings[i]+".spn";
               }
            catch (...)
               {
                  Application->MessageBoxA(LMessagesProg.ReadPrefsError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
               }
            char *AppPath, *PathCh;
            AppPath=new char [strlen((IncludeTrailingBackslash(ExtractFilePath(Application->ExeName))+SNotesXMForm->AllTabs->Tabs->Strings[i]+".spn").c_str())+1];
            PathCh=new char [strlen(Path.c_str())+1];
            strcpy (AppPath, (IncludeTrailingBackslash(ExtractFilePath(Application->ExeName))+SNotesXMForm->AllTabs->Tabs->Strings[i]+".spn").c_str());
            strcpy(PathCh, Path.c_str());
            CopyLabel->Caption+=(" "+SNotesXMForm->AllTabs->Tabs->Strings[i]+".spn");
            if (CopyFile(AppPath, PathCh, false))
               ++Total;
            else
               {
                  char *Error=new char [strlen(LMessagesProg.ErrorCopyFile)+strlen(AppPath)+2];
                  strcpy(Error, LMessagesProg.ErrorCopyFile);
                  strcat(Error, " ");
                  strcat(Error, AppPath);
                  Application->MessageBoxA(Error, LMessagesProg.Error, MB_OK+MB_ICONERROR);
                  delete [] Error;
               }
            ProgressBar1->Position=100/(SNotesXMForm->AllTabs->Tabs->Count+1)*i+1;
            delete [] AppPath;
            delete [] PathCh;
         }
      AnsiString Path2;
      try
         {
            Path2=IncludeTrailingBackslash(Ini->ReadString("Options", "BackUpPath", ""))+"Preferences.ini";
         }
      catch (...)
         {
            Application->MessageBoxA(LMessagesProg.ReadPrefsError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
         }
      char *PathCh2=new char [strlen(Path2.c_str())+1];
      char *Prefs=new char [strlen(PrefFileProg.c_str())+1];
      strcpy(Prefs, PrefFileProg.c_str());
      strcpy(PathCh2, Path2.c_str());
      CopyLabel->Caption+=(' '+"Preferences.ini");
      if (CopyFile(Prefs, PathCh2, false))
         ++Total;
      else
         {
            char *Error=new char [strlen(LMessagesProg.ErrorCopyFile)+strlen(Prefs)+2];
            strcpy(Error, LMessagesProg.ErrorCopyFile);
            strcat(Error, " ");
            strcat(Error, Prefs);
            Application->MessageBoxA(Error, LMessagesProg.Error, MB_OK+MB_ICONERROR);
            delete [] Error;
         }
      delete [] PathCh2;
      delete [] Prefs;
      ProgressBar1->Position=100;
      CopyLabel->Caption=LMessagesProg.Copied+" "+IntToStr(Total)+"/"+IntToStr(SNotesXMForm->AllTabs->Tabs->Count+1);
      BackComplete->Visible=true;
      if (Total<SNotesXMForm->AllTabs->Tabs->Count+1)
         Application->MessageBoxA(LMessagesProg.CopyError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
   }
   if (!SNotesXMForm->IfBackup->Checked)
      {
         int TotalCopied=0, NeedCopy;
         TIniFile *IniRest=new TIniFile(FromCopy+"Preferences.ini");
         NeedCopy=IniRest->ReadInteger("Parameters", "PageCount", 0);
         for (int i=0; i<NeedCopy; i++)
            {
               AnsiString RestName=IniRest->ReadString("Pages", IntToStr(i), "");
               RestName+=".spn";
               CopyLabel->Caption+=(" "+RestName);
               if (CopyFile((FromCopy+RestName).c_str(), (ExtractFilePath(Application->ExeName)+RestName).c_str(), false))
                  ++TotalCopied;
               else
                   {
                      char *Error=new char [strlen(LMessagesProg.ErrorCopyFile)+strlen((FromCopy+RestName).c_str())+2];
                      strcpy(Error, LMessagesProg.ErrorCopyFile);
                      strcat(Error, " ");
                      strcat(Error, (FromCopy+RestName).c_str());
                      Application->MessageBoxA(Error, LMessagesProg.Error, MB_OK+MB_ICONERROR);
                      delete [] Error;
                   }
               ProgressBar1->Position=100/(NeedCopy+1)*i+1;
            }
         SNotesXMForm->CoolTray->HideMainForm();
         SNotesXMForm->CoolTray->IconVisible=false;
         AnsiString RestName=FromCopy+"Preferences.ini";
         CopyLabel->Caption+=(' '+"Preferences.ini");
         ++TotalCopied;
         ProgressBar1->Position=100;
         SNotesXMForm->FormCreate(Sender);
         SNotesXMForm->CoolTray->ShowMainForm();
         CopyLabel->Caption=LMessagesProg.Copied+" "+IntToStr(TotalCopied)+"/"+IntToStr(NeedCopy+1);
         BackComplete->Visible=true;
         delete IniRest;
         if (TotalCopied<NeedCopy+1)
            Application->MessageBoxA(LMessagesProg.RestoreError, LMessagesProg.Error, MB_OK+MB_ICONERROR);
      }
   delete Ini;
   CloseTimer->Interval=2500;
   CanClose=true;
}
//---------------------------------------------------------------------------
void __fastcall TBackupProgressForm::CloseTimerTimer(TObject *Sender)
{
   Close();        
}
//---------------------------------------------------------------------------
void __fastcall TBackupProgressForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if (!CanClose)
       Abort();
}
//---------------------------------------------------------------------------
