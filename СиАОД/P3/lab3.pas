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
  { ���������� ������⢮ ����㯭�� ����� �� ���� �ணࠬ�
    (��� �����㦥��� ��祪 �����) }
  writeln(' ������ୠ� ࠡ�� �3 ');
  PrefixStr := '**c+ab-d/fe';
  Writeln('��室��� ��ࠦ���� � ��䨪᭮� �ଥ: ',PrefixStr);
  BuildTree(T,PrefixStr);
  { ������ ��������� ��ॢ�: }
  {       *        }
  {   *       -    }
  { c   +   d   /  }
  {    a b     f e }
  Assert( '*', T[1] ); { ���設� ��ॢ� }
  Assert( '*-', copy(T,2,2) );
  Assert( 'c+d/', copy(T,4,4) );
  Assert( '  ab  fe', copy(T,8,8) );
  ShowTree(T);
  Show(T,Infix);
  Show(T,Prefix);
  Show(T,Postfix);
end.


