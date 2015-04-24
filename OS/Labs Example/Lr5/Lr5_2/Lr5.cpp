#include <stdio.h>
#include <conio.h>
#include <windows.h>

void main() {

  int  EndOfProgram = 0; // Метка окончания работы программы
  char ch;

  while (!EndOfProgram) {

    // Выводим приветствие
    system("cls");
    printf(" Enter name of file : ");

    // Читаем имя файла
    char FileName[MAX_PATH];
    scanf("%s", FileName);

    // Открытие файла
    HANDLE hFile = CreateFile( FileName,
                               GENERIC_WRITE,
                               0, 0,
                               OPEN_EXISTING,
                               FILE_FLAG_OVERLAPPED,
                               0
                             );

    // Проверяем значение возвращенное CreateFile
    if (hFile == INVALID_HANDLE_VALUE) {

      // Возникла ошибка при открытии файла
      printf("\n Error! File not found.\n\n ");
      getch();

    } // if hFile
    else {

      // Открытие прошло успешно
      printf("\n File successfully opened.\n\n ");
      getch();

      // Создаем событие
      HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

      // Заполняем структуру OVERLAPPED
      OVERLAPPED stOverlapped;

      stOverlapped.Offset = 0;
      stOverlapped.OffsetHigh = NULL;
      stOverlapped.hEvent = hEvent;


      // Проверяем создание события
      if (stOverlapped.hEvent == NULL) {

        // Возникла ошибка
        printf("Could not crate event. ErrorID : %d\n", GetLastError());
      } else {

        // Событие создано успешно, продолжаем работу

        char*  Buffer;              // Записываемая в файл строка
        Buffer = new char[50];
        DWORD Writed = 0;           // Количество записанных байт


        // Считываем вводимую строку
        printf("Input string to write in file : ");
        scanf("%s", Buffer);

        // Записываем буффер в файл
        WriteFile(hFile, Buffer, strlen(Buffer), &Writed, &stOverlapped);

        // Получаем информацию об операции
        int success = GetOverlappedResult(hFile, &stOverlapped, &Writed, TRUE);

        // Очищаем уже ненужный буффер
        delete [] Buffer;

        if (!success) {

          // Неудачная запись в файл
          printf("\n Write failed. ErrorID : %d\n\n ", GetLastError());
          getch();
        } else {

          // Удачная запись в файл
          GetOverlappedResult(hFile, &stOverlapped, &Writed, FALSE);
          printf("\n Write success.\n");
          printf(" %d bytes was written\n\n ", Writed);

          //Заканчиваем работу программы
          printf("Press 'c' to continue and any other key to exit.");
          ch = getch();

          if (ch != 'c') {
            EndOfProgram = 1;
            printf("\n\n ");
          }

          CloseHandle(hEvent);
          CloseHandle(hFile);

        } // if (!success)

      } // stOverlapped

    } // else hFile

  } // while (!EndOfProgram)

} // EndOfProgram
