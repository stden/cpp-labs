const N = 100;    { Максимальный размер таблицы с элементами }
                  { типа Person                              }
type NameString = string[10];  { Имя объекта в таблице }
     TreeType = (TName, TAge); { Тип дерева поиска }
     Person = record               { Тип "Персона" характеризует объект }
        Name: NameString;          { по имени (Name), по возрасту (Age),}
        Age,Height,Weight: integer;{по росту (Height) и по весу (Weight)}
     end;
     Index = 1..N;
     PersonsFile = array[Index] of Person;

     PointerN = ^NameNode;
     NameNode = record
        Name: NameString;    {Тип, определяющий узел дерева        }
        MyIndex: integer;    {поиска по ключу "Имя" (поле Name в   }
        Left,Right: PointerN {таблице MyFile (см. ниже)            }
     end;

     PointerA = ^AgeNode;
     AgeNode = record        {Тип, определяющий узел дерева        }
        Age: integer;        {поиска по ключу "Возраст" (поле Age в}
        MyIndex: integer;    {таблице MyFile (см. ниже)            }
        Left,Right: PointerA
     end;

var Count: Index;
    MyFile: PersonsFile;     { Массив персон }
    NameTree: PointerN;      { Дерево поиска по именам }
    AgeTree: PointerA;       { Дерево поиска по возрасту }

{ Вспомогательная процедура, инициализирующая значения в таблице
  MyFile}
procedure InitFile;
const ExamplNames: array[1..7] of NameString = ('Маша','Саша',
           'Юля','Петя','Коля','Вася','Даша');
      ExamplAges: array[1..7] of integer = (10,5,7,14,8,16,11);
      ExamplHeight: array[1..7] of integer = (15,8,9,48,9,54,32);
      ExamplWeight: array[1..7] of integer = (100,96,98,154,95,168,125);
begin
   for count:= 1 to 7 do
      with MyFile[count] do begin
         Name:= ExamplNames[count];
         Age:= ExamplAges[count];
         Height:= ExamplHeight[count];
         Weight:= ExamplWeight[count]
      end
end;

{Процедура построения  дерева  поиска по ключу "Имя" (Name - в таблице
 MyFile. Элемент с именем N, расположенный в таблице MyFile по индексу
 M помещается в соответствующее место заданного дерева (параметр P)}

procedure BildTreeName(var P: PointerN; N: NameString; M: integer);
begin
   if P=nil then begin
      New(P);
      with P^ do begin
         Name:= N; MyIndex:= M; Left:= nil; Right:= nil
      end
   end
   else
      if P^.Name[1] > N[1] then BildTreeName(P^.Left,N,M)
                           else BildTreeName(P^.Right,N,M)
end;

{Процедура построения дерева поиска по ключу "Возраст" (Age - в табли-
 це MyFile.  Элемент с именем N, расположенный в таблице MyFile по ин-
 дексу M помещается в соответствующее место заданного дерева (параметр
 P)}

procedure BildTreeAge(var P: PointerA; N: integer; M: integer);
begin
   if P=nil then begin
      New(P);
      with P^ do begin
         Age:= N; MyIndex:= M; Left:= nil; Right:= nil
      end
   end
   else
      if P^.Age > N then BildTreeAge(P^.Left,N,M)
                    else BildTreeAge(P^.Right,N,M)
end;

procedure WriteTree(Q: pointer; Tree: TreeType);
var P: pointer;
begin
   case Tree of
      TName: P:= PointerN(Q);
      TAge: P:= PointerA(Q);
   end;{case}
   if P <> nil then begin
      WriteTree(P^.Left,Tree);
      WriteLn(MyFile[P^.MyIndex].Name,' ',P^.MyIndex,' ',
                        MyFile[P^.MyIndex].Age);
      WriteTree(P^.Right)
   end
end;

procedure WriteTreeAge(P: PointerA);
begin
   if P <> nil then begin
      WriteTreeAge(P^.Left);
      WriteLn(MyFile[P^.MyIndex].Name,' ',P^.MyIndex,' ',
                        MyFile[P^.MyIndex].Age);
      WriteTreeAge(P^.Right)
   end
end;

begin
   InitFile; NameTree:= nil; AgeTree:= nil;
   for count:= 1 to 7 do begin
      BildTreeName(NameTree,MyFile[count].Name,count);
      BildTreeAge(AgeTree,MyFile[count].Age,count)
   end;
   WriteTree(PointerN(NameTree)); WriteLn;
   WriteTree(TAge); ReadLn
end.
