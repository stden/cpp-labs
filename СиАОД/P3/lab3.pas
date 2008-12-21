uses BTrees;

var
  T : BTree;
  prefix : string;
begin
  { ���������� ������⢮ ����㯭�� ����� �� ���� �ணࠬ�
    (��� �����㦥��� ��祪 �����) }
  writeln(' ������ୠ� ࠡ�� �3 ');
  prefix := '**c+ab-d/fe';
  Writeln('��室��� ��ࠦ���� � ��䨪᭮� �ଥ: ',prefix);
  BuildTree(T,prefix);
  { ������ ��������� ��ॢ�: }
  {       *        }
  {   *       -    }
  { c   +   d   /  }
  {    a b     f e }
  Assert( T[1] = '*' ); { ���設� ��ॢ� }
  Assert( copy(T,2,2) = '*-' );
  Assert( copy(T,4,4) = 'c+d/' );
  Assert( copy(T,8,8) = '  ab  fe' );
  ShowTree(T);
end.
