unit PMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms, 
  Dialogs, StdCtrls;

type
  TPageMain = class(TFrame)
    GroupBox1: TGroupBox;
    labelComputerName: TLabel;
    labelProcessorType: TLabel;
    labelUserName: TLabel;
    GroupBox2: TGroupBox;
    labelMemoryTotalPhys: TLabel;
    Label1: TLabel;
    Label2: TLabel;
    labelMemoryTotalVirtual: TLabel;
  private
    { Private declarations }
  public
    procedure init;
    { Public declarations }
  end;

implementation

{$R *.dfm}

procedure TPageMain.init;
var
  s: TSystemInfo;
  m: TMemoryStatus;
  buffer_size: DWORD;
   p: array[0..255] of char;
begin
  buffer_size := 255;
  GetComputerName(p,buffer_size);
  labelComputerName.Caption := p;
  //CPU Info
  GetSystemInfo(s);

  case s.dwProcessorType of
    386: labelProcessorType.Caption := '80386-совместимый процессор';
    486: labelProcessorType.Caption := '80486-совместимый процессор';
    586: labelProcessorType.Caption := 'Pentium-совместимый процессор';
  else labelProcessorType.Caption := 'Неизвестный процессор ['+IntToStr(s.dwProcessorType)+']';
  end;

  GetUserName(p,buffer_size);
  labelUserName.Caption := p;

  m.dwLength := SizeOf(TMemoryStatus);
  GlobalMemoryStatus(m);
  labelMemoryTotalPhys.Caption := IntToStr(m.dwTotalPhys shr 20 + 1) + ' MB';
  labelMemoryTotalVirtual.Caption := IntToStr(m.dwTotalVirtual shr 20 + 1) + ' MB';
end;

end.
