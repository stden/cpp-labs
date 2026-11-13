unit FConsole;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, ExtCtrls;

type
  T_Console = class(TForm)
    memo: TRichEdit;
    Panel1: TPanel;
    bClose: TButton;
    procedure bCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    procedure ExecConsoleApp(CmdLine: String);
  end;

var
  _Console: T_Console;

implementation

{$R *.dfm}

procedure T_Console.ExecConsoleApp(CmdLine: String);
const  
   ReadBuffer = 2400;
 var  
  Security       : TSecurityAttributes;  
  ReadPipe,WritePipe  : THandle;  
  start        : TStartUpInfo;  
  ProcessInfo     : TProcessInformation;  
  Buffer        : Pchar;  
  BytesRead      : DWord;  
  Apprunning      : DWord;  
 begin  

  With Security do begin
    nlength        := SizeOf(TSecurityAttributes);
    binherithandle    := true;
    lpsecuritydescriptor := nil;
  end;
  if Createpipe (ReadPipe, WritePipe, @Security, 0) then
  begin
    Buffer  := AllocMem(ReadBuffer + 1);
    FillChar(Start,Sizeof(Start),#0);
    start.cb      := SizeOf(start);
    start.hStdOutput  := WritePipe;
    start.hStdInput  := ReadPipe;
    start.dwFlags   := STARTF_USESTDHANDLES + STARTF_USESHOWWINDOW;
    start.wShowWindow := SW_HIDE;
  
  if CreateProcess(nil, PChar(CmdLine), @Security, @Security, true, NORMAL_PRIORITY_CLASS, nil, nil, start, ProcessInfo) then
  begin  
   repeat  
    Apprunning := WaitForSingleObject(ProcessInfo.hProcess,100);
    ReadFile(ReadPipe,Buffer[0],ReadBuffer,BytesRead,nil);
    Buffer[BytesRead]:= #0;
    OemToAnsi(Buffer,Buffer);
    memo.Lines.Append(Buffer);
    SendMessage(memo.Handle, EM_SCROLLCARET, 0, 0);
    Application.ProcessMessages;
   until (Apprunning <> WAIT_TIMEOUT);
  end
    else
  begin
    memo.Lines.Append('Не является внутренней или внешней командой, исполняемой программой или пакетным файлом.');
    SendMessage(memo.Handle, EM_SCROLLCARET, 0, 0); 
  end;
  FreeMem(Buffer);
  CloseHandle(ProcessInfo.hProcess);
  CloseHandle(ProcessInfo.hThread);
  CloseHandle(ReadPipe);
  CloseHandle(WritePipe);
  end;
end;


procedure T_Console.bCloseClick(Sender: TObject);
begin
 Close;
end;

end.
