
#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>

// Вспомогательные функции
int  ConnectToServer();
void ReadMessage();

// Статусы клиента
#define READING_STATE 1 
#define WRITING_STATE 2 

// Константы
#define BUFSIZE 4096
 
// Глобальные переменные
HANDLE     hPipe;              // Именованный канал 

HANDLE     hEvents[2];         // События канала
						       // 1 - запись в канал
					     	   // 2 - чтение из канала

bool       PendingIO = FALSE;  // Незавершенность какого-либо события

DWORD      dwState,            // Статус сервера
		   dwEventIndex,       // Индекс события
		   dwTransfered,       // Переданные в результате операции байты
		   dwToWrite;          // Кол-во байт, которые должны быть 


OVERLAPPED oOverlapped[2];     // Структуры OVERLAPPED

TCHAR      chBuffer[BUFSIZE],  // Буффер для считывания/посылки сообщений

		   chPipeName[] = "\\\\COMPUTER-1956EB\\pipe\\TestPipe";  // Имя сервера

int        Success   = 0;      // Успешность той или иной операции
	
// Основная функция
int main() {

	// Создание трех событий
	for (int i=0; i<2; i++) {

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

	// Подключаемся к серверу
	printf("Try connect to server...\n");
	if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}

	while(1) {

		// Ждем сигнализации какого-нибудь события
		dwEventIndex = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);

		// Определяем какой по номеру событие сигнализировало
		dwEventIndex -= WAIT_OBJECT_0;

		// Проверяем есть ли у нас такой номер события, если нет, то аварийно закрываемся
		if (dwEventIndex < 0 || dwEventIndex > 1) {
			printf("Index of event out of range.\n"); 
			CloseHandle(hPipe);
			getch();
			return 0;
		}

		// Какая-то операция еще не завершена
		if (PendingIO) {

			// Получаем статус завершенности операции
			Success = GetOverlappedResult( hPipe, &oOverlapped[dwEventIndex], &dwTransfered, FALSE);   
			
			// В зависимости от статуса сервера выполняем нужное действие
			switch(dwState) {

				// Выполнялась операция чтения
				case READING_STATE: 
					// Функция GetOverlappedResult сработала неверно или неверно сработала функция ReadFile (0 байт передано)
					if (!Success || dwTransfered == 0) { 
						// Завершаем работу клиента
						//printf("Function <ReadFile> or <GetOverlappedResult> failed! ErrorID : %d", GetLastError());
						printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
						if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
						continue;
					} 
					// Устанавливаем статус клиента к записи
					dwState = WRITING_STATE; 
					break; 

				// Выполнялась операция записи
				case WRITING_STATE: 
					// Функция GetOverlappedResult сработала неверно или неверно сработала функция WriteFile (должно быть передно байт не совпадает с переданными)
					if (!Success || dwTransfered != dwToWrite) { 
						// Завершаем работу клиента
						//printf("Function <WriteFile> failed! ErrorID : %d", GetLastError());
						//CloseHandle(hPipe);
						printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
						if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
						continue;
					} 
					// Устанавливаем статус сервера к чтению
					dwState = READING_STATE; 
					break; 

				// Ошибочный статус клиента, завершаем работу
				default: 
					printf("System message : Invalid client state.\n"); 
					CloseHandle(hPipe);
					getch();
					return 0;
            
			} // switch(dwState)
		} // if (PendingIO)

		// Определяем операцию
		switch(dwState) {

			// Читаем сообщение от сервера
			case READING_STATE: 

				// Читаем сообщение
				Success = ReadFile(hPipe, chBuffer, BUFSIZE*sizeof(TCHAR), &dwTransfered, &oOverlapped[1]); 
 
				// Операция чтения завершилась успешно
				if (Success && dwTransfered != 0) { 
					// Выполняющихся операций нет
					PendingIO = FALSE; 
					// Устанавливаем статус клиента к записи
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
 
				// Произошла ошибка, закрываем клиент
				//printf("Function <ReadFile> failed! ErrorID : %d", GetLastError());
				//CloseHandle(hPipe);
				printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
				if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
				break; 
			
			// Посылаем серверу сообщение
			case WRITING_STATE: 
				
				// Сначала выводим полученное сообщение
				printf("Server : %s\n", chBuffer);
				
				// Затем считываем пересылаемое сообщение
				printf("Client : ");
				ReadMessage();

				// Завершаем работу сервера, если введена команда выхода "exit"
				if (!stricmp(chBuffer, "exit")) {
					printf("System message : Server closing...\n");
					CloseHandle(hPipe);
					getch();
					return 1;
				}
				
				// Считаем размер сообщения
				dwToWrite  = (strlen(chBuffer)+1)*sizeof(TCHAR);

				// Посылаем сообщение
				Success = WriteFile(hPipe, chBuffer, dwToWrite, &dwTransfered, &oOverlapped[0]); 
 
				// Операция записи завершилась удачно
				if (Success && dwTransfered == dwToWrite) { 
					// Выполняющихся операций нет
					PendingIO = FALSE; 
					// Устанавливаем статус клиента к чтению
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
 
				// Произошла ошибка, закрываем клиент
				//printf("Function <WriteFile> failed! ErrorID : %d", GetLastError());
				//CloseHandle(hPipe);
				printf("\nSystem message : Connection broken, try reconnect to server.\n\n");
				if (!ConnectToServer()) { CloseHandle(hPipe); return 0;}
				break;
			// Ошибочный статус сервера, завершаем работу
			default: 
				printf("System message : Invalid client state.\n"); 
				CloseHandle(hPipe);
				getch();
				return 0;

		} // switch

	} // while (1)
 
   return 1; 
}

// Подключение к серверу ---------------------------------------------------------------------------------------------------------
int  ConnectToServer() {

	// Ждем возможности подключения
	while (1) {
		if (WaitNamedPipe(chPipeName, NMPWAIT_WAIT_FOREVER)) break;
	}

	// На всякий случай :)
	CloseHandle(hPipe);

	// Создаем канал-клиент
	hPipe = CreateFile( 
						chPipeName,           // Имя канала
						GENERIC_READ |        // Доступ к записи и чтению
						GENERIC_WRITE, 
						0,                    // Без слвместного использования
				        NULL,                 // Обычные аттрибуты защиты
						OPEN_EXISTING,        // Открыть существующий канал
						FILE_FLAG_OVERLAPPED, // Асинхронный Ввод/Вывод
						NULL );               
 
	// Удалось подключится к серверу 
	if (hPipe != INVALID_HANDLE_VALUE) { 

		// Говорим об этом пользователю
		printf("You connected to server.\n"); 

		// Задаем первое сообщение - информация о клиенте
		// Считаем размер сообщения
		dwToWrite  = (strlen("Client's name  : Bovin Alexandr\n")+1)*sizeof(TCHAR);

		// Посылаем сообщение
		WriteFile(hPipe, "Client's name  : Bovin Alexandr\n", dwToWrite, &dwTransfered, &oOverlapped[0]);

		// Устанавливаем статус клиента к записи
		dwState = WRITING_STATE;

		// Есть выполняющиеся операции
		PendingIO = TRUE;

		return 1;
	}
	
	// Выходим если ошибка отлична от ошибки - канал занят 
	if (GetLastError() != ERROR_PIPE_BUSY) {
		printf("Could not open pipe!\n"); 
		getch();
		return 0;
	}

	return 0;

} // ConnectToServer -------------------------------------------------------------------------------------------------------------

// Считывание строки -------------------------------------------------------------------------------------------------------------
void ReadMessage() {

	int  i = 0;          // Индекс символа
	bool EndOfEnter = 0; // Метка окончания ввода 
	char ch;             // Читаемый символ

	while (!EndOfEnter) {  
		ch = getc(stdin);  // Читаем символ из стандартного ввода
		switch (ch) {      // В зависимости от символа выполняем следующие действия 
			case 10 : EndOfEnter = 1; chBuffer[i] = 0; break;         // Нажали Enter, завершаем ввод
			default : chBuffer[i] = ch; i++; break;                   // Нажали любую другую клавишу, записываем ее в строку s
		} // switch (ch)	
	} // while
	
} // ReadMessage------------------------------------------------------------------------------------------------------------------
