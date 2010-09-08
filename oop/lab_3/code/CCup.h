//���� : CCup.h
//������ ������ "������"
//����� : ������ �.�.
//���� : 22.02.2010 �������� : 1.0

#ifndef CCUP_H
#define CCUP_H

#include <iostream.h>
#include "CPoint.h"
#include "CRect.h"
#include "CList.h"
#include "CListN.h"


class CCup {
private:
  CircleList<CPoint> MainPoints;
  CRectangle RightCupSide,BottomCupSide,LeftCupSide;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
public:

				/*������������*/
	//-------------------------------------------------
	CCup(CPoint,double,double,double,double,double);
      	CCup(double,double,double,double,double,double,double); // x, y, width, heigth, length
	CCup(); // Constructor without parametrs
	//-------------------------------------------------

				/*����������*/
	//-------------------------------------------------
      	~CCup();
	//-------------------------------------------------


	/**/

  int inv ();	// ���������
  void RefreshPoints ();

  //---------------------------------------------------
  void SetP1(double,double);
  void SetP1(CPoint); // ������� ����� P1
  void Move (double,double); // ������������������ ����������� �� dx dy
  const CircleList<CPoint>& GetPoints () const;
  CRectangle GetLeftSide() const;
  CRectangle GetBottomSide() const;
  CRectangle GetRightSide() const;

  //---------------------------------------------------

  void Print ();
  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();

};



#endif
