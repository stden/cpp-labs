#include "other.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

///////////////////////////////////////////////////

int int_var = 3;
int& ref = int_var;

int IncByValue( int e) 
{
  return e+1;
}

void IncByPointer(int* x)
{
  (*x)++;
}

void IncByReference(int& x)
{
  x++;
}

void Swap( int& x, int& y )
{
  int temp = x; 
  x = y; 
  y = temp;
}

void Swap( int* x, int* y )
{
  int temp = (*x); 
  (*x) = *y; 
  *y = temp;
}

//Подсказка-заготовка для задания 5а
//Без использования макросов
void VarArgs(int arg1,...)
{
  int number = 0;	//счетчик элементов
  //Объявите указатель на int и инициализируйте его адресом
  //первого аргумента
  int *p = &arg1;

  std::cout << "Элементы: ";

  //Пока не достигнут конец списка:
  while(*p != 0){
	// а) печать значения очередного аргумента
    std::cout << " " << *p;
    // б) модификация указателя (он должен указывать на
	//следующий аргумент списка)
	p++;
	// в) увеличить счетчик элементов
	number++;        
  }

  //Печать числа элементов
  std::cout << " Число элементов: " << number << "\n";
}

void VarArgs2(int arg1,...){
  va_list list;
  std::cout << "Элементы: ";
  va_start(list, arg1);
  int number = 0; // счетчик элементов
  for(int x = arg1; x!=0; x = va_arg(list, int)) {
    std::cout << " " << x;
	number++; 
  }
  va_end(list);

  //Печать числа элементов
  std::cout << " Число элементов: " << number << "\n";
}

int* MyMin(int* ar,int size){  
  int* minEl = &ar[0];
  for(int i=0;i<size;i++)
    if(ar[i] < *minEl)
	  minEl = &ar[i];
  return minEl;
}

