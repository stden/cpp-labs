#include <windows.h>
#include <conio.h>
#include <stdio.h>

/**- Вывод информации о регионе памяти---------------------**/
/**/ void PrintMBI       (MEMORY_BASIC_INFORMATION &mbi); /**/ 	
/**/ void PrintMBIType   (MEMORY_BASIC_INFORMATION &mbi); /**/ 
/**/ void PrintMBIProtect(MEMORY_BASIC_INFORMATION &mbi); /**/ 
/**--------------------------------------------------------**/

int main() {

	bool EndOfProgram = 0; // Метка окончания работы программы

	char ch;               // Нажимая клавиша

	while (!EndOfProgram) {

		// Выводим начальное меню
		system("cls");
		printf("\n Lr N5 : Virtual Memory -----------------------------------------------\n ");
		printf("1. The status of virtual memory, page size and allocation granularity.\n ");
		printf("2. The state of region of memory.\n ");
		printf("3. The allocation/release of a given region of memory.\n ");
		printf("4. Exit.\n\n >");

		// Считываем нажатие клавиши
		ch = getch();

		bool					  Ok              = 1   ; // Метка окончания цикла вывода информации о регионах
		PVOID					  pvAddress       = NULL, // Начальный адрес региона
			                      pvAddressRegion = NULL;
		MEMORY_BASIC_INFORMATION  mbi;			          // Структура для записи в нее информации о регионе 
		int                       ReserveSize     = 0,    // Размер резервируемой памяти
			                      CommitSize      = 0;    // Размер выделяемой памяти

		// В зависимости от нажатой клавиши выполняем нужное действие
		switch(ch) {
			// Статус ВП, размер страницы памяти, гранулярность
			case '1' : 

				SYSTEM_INFO  siSystemInfo  ;         // Структура для записи в нее информации о системе
				MEMORYSTATUS msMemoryStatus;         // Структура для записи в нее информации о статусе памяти

				GetSystemInfo     (&siSystemInfo  ); // Получаем информацию о системе
				GlobalMemoryStatus(&msMemoryStatus); // Получаем статус памяти

				// Выводим полученную информацию
				// Общий размер виртуального адресного пространства, доступный процессу
				printf("The total size of virtual memory : %10d bytes\n  ", msMemoryStatus.dwTotalVirtual       );
				// Незарезервированные фрагменты виртуального адресного пространства, доступные вызывающему процессу
				printf("Free virtual memory              : %10d bytes\n  ", msMemoryStatus.dwAvailVirtual       );
				// Размер страницы памяти
				printf("Page size                        : %10d bytes\n  ", siSystemInfo.dwPageSize             );
				// Гранулярность резервирования регионов адресного пространства
				printf("Allocation granularity           : %10d bytes\n  ", siSystemInfo.dwAllocationGranularity);

				// Ждем нажатия на клавишу
				getch();
				break;

			// Определение состояния заданного региона, либо вывод информации обо всех регионах
			case '2' : 

				// Уточнение операции - вывести информацию заданного региона, или всех
				printf("1 - Set address region\n  2 - All regions\n  ");

				// Считываем нажатую клавишу
				ch = getch();
				
				// В зависимости от нажатой клавиши выполняем нужную операцию
				switch(ch) {
					// Вывод информации заданного региона
					case '1' : 

						// Просим ввести адрес региона
						printf("\n  Enter address of region : 0x");

						// Считываем его
						scanf("%x", &pvAddress);
						printf("\n  ");

						// Получаем информацию о регионе
						Ok = ( VirtualQuery(pvAddress, &mbi, sizeof(mbi)) == sizeof(mbi) );

						// Если получили удачно выводим информацию, если нет, то сообщаем об ошибке
						if (Ok) { printf("\n  Address      Region size    State      Type       Protect\n  ");
								  PrintMBI(mbi); }
						else      printf("Bad memory address.\n  ");

						// Ждем нажатия клавиши
						getch();
						break;

					// Выводим информацию о всех регионах памяти
					case '2' : 
						
						// Заголовки таблицы
						printf("\n  Address      Region size    State      Type       Protect\n\n  ");
						// Цикл
						while (Ok) {

							// Получаем информацию о регионе по адресу pvAddress
							Ok = ( VirtualQuery(pvAddress, &mbi, sizeof(mbi)) == sizeof(mbi) );

							if (Ok) {
								// Выводим полученную информацию 
								PrintMBI(mbi);

								// Получаем адрес следущего региона
								pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
							}// if (Ok)

						}// while (Ok);

						getch();
						break;

					// Выбрали неверную операцию
					default  : printf("\n  Incorrect ID operation!"); getch(); break;
				} // switch ch
				break;

			// Выделение/освобождение заданного региона
			case '3' : 
				
				// Уточнение операции - резервирование самой системой или задание адреса вручную
				printf("1 - Automatically\n  2 - Set adress\n\n  ");

				// Читаем выбранную операцию
				ch = getch();

				// В зависимости от нажатой клавиши выполняем нужную операцию
				switch(ch) {
					// Резервирование региона системой
					case '1' :

						printf("Address      Region size    State      Type       Protect\n\n  ");
						// Резервируем регион размером 40кБ
						pvAddressRegion = VirtualAlloc( NULL, (10*4096), MEM_RESERVE, PAGE_READWRITE);

						// Получаем информацию о зарезервированном регионе
						VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

						// Выводим полученную информацию 
						printf("Reserve region :\n  ");
						PrintMBI(mbi);
						getch();
		
						// Передача памяти зарезервированному региону
						VirtualAlloc(pvAddressRegion, 4096, MEM_COMMIT, PAGE_READWRITE);

						// Получаем информацию о зарезервированном регионе c выделенной памятью
						VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

						// Выводим полученную информацию 
						printf("\n  The region with a dedicated memory :\n  ");
						PrintMBI(mbi);
						// Получаем адрес зарезервированного региона без выделенной памяти
						pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
						VirtualQuery(pvAddress, &mbi, sizeof(mbi));
						PrintMBI(mbi);
						getch();

						// Освобождаем зареервированный регион
						VirtualFree(pvAddressRegion, 0, MEM_RELEASE);
						printf("\n  Region released :\n  ");
						VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
						PrintMBI(mbi);
						getch();
						break;

					// Задание адреса вручную
					case '2' :

						// Просим ввести адрес регина
						printf("Enter address of reserve region : 0x");

						// Считываем его
						scanf("%x", &pvAddress);
						

						// Спрашиваем сколько будем резервировать
						printf("  Enter size of reserve           : ");

						// Считываем
						scanf("%d", &ReserveSize);

						// Резервируем регион
						pvAddressRegion = VirtualAlloc( pvAddress, ReserveSize, MEM_RESERVE, PAGE_READWRITE);

						if (pvAddressRegion != NULL) {
							// Если резервирование прошо удачно
							// Получаем информацию о зарезервированном регионе
							printf("\n  Address      Region size    State      Type       Protect\n\n  ");
							VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

							// Выводим полученную информацию 
							printf("Reserve region :\n  ");
							PrintMBI(mbi);
							getch();
	
							// Запрос на ввод выделяемой памяти
							printf("\n  Enter size of dedicated memory : ");
							scanf("%d", &CommitSize);

							if (ReserveSize < CommitSize) {

								// Неправильно ввели размер выделяемой памяти
								printf("\n  Error! Reserve memory size must be greater than dedicated memory size\n  ");

								// Освобождаем зарезервированный регион
								VirtualFree(pvAddressRegion, 0, MEM_RELEASE);

								// Выводим о нем информацию
								printf("\n  Region released :\n  ");
								VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
								PrintMBI(mbi);
								getch();
							}
							else {
								// Передача памяти зарезервированному региону
								VirtualAlloc(pvAddressRegion, CommitSize, MEM_COMMIT, PAGE_READWRITE);

								// Получаем информацию о зарезервированном регионе c выделенной памятью
								VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));

								// Выводим полученную информацию 
								printf("\n  The region with a dedicated memory :\n  ");
								PrintMBI(mbi);
								// Получаем адрес зарезервированного региона без выделенной памяти
								pvAddress = ((PBYTE) mbi.BaseAddress + mbi.RegionSize);
								VirtualQuery(pvAddress, &mbi, sizeof(mbi));
								PrintMBI(mbi);
								getch();

								// Освобождаем зареервированный регион
								VirtualFree(pvAddressRegion, 0, MEM_RELEASE);
								printf("\n  Region released :\n  ");
								VirtualQuery(pvAddressRegion, &mbi, sizeof(mbi));
								PrintMBI(mbi);
								getch();
							}
							
							
						} // if (pvRegionAdress != NULL)
						else {
							// ... а если неудачно :`(
							printf("\n  Bad memory address!");
							getch();
						}
						break;

					// Выбрали неверную операцию
					default  : printf("Incorrect ID operation!"); getch(); break;
				} // switch ch
				
				break;

			// Выход из программы
			case '4' : EndOfProgram = 1; printf("\n\n "); break;

			// Нажали другую клавишу
			default  : printf("Incorrect ID operation\n  "); getch(); break;
		} // switch ch
	} // while
}// End of program

// Вывод информации о регионе памяти -----------------------------------------------------------------------------------------
void PrintMBI(MEMORY_BASIC_INFORMATION &mbi)
{
	// Выводим базовый адрес региона
	printf("0x%8X   ", mbi.BaseAddress);
	
	// Размер региона
	printf("%11d    ", mbi.RegionSize);

	// Статус, тип региона памяти
	switch(mbi.State) {
	
		// Свободные страницы памяти
		case MEM_FREE    : 
			printf("FREE       \n  ");
			break;

		// Показывает на то, что под указанной страницей расположена физическая память
		case MEM_COMMIT  : 
			printf("COMMIT     ");
			PrintMBIType(mbi);
			PrintMBIProtect(mbi);
			break;

		// Регион зарезервирован
		case MEM_RESERVE : 
			printf("RESERVE    ");
			PrintMBIType(mbi);
			PrintMBIProtect(mbi);
			break;
	} // switch (mbi.state)
}

// Вывод типа региона --------------------------------------------------------------------------------------------------------
void PrintMBIType  (MEMORY_BASIC_INFORMATION &mbi)
{
	switch(mbi.Type) {
		// Cтраницы региона являются спроецированым образом EXE-файла или DLL
		case MEM_IMAGE   : printf("IMAGE      "); break;

		// Cтраницы региона являются спроецированым образом файла данных
		case MEM_MAPPED  : printf("MAPPED     "); break;

		// Cтраницы региона являются скрытыми (то есть недоступные другим процессам)
		case MEM_PRIVATE : printf("PRIVATE    "); break;
	}
}

// Вывод защиты региона ------------------------------------------------------------------------------------------------------
void PrintMBIProtect(MEMORY_BASIC_INFORMATION &mbi)
{
	switch(mbi.AllocationProtect) {
		// Права чтения
		case PAGE_READONLY          : printf("READ ONLY\n  "         ); break;
		// Права чтения/записи
		case PAGE_READWRITE         : printf("READ/WRITE\n  "        ); break;
		// Атрибуты защиты "копирование при записи"
		case PAGE_WRITECOPY         : printf("WRITE/COPY\n  "        ); break;
		// Права выполнения кода
		case PAGE_EXECUTE           : printf("EXECUTE\n  "           ); break;
		// Права чтения памяти и выполнения кода
		case PAGE_EXECUTE_READ      : printf("EXECUTE/READ\n  "      ); break;
		// Права чтения/записи памяти и выполнения кода
		case PAGE_EXECUTE_READWRITE	: printf("EXECUTE/READ/WRITE\n  "); break;
		// Атрибуты защиты "копирование при записи" и выполнения кода
		case PAGE_EXECUTE_WRITECOPY : printf("EXECUTE/WRITE/COPY\n  "); break;
		// Запрещает любой доступ к странице
		case PAGE_NOACCESS          : printf("NOACCESS\n  "          ); break;
	}
}
