//---------------------------------------------------------------------------

#ifndef SelLangH
#define SelLangH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class TLangForm : public TForm
{
__published:	// IDE-managed Components
        TListBox *Langs;
        TLabel *LabelOne;
        TButton *OKButton;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OKButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TLangForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLangForm *LangForm;
//---------------------------------------------------------------------------
#endif
