//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TAboutBox : public TForm {
 __published:
  TButton* OKButton;
  TGroupBox* AboutGroup;
  TImage* ProgramIcon;
  TLabel* ProductNameLabel;
  TLabel* VersionLabel;
  TLabel* MainAuthorLabel;
  TLabel* LogoCreationLabel;
  TLabel* LogoAuthorLabel;
  TLabel* WarrantyLabel;
  TLabel* HomePageLabel;
  TLabel* MailLabel;
  void __fastcall HomePageLabelClick(TObject* Sender);
  void __fastcall MailLabelClick(TObject* Sender);
  void __fastcall OKButtonClick(TObject* Sender);
  void __fastcall LogoAuthorLabelClick(TObject* Sender);
  void __fastcall FormCreate(TObject* Sender);
 private:
 public:
  virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox* AboutBox;
//----------------------------------------------------------------------------
#endif
