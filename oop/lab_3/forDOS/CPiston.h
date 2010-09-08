//���� : CPiston.h
//������ ������ "�������"
//����� : ������ �.�.
//���� : 22.02.2010 �������� : 1.0

#ifndef CPISTON_H
#define CPISTON_H

#include <iostream.h>
#include "CPoint.h"
#include "CSection.h"
#include "CRect.h"
#include "CList.h"
#include "CListN.h"


class CPiston {
private:
  CircleList<CPoint> MainPoints;
  CSection Stock;
  CRectangle Piston;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
public:

				/*������������*/
	//-------------------------------------------------
	CPiston(CPoint,double,double,double); // P1 width heigth length
      	CPiston(double,double,double,double,double); // x, y, width, heigth, length
	CPiston(CPoint,double); // p1 width = heigth = length
	CPiston(); // Constructor without parametrs
	//-------------------------------------------------

				/*����������*/
	//-------------------------------------------------
      	~CPiston();
	//-------------------------------------------------


	/**/

  int inv ();	// ���������
  void RefreshPoints ();

  //---------------------------------------------------
  void SetP1(double,double);
  void SetP1(CPoint); // ������� ����� P1
  void Move (double,double); // ������������������ ����������� �� dx dy
  const CircleList<CPoint>& GetPoints () const;
  double GetWidth() const;
  double GetHeight() const;
  double GetLength() const;
  CSection GetStock() const;
  CRectangle GetPiston() const;


  //---------------------------------------------------

  void Print ();
  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();

};



#endif