program gr7376;
uses U1, Crt;
var memory:LongInt;
Q,Com:Char;
TestList:List;
TestElem    : LTem;         {  ������� ���᪠     }
begin      { ����஢���� }
  memory := MemAvail;
  ClrScr;
  WriteLn('������� ᯨ᮪ ? y/n');
  Q := ReadKey;
  if Q in ['y','Y'] then
    begin
      LtCreate(TestList);
      WriteLn;
      WriteLn('������� :');
      WriteLn('  +  : ��⠢��� ��᫥ ⥪�饣� �������');
      WriteLn('  -  : ������� ⥪�騩 �������');
      WriteLn('  S  : �������� ⥪�騩 �������');
      WriteLn('  =  : �������� ⥪�騩 ������� ��  x');
      WriteLn('  N  : ��३� � ᫥���饬�');
      WriteLn('  P  : ��३� � �।��饬�');
      WriteLn('  <  : ��� �� ��砫�');
      WriteLn('  >  : ��� � �����');
      WriteLn('  E  : ���᮪ �� ����?');
      WriteLn('  F  : ���᮪ �� �����?');
      WriteLn('  [  : ��砫� ���᪠?');
      WriteLn('  ]  : ����� ���᪠?');
      WriteLn('  C  : ������ ���᮪');
      WriteLn('  Q  : �������� �ணࠬ��');
      WriteLn;
      repeat
        LtShow(TestList) ;                      {  �뤠�� ���᮪    }
        WriteLn;
        Write('������� : ');                    {  �ਭ��� �������  }
        Com:= ReadKey; WriteLn(Com);
        case Com of
        '+'    : begin            {��⠢���}
                   TestElem.Value:= ReadKey;
                   WriteLn('��⠢���   ',TestElem.Value);
                   LtInsert(TestList,TestElem);
                 end;

        '-'    : begin            {�������}
                   WriteLn('������� ⥪�騩 �������');
                   LtDelete(TestList);
                 end;
      'S','s'  : begin            {����騩}
                   WriteLn('����騩 �������: ',LtCurrent(TestList));
                 end;
        '='    : begin            {��������}
                   TestElem.Value:= ReadKey;
                   WriteLn('�������� ⥪�騩 ������� �� ',TestElem.Value);
                   LtReplace(TestList,TestElem);
                 end;
        'N','n': begin            {�� ᫥���騩}
                   WriteLn('��३� �� ᫥���騩 �������');
                   LtGoNext(TestList);
                 end;
        'P','p': begin            {�� �।��騩}
                   WriteLn('��३� �� �।��騩 �������');
                   LtGoPrior(TestList);
                 end;
    '<',','    : begin            {� ��砫�}
                   WriteLn('��� � ��砫� ���᪠');
                   LtGoBegin(TestList);
                 end;
    '>','.'    : begin            {� �����}
                   WriteLn('��� � ����� ���᪠');
                   LtGoEnd(TestList);
                 end;
        'E','e':                  {���᮪ �E ����?}
                 if LtNotEmpty(TestList) then
                    WriteLn('���᮪ �� ����')
                 else WriteLn('���᮪ ����');
        'F','f':                  {���᮪ �� �����?}
                 if LtNotFull(TestList)  then
                    WriteLn('���᮪ �� �����')
                 else WriteLn('���᮪ �����');
        '['    :                  {� ��砫�?}
                 if LtAtBegin(TestList) then
                    WriteLn('��砫� ���᪠')
                 else WriteLn('�� ��砫� ���᪠');
        ']'    :                  {� ����?}
                 if LtAtEnd(TestList) then
                    WriteLn('����� ���᪠')
                 else WriteLn('�� ����� ���᪠');
        'C','c': begin            {������ ���᮪}
                    WriteLn('������ ���᮪');
                    LtClear(TestList);
                 end;
        else
           if (Com<>'Q') or (Com<>'q')
           then WriteLn('�訡�筠� �������')
        end
      until ( Com = 'Q' ) or ( Com = 'q' );
      LtClear(TestList);
    {  Dispose(TestList); }
    end;
  Write('����祭� �����: ',memory - MemAvail);
  ReadKey;
end.