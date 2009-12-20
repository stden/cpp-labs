unit FFolder;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  T_folder = class(TForm)
    bCreate: TButton;
    eFolderName: TComboBox;
    procedure bCreateClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  _folder: T_folder;

implementation

uses FMain;

{$R *.dfm}

procedure T_folder.bCreateClick(Sender: TObject);
begin

 if (CreateDirectory(PChar(_main.SelectedView.CurrentDir+eFolderName.Text),nil)) then
 begin
  _main.SelectedView.LoadDir;
  ModalResult:=1;
  Close;
 end
  else
 begin
    MessageDlg('�� ������� ������� �������', mtError, [mbOk],0);
 end;
end;

end.
