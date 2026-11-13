{ ===================================== }
{ === Используемые структуры данных === }
{ ===================================== }
type
  DataType = integer; { Тип данных элементов матрицы }
  PElement = ^Element; { Указатель на элемент матрицы }
  Element = record { Элемент матрицы }
    Value : DataType; { Значение элемента матрицы }
    i,j : Integer; { Индексы элемента }
    Right,Down : PElement; { Ссылки вправо и вниз }
  end;
  Matrix = record { Матрица }
    N,M : integer; { Размеры матрицы: N - кол-во строк, M - кол-во столбцов }
    Root : Element; { Элемент с координатами 0,0 }
  end;

{ ================================== }
{ === Процедуры работы с данными === }
{ ================================== }

{ Процедура: Инициализация матрицы }
{ Входные параметры: }
{   N,M - размеры (N - кол-во строк, M - кол-во столбцов )  }
{ Выходные параметры: }
{   A - матрица (выходной параметр для заполнения) }
procedure InitMatrix( var A : Matrix; N,M : integer );
begin
  { Запишем размеры матрицы }
  A.N := N;
  A.M := M;
  { И заполним верхний левый фиктивный элемент (с координатами 0,0) }
  with A.Root do begin
    Right := nil;
    Down := nil;
    i := 0;
    j := 0;
  end;
end;

{ Проверяет, есть ли уже элемент с такими координатами }
function Find( A : Matrix; i,j : integer ):PElement;
var Cur : PElement;
begin
  Find := nil;
  Cur := @A.Root; { Начинаем с указателя на элемент вправо }
  while Cur <> nil do begin
    if Cur^.j = j then begin { Нашли столбец с заданным номером }
      { теперь спускаемся по столбцу j до строки i }
      while Cur <> nil do begin
        if Cur^.i = i then begin { Мы нашли элемент с нужным i,j }
          assert( Cur^.j = j ); { Убедились, что j правильный }
          Find := Cur; { Возвращаем элемент Cur }
          exit; { Всё, задача выполнена, элемент найден }
        end;
        Cur := Cur^.Down;
      end;
      exit; { Выход из функции }
    end;
    Cur := Cur^.Right;
  end;
end;

{ Надо найти в строке последний элемент с индексом меньшим j }
{ Входные параметры: }
{   Start - элемент, с которого начинаем поиск }
{ Выходные параметры: }
{   Указатель на предыдущий элемент }
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

{ Надо найти в столбце последний элемент с индексом меньшим i }
{ Входные параметры: }
{   Start - элемент, с которого начинаем поиск }
{ Выходные параметры: }
{   Указатель на предыдущий элемент }
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

{ Добавление элемента }
{  A - матрица }
function Add( var A : Matrix; i,j : integer; Value : DataType ):PElement;
var E,Row,Col,PrevR,PrevD : PElement;
begin
  E := Find(A,i,j);
  if E<>nil then begin { Если элемент уже существует, то заменяем значение и выходим }
    E^.Value := Value;
    Add := E;
    exit;
  end;
  { Элемент не существует }
  { Создаем его }
  new( E );
  Add := E;
  E^.Value := Value;
  E^.i := i;
  E^.j := j;
  E^.Right := nil;
  E^.Down := nil;
  if i=0 then begin { Добавлем элемент в 0-ую строку - опорные элементы столбцов }
    { Надо найти последний элемент с индексом меньшим j }
    PrevR := PrevInRow(@A.Root,j);
    { Новый элемент ссылается вправо на то, на что ссылается найденный }
    E^.Right := PrevR^.Right;
    PrevR^.Right := E;
    exit;
  end;
  if j=0 then begin { Добавлем элемент в 0-ой столбец - опорные элементы строк }
    { Надо найти последний элемент с индексом меньшим i }
    PrevD := PrevInCol(@A.Root,i);
    { Новый элемент ссылается вправо на то, на что ссылается найденный }
    E^.Down := PrevD^.Down;
    PrevD^.Down := E;
    exit;
  end;
  { Элемент - не опорный }
  assert( (i<>0) and (j<>0) );
  Row := Add(A,i,0,0); { Выбираем опорный элемент - строку, при необходимости создавая её }
  Col := Add(A,0,j,0); { Выбираем опорный элемент - столбец, при необходимости создавая её }
  PrevR := PrevInRow(Row,j);
  PrevD := PrevInCol(Col,i);
  E^.Right := PrevR^.Right;
  E^.Down := PrevD^.Down;
  PrevR^.Right := E;
  PrevD^.Down := E;
end;

{ Получить значение элемента матрицы }
function Get( A : Matrix; i,j : integer ):DataType;
var E : PElement;
begin
  E := Find(A,i,j);
  if E=nil then
    Get := 0
  else
    Get := E^.Value;
end;

{ Вывод матрицы на экран }
procedure Show( A : Matrix );
var i,j : integer;
begin
  writeln('Размеры матрицы: (',A.N,',',A.M,')');
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

{ Ввод элемента с клавиатуры }
procedure ManualAdd( A : Matrix );
var
  Row,Col : integer;
  Value : DataType;
begin
  writeln('Ввод нового элемента в матрицу (',A.N,',',A.M,')');
  write('Строка: '); readln(Row);
  write('Столбец: '); readln(Col);
  write('Значение: '); readln(Value);
  Add(A,Row,Col,Value);
end;

{ Тестирование функций работы с матрицами }
var
  m : Matrix; { Матрица для тестирования }
  i,j : integer;
begin
  { Создаем и инициализируем матрицу такими значениями, чтобы
    протестировать все случаи взаимного расположения элементов }
  InitMatrix(m,19,10); { Размер 23 строки и 10 столбцов }
  { Проверяем, что вся матрица пустая }
  for i:=0 to 19 do
    for j:=0 to 10 do
       assert( Get(m,i,j) = 0 );
  { Тестируем опорные элементы стоблцов }
  Add(m,0,3,5);
  assert( Get(m,0,3) = 5 );
  Add(m,0,2,6);
  assert( Get(m,0,3) = 5 );
  assert( Get(m,0,2) = 6 );
  { Тестируем опорные элементы строк }
  Add(m,3,0,8);
  assert( Get(m,3,0) = 8 );
  Add(m,1,0,9);
  assert( Get(m,3,0) = 8 );
  assert( Get(m,1,0) = 9 );

  Add(m,4,5,10); { Добавляем элемент 10 в строку 4 столбец 5 }
  assert( Get(m,4,5) = 10 );
  { Добавляем элемент в непересекающиеся строку и столбец }
  Add(m,7,6,13);
  assert( Get(m,7,6) = 13 );
  { Добавляем элементы ниже, выше, правее, левее }
  Add(m,7-2,6,18);
  assert( Get(m,7-2,6) = 18 );
  Add(m,7+2,6,19);
  assert( Get(m,7+2,6) = 19 );
  Add(m,7,6+2,20);
  assert( Get(m,7,6+2) = 20 );
  Add(m,7,6-2,21);
  assert( Get(m,7,6-2) = 21 );
  { Ввод нового элемента }
  ManualAdd(m);
  { Вывод матрицы на экран }
  Show(m);
end.
