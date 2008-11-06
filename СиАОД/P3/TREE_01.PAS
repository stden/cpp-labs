{ Пример демонстрирует построение двоичного дерева для
  заданной последовательности чисел, у которого все значения
  чисел в узлах любого левого поддерева меньше значения
  числа в его корне, а правого - больше или равно.
  На примере процедуры SortTree, обеспечивающей вывод
  исходных чисел в порядке возрастания, показано исполь-
  зование рекурсии для обхода дерева }
uses Crt;

type Pointer = ^Node;
     Node = record
        Member: integer;
        Left,Right: Pointer
     end;

var Tree: Pointer;
    i: integer;

function ReadN(m): Integer;
const D: array[1..8] of Integer = (11,4,5,18,9,22,1,25);
begin
   ReadN:= D[m]
end; {ReadN}

procedure Bild(X: Integer; var P: Pointer);
var q,m : Pointer;
    n: Boolean;
begin
   q:= P; n:= false;
   while (q <> nil) do begin
      n:= true; m:= q;
      if q^.Member < X then  q:= q^.Right
                       else  q:= q^.Left
   end;{while}
   New(q); q^.Member:= X; q^.Left:= nil; q^.Right:= nil;
   if n then
      if m^.Member < X then m^.Right:= q
                       else m^.Left:= q
   else P:= q

end;{Bild}

procedure SortTree(p: Pointer);
begin
  if p <> nil then begin
     SortTree(p^.Left);
     Write(p^.Member,' ');
     SortTree(p^.Right)
  end{if}
end;{SortTree}

begin
    ClrScr;
    Tree:= nil;
    for i:= 1 to 8 do begin
      Bild(ReadN(i), Tree)
    end;
    WriteLn;
    SortTree(Tree); ReadLn;
end.{tree_01}
