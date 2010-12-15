#include "stdafx.h"


/*************************************************************
	������������ ������� �3. �������.
	����������, �����������, �����.
	�������� ����������. ����������� ��������.
	��������� �� �������
*************************************************************/
#include <iostream>
#include <tchar.h>
#include <assert.h>
//#include <cstdio>
//#include <cstdarg>
#include "other.h"

#define	  stop __asm nop

int Min(int** ar, int N, int M){
  int min = ar[0][0];
  for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
	  if(ar[i][j] < min)
		min = ar[i][j];
  return min;
}

const int M = 3;

int Min(int ar[][M], int N){
  int min = ar[0][0];
  for(int i=0;i<N;i++)
    for(int j=0;j<M;j++)
	  if(ar[i][j] < min)
		min = ar[i][j];
  return min;
}

int MyStrCmp( const char* s1, const char* s2 ){
  int p = 0;
  // ���� ��� ������ ������������ � ����� - ��������� �����
  while((s1[p] == s2[p]) && s1[p]) p++;
  // ���� ������ ��������� ������������, ������ ��� �����
  if(s1[p] == s2[p]) return 0;
  return (s1[p] > s2[p]) ? +1 : -1;
}

// �������� �� ��� ����������?
int isLeapYear( int Year ){
  // ��� �������� ����������, ���� �� ������ 4 � ��� ���� �� ������ 100, ���� ������ 400
  return (Year % 4 == 0) && (Year % 100 != 0) || (Year % 400 == 0); 
}

int DayOfYear( int Day, int Month, int Year, int nDayTab[2][12] ){
  int d = Day;
  for(int m = 0; m < Month-1; m++) // ��������� ������������ ���� ���������� �������
	d += nDayTab[isLeapYear(Year)][m];
  return d; 
}

void DayOfMonth( int DayOfYear, int Year, int nDayTab[2][12],int& rDay,int& rMonth){
  // �������, ��� ���� ����� ��� � ����
  rDay = DayOfYear;
  // ������ ���� �� �������, ���� ���������� ���� ������ ��� � ������ ������, �������� ����� ������� ������
  // � ��������� � ���������� ������
  for(rMonth = 1; rDay > nDayTab[isLeapYear(Year)][rMonth-1]; rMonth++)
	rDay -= nDayTab[isLeapYear(Year)][rMonth-1];
}

// ������� ����� �� ������� ����� �����
int* RemoveDuplicates( int* A /* �������� ����� */, int size /* ������ ������� */, int& newSize /* ���������� */ ){
  // ������� ���������� ���������� ����� (����� ������� ������ ���������� ������)
  newSize = 0;
  for(int i=0; i<size; i++){
	bool unique = true; // �����������, ��� A[i] �� ���������� ��� ����� � ������� A
	for(int j=0; j<i; j++) // ��������� ��� �������� ������� A � ������ ������ �� �������� ��� A[i]
      if(A[j] == A[i]){ // ���� ���� ����� �� �������
		unique = false; // �� ������ �������� �� �����, ������ ����� A[i] �����
		break; // � �� ��������� ����, ������ ��� ������ ������ ������ ���
	  }
    if(unique) newSize++; // ����������� ���������� ����������
  }
  // ������� ������ ��� ���������� �������� � ������������ ������
  int *res = new int[newSize]; 
  int p=0;
  // � ��� ��� ��������� �������� ������ ����������� ������ ������ ��������
  for(int i=0; i<size; i++){
	bool unique = true; // �����������, ��� A[i] �� ���������� ��� ����� � ������� A
	for(int j=0; j<i; j++) // ��������� ��� �������� ������� A � ������ ������ �� �������� ��� A[i]
      if(A[j] == A[i]){ // ���� ���� ����� �� �������
		unique = false; // �� ������ �������� �� �����, ������ ����� A[i] �����
		break; // � �� ��������� ����, ������ ��� ������ ������ ������ ���
	  }
    if(unique){
	  res[p] = A[i];
	  p++;
	}
  }
  // ���������� ���������
  return res;
}

// ����� ������ N �����
int sum1N(int N){
  assert( N > 0, "N ������ ���� ������ 0" );
  return (N==1) ? 1 : sum1N(N-1)+N;
}

int _tmain()
{
	
	/////////////////////////////////////////////////////////////////////////////
	// ������� 1. ������.
	//�������� ������ �� ��� double. ����������� ������ �������� ��������

	double d = 1.0;
	double* dr = &d;
	*dr = 2.0;
	std::cout << d << "\n";

	//���������������� ��� ��������� �������. ��� ������� �������, �����
	//linker �� ������� ������ ��� �������� exe-�����
	extern int& ref;
	ref++;
	std::cout << ref << "\n";

	//���������������� ��������� ������. ��� ������� �������, �����
	//���������� �� ������� ������ 
	
	const int& ref1 = 1;// ����������� ������ �������� 239
	

	//����� ���������:
	char c='A';
	char* pc = &c;
	//�������� ������ �� ���������. ����������� ������ ��������
	//�) �������� �� ������
	//�) ��� �����

	char*& ref2= pc;  

	*ref2 = 3;
	ref2 = (char *)4;//���������� � ���� char *

	//������� 2. ������� ��� �������� ���������� �) �� ��������,
	// �) �� ������, �) �� ���������
	//�������� � ���������� ��� ������� , ������� ����������� ��������
	//� ������� ��������� �������� �� 1 ( �) - IncByValue(),
	// �) - IncByPointer(), �) - IncByReference() ). 
	//��������� ������������ � ������� ���������.
	//
	//���������: ���������� ������� ������� �������� � ������������ ����
	int val =1;//�������� ���� ���������� ������ ���� ��������� � �������
				//������ �� ������� �� �������
	std::cout << "val = " << val << "\n";
	assert( val == 1 ); // ����������, ��� � ���������� val �������� 1
    val = IncByValue(val); 
	assert( val == 2 ); // ���������� val �����������
	std::cout << "val = " << val << "\n";
	IncByPointer(&val); // ��� ��� ����������� �� ������
	assert( val == 3 );
	std::cout << "val = " << val << "\n";
	IncByReference(val); // ��� ��� ����������� �� ��������
	assert( val == 4 );
	std::cout << "val = " << val << "\n";
	stop

	//������� 2�. �������� ���������� c ������� ��������� � �� ������. 
	//������������� ����� �������.
	//�������� ������� (�������) Swap(), ������� ������ ��������
	//���������� nX � nY �������. 
	// �)������� ������ ��������� ��� ��������� �� int, �������� � 
	//�������� ������ �������� ���������� � ���������� ���������
	// �)������� ������ ��������� ��� ������ �� int 
	//��������� ������������ � ������� ������������ ���� ���������.

	int	nX = 1;
	int nY = -1;
	Swap(&nX, &nY);	//�������� ������� �������� nX � nY �
						//������� ���������� �� nX � nY
	std::cout << "nX = " << nX << " " << nY << "\n";
	Swap(nX, nY);	//� ������ ������� � ������� ������ �� nX � nY
	std::cout << "nX = " << nX << " " << nY << "\n";
	stop

	//������� 3. ��������� �� ������� � �������� ����������.
	//3a.�������� ��� �������� ������� ������ ������������ ��������
	//1. �� ���������� ���������� �������
	//2. � ������������ ���������� ������� (��� ����������� �����������)
	
	//1.��������:
	const int N = 2;
	int ar[N][M] = {{6,7,4},{4,3,9}/*������ ���������������*/}; //��������� - ��� � ��� ������ ���� ������ N � M
	int res = Min(ar, N /* N - ���������� �����. ... ����� ����, ����������� �������� ��� �����-������ ������*/ ); 
	std::cout << "min(ar) = " << res << "\n";

	int** ar2 = new int*[N];
	for(int i=0;i<N;i++){
	  ar2[i] = new int[M]; // ������� � ������������ ������ ��������� ������
	  for(int j=0;j<M;j++)
	    ar2[i][j] = ar[i][j]; // �������������� ������ ������ ���� �� ���������� ��� � ������
	}
	int res2 = Min(ar2, N, M ); 
	std::cout << "min(ar2) = " << res2 << "\n";

	//3b. �������� ������� ��������� ���� ����� - MyStrCmp():
	//������� ������ ��������� ��� ��������� �� ������������
	//������ (�������� �� ������ ������� �����������, ��� �������
	//�� ����� ����� �������������� ���������� �����)
	//������� ������ ���������� ������������� ��������, ����
	//������ ������ ��������������� ������ ������, 0 - ����
	//��� ����� � ������������� ��������, ���� ������ ������
	//������ ������.
	//���������, ��� ��������� ����� ������ �������� ������� ����.
	
	//�������� ��� ������ ��� ���������: 
	const char* s1 = "Hello";
	const char* s2 = "World!";

	//�������� ������� ���������
	assert( MyStrCmp(s1,s2) == -1 ); // ������ "Hello" ������ ��� "World!"
	assert( MyStrCmp(s1,s1) == 0 ); // ������ �����
	assert( MyStrCmp(s2,s1) == +1 ); // ������ "World!" ������ "Hello" 
	assert( MyStrCmp("12","12") == 0 ); // ������ �����

	int cmp_res = MyStrCmp(s1,s2);

	//�������� ��������� ��������� � ������� cout:
	std::cout << "MyStrCmp(\"" << s1 << "\",\"" << s2 << "\") = " << cmp_res << "\n";

	stop

	//������� 4.������ � �������� ����������. �������� ��������� �� ����������
	//������ � �������� ��������� �������.
	//�������� ��� ����������������� ���� ����� �������:
	//1.  ... DayOfYear(...)
	//- ����������� ���� ������ (�����,����� � ��� �������� � �������� ����������)
	//� ���������� ���� ����(������������ ��������)
	//2. ... DayOfMonth(...) - ������� ����������� ���������� ���� ���� � ���� ������
	// (��������� ��� � ���������� ���� ���� � �������� ���������� � ������ ������������
	// ���� ������ � ����� ������ � �����-�� ������� �������� ��� �������� ���������� ���������)
	
	//��������� ����������������� ����� ������� � ������� ���������� ���������:

	//� �������� ���������� ��� �������� ��������� "���������� - ������������" ���.
	//��� ����� ������������ � ������ ������� � �������� ������ �� ���������� ����������
	//������ ������������ ���� ����������� ������� nDayTab

	int nDayTab[2][12]={
		{31,28,31,30,31,30,31,31,30,31,30,31}, //������������ ���
		{31,29,31,30,31,30,31,31,30,31,30,31}	};	//���������� ���
	
	//����� ������� DayOfYear
    assert( DayOfYear(01,01,2010,nDayTab) == 1 ); // 1 ���� ����
    assert( DayOfYear(01,02,2010,nDayTab) == 31+1 ); // ������ + 1 ����
    assert( DayOfYear(10,03,2010,nDayTab) == 31+28+10 ); // ������ + ������� + 10 ����
	// 2000-�� - ����������
    assert( DayOfYear(01,02,2000,nDayTab) == 31+1 ); // ������ + 1 ����
    assert( DayOfYear(10,03,2000,nDayTab) == 31+29+10 ); // ������ + ������� (����������) + 10 ����

	//�������� ���������� �������� �������� DayOfMonth
	for(int Year=2000;Year<=2010;Year++){
	  int leap = isLeapYear(Year);
   	  for(int Month=1;Month<=12;Month++)
		for(int Day=1;Day<=nDayTab[leap][Month-1];Day++){
		  int dayOfYear = DayOfYear(Day,Month,Year,nDayTab);
		  int rDay,rMonth;
		  DayOfMonth(dayOfYear,Year,nDayTab,rDay,rMonth);
		  assert( Day == rDay );
		  assert( Month == rMonth );
		}
	}

//    assert( DayOfYear(01,02,2000,nDayTab) == 31+1 ); // ������ + 1 ����
  //  assert( DayOfMonth(DayOfYear(10,03,2000,nDayTab) == 31+29+10 ); // ������ + ������� (����������) + 10 ����
	//...

	stop

	//������� 5. �������� ���������� ������ (����������� ����������� � ��������
	//���������� ���������), ��������� ��� ����������.
	//�������� �������, ������� �������� �� ������� �����. ���������: ��� ���� ������
	//������� ������ �����������!
	//��� �������� �������� �������, ������� ������� �������� ���� ��������� �� �����
	int* numAr;
	int sizeAr = 15; // ����� ������ �������
	numAr = new int[sizeAr]; // ������ ������ � ������������ ������
	for(int i=0; i<sizeAr; i++)
	  numAr[i] = rand() % 8;
	std::cout << "source array: ";
	for(int i=0; i<sizeAr; i++)
	  std::cout << " " << numAr[i];
    std::cout << "\n";

	int newSize;
	int* numArRes = RemoveDuplicates(numAr,sizeAr,newSize);
	std::cout << "result array: ";
	for(int i=0; i<newSize; i++)
	  std::cout << " " << numArRes[i];
    std::cout << "\n";
	  
	//������� 6. ����������� �������. �������� ����������� ������� ����������
	//����� ������ N ����������� �����.

	int NN;
	std::cout << "N = ";
	std::cin >> NN;
	for(int i=1;i<NN;i++)
      std::cout << i << "+";
	std::cout << NN << " = " << sum1N(NN) << "\n";


	char Winter;
	std::cin >> Winter;

	//������� 7�. ������� � ���������� ������ ����������.
	//�������� ������� (���� ��������� VarArgs, �� ������������
	// �������), ������� ��������� ���������� ����� ����������
	// ���� int � ������� �� ������ ����� �������� ���������� �
	// �� ��������.
	// ��������� ����� ������ �������� ������� ��������.
	
	int nN1=5, nN2=11, nN3=4, nN4=7, nN5=-1;
	VarArgs(nN1,0);	
	VarArgs(nN1,nN2,0);	
	VarArgs(nN1,nN2,nN3,nN4,nN5,0);	
	stop


	//������� 7�. ������������� ������� 5� � ������� ��������
	// va_start, va_arg, va_end




	//������� 8. ����������� ������.
	//�������� �������, ������� ������� ����������� �������� � �������,
	// ����� �������, ����� �� ����� ����� ���� ������������ ����� �� ����� 
	// ���������: *MyMin(���������) = 0;
	
	

	return 0;
}//main

