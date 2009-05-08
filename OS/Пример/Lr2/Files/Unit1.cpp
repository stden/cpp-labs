#include <vcl.h>
#pragma hdrstop
//------------------------------------------------------------------------------
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
//------------------------------------------------------------------------------
int main()
{
        int N(MAX_PATH);     // Размер буфера
        char s[MAX_PATH];    // Буфер

        // Выдача текущей директории  - возвращает число символов записанное в буфер (длина)
        unsigned int k = GetCurrentDirectory(N,s);
        cout << "1. Current directory is " << s << "\n   Length = " << k << endl << endl;
        //----------------------------------------------------------------------
        // Основная директория Windows - так же возвращает длину
        k = GetWindowsDirectory(s,N);
        cout << "2. Windows directory is " << s << "\n   Length = " << k << endl << endl;
        //----------------------------------------------------------------------
        // Изменение текущей директории на заданную
        cout << "3. Enter the new current directory : ";
        cin  >> s; // Новая директория
        if ( !SetCurrentDirectory(s) ) {
                // Вывод ошибки в случае неудачи
                cout << "   Could not set new current directory : ErrorID " << GetLastError() << endl;
                k = GetCurrentDirectory(N,s);
                cout << "   Current directory is " << s << "\n   Length = " << k << endl << endl; }
        else
                cout << "   The current directory is changed successfully\n\n";
        //----------------------------------------------------------------------
        // Cоздание директории
        cout << "4. Enter the new creating directory : ";
        cin  >> s; // Новая директория
        if (!CreateDirectory(s,0))
                // Вывод ошибки в случае неудачи
                if (GetLastError() == ERROR_ALREADY_EXISTS)
                        // Директория уже есть
                        cout << "   Creating new directory fails : directory already exists\n\n";
                else
                        cout << "   Creating new directory fails : ErrorID " << GetLastError() << "\n\n";
        else
                // Оповещение об удачном создании директории
                cout << "   The new directory is created successfully\n\n";
        //----------------------------------------------------------------------
        // Создание файла
        cout << "5. Enter the name of new file : ";
        cin  >> s;
        int h;
        HANDLE (h);  // Дескриптор - идентификатор файла в системе
        h = CreateFile( TEXT(s),                   // Имя
                        GENERIC_WRITE,             // Способ доступа - для записи
                        0,                         // 0 - совместный доступ запрещен
                        NULL,                      // Атрибуты по умолчанию
                        CREATE_NEW,                // Создается новый файл
                        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, // Набор атрибутов
                        NULL );                    // Не используется

        if (h == INVALID_HANDLE_VALUE)
                // Вывод ошибки в случае неудачи
                if (GetLastError() == ERROR_FILE_EXISTS)
                        cout << "   Could not create file : file already exists\n\n";
                else
                        cout << "   Could not create file : ErrorID " << GetLastError() << "\n\n";
        else
                cout << "   New file was created successfully\n\n";
        CloseHandle(h);
        //----------------------------------------------------------------------
        // Копирование
        cout << "6. Enter the name of copying file        : ";
        cin  >> s; // Копируемый файл
        char d[MAX_PATH];
        cout << "   Enter the name of copy of copyng file : ";
        cin  >> d; // Копия файла
        if (!CopyFile(s,d,true))
                // Вывод ошибки в случае неудачи
                if (GetLastError() == ERROR_FILE_EXISTS)
                        cout << "   Copy fails : file with this name already exists\n\n";
                else
                        cout << "   Copy fails : ErrorID " << GetLastError() << "\n\n";
        else
                cout << "   The file is copied successfully\n\n";
        //----------------------------------------------------------------------
        // Перемещение
        cout << "7. Enter the name of moving file     : ";
        cin  >> s; // Перемещаемый файл
        cout << "   Enter the new name of moving file : ";
        cin  >> d;
        if (!MoveFile(s,d))
                // Вывод ошибки в случае неудачи
                if (GetLastError() == 183)
                        cout << "   Move fails : file/directory with this name already exists in the directory receiver\n\n";
                else
                        cout << "   Move fails : ErrorID " << GetLastError();
        else
                cout << "   The file/directory is moved successfully";

        cout << "\n\nPress any key";
        getch();
}
//------------------------------------------------------------------------------
