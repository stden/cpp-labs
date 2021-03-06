// ����: Rectangle.h
// ���������� ������ ������
// �����: ������� �.
// ����: 16.05.10, ��������: 1.0

#ifndef _GLASS_H
#define _GLASS_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include <conio.h>

class CGlass {
  // ���
  cRectangle m_bottom;

  // �������
  CTrapezium m_cage;

  // ����� ������
  CParallelogram m_leftSide;

  // ������ ������
  CParallelogram m_rightSide;

 public:
  /*
  * �����������
  * x - ����� ������ �����, y - ����� �������, bottom - ����� ���������,
  * hBottom - ������ ���������, lessSide - ����� �������� ����� ������� ������
  */
  CGlass(const CCountedPoint& x, const CCountedPoint& y,
         const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * ����������
  */
  ~CGlass(void);

  /*
   * �����������
   */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * ��������
  */
  void MovedXdY(double x, double y);

  /*
  * �������� ������ � �����
  */
  friend ostream& operator << (ostream& s, CGlass& r) {
    s << "Glass: "
      << "  Bottom: " << r.m_bottom;
    getch();
    s  << "  Cage: " << r.m_cage;
    getch();
    s << "  Left side: " << r.m_leftSide;
    getch();
    s  << "  Right side: " << r.m_rightSide;
    getch();

    return s;
  }

};


#endif