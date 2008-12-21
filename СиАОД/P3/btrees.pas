{ Программный модуль, реализующий тип данных "двоичное дерево" }
unit btrees;

interface

type { Дерево, реализованная, как "куча" Heap }
  BTree = string;
  index = integer;

const { Индекс корневого узла }
  RootIdx = 1; { Первый символ строки }
  Operations = ['+','-','*','/']; { Операции }
  Vars = ['a'..'z','A'..'Z']; { Переменные }

{ На входе i - индекс элемента }
{ На выходе - индекс его левого потомка }
function L( i:index ):index;

{ На входе i - индекс элемента }
{ На выходе - индекс его правого потомка }
function R( i:index ):index;

{ Построение дерева для конкретного арифметического выражения,
  заданного в префиксной форме и состоящего из 16-ти символов
  (буквенных символов и символов операций). }
procedure BuildTree( var tree:BTree; prefix:string );

{ Показать дерево на экране }
procedure ShowTree( tree:BTree );

implementation

{ Стек для хранения информации об отрисовке }
type
  PRenderStack = ^TRenderStack;
  TRenderStack = record
    C : char;
    row, col : integer;
    Next : PRenderStack;
  end;

{ Добавление элемента в стек }
procedure StPush( var Stack : PRenderStack; c : char; row,col : Integer );
var El : PRenderStack;
begin
  { Создаём новый элемент }
  new( El );
  El^.c := c;
  El^.row := row;
  El^.col := col;
  { Помещаем его на вершину стека }
  El^.Next := Stack;
  Stack := El;
end;

{ Отчистка стека }


{ Показать дерево на экране }
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
  { Расширяем строку до длины Len }
  procedure FixLen( Len : integer );
  begin
    while Length(tree) < Len do
      tree := tree + ' ';
  end;

  { Построение с символа i в префиксной форме }
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
