{ ===================================== }
{ === �ᯮ��㥬� �������� ������ === }
{ ===================================== }
type
  DataType = integer; { ��� ������ ����⮢ ������ }
  PElement = ^Element; { �����⥫� �� ����� ������ }
  Element = record { ������� ������ }
    Value : DataType; { ���祭�� ����� ������ }
    i,j : Integer; { ������� ����� }
    Right,Down : PElement; { ��뫪� ��ࠢ� � ���� }
  end;
  Matrix = record { ����� }
    N,M : integer; { ������� ������: N - ���-�� ��ப, M - ���-�� �⮫�殢 }
    Root : Element; { ������� � ���न��⠬� 0,0 }
  end;

{ ================================== }
{ === ��楤��� ࠡ��� � ����묨 === }
{ ================================== }

{ ��楤��: ���樠������ ������ }
{ �室�� ��ࠬ����: }
{   N,M - ࠧ���� (N - ���-�� ��ப, M - ���-�� �⮫�殢 )  }
{ ��室�� ��ࠬ����: }
{   A - ����� (��室��� ��ࠬ��� ��� ����������) }
procedure InitMatrix( var A : Matrix; N,M : integer );
begin
  { ����襬 ࠧ���� ������ }
  A.N := N;
  A.M := M;
  { � �������� ���孨� ���� 䨪⨢�� ����� (� ���न��⠬� 0,0) }
  with A.Root do begin
    Right := nil;
    Down := nil;
    i := 0;
    j := 0;
  end;
end;

{ �஢����, ���� �� 㦥 ����� � ⠪��� ���न��⠬� }
function Find( A : Matrix; i,j : integer ):PElement;
var Cur : PElement;
begin
  Find := nil;
  Cur := @A.Root; { ��稭��� � 㪠��⥫� �� ����� ��ࠢ� }
  while Cur <> nil do begin
    if Cur^.j = j then begin { ��諨 �⮫��� � ������� ����஬ }
      { ⥯��� ��᪠���� �� �⮫��� j �� ��ப� i }
      while Cur <> nil do begin
        if Cur^.i = i then begin { �� ��諨 ����� � �㦭� i,j }
          assert( Cur^.j = j ); { ���������, �� j �ࠢ���� }
          Find := Cur; { �����頥� ����� Cur }
          exit; { ���, ����� �믮�����, ����� ������ }
        end;
        Cur := Cur^.Down;
      end;
      exit; { ��室 �� �㭪樨 }
    end;
    Cur := Cur^.Right;
  end;
end;

{ ���� ���� � ��ப� ��᫥���� ����� � �����ᮬ ����訬 j }
{ �室�� ��ࠬ����: }
{   Start - �����, � ���ண� ��稭��� ���� }
{ ��室�� ��ࠬ����: }
{   �����⥫� �� �।��騩 ����� }
function PrevInRow( Start:PElement; j:integer ):PElement;
var Cur : PElement;
begin
  Cur := Start;
  while Cur^.Right<>nil do begin
    if Cur^.Right^.j > j then break;
    Cur := Cur^.Right;
  end;
  PrevInRow := Cur;
end;

{ ���� ���� � �⮫�� ��᫥���� ����� � �����ᮬ ����訬 i }
{ �室�� ��ࠬ����: }
{   Start - �����, � ���ண� ��稭��� ���� }
{ ��室�� ��ࠬ����: }
{   �����⥫� �� �।��騩 ����� }
function PrevInCol( Start:PElement; i:integer ):PElement;
var Cur : PElement;
begin
  Cur := Start;
  while Cur^.Down<>nil do begin
    if Cur^.Down^.i > i then break;
    Cur := Cur^.Down;
  end;
  PrevInCol := Cur;
end;

{ ���������� ����� }
{  A - ����� }
function Add( var A : Matrix; i,j : integer; Value : DataType ):PElement;
var E,Row,Col,PrevR,PrevD : PElement;
begin
  E := Find(A,i,j);
  if E<>nil then begin { �᫨ ����� 㦥 �������, � �����塞 ���祭�� � ��室�� }
    E^.Value := Value;
    Add := E;
    exit;
  end;
  { ������� �� ������� }
  { ������� ��� }
  new( E );
  Add := E;
  E^.Value := Value;
  E^.i := i;
  E^.j := j;
  E^.Right := nil;
  E^.Down := nil;
  if i=0 then begin { �������� ����� � 0-�� ��ப� - ����� ������ �⮫�殢 }
    { ���� ���� ��᫥���� ����� � �����ᮬ ����訬 j }
    PrevR := PrevInRow(@A.Root,j);
    { ���� ����� ��뫠���� ��ࠢ� �� �, �� �� ��뫠���� �������� }
    E^.Right := PrevR^.Right;
    PrevR^.Right := E;
    exit;
  end;
  if j=0 then begin { �������� ����� � 0-�� �⮫��� - ����� ������ ��ப }
    { ���� ���� ��᫥���� ����� � �����ᮬ ����訬 i }
    PrevD := PrevInCol(@A.Root,i);
    { ���� ����� ��뫠���� ��ࠢ� �� �, �� �� ��뫠���� �������� }
    E^.Down := PrevD^.Down;
    PrevD^.Down := E;
    exit;
  end;
  { ������� - �� ����� }
  assert( (i<>0) and (j<>0) );
  Row := Add(A,i,0,0); { �롨ࠥ� ����� ����� - ��ப�, �� ����室����� ᮧ����� �� }
  Col := Add(A,0,j,0); { �롨ࠥ� ����� ����� - �⮫���, �� ����室����� ᮧ����� �� }
  PrevR := PrevInRow(Row,j);
  PrevD := PrevInCol(Col,i);
  E^.Right := PrevR^.Right;
  E^.Down := PrevD^.Down;
  PrevR^.Right := E;
  PrevD^.Down := E;
end;

{ ������� ���祭�� ����� ������ }
function Get( A : Matrix; i,j : integer ):DataType;
var E : PElement;
begin
  E := Find(A,i,j);
  if E=nil then
    Get := 0
  else
    Get := E^.Value;
end;

{ �뢮� ������ �� �࠭ }
procedure Show( A : Matrix );
var i,j : integer;
begin
  writeln('������� ������: (',A.N,',',A.M,')');
  write('      ');
  for j:=1 to A.M do
    write('[',j:2,']');
  writeln;
  for i:=1 to A.N do begin
    write('[',i:2,'] ');
    for j:=1 to A.M do
      write(Get(A,i,j):4);
    writeln;
  end;
end;

{ ���� ����� � ���������� }
procedure ManualAdd( A : Matrix );
var
  Row,Col : integer;
  Value : DataType;
begin
  writeln('���� ������ ����� � ������ (',A.N,',',A.M,')');
  write('��ப�: '); readln(Row);
  write('�⮫���: '); readln(Col);
  write('���祭��: '); readln(Value);
  Add(A,Row,Col,Value);
end;

{ ����஢���� �㭪権 ࠡ��� � ����栬� }
var
  m : Matrix; { ����� ��� ���஢���� }
  i,j : integer;
begin
  { ������� � ���樠�����㥬 ������ ⠪��� ���祭�ﬨ, �⮡�
    �����஢��� �� ��砨 ��������� �ᯮ������� ����⮢ }
  InitMatrix(m,19,10); { ������ 23 ��ப� � 10 �⮫�殢 }
  { �஢��塞, �� ��� ����� ����� }
  for i:=0 to 19 do
    for j:=0 to 10 do
       assert( Get(m,i,j) = 0 );
  { �����㥬 ����� ������ �⮡�殢 }
  Add(m,0,3,5);
  assert( Get(m,0,3) = 5 );
  Add(m,0,2,6);
  assert( Get(m,0,3) = 5 );
  assert( Get(m,0,2) = 6 );
  { �����㥬 ����� ������ ��ப }
  Add(m,3,0,8);
  assert( Get(m,3,0) = 8 );
  Add(m,1,0,9);
  assert( Get(m,3,0) = 8 );
  assert( Get(m,1,0) = 9 );

  Add(m,4,5,10); { ������塞 ����� 10 � ��ப� 4 �⮫��� 5 }
  assert( Get(m,4,5) = 10 );
  { ������塞 ����� � �����ᥪ��騥�� ��ப� � �⮫��� }
  Add(m,7,6,13);
  assert( Get(m,7,6) = 13 );
  { ������塞 ������ ����, ���, �ࠢ��, ����� }
  Add(m,7-2,6,18);
  assert( Get(m,7-2,6) = 18 );
  Add(m,7+2,6,19);
  assert( Get(m,7+2,6) = 19 );
  Add(m,7,6+2,20);
  assert( Get(m,7,6+2) = 20 );
  Add(m,7,6-2,21);
  assert( Get(m,7,6-2) = 21 );
  { ���� ������ ����� }
  ManualAdd(m);
  { �뢮� ������ �� �࠭ }
  Show(m);
end.
