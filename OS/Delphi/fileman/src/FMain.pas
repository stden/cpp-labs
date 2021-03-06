unit FMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, ToolWin, ExtCtrls, Menus, XPMan, ImgList, StdCtrls, FFileView,
  Functions, FFolder, FMove, FAbout, DateUtils;

type
  T_main = class(TForm)
    MainMenu: TMainMenu;
    N1: TMenuItem;
    Panel2: TPanel;
    StatusBar: TStatusBar;
    XPManifest: TXPManifest;
    PanelLeft: TPanel;
    PanelRight: TPanel;
    Splitter1: TSplitter;
    iFileTypes: TImageList;
    bOpen: TButton;
    bRename: TButton;
    bCopy: TButton;
    bFoolder: TButton;
    bDelete: TButton;
    mExit: TMenuItem;
    epath: TPanel;
    eCMD: TEdit;
    N2: TMenuItem;
    mAbout: TMenuItem;
    procedure FormCreate(Sender: TObject);
    procedure bRenameClick(Sender: TObject);
    procedure bFoolderClick(Sender: TObject);
    procedure mExitClick(Sender: TObject);
    procedure bDeleteClick(Sender: TObject);
    procedure bCopyClick(Sender: TObject);
    procedure eCMDClick(Sender: TObject);
    procedure eCMDKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormResize(Sender: TObject);
    procedure mAboutClick(Sender: TObject);
  private
    { Private declarations }
     fview_a, fview_b: TFileView;
  public
    { Public declarations }
    SelectedView: TFileView;
  end;
 

var
  _main: T_main;
  
implementation

uses FConsole;

{$R *.dfm}

procedure T_main.FormCreate(Sender: TObject);
begin
  fview_a := TFileView.Create(PanelLeft);
  fview_a.Parent := PanelLeft;
  fview_a.Init;
  fview_b := TFileView.Create(PanelRight);
  fview_b.Parent := PanelRight;
  fview_b.Init;

  fview_a.Focus;
end;

procedure T_main.bRenameClick(Sender: TObject);
begin
  with SelectedView do
  begin
    if (ListView.ItemIndex>=0) then
    begin
      ListView.Items[ListView.ItemIndex].EditCaption;
    end;
 end;
end;

procedure T_main.bFoolderClick(Sender: TObject);
begin
  _folder.ShowModal;
  
end;

procedure T_main.mExitClick(Sender: TObject);
begin
  close;
end;

procedure T_main.bDeleteClick(Sender: TObject);
begin
with SelectedView do
  begin
    if (ListView.ItemIndex>=0) then
    begin
      if MessageDlg(CurrentDir+String(ListView.Items[ListView.ItemIndex].Data), mtConfirmation, mbYesNoCancel, 0) = mrYes  then
      begin
        RemoveAll(CurrentDir+String(ListView.Items[ListView.ItemIndex].Data));
        LoadDir;
      end;
    end;         
 end;
end;

procedure T_main.bCopyClick(Sender: TObject);
begin
  _Move.ShowModal;
end;

procedure T_main.eCMDClick(Sender: TObject);
begin
  if not _Console.Visible then
  begin
   _Console.Left := eCMD.ClientOrigin.X;
   _Console.Top := eCMD.ClientOrigin.Y-_Console.Height;
   _Console.Width := eCMD.Width;
   _Console.show;
   eCMD.SetFocus;
  end;
end;

procedure T_main.eCMDKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key = 13 then
  begin
    _Console.ExecConsoleApp(eCMD.Text);
    eCMD.Text := '';
  end;
end;

procedure T_main.FormResize(Sender: TObject);
begin
  if _main.Visible AND _Console.Visible then
  begin
   _Console.Left := eCMD.ClientOrigin.X;
   _Console.Top := eCMD.ClientOrigin.Y-_Console.Height;
   _Console.Width := eCMD.Width;
  end;
end;

procedure T_main.mAboutClick(Sender: TObject);
begin
  _about.show;
end;

end.
