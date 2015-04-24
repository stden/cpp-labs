//---------------------------------------------------------------------------

#include <windows.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>

int main() {
  // �������� ��� ���������� ---------------------------------------------
  char  ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD dwLen = MAX_COMPUTERNAME_LENGTH + 1;

  GetComputerName(ComputerName, &dwLen);

  printf("1. Computer name and name's length\n\tName   : %s\n\tLength : %i\n\n", ComputerName, dwLen);


  // �������� ���������� � ������� ---------------------------------------
  SYSTEM_INFO siSysInfo;
  GetSystemInfo(&siSysInfo);

  // ������� ���������� ����������
  printf("2. System information\n");

  // ������� ���������� �� ����������� ����������
  switch(siSysInfo.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_INTEL   :
      printf("\tProcessor architecture      : INTEL \n")  ;
      break;

    case PROCESSOR_ARCHITECTURE_MIPS    :
      printf("\tProcessor architecture      : MIPS\n")    ;
      break;

    case PROCESSOR_ARCHITECTURE_ALPHA   :
      printf("\tProcessor architecture      : ALPHA\n")   ;
      break;

    case PROCESSOR_ARCHITECTURE_PPC     :
      printf("\tProcessor architecture      : PPC\n")     ;
      break;

    case PROCESSOR_ARCHITECTURE_UNKNOWN :
      printf("\tProcessor architecture      : UN-KNOWN\n");
      break;
  } // switch

  // ������ �������� ������
  printf("\tPage size                   : %d\n", siSysInfo.dwPageSize);

  // ��������� �� ���������� ��������� ������
  printf("\tMinimum application address : %d\n", siSysInfo.lpMinimumApplicationAddress);

  // ��������� �� ���������� ��������� ������
  printf("\tMaximum application address : %d\n", siSysInfo.lpMaximumApplicationAddress);

  // ���-�� ����������� � �������
  printf("\tNumber of processors        : %d\n", siSysInfo.dwNumberOfProcessors);

  // �����, �������������� ��������� ��������� � ������� �����������
  printf("\tActive processor mask       : %d\n", siSysInfo.dwActiveProcessorMask);

  // ��� ����������
  printf("\tProcessor type              : ");

  switch(siSysInfo.dwProcessorType) {
    case PROCESSOR_INTEL_386     :
      printf("INTEL 386 \n\n")   ;
      break;

    case PROCESSOR_INTEL_486     :
      printf("INTEL 486\n\n")    ;
      break;

    case PROCESSOR_INTEL_PENTIUM :
      printf("INTEL PENTIUM\n\n");
      break;

    case PROCESSOR_MIPS_R4000    :
      printf("MIPS R4000\n\n")   ;
      break;

    case PROCESSOR_ALPHA_21064   :
      printf("ALPHA 21064\n\n")  ;
      break;
  } // switch

  // ���������� ��������� ���������� ����� -------------------------------
  int  n;
  char dd[4];

  // ����� ��������� � ������� ������ ���������� � ���������� Dr
  DWORD Dr = GetLogicalDrives();

  // ������� ��������� ���������� �����
  printf("3. Available disk drives\n\t");




  for ( int i = 0; i < 26; i++ ) {  //26 �������� � ��������� ����
    // �������� ��� � ���������� ������� i
    n = ((Dr >> i) & 0x00000001);

    // ���� ��� ����� 1, ������ ���� ���� � �������
    if( n == 1 ) {
      dd[0] = char (65 + i); // ����� �����
      dd[1] = ':';
      dd[2] = '\\';
      dd[3] = 0;
      printf("%s ", dd);
    } // if
  } // for

  printf("\n\n");


  // ������� ���������� �� ����� �� ��������� ������ ---------------------

  printf("4. Enter the name of disk : ");
  char* Disk_Name = new char [3];

  // ��������� ��������� ����� �����
  scanf("%c", &Disk_Name[0]);
  Disk_Name[1] = ':';
  Disk_Name[2] = '\0';

  // ����������� ���� �����
  UINT Disk_type = GetDriveType(Disk_Name);
  printf("\tDrive type                 : ");

  switch(Disk_type) {
    case 0               :
      printf("Cannot be determined\n")              ;
      break;

    case 1               :
      printf("The root directory does not exist\n") ;
      break;

    case DRIVE_REMOVABLE :
      printf("Flash drive\n")                       ;
      break;

    case DRIVE_FIXED     :
      printf("Hard drive\n")                        ;
      break;

    case DRIVE_REMOTE    :
      printf("Remote (network) drive\n")            ;
      break;

    case DRIVE_CDROM     :
      printf("CD-ROM drive\n")                      ;
      break;

    case DRIVE_RAMDISK   :
      printf("RAM disk\n")                          ;
      break;
  } // switch

  // ���������� ���-�� ���������� ������������� �� �����
  unsigned long SpC, BpS, NoFC, TNoC;
  GetDiskFreeSpace(Disk_Name, &SpC, &BpS, &NoFC, &TNoC);

  // ������� ���������� ����������
  printf("\tFree space of the %s on Mb : %f\n", Disk_Name, (float)SpC * BpS * NoFC / (1024 * 1024));
  delete []Disk_Name;

  // ���� ������� ������� � ������� �� ���������
  getch();

  return 0;
}
//---------------------------------------------------------------------------

