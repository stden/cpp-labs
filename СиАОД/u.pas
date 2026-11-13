{ Модуль, который будем тестировать }
unit u;

interface { Интерфейсная часть модуля }

var Error : string;

function fact( i: integer ):longint;

procedure sq_roots( a,b,c:double; var x1,x2:double );

procedure sort( var x1,x2 : double );

implementation { Реализация }

function fact( i: integer ):longint;
begin
  if i<0 then begin
    Error := 'i должно быть положительным!';
    exit;
  end;
  Error := '';
  if i<=2 then
    fact := i
  else
    fact := i*fact(i-1);
end;

procedure sq_roots( a,b,c:double; var x1,x2:double );
var D : double;
begin
  assert( a <> 0 );
  D := b*b - 4 * a * c;
  x1 := (-b - sqrt(D)) / (2*a);
  x2 := (-b + sqrt(D)) / (2*a);
  sort( x1, x2 );
end;

procedure sort( var x1,x2 : double );
var temp : double;
begin
  if x1 > x2 then begin
    temp := x1;
    x1 := x2;
    x2 := temp;
  end;
  assert( x1 <= x2 );
end;

begin
  Error := '';
end.