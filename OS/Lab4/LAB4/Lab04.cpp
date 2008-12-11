/********************************************
Лабораторная работа №4 по дисциплине ОС
*********************************************
Задание: Операции над характеристиками файлов
Вариант: 20
Сделал: Беломытцев Алексей
Группа: 0362
*********************************************/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
int main(void)
{
	printf("\n\tБеломытцев Алексей гр.0362\n\t\tЛабораторная Работа №4\n");

	BOOL ans;

	char* filename;
	filename = new char[200];

	HANDLE createdfile;

	BY_HANDLE_FILE_INFORMATION info;

//Создать файл
	printf("Create file: ");
	scanf("%s", filename);
	createdfile = CreateFile(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL);
	CloseHandle(createdfile);
	printf("Edit File and press Enter");
	_getch();
	fflush(stdin);

//Получение информации о файле по указателю (handle)
	OFSTRUCT of;
	HFILE hf;
	WORD fatdate;
	WORD fattime;

	hf = OpenFile(filename, &of, OF_READWRITE);
	if(hf != HFILE_ERROR) createdfile = (HANDLE) hf;
	GetFileInformationByHandle(createdfile, &info);
	char* str;
		str = new char[200];
			str[0]='\0';
	if(info.dwFileAttributes==0)
		strcat(str, "\n\tReadOnly");
	if(((info.dwFileAttributes)>>1) & 1)
		strcat(str, "\n\tHidden");
	if(((info.dwFileAttributes)>>2) & 1)
		strcat(str, "\n\tSystem");
	if(((info.dwFileAttributes)>>4) & 1)
		strcat(str, "\n\tDirectory");
	if(((info.dwFileAttributes)>>5) & 1)
		strcat(str, "\n\tArchieved");
	if(((info.dwFileAttributes)>>7) & 1)
		strcat(str, "\n\tNormal");
	if(((info.dwFileAttributes)>>8) & 1)
		strcat(str, "\n\tTemporary");
	if(((info.dwFileAttributes)>>11) & 1)
		strcat(str, "\n\tCompressed");
	if(((info.dwFileAttributes)>>12) & 1)
		strcat(str, "\n\tOffline");

	printf("\n\nFile Attributes: %s\n", str);
	printf("Volume Serial Number: %d\n", info.dwVolumeSerialNumber);
	printf("High File Size: %d\n", info.nFileSizeHigh);
	printf("Low File Size: %d\n", info.nFileSizeLow);
	printf("Number of links: %d\n", info.nNumberOfLinks);
	printf("High File Index: %d\n", info.nFileIndexHigh);
	printf("Low File Index: %d\n", info.nFileIndexLow);

//Конвертирование FT -> DOS DT
	int UTC = 4;
	unsigned short u[8];
	FileTimeToDosDateTime(&info.ftCreationTime, &fatdate, &fattime);
	u[0] = fatdate & 31;			//Date
	u[1] = fatdate >> 5;			//Month
	u[1] = u[1] & 15;				//Month
	u[2] = (fatdate >> 9) + 1980;	//Year
	u[3] = (fattime & 31) * 2;		//Seconds
	u[4] = fattime >> 5;			//Minute
	u[4] = u[4] & 63;				//Minute
	u[5] = fattime >> 11;			//Hour - GMT?
	printf("Created: %d-%d-%d %d:%d:%d\n", 
		u[0], u[1], u[2], u[5], u[4], u[3]);

	FileTimeToDosDateTime(&info.ftLastAccessTime, &fatdate, &fattime);
	u[0] = fatdate & 31;			//Date
	u[1] = fatdate >> 5;			//Month
	u[1] = u[1] & 15;				//Month
	u[2] = (fatdate >> 9) + 1980;	//Year
	u[3] = (fattime & 31) * 2;		//Seconds
	u[4] = fattime >> 5;			//Minute
	u[4] = u[4] & 63;				//Minute
	u[5] = fattime >> 11;			//Hour - GMT?
	printf("Last Accessed: %d-%d-%d %d:%d:%d\n", 
		u[0], u[1], u[2], u[5], u[4], u[3]);

	FileTimeToDosDateTime(&info.ftLastWriteTime, &fatdate, &fattime);
	u[0] = fatdate & 31;			//Date
	u[1] = fatdate >> 5;			//Month
	u[1] = u[1] & 15;				//Month
	u[2] = (fatdate >> 9) + 1980;	//Year
	u[3] = (fattime & 31) * 2;		//Seconds
	u[4] = fattime >> 5;			//Minute
	u[4] = u[4] & 63;				//Minute
	u[5] = fattime >> 11;			//Hour - GMT?
	printf("Last Written: %d-%d-%d %d:%d:%d\n", 
		u[0], u[1], u[2], u[5], u[4], u[3]);

//Получение типа файла
	char* strt;
		strt = new char[200];
	DWORD tst;
	switch(tst = GetFileType(createdfile))
	{
	case FILE_TYPE_UNKNOWN: strcpy(strt, "Unknown"); break;
	case FILE_TYPE_DISK: strcpy(strt, "Disk"); break;
	case FILE_TYPE_PIPE: strcpy(strt, "Pipe"); break;
	case FILE_TYPE_REMOTE: strcpy(strt, "Remote"); break;
	default: sprintf(strt, "Unknown [type %d]", tst);
	};
	printf("\nFile Type: %s", strt);
	//FILE_TYPE_UNKNOWN 

//Получение системного времени
	SYSTEMTIME systm;
	GetSystemTime(&systm);
	printf("\n\nSystem time: %d-%d-%d %d:%d:%d.%d\nDay of week: %d\n",
		systm.wDay, systm.wMonth, systm.wYear, systm.wHour, 
			systm.wMinute, systm.wSecond, systm.wMilliseconds,
				systm.wDayOfWeek);
	CloseHandle(createdfile);

//Изменение времени создания файла
//Конвертирование DOS DT -> FT

	hf = OpenFile(filename, &of, OF_READWRITE);
	if(hf != HFILE_ERROR) createdfile = (HANDLE) hf;

	FILETIME la, lw, cr;

//	u[0]=29; u[1]=3; u[2]=1982; u[3]=15; u[4]=16; u[5]=17;
	printf("\nSet creation date to (DD-MM-YY,hh:mm:ss): \n");
	scanf("%d-%d-%d,%d:%d:%d", &u[0], &u[1], &u[2], &u[3], &u[4], &u[5]);
	fatdate=((u[2] - 1980) << 9) + (u[1] << 5) + u[0];
	fattime=(u[3] << 11) + (u[4] << 5) + u[5];
	ans = DosDateTimeToFileTime(fatdate, fattime, &cr);

	printf("Set Last Access date to (DD-MM-YY,hh:mm:ss): ");
	scanf("%d-%d-%d,%d:%d:%d", &u[0], &u[1], &u[2], &u[3], &u[4], &u[5]);
	fatdate=((u[2] - 1980) << 9) + (u[1] << 5) + u[0];
	fattime=(u[3] << 11) + (u[4] << 5) + u[5];
	ans = DosDateTimeToFileTime(fatdate, fattime, &la);
/*
	printf("Set Last Write date to (DD-MM-YY,hh:mm:ss): ");
	scanf("%d-%d-%d,%d:%d:%d", &u[0], &u[1], &u[2], &u[3], &u[4], &u[5]);
	fatdate=((u[2] - 1980) << 9) + (u[1] << 5) + u[0];
	fattime=(u[3] << 11) + (u[4] << 5) + u[5];
*/
	ans = DosDateTimeToFileTime(fatdate, fattime, &lw);

	ans = 0;
	ans = SetFileTime(createdfile, &cr, &la, &lw);
	
//Сравнение двух файловых времен
	char* val;
	val = new char[15];
	switch(CompareFileTime(&cr, &la))
	{
		case 1: {strcpy(val, "greater than"); break;};
		case 0: {strcpy(val, "equal to"); break;};
		case -1: {strcpy(val, "less than"); break;};
		default: {strcpy(val, "\0"); break;};
	};
	printf("\nCreaion date is %s Last Access date.\n", val);

//Все, конец
	ans = CloseHandle(createdfile);
	return 0;
};