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
var idx : index;
  { ����஥��� � ᨬ���� i � ��䨪᭮� �ଥ }
  procedure Build( node : index );
  begin
    { �����塞 ��ப� �� ����� nodeIdx }
    while Length(T) < node do
      T:=T+' ';
    { �����뢠�� ��।��� ᨬ��� � ��ॢ� }
    T[node] := prefix[idx];
    { ���室�� � ᫥���饬� ᨬ���� � ��ப� }
    idx:=idx+1;
    { �᫨ �� ��ࠡ��뢠�� ������ => ��ந� �ࠢ�� � ����� �����ॢ� }
    if T[node] in Operations then begin
      Build(L(node));
      Build(R(node));
    end;
  end;
begin
  T := '';
  idx := 1;
  Build(1);
end;

{ �뢮� ��ࠦ���� �� �࠭ � �������� �ଥ }
procedure Show( T:BTree; Form:TForm );

procedure S( node:index; parentOp:char );
var Skobki : Boolean;
begin
  if node > Length(T) then exit;
  if T[node] in Operations then begin
    Skobki := (Form = Infix) and (T[node] in Op1) and (parentOp in Op2);
    if Skobki then write('(');
    if Form = Prefix then write(T[node]);
    S(L(node),T[node]);
    if Form = Infix then write(T[node]);
    S(R(node),T[node]);
    if Form = Postfix then write(T[node]);
    if Skobki then write(')');
  end;
  if T[node] in Vars then write(T[node]);
end;
begin
  case Form of
    Infix: write('��䨪᭠� �ଠ: ');
    Prefix: write('��䨪᭠� �ଠ: ');
    Postfix: write('����䨪᭠� �ଠ: ');
  end;
  S(1,' ');
  writeln;
end;

end.
