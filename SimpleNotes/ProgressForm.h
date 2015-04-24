//---------------------------------------------------------------------------

#ifndef ProgressFormH
#define ProgressFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TBackupProgressForm : public TForm {
 __published:  // IDE-managed Components
  TLabel* CopyLabel;
  TProgressBar* ProgressBar1;
  TLabel* BackComplete;
  TTimer* StartTimer;
  TTimer* CloseTimer;
  void __fastcall FormCreate(TObject* Sender);
  void __fastcall FormShow(TObject* Sender);
  void __fastcall StartTimerTimer(TObject* Sender);
  void __fastcall CloseTimerTimer(TObject* Sender);
  void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
 private:  // User declarations
 public:   // User declarations
  __fastcall TBackupProgressForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBackupProgressForm* BackupProgressForm;
//---------------------------------------------------------------------------
#endif
