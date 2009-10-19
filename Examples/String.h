// Определение класса String.
#ifndef STRING_H
#define STRING_H

#include <iostream>


class String
{

      
public:
      String ();// конструктор по умолчанию
      String( char *);//преобразования
      
      operator char * ();
      String operator= ( String );
      String operator+ ( String );//прибавляет строчку
      String operator+= ( String );
      String operator-(int);//удаляет n символов
      String operator -=(int);
private:
        int len; //длина строки(без 0)
        char *str; //указатель на начало представления строки
}; //конец класса

#endif
            
