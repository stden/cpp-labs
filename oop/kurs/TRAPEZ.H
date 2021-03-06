// ����: Trapez.h
// ������� ����� �࠯��� (��ॢ�����)
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0
#ifndef _TRAPEZ_H_
#define _TRAPEZ_H_

#include <math.h>
#include "CoPoint.h"
#include "CoList.h"
#include "debug.h"

class CTrapezium {
 private:
  CList<CCountedPoint> m_list;

 public:

  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������ �窠, l - ����� ����襣� �᭮�����
  */
  CTrapezium(const CCountedPoint& x, const CCountedPoint& y,
             const double& l) {
    m_list.insert(x);
    m_list.insert(y);
    m_list.insert(CCountedPoint(y.getX() + l + abs(x.getX() - y.getX()) * 2, y.getY()));
    m_list.insert(CCountedPoint(x.getX() + l, x.getY()));
    m_list.goFirst();

    cout << "      Trapezium created " << *this;
  };

  ~CTrapezium(void);

  void MovedXdY(double dx, double dy);
  void MoveToPoint(const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() const {
    return m_list;
  }
  const CCountedPoint& getPoint(int index);

  void GetBorders(double* minx, double* maxx, double* miny, double* maxy);

  friend ostream& operator << (ostream& s, CTrapezium& r);
};

#endif

