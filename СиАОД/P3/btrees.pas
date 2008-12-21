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
procedure BuildTree( var T:BTree; prefix:string );

{ Показать дерево на экране }
procedure ShowTree( T:BTree );

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
procedure ShowTree( T:BTree );
  { Вывод N пробелов }
  procedure Spaces( N:integer );
  var i:integer;
  begin
    for i:=1 to N do write(' ');
  end;
var i,k,q,S,Last:integer;
begin
  { Ищем ближайшую степень 2-ки большую либо равную количеству узлов }
  S:=1;
  while S < Length(T) do S:=S*2;
  { Вычисляем отступ }
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
  { Построение с символа i в префиксной форме }
  procedure Build( treeIdx : index );
  begin
    { Удлиняем строку до длины treeIdx }
    while Length(T) < treeIdx do
      T:=T+' ';
    T[treeIdx] := prefix[idx];
    idx:=idx+1;
    if T[treeIdx] in Operations then begin
      Build(L(treeIdx));
      Build(R(treeIdx));
    end;
  end;
begin
  T := '';
  idx := 1;
  Build(1);
end;


end.
