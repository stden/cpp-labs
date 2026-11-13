//---------------------------------------------------------------------------

#ifndef PrefersH
#define PrefersH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "RxCombos.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include "JvComponent.hpp"
#include "JvExComCtrls.hpp"
#include "JvExControls.hpp"
#include "JvPageList.hpp"
#include "JvPageListTreeView.hpp"

//---------------------------------------------------------------------------
class TPrefsForm : public TForm {
 __published:  // IDE-managed Components
  TColorDialog* ColorDialog1;
  TBitBtn* ApplyButton;
  TBitBtn* OKButton;
  TBitBtn* CancelButton;
  TTreeView* PagesTree;
  TGroupBox* GeneralGroupBox;
  TLabel* SelectBackupFolderLabel;
  TLabel* HideLabel;
  TCheckBox* MinOnClose;
  TCheckBox* StartWithWindows;
  TGroupBox* StorePagesGroupBox;
  TRadioButton* TopPages;
  TRadioButton* BottomPages;
  TEdit* BackupPath;
  TButton* BrowseButton;
  TCheckBox* TaskbarCheck;
  TCheckBox* HideWind;
  TEdit* HideTime;
  TUpDown* HideTimePosition;
  TCheckBox* IconInTray;
  TGroupBox* ViewGroupBox;
  TLabel* SpeedLabel;
  TLabel* StyleLabel;
  TCheckBox* Transparency;
  TTrackBar* TransValue;
  TCheckBox* MultiLines;
  TCheckBox* URLDetect;
  TCheckBox* FadeShow;
  TEdit* FadeSpeed;
  TUpDown* FadeSpeedPosition;
  TComboBox* StyleBox;
  TCheckBox* XPEffects;
  TGroupBox* ProgramModeGroupBox;
  TLabel* NormalModeLabel;
  TLabel* SecurityModeLabel;
  TRadioButton* NormalMode;
  TRadioButton* HighMode;
  TGroupBox* HotkeyGroupBox;
  TLabel* HotkeyLabel;
  THotKey* HotKeyComb;
  TCheckBox* FadeHide;
  TBitBtn* SetHotkeyButton;
  TGroupBox* DefaultGroupBox;
  TLabel* DefaultFontLabel;
  TLabel* DefaultPageColorLabel;
  TSpeedButton* DefaultColor;
  TLabel* DefaultFontSizeLabel;
  TLabel* PageFormatLabel;
  TLabel* AttentionLabel;
  TFontComboBox* FontComboBox1;
  TEdit* DefaultSize;
  TUpDown* DefaultFontSizePosition;
  TComboBox* FormatPageBox;
  TCheckBox* AskFormat;
  void __fastcall TransValueChange(TObject* Sender);
  void __fastcall ApplyButtonClick(TObject* Sender);
  void __fastcall TransparencyClick(TObject* Sender);
  void __fastcall FormShow(TObject* Sender);
  void __fastcall CancelButtonClick(TObject* Sender);
  void __fastcall SetHotkeyButtonClick(TObject* Sender);
  void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
  void __fastcall FadeShowClick(TObject* Sender);
  void __fastcall FadeSpeedKeyPress(TObject* Sender, char& Key);
  void __fastcall OKButtonClick(TObject* Sender);
  void __fastcall FormCreate(TObject* Sender);
  void __fastcall DefaultColorClick(TObject* Sender);
  void __fastcall BrowseButtonClick(TObject* Sender);
  void __fastcall StyleBoxChange(TObject* Sender);
  void __fastcall BackupPathChange(TObject* Sender);
  void __fastcall MinOnCloseClick(TObject* Sender);
  void __fastcall StartWithWindowsClick(TObject* Sender);
  void __fastcall TaskbarCheckClick(TObject* Sender);
  void __fastcall TopPagesClick(TObject* Sender);
  void __fastcall BottomPagesClick(TObject* Sender);
  void __fastcall MultiLinesClick(TObject* Sender);
  void __fastcall URLDetectClick(TObject* Sender);
  void __fastcall FadeSpeedChange(TObject* Sender);
  void __fastcall XPEffectsClick(TObject* Sender);
  void __fastcall NormalModeClick(TObject* Sender);
  void __fastcall HighModeClick(TObject* Sender);
  void __fastcall HotKeyCombChange(TObject* Sender);
  void __fastcall FadeHideClick(TObject* Sender);
  void __fastcall FontComboBox1Change(TObject* Sender);
  void __fastcall DefaultSizeChange(TObject* Sender);
  void __fastcall HideWindClick(TObject* Sender);
  void __fastcall HideTimeChange(TObject* Sender);
  void __fastcall FormatPageBoxChange(TObject* Sender);
  void __fastcall AskFormatClick(TObject* Sender);
  void __fastcall IconInTrayClick(TObject* Sender);
  void __fastcall PagesTreeChange(TObject* Sender, TTreeNode* Node);
 private:  // User declarations
 public:   // User declarations
  __fastcall TPrefsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPrefsForm* PrefsForm;
//---------------------------------------------------------------------------
#endif
