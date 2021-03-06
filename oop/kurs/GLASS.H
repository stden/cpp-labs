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
#include "id_obj.h"

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

  // �����䨪���
  const int m_id;

 public:
  int getID() const {
    return m_id;
  }

  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������, bottom - ����� �᭮�����,
  * hBottom - ���� �᭮�����, lessSide - ����� ����襣� ॡ� ������� �⥭��
  */
  CGlass(int id, const CCountedPoint& x, const CCountedPoint& y,
         const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * ��������
  */
  ~CGlass(void);

  CCountedPoint getBasePoint() {
    return m_bottom.getPoint(0);
  }

  CRectangle& getBottom() {
    return m_bottom;
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
    cout << "Glass #" << getID() << " MovedXdY(" << dX << "," << dY << ")" << endl;
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
  * ����祭�� �࠭�� (��אַ㣮�쭨��, ����뢠�饣� ��� 䨣���)
  */
  void GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
    *minx = MAXDOUBLE;
    *maxx = MINDOUBLE;
    *miny = MAXDOUBLE;
    *maxy = MINDOUBLE;
    m_bottom.GetBorders(minx, maxx, miny, maxy);
    m_cage.GetBorders(minx, maxx, miny, maxy);
    m_leftSide.GetBorders(minx, maxx, miny, maxy);
    m_rightSide.GetBorders(minx, maxx, miny, maxy);
  };
};

#endif