// ����: CSection.h
//������ ������ "�������"
// �����: ������� �. ��. ��. 7304
// ����: 22.02.2010 ��������: 1.0

#ifndef CSECTION_H
#define CSECTION_H

#include <iostream.h>
#include "CPoint.h"



class CSection {
private:
  CPoint P1, P2;
  double L;
  static int debug;
  static int total;
  int id;
  static int current;
public:

  /*������������*/
  -----------
  CSection(double, double, double); // x1 y1 y2
  CSection(CPoint, double); // p1 y2
  CSection();
  -----------

  /*����������*/
  -----------
  ~CSection();
  -----------


  /**/

  int inv();  // ���������

  -------------
  void SetP1(double, double);
  void SetP1(CPoint); // ������� ����� P1
  void SetL(double);
  void Move(double, double); // ������������������ ����������� �� dx dy
  CPoint GetP1() const;
  CPoint GetP2() const;
  double GetL() const;
  -------------

  void Print();
  void setDebug(int);
  int getID();
  int GetCurrent();
  int GetTotal();

  // Point Relations
  double d(CPoint);          // ���������� �� ����� �� ������
  double d2(CPoint);         // ������� ���������� �� ����� �� ������
  int isLeft(CPoint);
  int isOn(CPoint);
  int isParallel(const CSection&);

  // ���������

  CSection& operator = (CSection&);
  int operator == (CSection&);

};



#endif