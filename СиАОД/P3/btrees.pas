{ �ணࠬ��� �����, ॠ�����騩 ⨯ ������ "����筮� ��ॢ�" }
unit btrees;

interface

type { ��ॢ�, ॠ����������, ��� "���" Heap }
  BTree = string;
  index = integer;

const { ������ ��୥���� 㧫� }
  RootIdx = 1; { ���� ᨬ��� ��ப� }
  Operations = ['+','-','*','/']; { ����樨 }
  Op1 = ['+','-']; { ����樨 � �ਮ��⮬ 1 }
  Op2 = ['*','/']; { ����樨 � �ਮ��⮬ 2 (����� ��᮪�� �ਮ��⮬) }
  Vars = ['a'..'z','A'..'Z']; { ��६���� }

{ �� �室� i - ������ ����� }
{ �� ��室� - ������ ��� ������ ��⮬�� }
function L( i:index ):index;

{ �� �室� i - ������ ����� }
{ �� ��室� - ������ ��� �ࠢ��� ��⮬�� }
function R( i:index ):index;

{ ����஥��� ��ॢ� ��� �����⭮�� ��䬥��᪮�� ��ࠦ����,
  ��������� � ��䨪᭮� �ଥ � ����饣� �� 16-� ᨬ�����
  (�㪢����� ᨬ����� � ᨬ����� ����権). }
procedure BuildTree( var T:BTree; prefix:string );

{ �������� ��ॢ� �� �࠭� }
procedure ShowTree( T:BTree );

type { ���� �।�⠢����� ��⥬���᪨� ��ࠦ���� }
  TForm = (Infix,Prefix,Postfix);

{ �뢮� ��ࠦ���� �� �࠭ � �������� �ଥ }
procedure Show( T:BTree; Form:TForm );

implementation

{ �⥪ ��� �࠭���� ���ଠ樨 �� ���ᮢ�� }
type
  PRenderStack = ^TRenderStack;
  TRenderStack = record
    C : char;
    row, col : integer;
    Next : PRenderStack;
  end;

{ ���������� ����� � �⥪ }
procedure StPush( var Stack : PRenderStack; c : char; row,col : Integer );
var El : PRenderStack;
begin
  { ������ ���� ����� }
  new( El );
  El^.c := c;
  El^.row := row;
  El^.col := col;
  { ����頥� ��� �� ���設� �⥪� }
  El^.Next := Stack;
  Stack := El;
end;

{ ����⪠ �⥪� }


{ �������� ��ॢ� �� �࠭� }
procedure ShowTree( T:BTree );
  { �뢮� N �஡���� }
  procedure Spaces( N:integer );
  var i:integer;
  begin
    for i:=1 to N do write(' ');
  end;
var i,k,q,S,Last:integer;
begin
  { �饬 ��������� �⥯��� 2-�� ������� ���� ࠢ��� �������� 㧫�� }
  S:=1;
  while S < Length(T) do S:=S*2;
  { ����塞 ����� }
  K := S div 2 - 1;
  i := 1;
  while i < S do begin
    Spaces(K);
    Last := 2*i-1;
    if Last > Length(T) then
      Last := Length(T);
    for q:=i to Last-1 do begin
      write(T[q]);
      Spaces(2*K+1);
    end;
    writeln(T[Last]);
    k := k div 2;
    i := i*2;
  end;
end;

function L( i:index ):index;
begin
  L := i*2;
end;

function R( i:index ):index;
begin
  R := i*2+1;
end;

procedure BuildTree( var T:BTree; prefix:string );
var i : index;
  { ����஥��� � ᨬ���� i � ��䨪᭮� �ଥ }
  procedure Build( node : index );
  begin
    { �����塞 ��ப� �� ����� nodeIdx }
    while Length(T) < node do
      T:=T+' ';
    { �����뢠�� ��।��� ᨬ��� � ��ॢ� }
    T[node] := prefix[i];
    { ���室�� � ᫥���饬� ᨬ���� � ��ப� }
    i:=i+1;
    { �᫨ �� ��ࠡ��뢠�� ������ => ��ந� �ࠢ�� � ����� �����ॢ� }
    if T[node] in Operations then begin
      Build(L(node));
      Build(R(node));
    end;
  end;
begin
  T := '';
  i := 1;
  Build(1);
end;

{ ����祭�� ��ࠦ���� � ��।������� �ଥ }
function GetForm( T:BTree; Form:TForm ):string;

function S( i:index; parentOp:char ):string;
var Left,Right : string;
begin
  if i > Length(T) then begin
    S := '';
    exit;
  end;
  Left := S(L(i),T[i]);
  Right := S(R(i),T[i]);
  if T[i] in Operations then begin
    case Form of
      Infix: begin
        if (T[i] in Op1) and (parentOp in Op2) then
          S := '(' + Left + T[i] + Right + ')'
        else
          S := Left + T[i] + Right;
      end;
      Prefix: S := T[i] + Left + Right;
      Postfix: S := Left + Right + T[i];
    end;
  end else
    if T[i] in Vars then S:=T[i];
end;
begin
  GetForm := S(1,' ');
end;

{ �뢮� ��ࠦ���� �� �࠭ � �������� �ଥ }
procedure Show( T:BTree; Form:TForm );
begin
  case Form of
    Infix: write('��䨪᭠� �ଠ: ');
    Prefix: write('��䨪᭠� �ଠ: ');
    Postfix: write('����䨪᭠� �ଠ: ');
  end;
  writeln(GetForm(T,Form));
end;

end.
