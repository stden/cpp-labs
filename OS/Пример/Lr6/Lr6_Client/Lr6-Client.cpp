
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

// ��������������� �������
int  ConnectToServer();
void ReadMessage();

// ������� �������
#define READING_STATE 1 
#define WRITING_STATE 2 

// ���������
#define BUFSIZE 4096
 
// ���������� ����������
HANDLE     hPipe;              // ����������� ����� 

HANDLE     hEvents[2];         // ������� ������
						       // 1 - ������ � �����
					     	   // 2 - ������ �� ������

bool       PendingIO = FALSE;  // ��������������� ������-���� �������

DWORD      dwState,            // ������ �������
		   dwEventIndex,       // ������ �������
		   dwTransfered,       // ���������� � ���������� �������� �����
		   dwToWrite;          // ���-�� ����, ������� ������ ���� 


OVERLAPPED oOverlapped[2];     // ��������� OVERLAPPED

TCHAR      chBuffer[BUFSIZE],  // ������ ��� ����������/������� ���������

		   chPipeName[] = "\\\\COMPUTER-1956EB\\pipe\\TestPipe";  // ��� �������

int        Success   = 0;      // ���������� ��� ��� ���� ��������
	
// �������� �������
int main() {

	// �������� ���� �������
	for (int i=0; i<2; i++) {

		// ������� �������
		hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);

		// ���� �������� ������� ����������� �������, �������� �� ���� � ������� �� ��������
		if (hEvents[i] == NULL) {
			printf("Function <CreateEvent> failed! ErrorID : %d.\n", GetLastError()); 
			getch();
			return 0;
		} // ��������� �������� �������

		// ����������� ������ ��������� OVERLAPPED
		oOverlapped[i].hEvent = hEvents[i];

	} // for

	// ������������ � �������
	printf("Try connect to server...\n");
	if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}

	while(1) {

		// ���� ������������ ������-������ �������
		dwEventIndex = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);

		// ���������� ����� �� ������ ������� ���������������
		dwEventIndex -= WAIT_OBJECT_0;

		// ��������� ���� �� � ��� ����� ����� �������, ���� ���, �� �������� �����������
		if (dwEventIndex < 0 || dwEventIndex > 1) {
			printf("Index of event out of range.\n"); 
			CloseHandle(hPipe);
			getch();
			return 0;
		}

		// �����-�� �������� ��� �� ���������
		if (PendingIO) {

			// �������� ������ ������������� ��������
			Success = GetOverlappedResult( hPipe, &oOverlapped[dwEventIndex], &dwTransfered, FALSE);   
			
			// � ����������� �� ������� ������� ��������� ������ ��������
			switch(dwState) {

				// ����������� �������� ������
				case READING_STATE: 
					// ������� GetOverlappedResult ��������� ������� ��� ������� ��������� ������� ReadFile (0 ���� ��������)
					if (!Success || dwTransfered == 0) { 
						// ��������� ������ �������
						//printf("Function <ReadFile> or <GetOverlappedResult> failed! ErrorID : %d", GetLastError());
						printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
						if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
						continue;
					} 
					// ������������� ������ ������� � ������
					dwState = WRITING_STATE; 
					break; 

				// ����������� �������� ������
				case WRITING_STATE: 
					// ������� GetOverlappedResult ��������� ������� ��� ������� ��������� ������� WriteFile (������ ���� ������� ���� �� ��������� � �����������)
					if (!Success || dwTransfered != dwToWrite) { 
						// ��������� ������ �������
						//printf("Function <WriteFile> failed! ErrorID : %d", GetLastError());
						//CloseHandle(hPipe);
						printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
						if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
						continue;
					} 
					// ������������� ������ ������� � ������
					dwState = READING_STATE; 
					break; 

				// ��������� ������ �������, ��������� ������
				default: 
					printf("System message : Invalid client state.\n"); 
					CloseHandle(hPipe);
					getch();
					return 0;
            
			} // switch(dwState)
		} // if (PendingIO)

		// ���������� ��������
		switch(dwState) {

			// ������ ��������� �� �������
			case READING_STATE: 

				// ������ ���������
				Success = ReadFile(hPipe, chBuffer, BUFSIZE*sizeof(TCHAR), &dwTransfered, &oOverlapped[1]); 
 
				// �������� ������ ����������� �������
				if (Success && dwTransfered != 0) { 
					// ������������� �������� ���
					PendingIO = FALSE; 
					// ������������� ������ ������� � ������
					dwState = WRITING_STATE;
					// ��������� �� ����� �������� �����
					continue; 
				} 
 
				// �������� ������ ��� ��� �����������
				if (!Success && (GetLastError() == ERROR_IO_PENDING)) { 
					// ���� ������������� ��������
					PendingIO = TRUE; 
					// ��������� �� ����� �������� �����
					continue; 
				} 
 
				// ��������� ������, ��������� ������
				//printf("Function <ReadFile> failed! ErrorID : %d", GetLastError());
				//CloseHandle(hPipe);
				printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
				if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
				break; 
			
			// �������� ������� ���������
			case WRITING_STATE: 
				
				// ������� ������� ���������� ���������
				printf("Server : %s\n", chBuffer);
				
				// ����� ��������� ������������ ���������
				printf("Client : ");
				ReadMessage();

				// ��������� ������ �������, ���� ������� ������� ������ "exit"
				if (!stricmp(chBuffer, "exit")) {
					printf("System message : Server closing...\n");
					CloseHandle(hPipe);
					getch();
					return 1;
				}
				
				// ������� ������ ���������
				dwToWrite  = (strlen(chBuffer)+1)*sizeof(TCHAR);

				// �������� ���������
				Success = WriteFile(hPipe, chBuffer, dwToWrite, &dwTransfered, &oOverlapped[0]); 
 
				// �������� ������ ����������� ������
				if (Success && dwTransfered == dwToWrite) { 
					// ������������� �������� ���
					PendingIO = FALSE; 
					// ������������� ������ ������� � ������
					dwState = READING_STATE; 
					// ��������� �� ����� �������� �����
					continue; 
				} 
 
				// �������� ������ ��� �����������
				if (! Success && (GetLastError() == ERROR_IO_PENDING)) { 
					// ���� ������������� ��������
					PendingIO = TRUE;
					// ��������� �� ����� �������� �����
					continue; 
				} 
 
				// ��������� ������, ��������� ������
				//printf("Function <WriteFile> failed! ErrorID : %d", GetLastError());
				//CloseHandle(hPipe);
				printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
				if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
				break;
			// ��������� ������ �������, ��������� ������
			default: 
				printf("System message : Invalid client state.\n"); 
				CloseHandle(hPipe);
				getch();
				return 0;

		} // switch

	} // while (1)
 
   return 1; 
}

// ����������� � ������� ---------------------------------------------------------------------------------------------------------
int  ConnectToServer() {

	// ���� ����������� �����������
	while (1) {
		if (WaitNamedPipe(chPipeName, NMPWAIT_WAIT_FOREVER)) break;
	}

	// �� ������ ������ :)
	CloseHandle(hPipe);

	// ������� �����-������
	hPipe = CreateFile( 
						chPipeName,           // ��� ������
						GENERIC_READ |        // ������ � ������ � ������
						GENERIC_WRITE, 
						0,                    // ��� ����������� �������������
				        NULL,                 // ������� ��������� ������
						OPEN_EXISTING,        // ������� ������������ �����
						FILE_FLAG_OVERLAPPED, // ����������� ����/�����
						NULL );               
 
	// ������� ����������� � ������� 
	if (hPipe != INVALID_HANDLE_VALUE) { 

		// ������� �� ���� ������������
		printf("You connected to server.\n"); 

		// ������ ������ ��������� - ���������� � �������
		// ������� ������ ���������
		dwToWrite  = (strlen("Client's name  : Bovin Alexandr\n")+1)*sizeof(TCHAR);

		// �������� ���������
		WriteFile(hPipe, "Client's name  : Bovin Alexandr\n", dwToWrite, &dwTransfered, &oOverlapped[0]);

		// ������������� ������ ������� � ������
		dwState = WRITING_STATE;

		// ���� ������������� ��������
		PendingIO = TRUE;

		return 1;
	}
	
	// ������� ���� ������ ������� �� ������ - ����� ����� 
	if (GetLastError() != ERROR_PIPE_BUSY) {
		printf("Could not open pipe!\n"); 
		getch();
		return 0;
	}

	return 0;

} // ConnectToServer -------------------------------------------------------------------------------------------------------------

// ���������� ������ -------------------------------------------------------------------------------------------------------------
void ReadMessage() {

	int  i = 0;          // ������ �������
	bool EndOfEnter = 0; // ����� ��������� ����� 
	char ch;             // �������� ������

	while (!EndOfEnter) {  
		ch = getc(stdin);  // ������ ������ �� ������������ �����
		switch (ch) {      // � ����������� �� ������� ��������� ��������� �������� 
			case 10 : EndOfEnter = 1; chBuffer[i] = 0; break;         // ������ Enter, ��������� ����
			default : chBuffer[i] = ch; i++; break;                   // ������ ����� ������ �������, ���������� �� � ������ s
		} // switch (ch)	
	} // while
	
} // ReadMessage------------------------------------------------------------------------------------------------------------------
