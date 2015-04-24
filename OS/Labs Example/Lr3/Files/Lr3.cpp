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

// �������� �� ������������� �����.
bool FileExists (const char* fname);

// ����� ������� ��������������� � DOS �������
void OutDosTime(FILETIME ftTime);

int main() {

  bool EndOfProgram = 0; // ����� ���������� ���������

  while (!EndOfProgram) {

    // ������� �����
    system("cls");

    // ������� ������ �� ���� ���� � �����
    printf("\n Set the path to file or file name in the current directory. \n");

    // �������� � ������� �� ����� ������� ����������
    TCHAR s[MAX_PATH];        // �����
    int N = MAX_PATH;         // ������ ������
    GetCurrentDirectory(N, s);
    printf(" Current directory : %s\n", Rus(s));

    // �� ��� ����� ��� ������.
    printf(" <Ctrl+C> to exit\n\n >");

    // ��������� ��������� ������������� ������
    int  i = 0;          // ������
    bool EndOfEnter = 0; // ����� ��������� �����
    char ch;             // �������� ������

    while (!EndOfEnter) {
      ch = getc(stdin);  // ������ ������ �� ������������ �����

      switch (ch) {      // � ����������� �� ������� ��������� ��������� ��������
        case 10 :
          EndOfEnter = 1;
          s[i] = 0;
          break;         // ������ Enter, ��������� ����

        case 27 :
          EndOfEnter = 1;
          EndOfProgram = 1;
          break; // ������ Escape, ������� �� ���������

        default :
          s[i] = ch;
          i++;
          break;                   // ������ ����� ������ �������, ���������� �� � ������ s
      } // switch (ch)
    } // while (!EndOfEnter)


    // ��������� ������������� �����, ���� �� ����������, �� ���������� ������ � ������,
    // ����� ������ ������ ����� � ����� ������
    if (FileExists(s)) {
      HANDLE hFile;       // ���������� �����
      bool EndOfWork = 0; // ����� ��������� ������ � ������

      // ��������� ���� ��� ������
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
          // ��������� �����
          case '1' :
            DWORD dwFileAttributes;

            // �������� ��������� �����
            dwFileAttributes = GetFileAttributes(s);

            // ������� �� �� ����� � ������ ������
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


          // ������ �����
          case '2' :
            DWORD  dwFileSize;  // ������ ����� � ������

            // �������� ������ �����
            dwFileSize = GetFileSize(hFile, NULL);

            // ������� ���������� ����������
            if (dwFileSize == INVALID_FILE_SIZE)
              // ��������� ������
              printf("An error occurred. Error ID : %i", GetLastError());
            else
              // ������� ������ �����
              printf("File size : %d bytes", dwFileSize);

            getch();
            break;


          // �������� ����� �����
          case '3' :
            FILETIME ftCreate,      // ����� �������� ����� (UTC)
                     ftLocalCreate, // -/-/- (���������)
                     ftAccess,      // ����� ���������� ������� � �����
                     ftLocalAccess, // -/-/- (���������)
                     ftWrite,       // ����� ���������� ��������� �����
                     ftLocalWrite;  // -/-/- (���������)

            SYSTEMTIME stUTC,   // ������������� ������������������ ����� (UTC)
                       stLocal; // ��������� �����

            // �������� �����
            if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {

              printf("File time received a function <FileTimeToSystemTime>\n  ");

              // ����� �������� �����

              FileTimeToSystemTime(&ftCreate, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date created  : %02d/%02d/%d  %02d:%02d:%02d\n  ",   stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // ����� ���������� ��������� �����
              FileTimeToSystemTime(&ftWrite, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date modified : %02d/%02d/%d  %02d:%02d:%02d\n  ",   stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // ����� ���������� ������� � �����
              FileTimeToSystemTime(&ftAccess, &stUTC);
              SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
              printf("Date accessed : %02d/%02d/%d  %02d:%02d:%02d\n\n  ", stLocal.wDay, stLocal.wMonth, stLocal.wYear, stLocal.wHour, stLocal.wMinute, stLocal.wSecond);

              // ������� ����� �������������� � DOS �������
              printf("File time received a function <FileTimeToDosDateTime>\n  ");
              // ����� �������� �����
              FileTimeToLocalFileTime(&ftCreate, &ftLocalCreate);
              printf("Date created  : ");
              OutDosTime(ftLocalCreate);
              // ����� ���������� ��������� �����
              FileTimeToLocalFileTime(&ftWrite, &ftLocalWrite);
              printf("Date modified : ");
              OutDosTime(ftLocalWrite);
              // ����� ���������� ������� � �����
              FileTimeToLocalFileTime(&ftAccess, &ftLocalAccess);
              printf("Date accessed : ");
              OutDosTime(ftLocalAccess);

              getch();
            } else {
              // ��������� ������ �� ����� ��������� ������� �����
              printf("An error occurred. Error ID : %i", GetLastError());
              getch();
            }

            break;


          // ������������� ����� �����
          case '4' :
            FILETIME   ftNewCreate; // ����� ����� �������� �����

            SYSTEMTIME stNewCreate; // ����� ����� �������� �����

            printf("For example sets the created time for a file to the current system time\n  ");

            // �������� ������� ����� � �������
            GetSystemTime(&stNewCreate);

            // ����������� �����
            if (SystemTimeToFileTime(&stNewCreate, &ftNewCreate)) {
              // ������������� ����� �����
              if (SetFileTime(hFile, &ftNewCreate, (LPFILETIME) NULL, (LPFILETIME) NULL))
                printf("Time sets successfully");
              else
                printf("An error occurred (SetFileTime). Error ID : %i", GetLastError);
            } else
              printf("An error occurred (SystemTimeToFileTime). Error ID : %i", GetLastError);


            getch();
            break;


          // �������� ����� ����
          case '5' :
            CloseHandle(hFile);
            EndOfWork = 1;
            break;


          // ������� �� ���������
          case '6' :
            CloseHandle(hFile);
            EndOfWork = 1;
            EndOfProgram = 1;
            printf("\n\n ");
            break;

          // ������� �������� ��������
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
  WORD dFatDate,  // ����
       dFatTime;  // �����

  if (FileTimeToDosDateTime(&ftTime, &dFatDate, &dFatTime)) {

    int Day    = 0, // ����
        Mounth = 0, // �����
        Year   = 0, // ���
        i;          // �������

    // ����������� ���� ������
    for (i = 0; i < 5; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Day    += pow(2, i);

    // ����������� �����
    for (i = 5; i < 9; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Mounth += pow(2, i - 5);

    // ����������� ���
    for (i = 9; i < 16; i++)
      if ( (dFatDate >> i) & 0x00000001 ) Year   += pow(2, i - 9);

    int Second = 0, // �������
        Minute = 0, // ������
        Hour   = 0; // ����

    // ����������� �������
    for (i = 0; i < 5; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Second += pow(2, i);

    // ����������� ������
    for (i = 5; i < 11; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Minute += pow(2, i - 5);

    // ����������� ����
    for (i = 11; i < 16; i++)
      if ( (dFatTime >> i) & 0x00000001 ) Hour   += pow(2, i - 11);

    // ������� �� ����� ����������
    printf("%02d/%02d/%02d  %02d:%02d:%02d\n  ", Day, Mounth, Year + 1980, Hour, Minute, Second * 2);
  } else
    printf("An error occurred. Error ID : %i\n  ", GetLastError());
}

