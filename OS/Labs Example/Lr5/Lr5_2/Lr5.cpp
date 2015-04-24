#include <stdio.h>
#include <conio.h>
#include <windows.h>

void main() {

  int  EndOfProgram = 0; // ����� ��������� ������ ���������
  char ch;

  while (!EndOfProgram) {

    // ������� �����������
    system("cls");
    printf(" Enter name of file : ");

    // ������ ��� �����
    char FileName[MAX_PATH];
    scanf("%s", FileName);

    // �������� �����
    HANDLE hFile = CreateFile( FileName,
                               GENERIC_WRITE,
                               0, 0,
                               OPEN_EXISTING,
                               FILE_FLAG_OVERLAPPED,
                               0
                             );

    // ��������� �������� ������������ CreateFile
    if (hFile == INVALID_HANDLE_VALUE) {

      // �������� ������ ��� �������� �����
      printf("\n Error! File not found.\n\n ");
      getch();

    } // if hFile
    else {

      // �������� ������ �������
      printf("\n File successfully opened.\n\n ");
      getch();

      // ������� �������
      HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

      // ��������� ��������� OVERLAPPED
      OVERLAPPED stOverlapped;

      stOverlapped.Offset = 0;
      stOverlapped.OffsetHigh = NULL;
      stOverlapped.hEvent = hEvent;


      // ��������� �������� �������
      if (stOverlapped.hEvent == NULL) {

        // �������� ������
        printf("Could not crate event. ErrorID : %d\n", GetLastError());
      } else {

        // ������� ������� �������, ���������� ������

        char*  Buffer;              // ������������ � ���� ������
        Buffer = new char[50];
        DWORD Writed = 0;           // ���������� ���������� ����


        // ��������� �������� ������
        printf("Input string to write in file : ");
        scanf("%s", Buffer);

        // ���������� ������ � ����
        WriteFile(hFile, Buffer, strlen(Buffer), &Writed, &stOverlapped);

        // �������� ���������� �� ��������
        int success = GetOverlappedResult(hFile, &stOverlapped, &Writed, TRUE);

        // ������� ��� �������� ������
        delete [] Buffer;

        if (!success) {

          // ��������� ������ � ����
          printf("\n Write failed. ErrorID : %d\n\n ", GetLastError());
          getch();
        } else {

          // ������� ������ � ����
          GetOverlappedResult(hFile, &stOverlapped, &Writed, FALSE);
          printf("\n Write success.\n");
          printf(" %d bytes was written\n\n ", Writed);

          //����������� ������ ���������
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
