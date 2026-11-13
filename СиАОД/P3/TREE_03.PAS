{ Построение дерева, соответствующего арифметическому выраже-
  нию, представленному в прямой польской записи [Баррон,
  Рекурсивные методы программирования, стр. 39 - 43]. Процеду-
  ры обхода дерева [Вирт, стр.231] позволяют преобразовать
  исходное выражение в инфиксную форму и предствить в исходном
  виде (префиксная форма)
}
program Tree_3;
uses Crt;

type TypeMember = char;
     Pointer = ^Node;
     Node = record
        Member: TypeMember;
        Right, Left: Pointer;
     end;{Node}

var Tree: Pointer;
    i: integer;

function ReadChar: char;
const G: array[1..11] of char = ('/','*','F','+','A','B','+','C','*','D','E');
begin
   i:= i + 1;
   ReadChar:= G[i]
end;{ReadNumber}

procedure BildTree(var M: Pointer);
var
  C: char;
begin
  if i <= 11 then begin
     C:= ReadChar;
     new(M);
     with M^ do begin
       Member:= C;
       if (C='/') or (C='*') or (C='+') or (C='-') then begin
          BildTree(Left);
          BildTree(Right); end
       else begin
          Left:= nil; Right:= nil;
       end;{if}
     end;{with}
  end;{if}
end;{BiltTree}

procedure InSortTree(R: Pointer);
begin
   if R <> nil then begin
      InSortTree(R^.Left);
      Write(' ',R^.Member);
      InSortTree(R^.Right)
   end;{if}
end;{PrintTree}

procedure PreSortTree(R: Pointer);
begin
   if R <> nil then begin
      Write(' ',R^.Member);
      PreSortTree(R^.Left);
      PreSortTree(R^.Right)
   end;{if}
end;{PrintTree}

procedure PostSortTree(R: Pointer);
begin
   if R <> nil then begin
      PreSortTree(R^.Left);
      PreSortTree(R^.Right);
      Write(' ',R^.Member)
   end;{if}
end;{PrintTree}

begin
   ClrScr;
   i:= 0;
   BildTree(Tree);
   WriteLn;
   InSortTree(Tree);
   ReadLn;
   PreSortTree(Tree);
   ReadLn;
   PostSortTree(Tree);
   ReadLn
end.{tree_03}
