//String.cpp
using namespace std;
#include <iostream>
#include <conio.h>
#include <cstring>

#include "String.h"
//по умолчанию
String::String() {
  len = 0;
  str = NULL;
};
//Преобразования
String::String(char* s) {
  len = strlen(s);
  str = new char[len + 1];
  strcpy (str, s);
};


//перевод string в char*
String::operator char* () {
  return str;
};

String String::operator= (String s) {
  if (&s != this) {
    delete[] str;
    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
  };

  return *this;
};

String String::operator+ (String s) {
  String temp;
  temp.len = len + s.len;
  temp.str = new char [temp.len + 1];
  strcpy (temp.str, str);
  strcat (temp.str, s.str);
  return temp;
};

String String::operator-(int i) {
  String temp;
  temp.len = len - i;
  temp.str = new char [temp.len + 1];
  strncpy (temp.str, str, len - i);
  //cout << temp << endl;
  return temp;
};

String String::operator += (String s) {
  String temp = *this + s;
  *this = temp;
  return *this;
};

String String::operator -= (int i) {
  String temp = *this - i;
  *this = temp;
  return *this;
};

int main() {


  String S1("abc");//конструктор
  String S2("def");//конструктор
  cout << S1 << endl;
  cout << S2 << endl;
  String S3 = S1 + S2;//конструктор копирования с элементами сложения
  cout << S3 << endl;
  S3 = S3 - 3;
  cout << S3 << endl;
  S3 += "abcdef";
  cout << S3 << endl;
  S3 -= 4;
  cout << S3 << endl;
  getch();
  return 0;
}











