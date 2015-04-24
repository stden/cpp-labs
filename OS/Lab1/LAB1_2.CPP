// lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Функции ----------------------------------------------------------------------------
void ClearScreen();

// Константы --------------------------------------------------------------------------
const int CDrv = 5;

char TypeDrive[CDrv][50] = {"Removable drive.",
                            "Fixed drive.",
                            "Network drive.",
                            "CD-ROM drive.",
                            "RAM disk."
                           };

int main(int argc, char* argv[]) {
  DWORD Drives, Flg, Type;
  char Name[4];

  char VolumeNameBuffer[100];
  char FileSystemNameBuffer[100];
  unsigned long VolumeSerialNumber;
  BOOL GetVolumeInformationFlag;
  DWORD FreeBytesAvailable;
  DWORD TotalNumberOfBytes;
  DWORD TotalNumberOfFreeBytes;
  BOOL GetDiskFreeSpaceFlag;

  ClearScreen();

  do {
    printf("For drive information press drive letter.\n");
    Drives = GetLogicalDrives();
    printf("Drives:\n");

    for( int i = 0; i < 26; i++ ) {
      Flg = ((Drives >> i) & (DWORD)1);

      if(Flg == (DWORD)1) {
        Name[0] = char(65 + i);
        Name[1] = ':';
        Name[2] = '\\';
        Name[3] = 0;
        printf("%s - ", Name);
        Type = GetDriveType(Name) - 2;

        if(Type >= 0 && Type < CDrv)
          printf("%s\n", TypeDrive[Type]);
        else
          printf("?\n");
      }
    }

    Name[0] = (char)getch();
    ClearScreen();
    printf("Information for drive %s\n", Name);
    GetVolumeInformationFlag = GetVolumeInformationA( Name, VolumeNameBuffer, 100, &VolumeSerialNumber, NULL, NULL, FileSystemNameBuffer, 100 );

    if(GetVolumeInformationFlag != 0) {
      printf(" Volume Name is %s\n", VolumeNameBuffer);
      printf(" Volume Serial Number is %ul\n", VolumeSerialNumber);
      printf(" File System is %s\n", FileSystemNameBuffer);
    }// else printf(" Not Present (GetVolumeInformation)\n");

    GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx( Name, (PULARGE_INTEGER)&FreeBytesAvailable, (PULARGE_INTEGER)&TotalNumberOfBytes, (PULARGE_INTEGER)&TotalNumberOfFreeBytes);

    if(GetDiskFreeSpaceFlag != 0) {
      printf(" Total Number Of Bytes = %ul ( %f Mb )\n", (unsigned long)TotalNumberOfBytes, double(unsigned long(TotalNumberOfBytes)) / 1024 / 1000);
      printf(" Total Number Of Free Bytes = %ul ( %f Mb )\n", (unsigned long)TotalNumberOfFreeBytes, double(unsigned long(TotalNumberOfFreeBytes)) / 1024 / 1000);
    }// else printf(" Not Present (GetDiskSpace)\n");
  } while(Name[0] != 27);

  return 0;
}

void ClearScreen() {
  for(int i = 0; i < 1920; i++) printf(" ");
}

