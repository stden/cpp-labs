uses Crt;

const N = 100;

type NameString = string[10];
    Person = record       { ��� "���ᮭ�" �ࠪ�ਧ�� ��ꥪ� }
       Name: NameString;  { �� ����� (Name), �� ������� (Age),}
       Age,Height,Weight: integer;
    end;                  {�� ���� (Height) � �� ���� (Weight)}
    Index = 1..N;
    PersonsFile = array[Index] of Person;
    IndexType = (NameIndex,AgeIndex);
    Pointer = ^NameNode;
    NameNode = record
       MyIndex: integer;
       Left,Right: Pointer;
       case IndexTree: IndexType of
            NameIndex: (Name: NameString);
            AgeIndex: (Age: Integer)
    end;

var Count: Index;
    MyFile: PersonsFile;    { ���ᨢ ���ᮭ }
    NameTree: Pointer;      { ��ॢ� ���᪠ �� ����� }
    AgeTree: Pointer;       { ��ॢ� ���᪠ �� ������� }

procedure InitFile;
const ExamplNames: array[1..7] of NameString = ('���','���',
           '���','����','����','����','���');
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
end;{InitFile}

procedure BildIndex(var P: Pointer; T: IndexType; M: integer; var N);
var
   S: NameString;
   A: integer;
begin
   if P=nil then begin
      New(P);
      with P^ do begin
         MyIndex:= M; Left:= nil; Right:= nil;
         case T of
            NameIndex: Name:= NameString(N);
            AgeIndex: Age:= integer(N)
         end
      end
   end
   else
      case T of
         NameIndex: begin
            S:= NameString(N);
            if P^.Name[1] > S[1] then BildIndex(P^.Left,T,M,N)
                                 else Bildindex(P^.Right,T,M,N)
                    end;
         AgeIndex: begin
            A:= integer(N);
            if P^.Age> A then BildIndex(P^.Left,T,M,N)
                         else BildIndex(P^.Right,T,M,N)
                   end
      end
end;{BildTree}

procedure WriteTree(P: Pointer);
begin
   if P <> nil then begin
      WriteTree(P^.Left);
      WriteLn(MyFile[P^.MyIndex].Name,' ',P^.MyIndex,' ',
                        MyFile[P^.MyIndex].Age);
      WriteTree(P^.Right)
   end
end;{WriteTree}

begin
   ClrScr; InitFile; NameTree:= nil; AgeTree:= nil;
   for count:= 1 to 7 do begin
      BildIndex(NameTree,NameIndex,count,MyFile[count].Name);
      BildIndex(AgeTree,AgeIndex,count,MyFile[count].Age)
   end;
   WriteTree(NameTree); WriteLn;
   WriteTree(AgeTree); ReadLn
end.