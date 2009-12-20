unit FAbout;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  T_about = class(TForm)
    buttonClose: TButton;
    procedure buttonCloseClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  _about: T_about;

implementation

{$R *.dfm}

procedure T_about.buttonCloseClick(Sender: TObject);
begin
Close;
end;

end.
