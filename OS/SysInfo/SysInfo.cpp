#include <fstream.h>
#include <windows.h>
#include <conio.h>

void main(){
  LPSYSTEM_INFO lpSystemInfo = (LPSYSTEM_INFO) malloc (sizeof(SYSTEM_INFO));  // system information - ���������� � �������				[out]
  GetSystemInfo( //��������� ���������� � �������
    lpSystemInfo  // system information - ���������� � �������				[out]
  );
  cout << "SysInfo.cpp" << endl;
  cout << "����������� ����������" << lpSystemInfo->wProcessorArchitecture << endl;
  /*      WORD wProcessorArchitecture;		// ����������� ����������
      WORD wReserved;
  }
  DWORD dwPageSize;	// ������ �������� ������
  LPVOID lpMinimumApplicationAddress;	// ������ ������� ���������� ��������� ������������
  LPVOID lpMaximumApplicationAddress;	// ������� ������� ���������� ��������� ������������
  DWORD dwActiveProcessorMask;		// ����� ���������� �����������
  DWORD dwNumberOfProcessors;		// ����� �����������
  DWORD dwProcessorType;		// ��� ����������
  DWORD dwAllocationGranularity;		// ������������� �������������� �������� ������
  WORD wProcessorLevel;			// ������� ����������
  WORD wProcessorRevision;		// �������������� ���������� � ����������
*/
  getch();
};  