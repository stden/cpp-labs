#include <io.h>
#include <math.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream.h>
#pragma hdrstop
using namespace std;
#if !defined (INVALID_FILE_ATTRIBUTES)
#define INVALID_FILE_ATTRIBUTES ((DWORD)-1)
#endif

char* Rus(const char* text);

// Проверка на существование файла.
bool FileExists (const char* fname);

// вывод времени представленного в DOS формате
void OutDosTime(FILETIME ftTime);

int main() {

  bool EndOfProgram = 0; // Метка завершения программы

  while (!EndOfProgram) {

    // Очищаем экран
    system("cls");

    // Выводим запрос на ввод пути к файлу
    printf("\n Set the path to file or file name in the current directory. \n");

    // Получаем и выводим на экран текущую директорию
    TCHAR s[MAX_PATH];        // Буфер
    int N = MAX_PATH;         // Размер буфера
    GetCurrentDirectory(N, s);
    printf(" Current directory : %s\n", Rus(s));

    // То что нужно для выхода.
    printf(" <Ctrl+C> to exit\n\n >");

    // Считываем введенную пользователем строку
    int  i = 0;          // Индекс
    bool EndOfEnter = 0; // Метка окончания ввода
    char ch;             // Читаемый символ

    while (!EndOfEnter) {
      ch = getc(stdin);  // Читаем символ из стандартного ввода

      switch (ch) {      // В зависимости от символа выполняем следующие действия
        case 10 :
          EndOfEnter = 1;
          s[i] = 0;
          break;         // Нажали Enter, завершаем ввод

        case 27 :
          EndOfEnter = 1;
          EndOfProgram = 1;
          break; // Нажали Escape, выходим из программы

        default :
          s[i] = ch;
          i++;
          break;                   // Нажали любую другую клавишу, записываем ее в строку s
      } // switch (ch)
    } // while (!EndOfEnter)


    // Проверяем существование файла, если он существует, то продолжаем работу с файлом,
    // иначе просим ввести пусть к файлу заново
    if (FileExists(s)) {
      HANDLE hFile;       // Дескриптор файла
      bool EndOfWork = 0; // Метка окончания работы с файлом

      // Открываем файл для чтения
      hFile = CreateFile( s,
                          GENERIC_READ | FILE_WRITE_ATTRIBUTES,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL );

      while (!EndOfWork) {
        system("cls");
        printf("\n Select the operation\n ");
        printf("1. Show file attributes\n ");
        printf("2. File size\n ");
        printf("3. File time\n ");
        printf("4. Set file time\n ");
        printf("5. Choose a new file\n ");
        printf("6. Exit\n\n >");

        int operation_id;
        operation_id = getch();

        switch (operation_id) {
          // Аттрибуты файла
          case '1' :
            DWORD dwFileAttributes;

            // Получаем аттрибуты файла
            dwFileAttributes = GetFileAttributes(s);

            // выводим их на экран в случае успеха
            if (dwFileAttributes == INVALID_FILE_ATTRIBUTES) {
              printf("An error occurred. Invalid file attributes");
              getch();
            } else {
              if (dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE    )
                printf("A file is an archive file\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED )
                printf("A file is compressed.\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_ENCRYPTED  )
                printf("A file is encrypted\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY  )
                printf("The handle that identifies a directory\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_HIDDEN     )
                printf("A file is hidden\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_NORMAL     )
                printf("A file that does not have other attributes set\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_OFFLINE    )
                printf("The data of a file is not available immediately\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_READONLY   )
                printf("A file is read-only\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_SYSTEM     )
                printf("File is part of, or is used exclusively by, the operating system\n  ");

              if (dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY  )
                printf("A file that is being used for temporary storage\n  ");
            }

            getch();
            break;


          // Размер файла
          case '2' :
            DWORD  dwFileSize;  // Размер файла в байтах

            // Получаем размер файла
            dwFileSize = GetFileSize(hFile, NULL);

            // Выводим полученную информацию
            if (dwFileSize == INVALID_FILE_SIZE)
              // Произошла ошибка
              printf("An error occurred. Error ID : %i", GetLastError());
            else
              // Выводим размер файла
              printf("File size : %d bytes", dwFileSize);

            getch();
            break;


          // Показать время файла
          case '3' :
            FILETIME ftCreate,      // Время создания файла (UTC)
                     ftLocalCreate, // -/-/- (локальное)
                     ftAccess,      // Время последнего доступа к файлу
                     ftLocalAccess, // -/-/- (локальное)
                     ftWrite,       // Время последнего изменения файла
                     ftLocalWrite;  // -/-/- (локальное)

            SYSTEMTIME stUTC,   // Универсальное синхронизированное время (UTC)
                       stLocal; // Локальное время

            // Получаем время
            if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {

              printf("File time received a function <FileTimeToSystemTime>\n  ");

              // Время создания файла

              FileTimeToSystemTime(&ftCreate, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date created  : %02d/%02d/%d  %02d:%02d:%02d\n  ",   stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // Время последнего изменения файла
              FileTimeToSystemTime(&ftWrite, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date modified : %02d/%02d/%d  %02d:%02d:%02d\n  ",   stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // Время последнего доступа к файлу
              FileTimeToSystemTime(&ftAccess, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date accessed : %02d/%02d/%d  %02d:%02d:%02d\n\n  ", stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // Выводим время пердставленное в DOS формате
              printf("File time received a function <FileTimeToDosDateTime>\n  ");
              // Время создания файла
              FileTimeToLocalFileTime(&ftCreate, &ftLocalCreate);
              printf("Date created  : ");
              OutDosTime(ftLocalCreate);
              // Время последнего изменения файла
              FileTimeToLocalFileTime(&ftWrite, &ftLocalWrite);
              printf("Date modified : ");
              OutDosTime(ftLocalWrite);
              // Время последнего доступа к файлу
              FileTimeToLocalFileTime(&ftAccess, &ftLocalAccess);
              printf("Date accessed : ");
              OutDosTime(ftLocalAccess);

              getch();
            } else {
              // Произошла ошибка во время получения времени файла
              printf("An error occurred. Error ID : %i", GetLastError());
              getch();
            }

            break;


          // Устанавливаем время файла
          case '4' :
            FILETIME   ftNewCreate; // Новое время создания файла

            SYSTEMTIME stNewCreate; // Новое время создания файла

            printf("For example sets the created time for a file to the current system time\n  ");

            // Получаем текущее время в системе
            GetSystemTime(&stNewCreate);

            // Ковертируем время
            if (SystemTimeToFileTime(&stNewCreate, &ftNewCreate)) {
              // Устанавливаем новое время
              if (SetFileTime(hFile, &ftNewCreate, (LPFILETIME) NULL, (LPFILETIME) NULL))
                printf("Time sets successfully");
              else
                printf("An error occurred (SetFileTime). Error ID : %i", GetLastError);
            } else
              printf("An error occurred (SystemTimeToFileTime). Error ID : %i", GetLastError);


            getch();
            break;


          // Выбираем новый файл
          case '5' :
            CloseHandle(hFile);
            EndOfWork = 1;
            break;


          // Выходим из программы
          case '6' :
            CloseHandle(hFile);
            EndOfWork = 1;
            EndOfProgram = 1;
            printf("\n\n ");
            break;

          // Выбрали неверную операцию
          default  :
            printf("Wrong id operation!");
            getch();
            break;
        }
      } // while !EndOfWork
    } else {
      printf(" The file is not found, try again!");
      getch();
    }

  } // while !EndOfProgram

}


char bufRus[256];
char* Rus(const char* text) {
  CharToOem(text, bufRus);
  return bufRus;
}



bool FileExists(const char* fname) {
  return access(fname, 0) != -1;
}

void OutDosTime(FILETIME ftTime) {
  WORD dFatDate,  // Дата
       dFatTime;  // Время

  if (FileTimeToDosDateTime(&ftTime, &dFatDate, &dFatTime)) {

    int Day    = 0, // День
        Mounth = 0, // Месяц
        Year   = 0, // Год
        i;          // Счетчик

    // Высчитываем день месяца
    for (i = 0; i < 5; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Day    += pow(2, i);

    // Высчитываем месяц
    for (i = 5; i < 9; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Mounth += pow(2, i - 5);

    // Высчитываем год
    for (i = 9; i < 16; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Year   += pow(2, i - 9);

    int Second = 0, // Секунды
        Minute = 0, // Минуты
        Hour   = 0; // Часы

    // Высчитываем секунды
    for (i = 0; i < 5; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Second += pow(2, i);

    // Высчитываем минуты
    for (i = 5; i < 11; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Minute += pow(2, i - 5);

    // Высчитываем часы
    for (i = 11; i < 16; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Hour   += pow(2, i - 11);

    // Выводим на экран информацию
    printf("%02d/%02d/%02d  %02d:%02d:%02d\n  ", Day, Mounth, Year + 1980, Hour, Minute, Second * 2);
  } else
    printf("An error occurred. Error ID : %i\n  ", GetLastError());
}

