{Функция SizeOf(<имя_типа>): Integer - количество байтов, выделяемое
 под переменную типа имя_типа.

 Процедура GetMem(var P: Pointer; Size: Word) - создает в динамической памяти
 переменную, размером Size и передает указатель на нее в переменную P.

 Процедура Move(var Source, Dest; Count: Word) - перемещает значение
 переменной Source в переменную Dest, типы которых совместимы по размеру
 выделяемой памяти.

 Процедура FreeMem(var P: Pointer; Size: Word) - освобождает память, выде-
 ленную под  значение переменной с помощью процедуры GetMem.

 Функция MaxAvail: Longint - возвращает размер максимального блока свободной
 памяти в heap.
  }
  type TStack = ^StackElem;
       StackElem = Record
          TElement: Pointer;
          Next: TStack
       end;
       Stack = Record
          Top: TStack;
          Size: Integer;
       end;
       ElementType = Char;

   var MyStack: Stack;
       Ch: Char;

   procedure InitStack(var S: Stack; ElemSize: Integer);
   begin
      S^.Top:= New(TStack);
      S^.Sise:= ElemSize;
{      GetMem(Top^.TElement, ElemSize);
      Top^.Next:= nil;
      Top^.Size:= ElemSize}
   end;

   procedure ShowStack(S: Stack);
   var P: TStack;
   begin
      P:= S^.Top;
      if P^.Next<>nil then
         repeat
           WriteLn(P^.Element^);
           P:= P^.Next
         until P^.Next=nil
      else WriteLn('Empty')
   end;

   procedure Push(S:TStack; Element);
   var P: TStack;
       Q: Pointer;
   begin
      GetMem(Q, S^.Size);
      Move(Element, Q^, S^.Sise);
      P:= New(TStack);
      P^.Next:= S^.Next;
      P
      S^.Next:= P;
      S

   begin
      InitStack(SizeOf(ElementType), MyStack);
      repeat
         Ch:= ReadKey;
         case Ch of
         P: Push(MyStack, ReadKey)
         end
      until Ch='z';
