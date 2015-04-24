//---------------------------------------------------------------------------

#ifndef SNotesH
#define SNotesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ToolWin.hpp>
#include <Dialogs.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include "RxRichEd.hpp"
#include "RxCombos.hpp"
#include "RXShell.hpp"
#include "CoolTrayIcon.hpp"
#include "TB2Dock.hpp"
#include "TB2Item.hpp"
#include "TB2Toolbar.hpp"
#include "TBX.hpp"
#include "TBXSwitcher.hpp"
#include "ThemeMgr.hpp"
#include "TBXToolPals.hpp"
#include "JvExStdCtrls.hpp"
#include "JvRichEdit.hpp"
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TSNotesXMForm : public TForm {
 __published:  // IDE-managed Components
  TJvRichEdit* RichEdit1;
  TTabControl* AllTabs;
  TFontDialog* FontDialog1;
  TImageList* ImageList1;
  TSaveDialog* SaveDialog1;
  TApplicationEvents* ApplicationEvents1;
  TColorDialog* ColorDialog1;
  TTimer* Timer1;
  TCoolTrayIcon* CoolTray;
  TTBXToolbar* MainMenuBar;
  TTBXSubmenuItem* FileMenu;
  TTBXItem* NewPageMenu;
  TTBXItem* SaveAsPageMenu;
  TTBXItem* PrintPageMenu;
  TTBXSeparatorItem* FileMenuSeparator;
  TTBXItem* ExitMenu;
  TTBXSubmenuItem* EditMenu;
  TTBXItem* UndoMenu;
  TTBXSeparatorItem* EditMenuSeparator1;
  TTBXItem* CutMenu;
  TTBXItem* CopyMenu;
  TTBXItem* PasteTextMenu;
  TTBXSeparatorItem* EditMenuSeparator2;
  TTBXItem* SelectAllMenu;
  TTBXSeparatorItem* EditMenuSeparator3;
  TTBXItem* FindMenu;
  TTBXItem* ReplaceMenu;
  TTBXSubmenuItem* ViewMenu;
  TTBXItem* WordWrapMenu;
  TTBXItem* StayOnTopMenu;
  TTBXSubmenuItem* FormatMenu;
  TTBXItem* FontMenu;
  TTBXItem* BackColor;
  TTBXSubmenuItem* LanguageMenu;
  TTBXItem* RussianLangMenu;
  TTBXItem* EnglishLangMenu;
  TTBXSubmenuItem* ToolsMenu;
  TTBXItem* CalcMenu;
  TTBXItem* PreferencesMenu;
  TTBXItem* BackupMenu;
  TTBXSubmenuItem* HelpMenu;
  TTBXItem* AboutMenu;
  TTBXItem* RedoMenu;
  TTBXDock* Dock1;
  TTBXDock* Dock2;
  TTBControlItem* TBControlItem1;
  TTBControlItem* TBControlItem2;
  TTBXItem* AlignLeftButton;
  TTBXItem* AlignCenterButton;
  TTBXItem* AlignRightButton;
  TFontComboBox* FontNameBox;
  TComboBox* FontSizeBox;
  TTBXDock* Dock3;
  TTBXToolbar* ServiceBar;
  TTBXItem* NewPageButton;
  TTBXItem* DeletePageButton;
  TTBXItem* SavePageButton;
  TTBXItem* PrintPageButton;
  TTBXSeparatorItem* TBSeparatorItem1;
  TTBXItem* SearchButton;
  TTBXItem* CalculatorButton;
  TTBXItem* BackupButton;
  TTBXToolbar* FormatBar;
  TTBXSwitcher* TBXSwitcher1;
  TThemeManager* ThemeManager1;
  TTBXPopupMenu* EditorPopupMenu;
  TTBXPopupMenu* TrayPopupMenu;
  TTBXPopupMenu* PagePopupMenu;
  TTBXDock* Dock4;
  TTBXDock* Dock5;
  TTBXSubmenuItem* ToolbarsMenu;
  TTBXItem* FormatBarMenu;
  TTBXItem* ServiceBarMenu;
  TTBXItem* BoldNot;
  TTBXItem* ItalickNot;
  TTBXItem* UnderlineNot;
  TTBXItem* StrikeNot;
  TTBXItem* MarkersNot;
  TTBXItem* DateNot;
  TTBXItem* RightNot;
  TTBXItem* CenterNot;
  TTBXItem* LeftNot;
  TTBXItem* RenameNot;
  TTBXItem* DeleteNot;
  TTBXItem* HomePageMenu;
  TTBXItem* WriteLetterMenu;
  TTBXSeparatorItem* HelpMenuSeparator;
  TTBXItem* CalcPop;
  TTBXItem* RestorePop;
  TTBXItem* ExitPop;
  TTBXSeparatorItem* TraySeparator1;
  TTBXItem* WriteLetterPop;
  TTBXItem* HomePagePop;
  TTBXSeparatorItem* TraySeparator2;
  TTBXItem* RenamePagePop;
  TTBXItem* DeletePagePop;
  TTBXItem* NewPagePop;
  TTBXItem* ReplacePop;
  TTBXItem* FindPop;
  TTBXItem* InsertDatePop;
  TTBXItem* SelectAllPop;
  TTBXItem* PastePop;
  TTBXItem* CopyPop;
  TTBXItem* CutPop;
  TTBXItem* RedoPop;
  TTBXItem* UndoPop;
  TTBXSeparatorItem* EditorMenuSeparator2;
  TTBXSeparatorItem* EditorMenuSeparator1;
  TTBXItem* FontPop;
  TTBXSubmenuItem* ColorPop;
  TTBXSubmenuItem* FormatPop;
  TTBXItem* FontMarkersPop;
  TTBXItem* FontStrikeoutPop;
  TTBXItem* FontUnderlinePop;
  TTBXItem* FontItalicPop;
  TTBXItem* FontBoldPop;
  TTBXItem* ColorWhitePop;
  TTBXItem* ColorBlackPop;
  TTBXSeparatorItem* ColorMenuSeparator;
  TTBXItem* ColorGrayPop;
  TTBXItem* ColorPurplePop;
  TTBXItem* ColorLimePop;
  TTBXItem* ColorAquaPop;
  TTBXItem* ColorDarkBluePop;
  TTBXItem* ColorDarkRedPop;
  TTBXItem* ColorPinkPop;
  TTBXItem* ColorYellowPop;
  TTBXItem* ColorBluePop;
  TTBXItem* ColorGreenPop;
  TTBXItem* ColorRedPop;
  TTBXItem* PrefButton;
  TTBXItem* UpCase;
  TTBXItem* LowCase;
  TTBXItem* Unindent;
  TTBXItem* Indent;
  TTBXItem* InsertObjectMenu;
  TTBXItem* CopyURL;
  TTBXSeparatorItem* CopyURLSep;
  TTBXItem* PastePopSm;
  TTBXItem* PasteMenu;
  TTimer* HintTimer;
  TTBXSeparatorItem* EditMenuSeparator4;
  TTBXItem* PasteSpecialMenu;
  TTimer* HideWindTimer;
  TTBXItem* InsertImageMenu;
  TOpenDialog* OpenDialog1;
  TTBXItem* InsertImageButton;
  TTBXSubmenuItem* FormatSelector;
  TTBXItem* RTFFormat;
  TTBXItem* TXTFormat;
  TTBXSeparatorItem* MainMenuSeparator;
  TTBImageList* TBImageList1;
  TTBXSubmenuItem* FontColorButton;
  TTBXColorPalette* ColorPalette;
  TTBXSeparatorItem* FormatBarSeparator;
  TTBXSeparatorItem* FontColorButtonSeparator1;
  TTBXItem* MoreColors;
  TTBXSeparatorItem* FontColorButtonSeparator2;
  TTBXItem* AutoColor;
  TTimer* MouseEventTimer;
  TTBXItem* MainMenuMenu;
  TTBXItem* OpenPageMenu;
  TOpenDialog* OpenDialog2;
  TTBXItem* RestoreMenu;
  TTBXItem* IfBackup;
  TPrintDialog* PrintDialog1;
  TTBXItem* LeftMarginMenu;
  void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
  void __fastcall AllTabsChanging(TObject* Sender,
                                  bool& AllowChange);
  void __fastcall AllTabsChange(TObject* Sender);
  void __fastcall FontMenuClick(TObject* Sender);
  void __fastcall NewPageMenuClick(TObject* Sender);
  void __fastcall ExitMenuClick(TObject* Sender);
  void __fastcall AlignLeftButtonClick(TObject* Sender);
  void __fastcall AlignCenterButtonClick(TObject* Sender);
  void __fastcall AlignRightButtonClick(TObject* Sender);
  void __fastcall RichEdit1SelectionChange(TObject* Sender);
  void __fastcall SaveAsPageMenuClick(TObject* Sender);
  void __fastcall FontPopClick(TObject* Sender);
  void __fastcall FindPopClick(TObject* Sender);
  void __fastcall ReplacePopClick(TObject* Sender);
  void __fastcall FindMenuClick(TObject* Sender);
  void __fastcall ReplaceMenuClick(TObject* Sender);
  void __fastcall PrintPageMenuClick(TObject* Sender);
  void __fastcall SearchButtonClick(TObject* Sender);
  void __fastcall WordWrapMenuClick(TObject* Sender);
  void __fastcall StayOnTopMenuClick(TObject* Sender);
  void __fastcall ExitPopClick(TObject* Sender);
  void __fastcall FormCreate(TObject* Sender);
  void __fastcall AboutMenuClick(TObject* Sender);
  void __fastcall BackColorClick(TObject* Sender);
  void __fastcall CalcMenuClick(TObject* Sender);
  void __fastcall CalculatorButtonClick(TObject* Sender);
  void __fastcall CalcPopClick(TObject* Sender);
  void __fastcall Timer1Timer(TObject* Sender);
  void __fastcall NewPageButtonClick(TObject* Sender);
  void __fastcall DeletePageButtonClick(TObject* Sender);
  void __fastcall FontSizeBoxKeyPress(TObject* Sender, char& Key);
  void __fastcall FontButtonClick(TObject* Sender);
  void __fastcall AllTabsMouseUp(TObject* Sender,
                                 TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall RenamePagePopClick(TObject* Sender);
  void __fastcall NewPagePopClick(TObject* Sender);
  void __fastcall DeletePagePopClick(TObject* Sender);
  void __fastcall SavePageButtonClick(TObject* Sender);
  void __fastcall PrintPageButtonClick(TObject* Sender);
  void __fastcall ApplicationEvents1Message(tagMSG& Msg,
      bool& Handled);
  void __fastcall ApplicationEvents1Minimize(TObject* Sender);
  void __fastcall PreferencesMenuClick(TObject* Sender);
  void __fastcall FontSizeBoxSelect(TObject* Sender);
  void __fastcall FontSizeBoxClick(TObject* Sender);
  void __fastcall RichEdit1URLClick(TObject* Sender,
                                    const AnsiString URLText, TMouseButton Button);
  void __fastcall FontBoldPopClick(TObject* Sender);
  void __fastcall FontItalicPopClick(TObject* Sender);
  void __fastcall FontUnderlinePopClick(TObject* Sender);
  void __fastcall FontStrikeoutPopClick(TObject* Sender);
  void __fastcall FontNameBoxClick(TObject* Sender);
  void __fastcall FontNameBoxChange(TObject* Sender);
  void __fastcall RestorePopClick(TObject* Sender);
  void __fastcall FormShow(TObject* Sender);
  void __fastcall ColorBlackPopClick(TObject* Sender);
  void __fastcall ColorWhitePopClick(TObject* Sender);
  void __fastcall ColorRedPopClick(TObject* Sender);
  void __fastcall ColorGreenPopClick(TObject* Sender);
  void __fastcall ColorBluePopClick(TObject* Sender);
  void __fastcall ColorYellowPopClick(TObject* Sender);
  void __fastcall ColorPinkPopClick(TObject* Sender);
  void __fastcall ColorDarkRedPopClick(TObject* Sender);
  void __fastcall ColorDarkBluePopClick(TObject* Sender);
  void __fastcall ColorAquaPopClick(TObject* Sender);
  void __fastcall ColorLimePopClick(TObject* Sender);
  void __fastcall ColorPurplePopClick(TObject* Sender);
  void __fastcall ColorGrayPopClick(TObject* Sender);
  void __fastcall CoolTrayClick(TObject* Sender);
  void __fastcall FontMarkersPopClick(TObject* Sender);
  void __fastcall BackupMenuClick(TObject* Sender);
  void __fastcall RussianLangMenuClick(TObject* Sender);
  void __fastcall EnglishLangMenuClick(TObject* Sender);
  void __fastcall BackupButtonClick(TObject* Sender);
  void __fastcall CoolTrayStartup(TObject* Sender,
                                  bool& ShowMainForm);
  void __fastcall InsertDatePopClick(TObject* Sender);
  void __fastcall RedoPopClick(TObject* Sender);
  void __fastcall RedoMenuClick(TObject* Sender);
  void __fastcall AllTabsMouseDown(TObject* Sender,
                                   TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall AllTabsDragOver(TObject* Sender, TObject* Source,
                                  int X, int Y, TDragState State, bool& Accept);
  void __fastcall AllTabsEndDrag(TObject* Sender, TObject* Target,
                                 int X, int Y);
  void __fastcall ServiceBarMenuClick(TObject* Sender);
  void __fastcall FormatBarMenuClick(TObject* Sender);
  void __fastcall FormatBarVisibleChanged(TObject* Sender);
  void __fastcall ServiceBarVisibleChanged(TObject* Sender);
  void __fastcall RichEdit1KeyDown(TObject* Sender, WORD& Key,
                                   TShiftState Shift);
  void __fastcall BoldNotClick(TObject* Sender);
  void __fastcall ItalickNotClick(TObject* Sender);
  void __fastcall UnderlineNotClick(TObject* Sender);
  void __fastcall StrikeNotClick(TObject* Sender);
  void __fastcall MarkersNotClick(TObject* Sender);
  void __fastcall DateNotClick(TObject* Sender);
  void __fastcall LeftNotClick(TObject* Sender);
  void __fastcall CenterNotClick(TObject* Sender);
  void __fastcall RightNotClick(TObject* Sender);
  void __fastcall DeleteNotClick(TObject* Sender);
  void __fastcall RenameNotClick(TObject* Sender);
  void __fastcall HomePageMenuClick(TObject* Sender);
  void __fastcall WriteLetterMenuClick(TObject* Sender);
  void __fastcall HomePagePopClick(TObject* Sender);
  void __fastcall WriteLetterPopClick(TObject* Sender);
  void __fastcall PrefButtonClick(TObject* Sender);
  void __fastcall UpCaseClick(TObject* Sender);
  void __fastcall LowCaseClick(TObject* Sender);
  void __fastcall IndentClick(TObject* Sender);
  void __fastcall UnindentClick(TObject* Sender);
  void __fastcall InsertObjectMenuClick(TObject* Sender);
  void __fastcall RichEdit1MouseUp(TObject* Sender,
                                   TMouseButton Button, TShiftState Shift, int X, int Y);
  void __fastcall EditorPopupMenuPopup(TObject* Sender);
  void __fastcall CopyURLClick(TObject* Sender);
  void __fastcall CopyPopClick(TObject* Sender);
  void __fastcall PastePopClick(TObject* Sender);
  void __fastcall SelectAllPopClick(TObject* Sender);
  void __fastcall CutPopClick(TObject* Sender);
  void __fastcall UndoPopClick(TObject* Sender);
  void __fastcall UndoMenuClick(TObject* Sender);
  void __fastcall CutMenuClick(TObject* Sender);
  void __fastcall CopyMenuClick(TObject* Sender);
  void __fastcall PasteTextMenuClick(TObject* Sender);
  void __fastcall SelectAllMenuClick(TObject* Sender);
  void __fastcall EditMenuPopup(TTBCustomItem* Sender, bool FromLink);
  void __fastcall PastePopSmClick(TObject* Sender);
  void __fastcall PasteMenuClick(TObject* Sender);
  void __fastcall HintTimerTimer(TObject* Sender);
  void __fastcall FormMouseWheelDown(TObject* Sender,
                                     TShiftState Shift, TPoint& MousePos, bool& Handled);
  void __fastcall FormMouseWheelUp(TObject* Sender,
                                   TShiftState Shift, TPoint& MousePos, bool& Handled);
  void __fastcall PasteSpecialMenuClick(TObject* Sender);
  void __fastcall ApplicationEvents1Deactivate(TObject* Sender);
  void __fastcall ApplicationEvents1Activate(TObject* Sender);
  void __fastcall HideWindTimerTimer(TObject* Sender);
  void __fastcall InsertImageMenuClick(TObject* Sender);
  void __fastcall InsertImageButtonClick(TObject* Sender);
  void __fastcall TXTFormatClick(TObject* Sender);
  void __fastcall RTFFormatClick(TObject* Sender);
  void __fastcall FontColorButtonDrawImage(TTBCustomItem* Item,
      TTBItemViewer* Viewer, TCanvas* Canvas, TRect& ImageRect,
      TPoint& ImageOffset, int StateFlags);
  void __fastcall AutoColorClick(TObject* Sender);
  void __fastcall MoreColorsClick(TObject* Sender);
  void __fastcall FontColorButtonClick(TObject* Sender);
  void __fastcall ColorPaletteChange(TObject* Sender);
  void __fastcall MouseEventTimerTimer(TObject* Sender);
  void __fastcall MainMenuMenuClick(TObject* Sender);
  void __fastcall MainMenuBarVisibleChanged(TObject* Sender);
  void __fastcall OpenPageMenuClick(TObject* Sender);
  void __fastcall RestoreMenuClick(TObject* Sender);
  void __fastcall FormResize(TObject* Sender);
  void __fastcall LeftMarginMenuClick(TObject* Sender);

 private:  // User declarations
 public:   // User declarations
  __fastcall TSNotesXMForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSNotesXMForm* SNotesXMForm;
//---------------------------------------------------------------------------
#endif
