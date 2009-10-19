#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
//---------------------------------------------------------------------------
void main()
{
        int N(9);           // ������ ������
        char s[MAX_PATH];    // �����

        // ������ ������� ����������  - ���������� ����� �������� ���������� 
        // � ����� (����� �� ����)
        unsigned int k = GetCurrentDirectory(N,s);
        cout << "1. Current directory is " << s << "\n   Length = " << k <<   
                                                                endl << endl;
        //-------------------------------------------------------------------
        // �������� ���������� Windows - ��� �� ���������� �����
        k = GetWindowsDirectory(s,N);
        cout << "2. Windows directory is " << s << "\n   Length = " << k << 
                                                                endl << endl;
        //-------------------------------------------------------------------
        // ��������� ������� ���������� �� ��������
        cout << "3. Enter the new current directory : ";
        cin  >> s; // ����� ����������
        if ( !SetCurrentDirectory(s) ) {
                // ����� ������ � ������ �������
                cout << "   Could not set new current directory : ErrorID " 
    << GetLastError() << endl;
        	    k = GetCurrentDirectory(N,s);
          cout << "   Current directory is " << s << "\n   Length = " << 
k << "\n\n";}
	  else 
cout << "   The current directory is changed 
successfully\n\n";
        //-------------------------------------------------------------------
        // C������� ����������
        cout << "4. Enter the new creating directory : ";
        cin  >> s; // ����� ����������
        if (!CreateDirectory(s,0))
                 // ����� ������ � ������ �������
		     if (GetLastError() == ERROR_ALREADY_EXISTS)
                        // ���������� ��� ����
                        cout << "   Creating new directory fails : directory
          already exists\n\n";
                 else
      cout << "   Creating new directory fails : ErrorID "
 				  << GetLastError() << endl << endl;
        else
                // ���������� �� ������� �������� ����������
                cout << "      The new directory is created
 successfully\n\n";
        //-------------------------------------------------------------------
        // �������� �����
        cout << "5. Enter the name of new file : ";
        cin  >> s;
        HANDLE h;  // ���������� - ������������� ����� � �������
        h = CreateFile( TEXT(s),          // ���
                        GENERIC_WRITE,    // ������ ������� - ��� ������
                        0,                // 0 - ���������� ������ ��������
                        NULL,             // �������� �� ���������
                        CREATE_ALWAYS,    // ��������� ����, ���� ���� ��� 
// �����, �� ����������������
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
// ����� ���������
                        NULL );          // �� ������������

        if (h == INVALID_HANDLE_VALUE)
                // ����� ������ � ������ �������
          if (GetLastError() == ERROR_FILE_EXISTS)
                	cout << "   Could not create file : file already
      exists\n\n";
                else
                	cout << "   Could not create file : ErrorID " << 
GetLastError() << "\n\n";
        else
                cout <<    New file was created successfully\n\n";
        CloseHandle(h);
        //-------------------------------------------------------------------
        // �����������
        cout << "6. Enter the name of copying file        : ";
        cin  >> s; // ���������� ����
        char d[80];
        cout << "   Enter the name of copy of copyng file : ";
        cin  >> d; // ����� �����
        if (!CopyFile(s,d,true))
                // ����� ������ � ������ �������
    if (GetLastError() == ERROR_FILE_EXISTS)
                	cout << "   Copy fails : file with this name already 
 exists\n\n";
                else
            cout << "   Copy fails : ErrorID " << GetLastError() << 
"\n\n";
        else
                cout << "      The file is copied successfully\n\n";
        //-------------------------------------------------------------------
        // �����������
        cout << "7. Enter the name of moving file     : ";
        cin  >> s; // ������������ ����
        cout << "   Enter the new name of moving file : ";
        cin  >> d;
        if (!MoveFile(s,d))
                // ����� ������ � ������ �������
		    if (GetLastError() == ERROR_FILE_EXISTS)	
                cout << "   Move fails : file/directory with this name 
 already exists in the directory receiver\n\n";
	    else
                cout << "   Move fails : ErrorID " << GetLastError();

        else
                cout << "   The file is moved successfully";

        cout << "\n\nPress any key";
        getch();
}
