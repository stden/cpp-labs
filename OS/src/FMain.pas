unit FMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, ComCtrls, ExtCtrls, PMain, PProcess, FAbout, PLogicalDrives,
  XPMan, StdCtrls;

type
  T_main = class(TForm)
    MainMenu: TMainMenu;
    StatusBar: TStatusBar;
    m_File: TMenuItem;
    m_Help: TMenuItem;
    mi_HelpAbout: TMenuItem;
    NavView: TTreeView;
    Split: TSplitter;
    PageArea: TPanel;
    mi_FileExit: TMenuItem;
    NavPanel: TPanel;
    Panel2: TPanel;
    TimerUpdateInfo: TTimer;
    XPManifest: TXPManifest;
    TimerUpdateSystemInfo: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure NavViewChange(Sender: TObject; Node: TTreeNode);
    procedure TimerUpdateInfoTimer(Sender: TObject);
    procedure mi_HelpAboutClick(Sender: TObject);
    procedure TimerUpdateSystemInfoTimer(Sender: TObject);
    procedure mi_FileExitClick(Sender: TObject);
  private
    { Private declarations }
    
    activePage: TFrame;
    procedure WMDevicechange(var Message: TMessage); message WM_DEVICECHANGE;

  public
    { Public declarations }
  end;

var
  _main: T_main;
  _Process: TPageProcess;
  _LogicalDrives: TLogicalDrives;

implementation

{$R *.dfm}


procedure T_main.FormCreate(Sender: TObject);
var
  b: TTreeNode;
  tmpFrame: TFrame;
begin
  tmpFrame := TPageMain.Create(_main.PageArea);
  tmpFrame.Hide;
  tmpFrame.Parent :=  _main.PageArea;
  TPageMain(tmpFrame).init;
  b :=NavView.Items.AddObjectFirst(NavView.TopItem, 'Компьютер', tmpFrame);

  _Process := TPageProcess.Create(_main.PageArea);
  _Process.Hide;
  _Process.Parent := _main.PageArea;
  _Process.init;
  NavView.Items.AddChildObject(b, 'Процессы', _Process);


  _LogicalDrives := TLogicalDrives.Create(_main.PageArea);
  _LogicalDrives.Hide;
  _LogicalDrives.Parent := _main.PageArea;
  _LogicalDrives.init;
  NavView.Items.AddChildObject(b, 'Диски', _LogicalDrives);
end;

procedure T_main.NavViewChange(Sender: TObject; Node: TTreeNode);
begin
  if(Node.Data <> nil )then
  begin
    if(activePage <> nil) then activePage.Hide;
    TFrame(Node.Data).Show;
    activePage := TFrame(Node.Data);
  end;
end;

procedure T_main.TimerUpdateInfoTimer(Sender: TObject);
var
  time: TSystemTime;
begin
  GetLocalTime(time);
  StatusBar.Panels[0].Text := Format('%0.2d:%0.2d:%0.2d', [time.wHour, time.wMinute, time.wSecond]);
end;

procedure T_main.mi_HelpAboutClick(Sender: TObject);
begin
  _about.Show;
end;

procedure T_main.TimerUpdateSystemInfoTimer(Sender: TObject);
var
  memoryStatus: TMemoryStatus;
begin
  memoryStatus.dwLength := SizeOf(TMemoryStatus);
  GlobalMemoryStatus(memoryStatus);

  with StatusBar.Canvas do
  begin
    Pen.Color   :=   clBtnFace;
    Brush.Color := clBtnFace;

    Rectangle(52,3,148,18);
    Rectangle(154,3,248,18);

    Pen.Color := clBtnFace;
    Brush.Color := clLime;

    Rectangle(52,3,148 - round((memoryStatus.dwAvailPhys / memoryStatus.dwTotalPhys) * 100),18);
    TextOut(55,4, IntToStr((memoryStatus.dwTotalPhys - memoryStatus.dwAvailPhys) shr 20 + 1) + ' MB');
  end;
end;

procedure T_main.mi_FileExitClick(Sender: TObject);
begin
  close;
end;

procedure T_main.WMDevicechange(var Message: TMessage);
begin
  _LogicalDrives.Update;
end;

end.
