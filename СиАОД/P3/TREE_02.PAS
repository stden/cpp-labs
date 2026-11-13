{ Повторение задания из примера Tree_01.pas с рекурсивной
  реализацией процедуры построения дерева }

uses Crt;

type Pointer = ^Node;
     Node = record
        Member: integer;
        Left,Right: Pointer
     end;

var Tree: Pointer;
    i: integer;

function ReadN(m:Integer): Integer;
const D: array[1..8] of Integer = (11,4,5,18,9,22,1,25);
begin
   ReadN:= D[i]
end; {ReadN}

procedure Bild(X: Integer; var P: Pointer);
begin
   if P = nil then begin
      New(P);
      P^.Member:= X; P^.Right:= nil; P^.Left:= nil end
   else
      if X > P^.Member then
         Bild(X, P^.Right)
      else
         Bild(X, P^.Left)
end; {Bild}

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
end.{tree_02}
