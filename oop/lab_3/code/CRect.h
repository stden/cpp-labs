//���� : CRect.h
//������ ������ "�������������"
//����� : ������ �.�.
//���� : 22.02.2010 �������� : 1.0

#ifndef CRECT_H
#define CRECT_H

#include <iostream.h>
#include "CPoint.h"



class CRectangle {
 private:
  CPoint P1, P2, P3, P4;
  double Width, Height;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
 public:

  /*������������*/
  //-------------------------------------------------
  CRectangle(CPoint, double, double); // P1 width heigth
  CRectangle(double, double, double, double); // x, y, width, heigth
  CRectangle(CPoint, double); // p1 width = heigth
  CRectangle(); // Constructor without parametrs
  //-------------------------------------------------

  /*����������*/
  //-------------------------------------------------
  ~CRectangle();
  //-------------------------------------------------


  /**/

  int inv (); // ���������

  //---------------------------------------------------
  void SetP1(double, double);
  void SetP1(CPoint); // ������� ����� P1
  void Move (double, double); // ������������������ ����������� �� dx dy
  CPoint GetP1() const;
  CPoint GetP2() const;
  CPoint GetP3() const;
  CPoint GetP4() const;
  double GetWidth() const;
  double GetHeight() const;

  //---------------------------------------------------

  void Print ();
  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();

  friend ostream& operator<<( ostream& output, const CRectangle& R);


};



#endif