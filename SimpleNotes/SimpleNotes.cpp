//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
USEFORM("SNotes.cpp", SNotesXMForm);
USEFORM("About.cpp", AboutBox);
USEFORM("Prefers.cpp", PrefsForm);
USEFORM("SelLang.cpp", LangForm);
USEFORM("ProgressForm.cpp", BackupProgressForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        HWND MainHandle=FindWindow("TNotesXMForm", NULL);
        try
        {        
                 Application->Initialize();
                 if (MainHandle==0)
                    {  
                       Application->Title = "SimpleNotes";
                       Application->CreateForm(__classid(TSNotesXMForm), &SNotesXMForm);
                       Application->ShowMainForm=false;
                       Application->Run();
                    }
                 else
                    {
                       Application->MessageBoxA("SNotes is already running! Close previous copy of SNotes and try again.", "SimpleNotes", MB_OK+MB_ICONWARNING);
                       return 0;
                    }
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }



        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
        
}
//---------------------------------------------------------------------------
