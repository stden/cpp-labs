program osinfo;

uses
  Forms,
  FMain in 'FMain.pas' {_main},
  FAbout in 'FAbout.pas' {_about},
  PMain in 'PMain.pas' {PageMain: TFrame},
  PLogicalDrives in 'PLogicalDrives.pas' {LogicalDrives: TFrame},
  PProcess in 'PProcess.pas' {PageProcess: TFrame},
  Functions in 'Functions.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(T_main, _main);
  Application.CreateForm(T_about, _about);
  Application.Run;
end.
