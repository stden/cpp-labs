// lab7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <Tlhelp32.h>
#include <windows.h>
#include <conio.h>

// Функции ----------------------------------------------------------------------------
void ClearScreen();

int main(int argc, char* argv[]) {

  BOOL Flag = 1, FCom, Next;
  char Buffer[100], Path[100];
  DWORD SizePath;
  HANDLE hInfP, hInfH;
  PROCESSENTRY32 pe;
  THREADENTRY32 te;

  ClearScreen();

  do {
    SizePath = GetCurrentDirectory(100, Path);
    cout << Path << '>';

    cin >> Buffer;
    ClearScreen();
    FCom = 0;

    if(memcmp(Buffer, "process", 7) == 0) {
      FCom = 1;
      hInfP = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
      pe.dwSize = sizeof(PROCESSENTRY32);
      Next = Process32First(hInfP, &pe);

      while(Next) {
        cout << "File - " << pe.szExeFile << endl;
        cout << "ID of process - " << pe.th32ProcessID << endl;
        cout << "Number of cnt on process - " << pe.cntUsage << endl;
        cout << "Prioretet - " << pe.pcPriClassBase << endl;
        cout << "Parent process - " << pe.th32ParentProcessID << endl;
        getch();
        cout <<  endl;
        pe.dwSize = sizeof(PROCESSENTRY32);
        Next = Process32Next(hInfP, &pe);
      }
    }

    if(memcmp(Buffer, "thread", 6) == 0) {
      FCom = 1;
      hInfH = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, NULL);
      te.cntUsage = 0;
      te.dwFlags = 0;
      te.th32OwnerProcessID = 0;
      te.th32ThreadID = 0;
      te.tpBasePri = 0;
      te.tpDeltaPri = 0;
      te.dwSize = sizeof(THREADENTRY32);
      Next = Thread32First(hInfH, &te);
      cout << GetLastError() << endl;

      while(Next) {
        cout << "ID of thread - " << te.th32ThreadID << endl;
        cout << "Number of cnt on process - " << te.cntUsage << endl;
        cout << "Prioretet (base) - " << te.tpBasePri << endl;
        cout << "Prioretet (delta) - ";

        switch(te.tpDeltaPri) {
          case THREAD_PRIORITY_LOWEST :
            cout << "MIN" << endl;
            break;

          case THREAD_PRIORITY_BELOW_NORMAL :
            cout << "LOWEST+1" << endl;
            break;

          case THREAD_PRIORITY_NORMAL :
            cout << "NORMAL" << endl;
            break;

          case THREAD_PRIORITY_ABOVE_NORMAL :
            cout << "HIGHEST-1" << endl;
            break;

          case THREAD_PRIORITY_ERROR_RETURN :
            cout << "MAXLONG" << endl;
            break;

          case THREAD_PRIORITY_TIME_CRITICAL :
            cout << "LOWPR" << endl;
            break;

          case THREAD_PRIORITY_IDLE :
            cout << "IDLE" << endl;
            break;
        }

        cout << "Owner process - " << te.th32OwnerProcessID << endl;
        getch();
        cout <<  endl;
        te.dwSize = sizeof(THREADENTRY32);
        Next = Thread32Next(hInfH, &te);
      }
    }

    if(memcmp(Buffer, "exit", 4) == 0) {
      Flag = 0;
      FCom = 1;
    }

    if(FCom == 0) cout << "Invalid command." << endl;
  } while(Flag == 1);

  return 0;
}

void ClearScreen() {
  for(unsigned int i = 0; i < 25; i++) cout << endl;
}
