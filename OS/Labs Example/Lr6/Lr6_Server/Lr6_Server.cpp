#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <aclapi.h>

// ��������������� �������
int  DisconnectAndReconnect();
int  ConnectToNewClient    ();
void ReadMessage ();
void CloseServer ();

// ������� ������� -----------------------------------------------------
#define CONNECTING_STATE 0
#define READING_STATE 1
#define WRITING_STATE 2

// ��� ������� SetSecurityInfo -----------------------------------------
#define PROTECTED_DACL_SECURITY_INFORMATION 0x80000000L

// ��������� -----------------------------------------------------------
#define PIPE_TIMEOUT 5000
#define BUFSIZE 4096

// ���������� ���������� ------------------------------------------------
HANDLE     hPipe;               // ����������� �����

HANDLE     hEvents[3];          // ������� ������
// 1 - ����������� �������
// 2 - ������ � �����
// 3 - ������ �� ������

bool       PendingIO = FALSE;   // ��������������� ������-���� �������

DWORD      dwState;             // ������ �������

OVERLAPPED oOverlapped[3];      // ��������� OVERLAPPED

TCHAR      chBuffer[BUFSIZE];   // ������ ��� ����������/������� ���������

BOOL       FirstMessage = TRUE; // ������ ���������

// �������� �������
int main() {

  int   Success   = 0;       // ���������� ��� ��� ���� ��������

  DWORD dwEventIndex,        // ������ �������
        dwTransfered,        // ���������� � ���������� �������� �����
        dwToWrite;           // ���-�� ����, ������� ������ ����


  // �������� ���� �������

  for (int i = 0; i < 3; i++) {

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


  // ������� ����������� �����
  hPipe = CreateNamedPipe( "\\\\.\\pipe\\TestPipe",
                           PIPE_ACCESS_DUPLEX |
                           FILE_FLAG_OVERLAPPED | WRITE_DAC,
                           PIPE_TYPE_MESSAGE |
                           PIPE_READMODE_MESSAGE |
                           PIPE_WAIT,
                           1,
                           BUFSIZE * sizeof(TCHAR),
                           BUFSIZE * sizeof(TCHAR),
                           PIPE_TIMEOUT,
                           NULL );

  // ��������� ������ ��� �������� ������
  if (hPipe == INVALID_HANDLE_VALUE) {
    printf("Function <CreateNamedPipe> failed! ErrorID : %d\n ", GetLastError());
    getch();
    return 0;
  } else printf("Server created!\n");

  // ��� ������ �� ����
  SetSecurityInfo(hPipe, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, NULL, NULL, NULL, NULL);


  // ���������� ������ � � ������ ������ ����������� ��������� ������ ���������
  if (!ConnectToNewClient()) {
    CloseServer();
    return 0;
  }

  // ���� ������ �������
  while (1) {

    // ���� ������������ ������-������ �������
    dwEventIndex = WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);

    // ���������� ����� �� ������ ������� ���������������
    dwEventIndex -= WAIT_OBJECT_0;

    // ��������� ���� �� � ��� ����� ����� �������, ���� ���, �� �������� �����������
    if (dwEventIndex < 0 || dwEventIndex > 2) {
      printf("Index of event out of range.\n");
      CloseServer();
      getch();
      return 0;
    }

    // �����-�� �������� ��� �� ���������
    if (PendingIO) {

      // �������� ������ ������������� ��������
      Success = GetOverlappedResult( hPipe, &oOverlapped[dwEventIndex], &dwTransfered, FALSE);

      // � ����������� �� ������� ������� ��������� ������ ��������
      switch(dwState) {

        // ����������� �������� ���������� � ��������
        case CONNECTING_STATE:

          // ������� GetOverlappedResult ��������� �������
          if (!Success) {
            printf("Connection failed! ErrorID : %d.\n", GetLastError());
            CloseServer();
            getch();
            return 0;
          }

          // ����������� ������� ������ �������, ������������� ������ ������� � ������
          printf("System message : Client connected.\n");
          dwState = READING_STATE;
          break;

        // ����������� �������� ������
        case READING_STATE:

          // ������� GetOverlappedResult ��������� ������� ��� ������� ��������� ������� ReadFile (0 ���� ��������)
          if (!Success || dwTransfered == 0) {
            // �������������� ������
            printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

            if (!DisconnectAndReconnect()) {
              CloseServer();
              return 0;
            }

            // ��������� �� ����� �������� �����
            continue;
          }

          // ������������� ������ ������� � ������
          dwState = WRITING_STATE;
          break;

        // ����������� �������� ������
        case WRITING_STATE:

          // ������� GetOverlappedResult ��������� ������� ��� ������� ��������� ������� WriteFile (������ ���� ������� ���� �� ��������� � �����������)
          if (!Success || dwTransfered != dwToWrite) {
            // �������������� ������
            if (DisconnectAndReconnect()) {
              CloseServer();
              return 0;
            }

            printf("\nSystem message : Connection broken, try to reconnect client.\n\n");
            // ��������� �� ����� �������� �����
            continue;
          }

          // ������������� ������ ������� � ������
          dwState = READING_STATE;
          break;

        // ��������� ������ �������, ��������� ������
        default:
          printf("System message : Invalid server state.\n");
          CloseServer();
          getch();
          return 0;

      } // switch(dwState)

    } // if (PendingIO)

    // ���������� ��������
    switch(dwState) {

      // ������ ��������� �� �������
      case READING_STATE:

        // ������ ���������
        Success = ReadFile(hPipe, chBuffer, BUFSIZE * sizeof(TCHAR), &dwTransfered, &oOverlapped[2]);

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

        // ��������� ������, �������������� ������
        printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

        if (!DisconnectAndReconnect()) {
          CloseServer();
          return 0;
        }

        break;

      // �������� ������� ���������
      case WRITING_STATE:

        // ������� ������� ���������� ���������
        if (FirstMessage) {
          printf("%s", chBuffer);
          FirstMessage = 0;
        } else printf("Client : %s\n", chBuffer);

        // ����� ��������� ������������ ���������
        printf("Server : ");
        ReadMessage();

        // ��������� ������ �������, ���� ������� ������� ������ "exit"
        if (!stricmp(chBuffer, "exit")) {
          printf("System message : Server closing...\n");
          CloseServer();
          getch();
          return 1;
        }

        // ������� ������ ���������
        dwToWrite  = (strlen(chBuffer) + 1) * sizeof(TCHAR);

        // �������� ���������
        Success = WriteFile(hPipe, chBuffer, dwToWrite, &dwTransfered, &oOverlapped[1]);

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

        // ��������� ������, �������������� ������
        printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

        if (!DisconnectAndReconnect()) {
          CloseServer();
          return 0;
        }

        break;

      // ��������� ������ �������, ��������� ������
      default:
        printf("System message : Invalid server state.\n");
        CloseServer();
        getch();
        return 0;

    } // switch

  } // while(1)

  return 1;
}

// ��������������� ������� -------------------------------------------------------------------------------------------------------
int DisconnectAndReconnect() {

  // ��������� ������
  if (!DisconnectNamedPipe(hPipe) ) {
    // ��������� ������
    printf("Function <DisconnectNamedPipe> failed! ErrorID : %d.\n", GetLastError());
    getch();
    return 0;
  }

  // �������������� ������
  if (!ConnectToNewClient()) return 0;

  // ���������� ������ ������� ���������
  FirstMessage = 1;

  return 1;

} // DisconnectAndReconnect ------------------------------------------------------------------------------------------------------

// ����������� ������ ������� ----------------------------------------------------------------------------------------------------
int ConnectToNewClient() {

  int Success = 0;

  // ���������� �������
  Success = ConnectNamedPipe(hPipe, &oOverlapped[0]);

  // ���� ������� ������ ��������� ��������, ������ ��� ����������� ���������
  if (Success) {
    printf("Function <ConnectNamedPipe> failed! ErrorID : %d.\n", GetLastError());
    getch();
    return 0;
  }

  // ������� ������ ���������� �������, ������������� ��
  switch (GetLastError()) {

    // ���������� � ��������
    case ERROR_IO_PENDING:
      PendingIO = TRUE;
      dwState = CONNECTING_STATE;
      break;

    // ������ ��� ��������� ������������� �� ����
    case ERROR_PIPE_CONNECTED:
      SetEvent(oOverlapped[0].hEvent);
      printf("System message : Client connected.\n");
      break;

    // �������� ������ �� ����� ����������� �������
    default:
      printf("ConnectNamedPipe failed with %d.\n", GetLastError());
      getch();
      return 0;
      break;
  } // switch (GetLastError())

  // ���� ����������� ���������, �� ������������� ������ ������� � ������
  if (!PendingIO) dwState = READING_STATE;

  return 1;

} // ConnectToNewClient ----------------------------------------------------------------------------------------------------------

// ���������� ������ -------------------------------------------------------------------------------------------------------------
void ReadMessage() {

  int  i = 0;          // ������ �������
  bool EndOfEnter = 0; // ����� ��������� �����
  char ch;             // �������� ������

  while (!EndOfEnter) {
    ch = getc(stdin);  // ������ ������ �� ������������ �����

    switch (ch) {      // � ����������� �� ������� ��������� ��������� ��������
      case 10 :
        EndOfEnter = 1;
        chBuffer[i] = 0;
        break;         // ������ Enter, ��������� ����

      default :
        chBuffer[i] = ch;
        i++;
        break;                   // ������ ����� ������ �������, ���������� �� � ������ s
    } // switch (ch)
  } // while

} // ReadMessage------------------------------------------------------------------------------------------------------------------

// �������� ������� --------------------------------------------------------------------------------------------------------------
void CloseServer() {

  // ��������� �������
  DisconnectNamedPipe(hPipe);
  // ��������� �����
  CloseHandle(hPipe);

} //------------------------------------------------------------------------------------------------------------------------------
