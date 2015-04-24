#include "other.h"
#include <stdio.h>
#include <stdarg.h>
#include <iostream>

///////////////////////////////////////////////////

int int_var = 3;
int& ref = int_var;

int IncByValue( int e) {
  return e + 1;
}

void IncByPointer(int* x) {
  (*x)++;
}

void IncByReference(int& x) {
  x++;
}

void Swap( int& x, int& y ) {
  int temp = x;
  x = y;
  y = temp;
}

void Swap( int* x, int* y ) {
  int temp = (*x);
  (*x) = *y;
  *y = temp;
}

//���������-��������� ��� ������� 5�
//��� ������������� ��������
void VarArgs(int arg1, ...) {
  int number = 0; //������� ���������
  //�������� ��������� �� int � ��������������� ��� �������
  //������� ���������
  int* p = &arg1;

  std::cout << "��������: ";

  //���� �� ��������� ����� ������:
  while(*p != 0) {
    // �) ������ �������� ���������� ���������
    std::cout << " " << *p;
    // �) ����������� ��������� (�� ������ ��������� ��
    //��������� �������� ������)
    p++;
    // �) ��������� ������� ���������
    number++;
  }

  //������ ����� ���������
  std::cout << " ����� ���������: " << number << "\n";
}

void VarArgs2(int arg1, ...) {
  va_list list;
  std::cout << "��������: ";
  va_start(list, arg1);
  int number = 0; // ������� ���������

  for(int x = arg1; x != 0; x = va_arg(list, int)) {
    std::cout << " " << x;
    number++;
  }

  va_end(list);

  //������ ����� ���������
  std::cout << " ����� ���������: " << number << "\n";
}

int* MyMin(int* ar, int size) {
  int* minEl = &ar[0];

  for(int i = 0; i < size; i++)
    if(ar[i] < *minEl)
      minEl = &ar[i];

  return minEl;
}

