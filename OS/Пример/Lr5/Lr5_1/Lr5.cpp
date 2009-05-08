#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {

	int  EndOfProgram = 0; // Метка окончания работы программы
	char ch;

	while (!EndOfProgram) {

		// Выводим приветствие	
		system("cls");
		printf(" Enter name of file : ");

		// Читаем имя файла
		char FileName[MAX_PATH];
		scanf("%s", FileName);

		// Открытие файла
		HANDLE hFile = CreateFile( FileName,
								   GENERIC_READ,
								   0, 0,
								   OPEN_EXISTING,
								   FILE_ATTRIBUTE_NORMAL,
								   0 
								 );
		
		// Проверяем значение возвращенное CreateFile
		if (hFile == INVALID_HANDLE_VALUE) {

			// Возникла ошибка при открытии файла
			printf("\n Error! File not found.\n\n ");
			getch();
		} // if hFile
		else {

			// Открытие прошло успешно, отображаем файл в память
			printf("\n File successfully opened.\n ");
			getch();
			HANDLE hMapFile = CreateFileMapping( hFile, 0, PAGE_READONLY, 0, 0, 0);

			// Проверяем значение возвращенное CreateFileMapping
			if ( (hMapFile != NULL) && (GetLastError() == ERROR_ALREADY_EXISTS) ) { 

				// Объект уже существует
				CloseHandle(hMapFile);
				hMapFile = NULL;
				printf("\n Error! Object already exists\n\n ");
				getch();
			} else if (hMapFile == NULL) {

				// Невозможно создать проецируемый объект
				printf("\n Could not create file mapping object. ErrorID : %d\n\n ",GetLastError());
			    getch();

			} else {

				// Создание прошло успешно
				printf("\n File mapping object successfully created.\n ");
				getch();

				// Получаем данные спроецированные в память
				LPCTSTR pBuf = (LPTSTR) MapViewOfFile ( hMapFile, FILE_MAP_READ, 0, 0, 0 );

				if (pBuf == NULL) {

					// Произошла ошибка
					printf("\n Error! Could not map view of file\n\n ");
					getch();
				} 
				else {

					// Ошибки не произошло выводим полученную информацию
					printf("\n The contents of file ------------------------------------------\n");
					printf("\n %s\n\n ", pBuf);
					printf("---------------------------------------------------------------\n\n ");
					getch();

					//Заканчиваем работу программы
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
