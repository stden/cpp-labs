// ����: CCover.h
//������ ������ "������"
// �����: ������� �. ��. ��. 7304
// ����: 22.02.2010 ��������: 1.0

#ifndef CCOVER_H
#define CCOVER_H

#include <iostream.h>
#include "CPoint.h"
#include "CRect.h"
#include "CList.h"
#include "CListN.h"


class CCover {
private:
  CircleList<CPoint> MainPoints;
  CRectangle Hole;
  CRectangle Cover;
  static int debug;
  static int total;
  int id;
  static int current;
public:

  /*������������*/
  -----------
  CCover(CPoint, double cover_width, double cover_height, double hole_width); // P1 width heigth length
  CCover(); // Constructor without parametrs
  -----------

  /*����������*/
  -----------
  ~CCover();
  -----------


  /**/

  int inv();  // ���������
  void RefreshPoints();

  void SetP1(double, double);
  void SetP1(CPoint P0); // ������� ����� P1
  void Move(double dx, double dy);  // ������������������ ����������� �� dx dy
  const CircleList<CPoint>& GetPoints() const;
  CRectangle GetHole() const;
  CRectangle GetCover() const;

  void Print();
  void setDebug(int);
  int getID();
  int GetCurrent();
  int GetTotal();
};

#endif