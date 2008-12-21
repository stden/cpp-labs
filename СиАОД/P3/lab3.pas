uses BTrees;

var
  T : BTree;
  prefix : string;
begin
  { Запоминаем количество доступной памяти при старте програмы
    (для обнаружения утечек памяти) }
  writeln(' Лабораторная работа №3 ');
  prefix := '**c+ab-d/fe';
  Writeln('Исходное выражение в префиксной форме: ',prefix);
  BuildTree(T,prefix);
  { Должно получиться дерево: }
  {       *        }
  {   *       -    }
  { c   +   d   /  }
  {    a b     f e }
  Assert( T[1] = '*' ); { Вершина дерева }
  Assert( copy(T,2,2) = '*-' );
  Assert( copy(T,4,4) = 'c+d/' );
  Assert( copy(T,8,8) = '  ab  fe' );
  ShowTree(T);
end.
