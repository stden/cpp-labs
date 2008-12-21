uses BTrees;

procedure Assert( e,a : String );
begin
  if e<>a then begin
    writeln('Expected "'+e+'" actual "'+a+'"');
    halt(1);
  end;
end;

var
  T : BTree;
  PrefixStr : string;
begin
  { Запоминаем количество доступной памяти при старте програмы
    (для обнаружения утечек памяти) }
  writeln(' Лабораторная работа №3 ');
  PrefixStr := '**c+ab-d/fe';
  Writeln('Исходное выражение в префиксной форме: ',PrefixStr);
  BuildTree(T,PrefixStr);
  { Должно получиться дерево: }
  {       *        }
  {   *       -    }
  { c   +   d   /  }
  {    a b     f e }
  Assert( '*', T[1] ); { Вершина дерева }
  Assert( '*-', copy(T,2,2) );
  Assert( 'c+d/', copy(T,4,4) );
  Assert( '  ab  fe', copy(T,8,8) );
  ShowTree(T);
  Show(T,Infix);
  Show(T,Prefix);
  Show(T,Postfix);
end.

