//---------------------------------------------------------------------------

#include <windows.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>

int main()
{
        // Получаем имя компьютера ---------------------------------------------
        char  ComputerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD dwLen = MAX_COMPUTERNAME_LENGTH + 1;

        GetComputerName(ComputerName, &dwLen);

        printf("1. Computer name and name's length\n\tName   : %s\n\tLength : %i\n\n", ComputerName, dwLen);
       

        // Получаем информацию о системе ---------------------------------------
        SYSTEM_INFO siSysInfo;
        GetSystemInfo(&siSysInfo);

        // Выводим полученную информацию
        printf("2. System information\n");

        // Выводим информацию об архитектуре процессора
        switch(siSysInfo.wProcessorArchitecture) {
                 case PROCESSOR_ARCHITECTURE_INTEL   :
                        printf("\tProcessor architecture      : INTEL \n")  ; break;
                 case PROCESSOR_ARCHITECTURE_MIPS    :
                        printf("\tProcessor architecture      : MIPS\n")    ; break;
                 case PROCESSOR_ARCHITECTURE_ALPHA   :
                        printf("\tProcessor architecture      : ALPHA\n")   ; break;
                 case PROCESSOR_ARCHITECTURE_PPC     :
                        printf("\tProcessor architecture      : PPC\n")     ; break;
                 case PROCESSOR_ARCHITECTURE_UNKNOWN :
                        printf("\tProcessor architecture      : UN-KNOWN\n"); break;
        } // switch

        // Размер страницы памяти
        printf("\tPage size                   : %d\n", siSysInfo.dwPageSize);

        // Указатель на наименьший доступный адресс
        printf("\tMinimum application address : %d\n", siSysInfo.lpMinimumApplicationAddress);

        // Указатель на наибольший доступный адресс
        printf("\tMaximum application address : %d\n", siSysInfo.lpMaximumApplicationAddress);

        // Кол-во процессоров в системе
        printf("\tNumber of processors        : %d\n",siSysInfo.dwNumberOfProcessors);

        // Маска, представляющая множество доступных в системе процессоров
        printf("\tActive processor mask       : %d\n",siSysInfo.dwActiveProcessorMask);

        // Тип процессора
        printf("\tProcessor type              : ");
        switch(siSysInfo.dwProcessorType){
                case PROCESSOR_INTEL_386     :
                        printf("INTEL 386 \n\n")   ; break;
                case PROCESSOR_INTEL_486     :
                        printf("INTEL 486\n\n")    ; break;
                case PROCESSOR_INTEL_PENTIUM :
                        printf("INTEL PENTIUM\n\n"); break;
                case PROCESSOR_MIPS_R4000    :
                        printf("MIPS R4000\n\n")   ; break;
                case PROCESSOR_ALPHA_21064   :
                        printf("ALPHA 21064\n\n")  ; break;
        } // switch

        // Определяем доступные логические диски -------------------------------
        int  n;
        char dd[4];

        // Маску доступных в системе дисков записываем в переменную Dr
        DWORD Dr = GetLogicalDrives();

        // Выводим доступные логические диски
        printf("3. Available disk drives\n\t");
                      
        
        
        
        for ( int i = 0; i < 26; i++ ) {  //26 строчных и прописных букв
                // Выделяем бит с порядковым номером i
                n = ((Dr>>i)&0x00000001);
                // Если бит равен 1, значит диск есть в системе
                if( n == 1 ) {
                        dd[0]=char (65 + i); // Буква диска
                        dd[1] = ':';
                        dd[2] = '\\';
                        dd[3] = 0;
                        printf("%s ", dd);
                } // if
        } // for
        printf("\n\n");   
       

        // Выводим информацию об одном из выбранных дисков ---------------------

        printf("4. Enter the name of disk : ");
        char* Disk_Name = new char [3];

        // Считываем введенную букву диска
        scanf("%c", &Disk_Name[0]);
        Disk_Name[1] = ':';
        Disk_Name[2] = '\0';

        // Опеределяем типа диска
        UINT Disk_type = GetDriveType(Disk_Name);
        printf("\tDrive type                 : ");
        switch(Disk_type) {
                case 0	             :
                        printf("Cannot be determined\n")              ; break;
                case 1               :
                        printf("The root directory does not exist\n") ; break;
                case DRIVE_REMOVABLE :
                        printf("Flash drive\n")                       ; break;
                case DRIVE_FIXED     :
                        printf("Hard drive\n")                        ; break;
                case DRIVE_REMOTE    :
                        printf("Remote (network) drive\n")            ; break;
                case DRIVE_CDROM     :
                        printf("CD-ROM drive\n")                      ; break;
                case DRIVE_RAMDISK   :
                        printf("RAM disk\n")                          ; break;
        } // switch

        // Определяем кол-во свободного простравнства на диске
        unsigned long SpC,BpS,NoFC,TNoC;
        GetDiskFreeSpace(Disk_Name,&SpC,&BpS,&NoFC,&TNoC);

        // Выводим полученную информацию
        printf("\tFree space of the %s on Mb : %f\n",Disk_Name,(float)SpC*BpS*NoFC/(1024*1024));
        delete []Disk_Name;

        // Ждем нажатия клавиши и выходим из программы
        getch();

        return 0;
}
//---------------------------------------------------------------------------

