// ����: Parallel.h
// ������� ����� ��ࠫ�����ࠬ�
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _PARALLEL_H
#define _PARALLEL_H

#include "CoPoint.h"
#include "CoList.h"
#include "debug.h"

/*
 * ��ࠫ�����ࠬ� ����騩 �� ����襬 ॡ�
 */
class CParallelogram {
 private:
  CList<CCountedPoint> m_list;

 public:
  /*
  * ���������
  * x - ����� ������ �窠, y - ����� ������, l - ����� ����襣� ॡ�
  */
  CParallelogram(const CCountedPoint& x, const CCountedPoint& y, const double& l) {
    m_list.insert(x);
    m_list.insert(y);
    m_list.insert(CCountedPoint(y.getX() + l, y.getY()));
    m_list.insert(CCountedPoint(x.getX() + l, x.getY()));
    m_list.goFirst();
    cout << "      Parallelogram created" << *this;
  };

  /*
  * ��������
  */
  ~CParallelogram(void) {
    cout << "      Parallelogram destroyed " << *this;
  };


  void MovedXdY(double dx, double dy);
  void MoveToPoint(const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() const {
    return m_list;
  }
  const CCountedPoint& getPoint(int index);

  void GetBorders(double* minx, double* maxx, double* miny, double* maxy);

  friend ostream& operator << (ostream& s, CParallelogram& r);
};

#endif