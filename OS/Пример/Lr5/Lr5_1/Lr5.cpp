#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {

	int  EndOfProgram = 0; // ����� ��������� ������ ���������
	char ch;

	while (!EndOfProgram) {

		// ������� �����������	
		system("cls");
		printf(" Enter name of file : ");

		// ������ ��� �����
		char FileName[MAX_PATH];
		scanf("%s", FileName);

		// �������� �����
		HANDLE hFile = CreateFile( FileName,
								   GENERIC_READ,
								   0, 0,
								   OPEN_EXISTING,
								   FILE_ATTRIBUTE_NORMAL,
								   0 
								 );
		
		// ��������� �������� ������������ CreateFile
		if (hFile == INVALID_HANDLE_VALUE) {

			// �������� ������ ��� �������� �����
			printf("\n Error! File not found.\n\n ");
			getch();
		} // if hFile
		else {

			// �������� ������ �������, ���������� ���� � ������
			printf("\n File successfully opened.\n ");
			getch();
			HANDLE hMapFile = CreateFileMapping( hFile, 0, PAGE_READONLY, 0, 0, 0);

			// ��������� �������� ������������ CreateFileMapping
			if ( (hMapFile != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS) ) { 

				// ������ ��� ����������
				CloseHandle(hMapFile);
				hMapFile = NULL;
				printf("\n Error! Object already exists\n\n ");
				getch();
			} else if (hMapFile == NULL) {

				// ���������� ������� ������������ ������
				printf("\n Could not create file mapping object. ErrorID : %d\n\n ",GetLastError());
			    getch();

			} else {

				// �������� ������ �������
				printf("\n File mapping object successfully created.\n ");
				getch();

				// �������� ������ ��������������� � ������
				LPCTSTR pBuf = (LPTSTR) MapViewOfFile ( hMapFile, FILE_MAP_READ, 0, 0, 0 );

				if (pBuf == NULL) {

					// ��������� ������
					printf("\n Error! Could not map view of file\n\n ");
					getch();
				} 
				else {

					// ������ �� ��������� ������� ���������� ����������
					printf("\n The contents of file ------------------------------------------\n");
					printf("\n %s\n\n ", pBuf);
					printf("---------------------------------------------------------------\n\n ");
					getch();

					//����������� ������ ���������
					printf("Press 'c' to continue and any other key to exit.");
					ch = getch();
					if (ch != 'c') { EndOfProgram = 1; printf("\n\n "); }
					UnmapViewOfFile(hMapFile);
					CloseHandle(hMapFile);
					CloseHandle(hFile);
				} // if/else (pBuf == NULL)
				
			}// else hMapFile

		} // else hFile

	} // while (!EndOfProgram)


}
