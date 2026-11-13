{
  Вычисление значения выражения X*(A+B)*(D-E/F) при X=5,
  A=10, B=2, D=10, E=8, F=2. Выражение в префиксной
  записи заносится на дерево, преобразуется в постфиксную
  запись и вычисляется с использованием стека из первого
  задания
}
uses Crt, StackM;

type Pointer = ^Node;
     Node = record
        Member: char;
        Left, Right: Pointer
     end;

var i: integer;
    Tree: Pointer;
    MyStack: Stack;

function ReadChar: char;
{ x*(a+b)*(d-e/f) -> * *x+ab-e/f d }
const D: array[1..11] of char = ('*','*','x','+','a','b','-','d','/','e','f');
begin
   ReadChar:= D[i]
end; {ReadChar}

function BildTree: Pointer;
var p: Pointer;
    Ch: char;
begin
   if i <= 11 then begin
      i:= i + 1;
      Ch:= ReadChar;
      New(p); BildTree:= p;
      with p^ do begin
         Member:= Ch;
         if (Ch = '*') or (Ch = '/') or (Ch = '-') or (Ch = '+') then begin
            Left:= BildTree;
            Right:= BildTree  end
         else begin
            Left:= nil;
            Right:= nil
         end{if}
      end{with}
   end{if}
end;{BildTree}

procedure Count(Ch: char);
var R: Element;
procedure Operation(var MyStack: Stack; C: char);
var X,Y: Element;
begin
   X:= Pop(MyStack);
   Y:= Pop(MyStack);
   case C of
      '/': Push(MyStack, Y div X);
      '*': Push(MyStack, Y * X);
      '+': Push(MyStack, Y + X);
      '-': Push(MyStack, Y - X)
   end{case}
end;{Operation}
begin
   case Ch of
      'x': Push(MyStack,5);
      'a': Push(MyStack,10);
      'b': Push(MyStack,2);
      'd': Push(MyStack,10);
      'e': Push(MyStack,8);
      'f': Push(MyStack,2);
      '/': Operation(MyStack,'/');
      '*': Operation(MyStack,'*');
      '+': Operation(MyStack,'+');
      '-': Operation(MyStack,'-')
   end; {case}
   if (Ch = '*') or (Ch = '/') or (Ch = '-') or (Ch = '+') then begin
      R:= Pop(MyStack);
      Write(R,' ');
      Push(MyStack,R)
   end {if}
end; {Count}

procedure WriteTree(p: Pointer);
begin
{  Write(p^.Member,' '); { Префиксная форма }
  if p^.Left <> nil then WriteTree(p^.Left);
{  Write(p^.Member,' '); { Инфиксная форма }
  if p^.Right <> nil then WriteTree(p^.Right);
{  Write(p^.Member,' '); { Постфиксная форма }
  Count(p^.Member)
end;{WriteTree}

begin
   i:= 0;
   Tree:= BildTree;
   ClrScr;
   WriteLn;
   WriteTree(Tree);
end. {Tree_04}
