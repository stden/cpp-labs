const N = 100;    { ���ᨬ���� ࠧ��� ⠡���� � ������⠬� }
                  { ⨯� Person                              }
type NameString = string[10];  { ��� ��ꥪ� � ⠡��� }
     TreeType = (TName, TAge); { ��� ��ॢ� ���᪠ }
     Person = record               { ��� "���ᮭ�" �ࠪ�ਧ�� ��ꥪ� }
        Name: NameString;          { �� ����� (Name), �� ������� (Age),}
        Age,Height,Weight: integer;{�� ���� (Height) � �� ���� (Weight)}
     end;
     Index = 1..N;
     PersonsFile = array[Index] of Person;

     PointerN = ^NameNode;
     NameNode = record
        Name: NameString;    {���, ��।����騩 㧥� ��ॢ�        }
        MyIndex: integer;    {���᪠ �� ����� "���" (���� Name �   }
        Left,Right: PointerN {⠡��� MyFile (�. ����)            }
     end;

     PointerA = ^AgeNode;
     AgeNode = record        {���, ��।����騩 㧥� ��ॢ�        }
        Age: integer;        {���᪠ �� ����� "������" (���� Age �}
        MyIndex: integer;    {⠡��� MyFile (�. ����)            }
        Left,Right: PointerA
     end;

var Count: Index;
    MyFile: PersonsFile;     { ���ᨢ ���ᮭ }
    NameTree: PointerN;      { ��ॢ� ���᪠ �� ������ }
    AgeTree: PointerA;       { ��ॢ� ���᪠ �� ������� }

{ �ᯮ����⥫쭠� ��楤��, ���樠��������� ���祭�� � ⠡���
  MyFile}
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
end;

{��楤�� ����஥���  ��ॢ�  ���᪠ �� ����� "���" (Name - � ⠡���
 MyFile. ������� � ������ N, �ᯮ������� � ⠡��� MyFile �� �������
 M ����頥��� � ᮮ⢥�����饥 ���� ��������� ��ॢ� (��ࠬ��� P)}

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

{��楤�� ����஥��� ��ॢ� ���᪠ �� ����� "������" (Age - � ⠡��-
 � MyFile.  ������� � ������ N, �ᯮ������� � ⠡��� MyFile �� ��-
 ����� M ����頥��� � ᮮ⢥�����饥 ���� ��������� ��ॢ� (��ࠬ���
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
