#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

void main() {
  LPSYSTEM_INFO lpSystemInfo = (LPSYSTEM_INFO) malloc (sizeof(SYSTEM_INFO));  // system information - ���������� � �������        [out]
  GetSystemInfo( //��������� ���������� � �������
    lpSystemInfo  // system information - ���������� � �������        [out]
  );
  cout << "SysInfo.cpp" << endl;
  char buf[256];
  CharToOem("����������� ���������� ", buf);
  cout << buf << lpSystemInfo->wProcessorArchitecture << endl; // ����������� ����������
  CharToOem("������ �������� ������ ", buf);
  cout << buf << lpSystemInfo->dwPageSize;  // ������ �������� ������
  /* � ��� ����� ������� ��������� ���������...

  LPVOID lpMinimumApplicationAddress; // ������ ������� ���������� ��������� ������������
    LPVOID lpMaximumApplicationAddress; // ������� ������� ���������� ��������� ������������
    DWORD dwActiveProcessorMask;    // ����� ���������� �����������
    DWORD dwNumberOfProcessors;   // ����� �����������
    DWORD dwProcessorType;    // ��� ����������
    DWORD dwAllocationGranularity;    // ������������� �������������� �������� ������
    WORD wProcessorLevel;     // ������� ����������
    WORD wProcessorRevision;    // �������������� ���������� � ����������
  */
  getch();
};