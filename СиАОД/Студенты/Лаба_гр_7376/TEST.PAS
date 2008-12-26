program gr7376;
uses U1, Crt;
var memory:LongInt;
Q,Com:Char;
TestList:List;
TestElem    : LTem;         {  Элемент Списка     }
begin      { Тестирование }
  memory := MemAvail;
  ClrScr;
  WriteLn('Создать список ? y/n');
  Q := ReadKey;
  if Q in ['y','Y'] then
    begin
      LtCreate(TestList);
      WriteLn;
      WriteLn('Команды :');
      WriteLn('  +  : Вставить после текущего элемента');
      WriteLn('  -  : Удалить текущий элемент');
      WriteLn('  S  : Показать текущий элемент');
      WriteLn('  =  : Заменить текущий элемент на  x');
      WriteLn('  N  : Перейти к следующему');
      WriteLn('  P  : Перейти к предыдущему');
      WriteLn('  <  : Идти на начало');
      WriteLn('  >  : Идти в конец');
      WriteLn('  E  : Список не пуст?');
      WriteLn('  F  : Список не полон?');
      WriteLn('  [  : Начало Списка?');
      WriteLn('  ]  : Конец Списка?');
      WriteLn('  C  : Очистить Список');
      WriteLn('  Q  : Завершить программу');
      WriteLn;
      repeat
        LtShow(TestList) ;                      {  Выдать Список    }
        WriteLn;
        Write('Команда : ');                    {  Принять команду  }
        Com:= ReadKey; WriteLn(Com);
        case Com of
        '+'    : begin            {Вставить}
                   TestElem.Value:= ReadKey;
                   WriteLn('Вставить   ',TestElem.Value);
                   LtInsert(TestList,TestElem);
                 end;

        '-'    : begin            {Удалить}
                   WriteLn('Удалить текущий элемент');
                   LtDelete(TestList);
                 end;
      'S','s'  : begin            {Текущий}
                   WriteLn('Текущий элемент: ',LtCurrent(TestList));
                 end;
        '='    : begin            {Заменить}
                   TestElem.Value:= ReadKey;
                   WriteLn('Заменить текущий элемент на ',TestElem.Value);
                   LtReplace(TestList,TestElem);
                 end;
        'N','n': begin            {На следующий}
                   WriteLn('Перейти на следующий элемент');
                   LtGoNext(TestList);
                 end;
        'P','p': begin            {На предыдущий}
                   WriteLn('Перейти на предыдущий элемент');
                   LtGoPrior(TestList);
                 end;
    '<',','    : begin            {В начало}
                   WriteLn('Идти в начало Списка');
                   LtGoBegin(TestList);
                 end;
    '>','.'    : begin            {В конец}
                   WriteLn('Идти в конец Списка');
                   LtGoEnd(TestList);
                 end;
        'E','e':                  {Список НE пуст?}
                 if LtNotEmpty(TestList) then
                    WriteLn('Список НЕ пуст')
                 else WriteLn('Список пуст');
        'F','f':                  {Список НЕ полон?}
                 if LtNotFull(TestList)  then
                    WriteLn('Список НЕ полон')
                 else WriteLn('Список полон');
        '['    :                  {В начале?}
                 if LtAtBegin(TestList) then
                    WriteLn('Начало Списка')
                 else WriteLn('НЕ начало Списка');
        ']'    :                  {В конце?}
                 if LtAtEnd(TestList) then
                    WriteLn('Конец Списка')
                 else WriteLn('НЕ конец Списка');
        'C','c': begin            {Очистить Список}
                    WriteLn('Очистить Список');
                    LtClear(TestList);
                 end;
        else
           if (Com<>'Q') or (Com<>'q')
           then WriteLn('Ошибочная команда')
        end
      until ( Com = 'Q' ) or ( Com = 'q' );
      LtClear(TestList);
    {  Dispose(TestList); }
    end;
  Write('затрачено памяти: ',memory - MemAvail);
  ReadKey;
end.