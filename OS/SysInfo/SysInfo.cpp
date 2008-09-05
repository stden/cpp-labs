#include <fstream.h>
#include <windows.h>
#include <conio.h>

void main(){
  LPSYSTEM_INFO lpSystemInfo = (LPSYSTEM_INFO) malloc (sizeof(SYSTEM_INFO));  // system information - информаци€ о системе				[out]
  GetSystemInfo( //ѕолучение информации о системе
    lpSystemInfo  // system information - информаци€ о системе				[out]
  );
  cout << "SysInfo.cpp" << endl;
  cout << "јрхитектура процессора" << lpSystemInfo->wProcessorArchitecture << endl;
  /*      WORD wProcessorArchitecture;		// архитектура процессора
      WORD wReserved;
  }
  DWORD dwPageSize;	// размер страницы пам€ти
  LPVOID lpMinimumApplicationAddress;	// нижн€€ граница доступного адресного пространства
  LPVOID lpMaximumApplicationAddress;	// верхн€€ граница доступного адресного пространства
  DWORD dwActiveProcessorMask;		// маска активности процессоров
  DWORD dwNumberOfProcessors;		// число процессоров
  DWORD dwProcessorType;		// тип процессора
  DWORD dwAllocationGranularity;		// гранул€рность резервировани€ регионов пам€ти
  WORD wProcessorLevel;			// уровень процессора
  WORD wProcessorRevision;		// дополнительна€ информаци€ о процессоре
*/
  getch();
};  