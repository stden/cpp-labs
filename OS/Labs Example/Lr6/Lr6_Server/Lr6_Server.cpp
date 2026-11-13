#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <aclapi.h>

// Вспомогательные функции
int  DisconnectAndReconnect();
int  ConnectToNewClient    ();
void ReadMessage ();
void CloseServer ();

// Статусы сервера -----------------------------------------------------
#define CONNECTING_STATE 0
#define READING_STATE 1
#define WRITING_STATE 2

// Для функции SetSecurityInfo -----------------------------------------
#define PROTECTED_DACL_SECURITY_INFORMATION 0x80000000L

// Константы -----------------------------------------------------------
#define PIPE_TIMEOUT 5000
#define BUFSIZE 4096

// Глобальные переменные ------------------------------------------------
HANDLE     hPipe;               // Именованный канал

HANDLE     hEvents[3];          // События канала
// 1 - подключение клиента
// 2 - запись в канал
// 3 - чтение из канала

bool       PendingIO = FALSE;   // Незавершенность какого-либо события

DWORD      dwState;             // Статус сервера

OVERLAPPED oOverlapped[3];      // Структуры OVERLAPPED

TCHAR      chBuffer[BUFSIZE];   // Буффер для считывания/посылки сообщений

BOOL       FirstMessage = TRUE; // Первое сообщение

// Основная функция
int main() {

  int   Success   = 0;       // Успешность той или иной операции

  DWORD dwEventIndex,        // Индекс события
        dwTransfered,        // Переданные в результате операции байты
        dwToWrite;           // Кол-во байт, которые должны быть


  // Создание трех событий

  for (int i = 0; i < 3; i++) {

    // Создаем событие
    hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);

    // Если создание события завершилось ошибкой, сообщаем об этом и выходим из прораммы
    if (hEvents[i] == NULL) {
      printf("Function <CreateEvent> failed! ErrorID : %d.\n", GetLastError());
      getch();
      return 0;
    } // Неудачное создание события

    // Присваиваем собтие структуре OVERLAPPED
    oOverlapped[i].hEvent = hEvents[i];

  } // for


  // Создаем именованный канал
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

  // Произошла ошибка при создании канала
  if (hPipe == INVALID_HANDLE_VALUE) {
    printf("Function <CreateNamedPipe> failed! ErrorID : %d\n ", GetLastError());
    getch();
    return 0;
  } else printf("Server created!\n");

  // Для работы по сети
  SetSecurityInfo(hPipe, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, NULL, NULL, NULL, NULL);


  // Подключаем клиент и в случае ошибки подключения завершаем работу программы
  if (!ConnectToNewClient()) {
    CloseServer();
    return 0;
  }

  // Цикл работы сервера
  while (1) {

    // Ждем сигнализации какого-нибудь события
    dwEventIndex = WaitForMultipleObjects(3, hEvents, FALSE, INFINITE);

    // Определяем какой по номеру событие сигнализировало
    dwEventIndex -= WAIT_OBJECT_0;

    // Проверяем есть ли у нас такой номер события, если нет, то аварийно закрываемся
    if (dwEventIndex < 0 || dwEventIndex > 2) {
      printf("Index of event out of range.\n");
      CloseServer();
      getch();
      return 0;
    }

    // Какая-то операция еще не завершена
    if (PendingIO) {

      // Получаем статус завершенности операции
      Success = GetOverlappedResult( hPipe, &oOverlapped[dwEventIndex], &dwTransfered, FALSE);

      // В зависимости от статуса сервера выполняем нужное действие
      switch(dwState) {

        // Выполнялась операция соединения с клиентом
        case CONNECTING_STATE:

          // Функция GetOverlappedResult сработала неверно
          if (!Success) {
            printf("Connection failed! ErrorID : %d.\n", GetLastError());
            CloseServer();
            getch();
            return 0;
          }

          // Подключение клиента прошло успешно, устанавливаем статус сервера к чтению
          printf("System message : Client connected.\n");
          dwState = READING_STATE;
          break;

        // Выполнялась операция чтения
        case READING_STATE:

          // Функция GetOverlappedResult сработала неверно или неверно сработала функция ReadFile (0 байт передано)
          if (!Success || dwTransfered == 0) {
            // Переподключаем клиент
            printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

            if (!DisconnectAndReconnect()) {
              CloseServer();
              return 0;
            }

            // Переходим на новую итерацию цикла
            continue;
          }

          // Устанавливаем статус сервера к записи
          dwState = WRITING_STATE;
          break;

        // Выполнялась операция записи
        case WRITING_STATE:

          // Функция GetOverlappedResult сработала неверно или неверно сработала функция WriteFile (должно быть передно байт не совпадает с переданными)
          if (!Success || dwTransfered != dwToWrite) {
            // Переподключаем клиент
            if (DisconnectAndReconnect()) {
              CloseServer();
              return 0;
            }

            printf("\nSystem message : Connection broken, try to reconnect client.\n\n");
            // Переходим на новую итерацию цикла
            continue;
          }

          // Устанавливаем статус сервера к чтению
          dwState = READING_STATE;
          break;

        // Ошибочный статус сервера, завершаем работу
        default:
          printf("System message : Invalid server state.\n");
          CloseServer();
          getch();
          return 0;

      } // switch(dwState)

    } // if (PendingIO)

    // Определяем операцию
    switch(dwState) {

      // Читаем сообщение от клиента
      case READING_STATE:

        // Читаем сообщение
        Success = ReadFile(hPipe, chBuffer, BUFSIZE * sizeof(TCHAR), &dwTransfered, &oOverlapped[2]);

        // Операция чтения завершилась успешно
        if (Success && dwTransfered != 0) {
          // Выполняющихся операций нет
          PendingIO = FALSE;
          // Устанавливаем статус сервера к записи
          dwState = WRITING_STATE;
          // Переходим на новую итерацию цикла
          continue;
        }

        // Операция чтения все еще выполняется
        if (!Success && (GetLastError() == ERROR_IO_PENDING)) {
          // Есть выполняющиеся операции
          PendingIO = TRUE;
          // Переходим на новую итерацию цикла
          continue;
        }

        // Произошла ошибка, переподключаем клиент
        printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

        if (!DisconnectAndReconnect()) {
          CloseServer();
          return 0;
        }

        break;

      // Посылаем клиенту сообщение
      case WRITING_STATE:

        // Сначала выводим полученное сообщение
        if (FirstMessage) {
          printf("%s", chBuffer);
          FirstMessage = 0;
        } else printf("Client : %s\n", chBuffer);

        // Затем считываем пересылаемое сообщение
        printf("Server : ");
        ReadMessage();

        // Завершаем работу сервера, если введена команда выхода "exit"
        if (!stricmp(chBuffer, "exit")) {
          printf("System message : Server closing...\n");
          CloseServer();
          getch();
          return 1;
        }

        // Считаем размер сообщения
        dwToWrite  = (strlen(chBuffer) + 1) * sizeof(TCHAR);

        // Посылаем сообщение
        Success = WriteFile(hPipe, chBuffer, dwToWrite, &dwTransfered, &oOverlapped[1]);

        // Операция записи завершилась удачно
        if (Success && dwTransfered == dwToWrite) {
          // Выполняющихся операций нет
          PendingIO = FALSE;
          // Устанавливаем статус сервера к чтению
          dwState = READING_STATE;
          // Переходим на новую итерацию цикла
          continue;
        }

        // Операция записи еще выполняется
        if (! Success && (GetLastError() == ERROR_IO_PENDING)) {
          // Есть выполняющиеся операции
          PendingIO = TRUE;
          // Переходим на новую итерацию цикла
          continue;
        }

        // Произошла ошибка, переподключаем клиент
        printf("\nSystem message : Connection broken, try to reconnect client.\n\n");

        if (!DisconnectAndReconnect()) {
          CloseServer();
          return 0;
        }

        break;

      // Ошибочный статус сервера, завершаем работу
      default:
        printf("System message : Invalid server state.\n");
        CloseServer();
        getch();
        return 0;

    } // switch

  } // while(1)

  return 1;
}

// Переподключение клиента -------------------------------------------------------------------------------------------------------
int DisconnectAndReconnect() {

  // Отключаем клиент
  if (!DisconnectNamedPipe(hPipe) ) {
    // Произошла ошибка
    printf("Function <DisconnectNamedPipe> failed! ErrorID : %d.\n", GetLastError());
    getch();
    return 0;
  }

  // Переподключаем клиент
  if (!ConnectToNewClient()) return 0;

  // Возвращаем статус первого сообщения
  FirstMessage = 1;

  return 1;

} // DisconnectAndReconnect ------------------------------------------------------------------------------------------------------

// Подключение нового клиента ----------------------------------------------------------------------------------------------------
int ConnectToNewClient() {

  int Success = 0;

  // Подключаем клиента
  Success = ConnectNamedPipe(hPipe, &oOverlapped[0]);

  // Если функция вернет ненулевое значение, значит она неправильно сработала
  if (Success) {
    printf("Function <ConnectNamedPipe> failed! ErrorID : %d.\n", GetLastError());
    getch();
    return 0;
  }

  // Функция должна завершится ошибкой, рассматриваем их
  switch (GetLastError()) {

    // Соединение в процессе
    case ERROR_IO_PENDING:
      PendingIO = TRUE;
      dwState = CONNECTING_STATE;
      break;

    // Клиент уже подключен сигнализируем об этом
    case ERROR_PIPE_CONNECTED:
      SetEvent(oOverlapped[0].hEvent);
      printf("System message : Client connected.\n");
      break;

    // Возникла ошибка во время подключения клиента
    default:
      printf("ConnectNamedPipe failed with %d.\n", GetLastError());
      getch();
      return 0;
      break;
  } // switch (GetLastError())

  // Если подключение произошло, то устанавливаем статус сервера к чтению
  if (!PendingIO) dwState = READING_STATE;

  return 1;

} // ConnectToNewClient ----------------------------------------------------------------------------------------------------------

// Считывание строки -------------------------------------------------------------------------------------------------------------
void ReadMessage() {

  int  i = 0;          // Индекс символа
  bool EndOfEnter = 0; // Метка окончания ввода
  char ch;             // Читаемый символ

  while (!EndOfEnter) {
    ch = getc(stdin);  // Читаем символ из стандартного ввода

    switch (ch) {      // В зависимости от символа выполняем следующие действия
      case 10 :
        EndOfEnter = 1;
        chBuffer[i] = 0;
        break;         // Нажали Enter, завершаем ввод

      default :
        chBuffer[i] = ch;
        i++;
        break;                   // Нажали любую другую клавишу, записываем ее в строку s
    } // switch (ch)
  } // while

} // ReadMessage------------------------------------------------------------------------------------------------------------------

// Закрытие сервера --------------------------------------------------------------------------------------------------------------
void CloseServer() {

  // Отключаем клиента
  DisconnectNamedPipe(hPipe);
  // Закрываем канал
  CloseHandle(hPipe);

} //------------------------------------------------------------------------------------------------------------------------------
