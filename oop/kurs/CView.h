// ����: CView.h
//������ ������ "��� �� ����� � ���������� ���������� �����������"
// �����: ������� �. ��. ��. 7304
// ����: 22.05.2010 ��������: 1.0

#ifndef CVIEW_H
#define CVIEW_H

#include <iostream.h>
#include "CPColl.h"
#include "CStand.h"
#include "CPoint.h"
#include "CList.h"


class CView : public CPistonCollection, public CStand {
private:

public:

  /*������������*/
  -----------
  CView(CPoint _P1, double _P1P2, CPoint _P3); // P1 width heigth length
  CView(); // Constructor without parametrs
  -----------

  /*����������*/
  -----------
  ~CView();
  -----------


  /**/

  int inv();  // ���������

  -------------
  virtual  void SetCollectionP1(CPoint P0); // ������� ����� P1
  void SetStandP1(CPoint P0);
  void MoveCollection(double dx, double dy);  // ������������������ ����������� �� dx dy
  void MoveStand(double dx, double dy);  // ������������������ ����������� �� dx dy
  void Add(CPistonMechanism*) const;
  void Add(const CPistonCollection& C) const;
  int isOnStand(CPistonMechanism*) const;


  -------------

  virtual void Print() const;
  void PrintView();


};



#endif