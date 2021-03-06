// ����: Glass.h
// ������� ����� �⠪��
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _GLASS_H
#define _GLASS_H

#include "Parallel.h"
#include "Trapez.h"
#include "Rectan.h"
#include "CoList.h"
#include "Ring.h"
#include <conio.h>
#include <values.h>

class CGlass {
 protected:
  // ���
  CRectangle m_bottom;

  // �������
  CTrapezium m_cage;

  // ����� �⥭��
  CParallelogram m_leftSide;

  // �ࠢ�� �⥭��
  CParallelogram m_rightSide;

  // ������⢮ ��������஢ ����� �⠪��
  static int countreal;

  // ��饥 ������⢮ ᮧ������ �����-���� ��������஢
  static int countall;

  // �����䨪���
  int m_id;

 public:
  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������, bottom - ����� �᭮�����,
  * hBottom - ���� �᭮�����, lessSide - ����� ����襣� ॡ� ������� �⥭��
  */
  CGlass(const CCountedPoint& x, const CCountedPoint& y,
         const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * ��������
  */
  ~CGlass(void);

  int getID() {
    return m_id;
  };

  CCountedPoint getBasePoint() {
    return m_bottom.getPoint(0);
  }

  /*
  * ��६�饭��
  */
  virtual void MoveToPoint(const CCountedPoint& point) {
    CCountedPoint basePoint = m_bottom.getPoint(0);

    double dx = point.getX() - basePoint.getX();
    double dy = point.getY() - basePoint.getY();

    MovedXdY(dx, dy);
  };

  /*
  * ���饭��
  */
  virtual void MovedXdY(double dX, double dY) {
    cout << "Glass #" << m_id << " MovedXdY(" << dX << "," << dY << ")" << endl;
    m_bottom.MovedXdY(dX, dY);
    m_cage.MovedXdY(dX, dY);
    m_leftSide.MovedXdY(dX, dY);
    m_rightSide.MovedXdY(dX, dY);
  };

  /*
  * ������ �뢮�� � ��⮪
  */
  friend ostream& operator << (ostream& s, CGlass& r) {
    return r.Write(s);
  }

  virtual ostream& Write(ostream& s) {
    s << "    Glass #" << getID() << ": " << endl
      << "      Bottom: " << m_bottom;
    s << "      Cage: " << m_cage;
    s << "      Left side: " << m_leftSide;
    s << "      Right side: " << m_rightSide;
    getch();
    return s;
  }

  /*
  * ������� ������⢮ ��������஢ �����
  */
  static int getCount() {
    return countreal;
  }

  /*
  * ����祭�� �࠭�� (��אַ㣮�쭨��, ����뢠�饣� ��� 䨣���)
  */
  void GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
    m_bottom.GetBorders(minx, maxx, miny, maxy);
    m_cage.GetBorders(minx, maxx, miny, maxy);
    m_leftSide.GetBorders(minx, maxx, miny, maxy);
    m_rightSide.GetBorders(minx, maxx, miny, maxy);
  };

};

#endif