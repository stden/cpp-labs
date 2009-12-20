unit PProcess;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ComCtrls, ExtCtrls, tlhelp32, StdCtrls, psAPI;

type
  TPageProcess = class(TFrame)
    ListProcess: TListView;
    PanelFooter: TPanel;
    Button1: TButton;
    ListThreads: TListView;
    Panel1: TPanel;
    LabelProcessFileName: TLabel;
    procedure init;
    procedure Button1Click(Sender: TObject);
    procedure ListProcessChange(Sender: TObject; Item: TListItem; Change: TItemChange);
  private
    { Private declarations }
    Snapshot: THandle;
    procedure UpdateProcessList();
    function ProcessFileName(a: Cardinal): string;
  public
    { Public declarations }
  end;

implementation

uses FMain, Functions;

{$R *.dfm}

function TPageProcess.ProcessFileName(a: Cardinal): string;
var
  Handle: THandle;
begin
  Result := '';
  Handle := OpenProcess(PROCESS_QUERY_INFORMATION or PROCESS_VM_READ, False, a);
  if Handle <> 0 then
  try
    SetLength(Result, MAX_PATH);
    if GetModuleFileNameEx(Handle, 0, PChar(Result), MAX_PATH) > 0 then
      SetLength(Result, StrLen(PChar(Result)))
    else
      Result := '';
  finally
    CloseHandle(Handle);
  end;
end;

procedure TPageProcess.UpdateProcessList;
var
  b: TListItem;
  e: TProcessEntry32;
  h: HWND;
  pmc: PPROCESS_MEMORY_COUNTERS;
  cb: Integer;
begin
  cb := SizeOf(_PROCESS_MEMORY_COUNTERS);
  GetMem(pmc, cb);
  pmc^.cb := cb;
  Snapshot := CreateToolHelp32Snapshot(TH32CS_SNAPALL	,0);
  if Snapshot=INVALID_HANDLE_VALUE then
  begin
    _main.StatusBar.SimpleText:=('���������� � ��������� �������.');
    exit;
  end;

  e.dwSize := SizeOf(e);
  ListProcess.Items.Clear;
  if Process32First(Snapshot, e) then
  begin
    repeat
      b := ListProcess.Items.Add;
      b.Caption := e.szExeFile;

      h := OpenProcess(PROCESS_VM_READ or PROCESS_QUERY_INFORMATION, False, e.th32ProcessID);
      b.Data := TObject(e.th32ProcessID);
      if GetProcessMemoryInfo(h, pmc, cb) then
        b.SubItems.Add(StringSize(pmc^.WorkingSetSize))
      else
        b.SubItems.Add('0 B');
    until not Process32Next(Snapshot,e);
  end;
  FreeMem(pmc);
end;

procedure TPageProcess.Button1Click(Sender: TObject);
begin
  UpdateProcessList();
end;

procedure TPageProcess.ListProcessChange(Sender: TObject; Item: TListItem; Change: TItemChange);
var
  ThreadEntry: TThreadEntry32;
  b: TListItem;
  f: THandle;

begin

  ListThreads.Clear;
  ThreadEntry.dwSize := SizeOf(TThreadEntry32);
  LabelProcessFileName.Caption := ProcessFileName(Cardinal(Item.data));
        CreateFileMapping 
  if Thread32First(Snapshot, ThreadEntry) then
  repeat
    if(ThreadEntry.th32OwnerProcessID = Cardinal(Item.data)) then
    begin
      b := ListThreads.Items.Add;
      b.Caption := FloatToStr(ThreadEntry.th32ThreadID);
     
    end;
  until not Thread32Next(Snapshot, ThreadEntry);
end;

procedure TPageProcess.init;
begin
   UpdateProcessList();
end;

end.
