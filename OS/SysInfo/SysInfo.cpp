#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void main(){
  LPSYSTEM_INFO lpSystemInfo = (LPSYSTEM_INFO) malloc (sizeof(SYSTEM_INFO));  // system information - информация о системе				[out]
  GetSystemInfo( //Получение информации о системе
    lpSystemInfo  // system information - информация о системе				[out]
  );
  cout << "SysInfo.cpp" << endl;
  char buf[256];
  CharToOem("Архитектура процессора ",buf);
  cout << buf << lpSystemInfo->wProcessorArchitecture << endl; // архитектура процессора
  CharToOem("Размер страницы памяти ",buf);
  cout << buf << lpSystemInfo->dwPageSize;	// размер страницы памяти
/* И так далее выводим остальные параметры...

LPVOID lpMinimumApplicationAddress;	// нижняя граница доступного адресного пространства
  LPVOID lpMaximumApplicationAddress;	// верхняя граница доступного адресного пространства
  DWORD dwActiveProcessorMask;		// маска активности процессоров
  DWORD dwNumberOfProcessors;		// число процессоров
  DWORD dwProcessorType;		// тип процессора
  DWORD dwAllocationGranularity;		// гранулярность резервирования регионов памяти
  WORD wProcessorLevel;			// уровень процессора
  WORD wProcessorRevision;		// дополнительная информация о процессоре
*/
  getch();
};  