program fileman;

uses
  Forms,
  FFileView in 'FFileView.pas' {FileView: TFrame},
  ULogicalDriveUtils in 'ULogicalDriveUtils.pas',
  Functions in 'Functions.pas',
  FFolder in 'FFolder.pas' {_folder},
  FConsole in 'FConsole.pas' {_Console},
  FMove in 'FMove.pas' {_move},
  FMain in 'FMain.pas' {_main},
  FAbout in 'FAbout.pas' {_about};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(T_main, _main);
  Application.CreateForm(T_folder, _folder);
  Application.CreateForm(T_Console, _Console);
  Application.CreateForm(T_move, _move);
  Application.CreateForm(T_about, _about);
  Application.Run;
end.
