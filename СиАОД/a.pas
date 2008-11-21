{ Пример тестирующей программы }
uses u; { Подключаем модуль }

function F( x:double ):string;
var Result : string;
begin
  Str(x:0:2,Result);
  F:= Result;
end;

const
  e = 'i должно быть положительным!';
  eps = 0.0001;
var
  test : integer;
  a,b,c,x1,x2,xx1,xx2 : double;
begin
  { Тестируем функцию вычисления факториала }
  fact(-10000);
  assert( Error = e );
  fact(-1);
  assert( Error = e );
  assert( fact(0) = 0 );
  assert( fact(1) = 1 );
  assert( fact(2) = 2 );
  assert( fact(3) = 6 );
  assert( fact(4) = 6*4 );
  assert( fact(5) = 6*4*5 );

  { Тестируем решение квадратного уравнения }
  { a*(x-x1)*(x-x2) = a*x^2 - a*x1*x - a*x2*x + a*x1*x2 = a*x^2+b*x+c }
  for test:=1 to 100 do begin
    x1 := random(1000);
    x2 := random(1000);
    repeat
      a := random(100)-50;
    until a <> 0;
    b := a*(-x1-x2);
    c := a*x1*x2;
    sort(x1,x2);
    assert( abs(a*x1*x1 + b*x1 + c) < eps );
    assert( abs(a*x2*x2 + b*x2 + c) < eps );
    sq_roots(a,b,c,xx1,xx2);
    assert( abs(x1-xx1) < eps,
      'Ожидалось x1='+F(x1)+' x2='+F(x2)+' возвращено '+F(xx1)+' '+F(xx2) );
    assert( abs(x2-xx2) < eps );
  end;
end.
