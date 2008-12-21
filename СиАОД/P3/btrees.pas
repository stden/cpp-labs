{ �ணࠬ��� �����, ॠ�����騩 ⨯ ������ "����筮� ��ॢ�" }
unit btrees;

interface

type { ��ॢ�, ॠ����������, ��� "���" Heap }
  BTree = string;
  index = integer;

const { ������ ��୥���� 㧫� }
  RootIdx = 1; { ���� ᨬ��� ��ப� }
  Operations = ['+','-','*','/']; { ����樨 }
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
procedure BuildTree( var tree:BTree; prefix:string );

{ �������� ��ॢ� �� �࠭� }
procedure ShowTree( tree:BTree );

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
procedure ShowTree( tree:BTree );
begin
end;

function L( i:index ):index;
begin
  L := i*2;
end;

function R( i:index ):index;
begin
  R := i*2+1;
end;

procedure BuildTree( var tree:BTree; prefix:string );
  { �����塞 ��ப� �� ����� Len }
  procedure FixLen( Len : integer );
  begin
    while Length(tree) < Len do
      tree := tree + ' ';
  end;

  { ����஥��� � ᨬ���� i � ��䨪᭮� �ଥ }
  procedure Build( i : index; treeIdx : index );
  begin
    if prefix[i] in Operations then
      tree[treeIdx] := prefix[i];

  end;
begin
  tree := '';
  Build(1,1);
end;


end.
