// lab6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Функции ----------------------------------------------------------------------------
void ClearScreen();

int main(int argc, char* argv[]) {

  BOOL Flag = 1, FCom;
  char Buffer[100], Path[100];
  DWORD SizePath;
  HANDLE hmFile = NULL, hFile;
  LPVOID AdrFile;
  PIMAGE_DOS_HEADER dosHeader;
  PIMAGE_NT_HEADERS plNTH;

  ClearScreen();

  do {
    SizePath = GetCurrentDirectory(100, Path);
    cout << Path << '>';

    cin >> Buffer;
    ClearScreen();
    FCom = 0;

    if(memcmp(Buffer, "cfmapp-", 7) == 0 && hmFile == NULL) {
      memcpy(Path, Buffer + 7, strlen(Buffer + 7) + 1);
      FCom = 1;
      hFile = CreateFile(Path, GENERIC_READ, 0, NULL, OPEN_EXISTING, NULL, NULL);

      if(hFile != INVALID_HANDLE_VALUE) {
        hmFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

        if(hmFile == 0)
          cout << "Fail." << endl;
        else cout << "Object created. " << hmFile << endl;
      } else cout << "Fail does not exist." << endl;
    }

    if(memcmp(Buffer, "mvoff", 5) == 0 && hmFile != NULL) {
      AdrFile = MapViewOfFile(hmFile, FILE_MAP_READ, 0, 0, NULL);
      FCom = 1;

      if(AdrFile == NULL) cout << "Fail." << endl;
      else cout << "File is mapping. " << AdrFile << endl;
    }

    if(memcmp(Buffer, "list", 4) == 0 && AdrFile != NULL) {
      //      printf("%s\n", AdrFile);
      FCom = 1;
      dosHeader = (PIMAGE_DOS_HEADER)AdrFile;

      if(dosHeader->e_lfarlc >= 0x40) {
        plNTH = (PIMAGE_NT_HEADERS)((PBYTE)dosHeader + dosHeader->e_lfanew);

        if(plNTH->Signature == IMAGE_NT_SIGNATURE) cout << "PE file." << endl;
      }
    }



    if(memcmp(Buffer, "umvoff", 6) == 0 && AdrFile != NULL) {
      FCom = 1;

      if(!UnmapViewOfFile(AdrFile)) cout << "Fail." << endl;
      else {
        AdrFile = NULL;
        cout << "File is unmapping." << endl;
      }
    }

    if(memcmp(Buffer, "clhandl", 7) == 0 && hmFile != NULL) {
      FCom = 1;

      if(CloseHandle(hmFile)) {
        hmFile = NULL;
        cout << "Object deleted." << endl;
      } else cout << "Fail." << endl;

      CloseHandle(hFile);
    }

    //      cout << "" <<  << endl;

    if(memcmp(Buffer, "exit", 4) == 0 && hmFile == NULL) {
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
