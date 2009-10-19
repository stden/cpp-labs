// ����������� ������ String.
#ifndef STRING_H
#define STRING_H

#include <iostream>


class String
{

      
public:
      String ();// ����������� �� ���������
      String( char *);//��������������
      
      operator char * ();
      String operator= ( String );
      String operator+ ( String );//���������� �������
      String operator+= ( String );
      String operator-(int);//������� n ��������
      String operator -=(int);
private:
        int len; //����� ������(��� 0)
        char *str; //��������� �� ������ ������������� ������
}; //����� ������

#endif
            
