// lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream.h>
#include <conio.h>
#include <windows.h>

// ������� ----------------------------------------------------------------------------
void ClearScreen();

int main(int argc, char* argv[]) {
  BOOL Flag = 1, FCom;
  char Buffer[100], Path[100];
  DWORD SizePath;

  ClearScreen();

  do {
    SizePath = GetCurrentDirectory(100, Path);
    cout << Path << '>';

    cin >> Buffer;
    ClearScreen();
    FCom = 0;

    if(memcmp(Buffer, "windir", 6) == 0) {
      GetWindowsDirectory(Path, 100);
      FCom = 1;
      cout << "Windows directory is " << Path << endl;
    }

    if(memcmp(Buffer, "sysdir", 6) == 0) {
      GetSystemDirectory(Path, 100);
      FCom = 1;
      cout << "System directory is " << Path << endl;
    }

    if(memcmp(Buffer, "cd-", 3) == 0) {
      memcpy(Path, Buffer + 3, strlen(Buffer + 3) + 1);
      FCom = 1;

      if(SetCurrentDirectory(Path))
        cout << "Ok." << endl;
      else cout << "Invalid path." << endl;
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
