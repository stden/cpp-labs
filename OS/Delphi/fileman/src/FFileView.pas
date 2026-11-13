unit FFileView;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, StdCtrls, ExtCtrls, ULogicalDriveUtils, Functions,
  ImgList;

type
  TFileView = class(TFrame)
    ListView: TListView;
    Panel1: TPanel;
    ComboDriveBox: TComboBox;
    pInfo: TPanel;
    bRoot: TButton;
    bUp: TButton;
    ePath: TComboBox;
    procedure ComboDriveBoxChange(Sender: TObject);
    procedure bRootClick(Sender: TObject);
    procedure ListViewDblClick(Sender: TObject);
    procedure bUpClick(Sender: TObject);
    procedure ListViewClick(Sender: TObject);
    procedure ListViewEdited(Sender: TObject; Item: TListItem;
      var S: String);
    procedure ePathKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
  private
    FCurrentDrive: Char;
    procedure SetCurrentDrive(Value: Char);
  public
    CurrentDir: String;

    procedure Init();
    procedure LoadDir();
    procedure Focus;
    function GetCurrentPath(): string;
  published
    property CurrentDrive: Char read FCurrentDrive write SetCurrentDrive;
  end;

implementation

uses FMain, Math;

{$R *.dfm}
procedure TFileView.SetCurrentDrive(Value: Char);
var
  FreeBytesAvailableToCaller, TotalNumberOfBytes, TotalNumberOfFreeBytes: TLargeInteger;
begin
  FCurrentDrive:=Value;
  GetDiskFreeSpaceEx(PChar(CurrentDrive + ':\'), FreeBytesAvailableToCaller, TotalNumberOfBytes, @TotalNumberOfFreeBytes);
  pInfo.Caption := StringSize(TotalNumberOfFreeBytes)+'/'+StringSize(TotalNumberOfBytes);

end;

procedure TFileView.Init;
begin
  ComboDriveBox.Items.Clear;
  ComboDriveBox.Items.BeginUpdate;
  ComboDriveBox.Items.Assign(UpdateAvailableDrives());
  ComboDriveBox.Items.EndUpdate;
  ComboDriveBox.ItemIndex := 0;

  ComboDriveBoxChange(ComboDriveBox);
end;

procedure TFileView.Focus;
begin
  _main.SelectedView  := Self;
  _main.epath.Caption := CurrentDir;
  SetCurrentDirectory(PChar(CurrentDir));
  _main.epath.Caption:= CurrentDir;
end;

procedure TFileView.ComboDriveBoxChange(Sender: TObject);
begin
  CurrentDrive := Char(ComboDriveBox.Items.Objects[ComboDriveBox.ItemIndex]);
  CurrentDir := CurrentDrive+':\';
  LoadDir();
end;

procedure TFileView.LoadDir();
var
  f:TSearchRec;
  a: TListItem;
begin
  ePath.Text := CurrentDir;
 ListView.Items.BeginUpdate;
 ListView.Items.Clear;
 if CurrentDir<>'' then if CurrentDir[length(CurrentDir)]<>'\' then CurrentDir:=CurrentDir+'\';

 if FindFirst(CurrentDir+'*.*', faDirectory, f)=0 then
 repeat
    if (f.name='.') or (f.name='..') then continue;
    a:= ListView.Items.Add;
    a.Caption:=f.Name;
    a.Data := TObject(f.Name);
    if (f.Attr and faDirectory)<>0 then
    begin
      a.ImageIndex := 1;
      a.SubItems.Add('<dir>');
      a.SubItems.Add('');
    end
      else
    begin
      a.SubItems.Add('<file>');
      a.SubItems.Add(StringSize(f.Size));
    end;
 until FindNext(f)<>0;
 FindClose(f);
 ListView.Items.EndUpdate;
 Focus;
end;

procedure TFileView.bRootClick(Sender: TObject);
begin
  CurrentDir := CurrentDrive+':';
  LoadDir();
end;

procedure TFileView.ListViewDblClick(Sender: TObject);
begin
 if ((ListView.ItemIndex>=0) AND DirectoryExists(CurrentDir+PChar(listView.Items[ListView.ItemIndex].data))) then
 begin
  CurrentDir:= CurrentDir+PChar(ListView.Items[ListView.ItemIndex].data)+'\';
  LoadDir;
 end;
end;

procedure TFileView.bUpClick(Sender: TObject);
begin
  SetCurrentDirectory(PChar(CurrentDir));
  SetCurrentDirectory('..');

  if StrLen(PChar(GetCurrentDir())) = 3 then
    CurrentDir:= GetCurrentDir()
  else
    CurrentDir:= GetCurrentDir()+'\';
  LoadDir;
end;

procedure TFileView.ListViewClick(Sender: TObject);
begin
  Focus;
end;

procedure TFileView.ListViewEdited(Sender: TObject; Item: TListItem;
  var S: String);
begin
  RenameFile(CurrentDir+PChar(Item.Data),CurrentDir+s);
  Item.Data := TObject(s);
end;

procedure TFileView.ePathKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 13) AND SetCurrentDir(ePath.Text) then
  begin
    CurrentDir:= GetCurrentPath();
    if(ExtractFileDrive(CurrentDir) <> CurrentDrive+'\') then
      SetCurrentDrive(PChar(CurrentDir)[0]);
    LoadDir;
  end;
end;

function TFileView.GetCurrentPath():String;
begin
  if StrLen(PChar(GetCurrentDir())) = 3 then
    Result:= GetCurrentDir()
  else
    Result:= GetCurrentDir()+'\';

end;


end.
