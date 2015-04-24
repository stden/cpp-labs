#include <windows.h>
#include <conio.h>
#include <stdio.h>

/**- ����� ���������� � ������� ������---------------------**/
/**/ void PrintMBI       (MEMORY_BASIC_INFORMATION& mbi); /**/
/**/ void PrintMBIType   (MEMORY_BASIC_INFORMATION& mbi); /**/
/**/ void PrintMBIProtect(MEMORY_BASIC_INFORMATION& mbi); /**/
/**--------------------------------------------------------**/

int main() {

  bool EndOfProgram = 0; // ����� ��������� ������ ���������

  char ch;               // ������� �������

  while (!EndOfProgram) {

    // ������� ��������� ����
    system("cls");
    printf("\n Lr N5 : Virtual Memory -----------------------------------------------\n ");
    printf("1. The status of virtual memory, page size and allocation granularity.\n ");
    printf("2. The state of region of memory.\n ");
    printf("3. The allocation/release of a given region of memory.\n ");
    printf("4. Exit.\n\n >");

    // ��������� ������� �������
    ch = getch();

    bool            Ok              = 1   ; // ����� ��������� ����� ������ ���������� � ��������
    PVOID           pvAddress       = NULL, // ��������� ����� �������
                    pvAddressRegion = NULL;
    MEMORY_BASIC_INFORMATION  mbi;                // ��������� ��� ������ � ��� ���������� � �������
    int                       ReserveSize     = 0,    // ������ ������������� ������
                              CommitSize      = 0;    // ������ ���������� ������

    // � ����������� �� ������� ������� ��������� ������ ��������
    switch(ch) {
      // ������ ��, ������ �������� ������, �������������
      case '1' :

        SYSTEM_INFO  siSystemInfo  ;         // ��������� ��� ������ � ��� ���������� � �������
        MEMORYSTATUS msMemoryStatus;         // ��������� ��� ������ � ��� ���������� � ������� ������

        GetSystemInfo     (&siSystemInfo  ); // �������� ���������� � �������
        GlobalMemoryStatus(&msMemoryStatus); // �������� ������ ������

        // ������� ���������� ����������
        // ����� ������ ������������ ��������� ������������, ��������� ��������
        printf("The total size of virtual memory : %10d bytes\n  ", msMemoryStatus.dwTotalVirtual       );
        // ������������������� ��������� ������������ ��������� ������������, ��������� ����������� ��������
        printf("Free virtual memory              : %10d bytes\n  ", msMemoryStatus.dwAvailVirtual       );
        // ������ �������� ������
        printf("Page size                        : %10d bytes\n  ", siSystemInfo.dwPageSize             );
        // ������������� �������������� �������� ��������� ������������
        printf("Allocation granularity           : %10d bytes\n  ", siSystemInfo.dwAllocationGranularity);

        // ���� ������� �� �������
        getch();
        break;

      // ����������� ��������� ��������� �������, ���� ����� ���������� ��� ���� ��������
      case '2' :

        // ��������� �������� - ������� ���������� ��������� �������, ��� ����
        printf("1 - Set address region\n  2 - All regions\n  ");

        // ��������� ������� �������
        ch = getch();

        // � ����������� �� ������� ������� ��������� ������ ��������
        switch(ch) {
          // ����� ���������� ��������� �������
          case '1' :

            // ������ ������ ����� �������
            printf("\n  Enter address of region : 0x");

            // ��������� ���
            scanf("%x", &pvAddress);
            printf("\n  ");

            // �������� ���������� � �������
            Ok = ( VirtualQuery(pvAddress, &mbi, sizeof(mbi)) == sizeof(mbi) );

            // ���� �������� ������ ������� ����������, ���� ���, �� �������� �� ������
            if (Ok) {
              printf("\n  Address      Region size    State      Type       Protect\n  ");
              PrintMBI(mbi);
            } else      printf("Bad memory address.\n  ");

            // ���� ������� �������
            getch();
            break;

          // ������� ���������� � ���� �������� ������
          case '2' :

            // ��������� �������
            printf("\n  Address      Region size    State      Type       Protect\n\n  ");

            // ����
            while (Ok) {

              // �������� ���������� � ������� �� ������ pvAddress
              Ok = ( VirtualQuery(pvAddress, &mbi, sizeof(mbi)) == sizeof(mbi) );

              if (Ok) {
                // ������� ���������� ����������
                PrintMBI(mbi);

                // �������� ����� ��������� �������
                pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
              }// if (Ok)

            }// while (Ok);

            getch();
            break;

          // ������� �������� ��������
          default  :
            printf("\n  Incorrect ID operation!");
            getch();
            break;
        } // switch ch

        break;

      // ���������/������������ ��������� �������
      case '3' :

        // ��������� �������� - �������������� ����� �������� ��� ������� ������ �������
        printf("1 - Automatically\n  2 - Set adress\n\n  ");

        // ������ ��������� ��������
        ch = getch();

        // � ����������� �� ������� ������� ��������� ������ ��������
        switch(ch) {
          // �������������� ������� ��������
          case '1' :

            printf("Address      Region size    State      Type       Protect\n\n  ");
            // ����������� ������ �������� 40��
            pvAddressRegion = VirtualAlloc( NULL, (10 * 4096), MEM_RESERVE, PAGE_READWRITE);

            // �������� ���������� � ����������������� �������
            VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

            // ������� ���������� ����������
            printf("Reserve region :\n  ");
            PrintMBI(mbi);
            getch();

            // �������� ������ ������������������ �������
            VirtualAlloc(pvAddressRegion, 4096, MEM_COMMIT, PAGE_READWRITE);

            // �������� ���������� � ����������������� ������� c ���������� �������
            VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

            // ������� ���������� ����������
            printf("\n  The region with a dedicated memory :\n  ");
            PrintMBI(mbi);
            // �������� ����� ������������������ ������� ��� ���������� ������
            pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
            VirtualQuery(pvAddress, &mbi, sizeof(mbi));
            PrintMBI(mbi);
            getch();

            // ����������� ���������������� ������
            VirtualFree(pvAddressRegion, 0, MEM_RELEASE);
            printf("\n  Region released :\n  ");
            VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
            PrintMBI(mbi);
            getch();
            break;

          // ������� ������ �������
          case '2' :

            // ������ ������ ����� ������
            printf("Enter address of reserve region : 0x");

            // ��������� ���
            scanf("%x", &pvAddress);


            // ���������� ������� ����� �������������
            printf("  Enter size of reserve           : ");

            // ���������
            scanf("%d", &ReserveSize);

            // ����������� ������
            pvAddressRegion = VirtualAlloc( pvAddress, ReserveSize, MEM_RESERVE, PAGE_READWRITE);

            if (pvAddressRegion != NULL) {
              // ���� �������������� ����� ������
              // �������� ���������� � ����������������� �������
              printf("\n  Address      Region size    State      Type       Protect\n\n  ");
              VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

              // ������� ���������� ����������
              printf("Reserve region :\n  ");
              PrintMBI(mbi);
              getch();

              // ������ �� ���� ���������� ������
              printf("\n  Enter size of dedicated memory : ");
              scanf("%d", &CommitSize);

              if (ReserveSize < CommitSize) {

                // ����������� ����� ������ ���������� ������
                printf("\n  Error! Reserve memory size must be greater than dedicated memory size\n  ");

                // ����������� ����������������� ������
                VirtualFree(pvAddressRegion, 0, MEM_RELEASE);

                // ������� � ��� ����������
                printf("\n  Region released :\n  ");
                VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
                PrintMBI(mbi);
                getch();
              } else {
                // �������� ������ ������������������ �������
                VirtualAlloc(pvAddressRegion, CommitSize, MEM_COMMIT, PAGE_READWRITE);

                // �������� ���������� � ����������������� ������� c ���������� �������
                VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

                // ������� ���������� ����������
                printf("\n  The region with a dedicated memory :\n  ");
                PrintMBI(mbi);
                // �������� ����� ������������������ ������� ��� ���������� ������
                pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
                VirtualQuery(pvAddress, &mbi, sizeof(mbi));
                PrintMBI(mbi);
                getch();

                // ����������� ���������������� ������
                VirtualFree(pvAddressRegion, 0, MEM_RELEASE);
                printf("\n  Region released :\n  ");
                VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
                PrintMBI(mbi);
                getch();
              }


            } // if (pvRegionAdress != NULL)
            else {
              // ... � ���� �������� :`(
              printf("\n  Bad memory address!");
              getch();
            }

            break;

          // ������� �������� ��������
          default  :
            printf("Incorrect ID operation!");
            getch();
            break;
        } // switch ch

        break;

      // ����� �� ���������
      case '4' :
        EndOfProgram = 1;
        printf("\n\n ");
        break;

      // ������ ������ �������
      default  :
        printf("Incorrect ID operation\n  ");
        getch();
        break;
    } // switch ch
  } // while
}// End of program

// ����� ���������� � ������� ������ -----------------------------------------------------------------------------------------
void PrintMBI(MEMORY_BASIC_INFORMATION& mbi) {
  // ������� ������� ����� �������
  printf("0x%8X   ", mbi.BaseAddress);

  // ������ �������
  printf("%11d    ", mbi.RegionSize);

  // ������, ��� ������� ������
  switch(mbi.State) {

    // ��������� �������� ������
    case MEM_FREE    :
      printf("FREE       \n  ");
      break;

    // ���������� �� ��, ��� ��� ��������� ��������� ����������� ���������� ������
    case MEM_COMMIT  :
      printf("COMMIT     ");
      PrintMBIType(mbi);
      PrintMBIProtect(mbi);
      break;

    // ������ ��������������
    case MEM_RESERVE :
      printf("RESERVE    ");
      PrintMBIType(mbi);
      PrintMBIProtect(mbi);
      break;
  } // switch (mbi.state)
}

// ����� ���� ������� --------------------------------------------------------------------------------------------------------
void PrintMBIType  (MEMORY_BASIC_INFORMATION& mbi) {
  switch(mbi.Type) {
    // C������� ������� �������� �������������� ������� EXE-����� ��� DLL
    case MEM_IMAGE   :
      printf("IMAGE      ");
      break;

    // C������� ������� �������� �������������� ������� ����� ������
    case MEM_MAPPED  :
      printf("MAPPED     ");
      break;

    // C������� ������� �������� �������� (�� ���� ����������� ������ ���������)
    case MEM_PRIVATE :
      printf("PRIVATE    ");
      break;
  }
}

// ����� ������ ������� ------------------------------------------------------------------------------------------------------
void PrintMBIProtect(MEMORY_BASIC_INFORMATION& mbi) {
  switch(mbi.AllocationProtect) {
    // ����� ������
    case PAGE_READONLY          :
      printf("READ ONLY\n  "         );
      break;

    // ����� ������/������
    case PAGE_READWRITE         :
      printf("READ/WRITE\n  "        );
      break;

    // �������� ������ "����������� ��� ������"
    case PAGE_WRITECOPY         :
      printf("WRITE/COPY\n  "        );
      break;

    // ����� ���������� ����
    case PAGE_EXECUTE           :
      printf("EXECUTE\n  "           );
      break;

    // ����� ������ ������ � ���������� ����
    case PAGE_EXECUTE_READ      :
      printf("EXECUTE/READ\n  "      );
      break;

    // ����� ������/������ ������ � ���������� ����
    case PAGE_EXECUTE_READWRITE :
      printf("EXECUTE/READ/WRITE\n  ");
      break;

    // �������� ������ "����������� ��� ������" � ���������� ����
    case PAGE_EXECUTE_WRITECOPY :
      printf("EXECUTE/WRITE/COPY\n  ");
      break;

    // ��������� ����� ������ � ��������
    case PAGE_NOACCESS          :
      printf("NOACCESS\n  "          );
      break;
  }
}
