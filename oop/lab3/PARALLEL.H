// ����: Parallel.h
// ������� ����� ��ࠫ�����ࠬ�
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _PARALLEL_H
#define _PARALLEL_H

#include "CoPoint.h"
#include "CoList.h"

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
  CParallelogram(const CCountedPoint& x, const CCountedPoint& y, const double& l);

  /*
  * ��������
  */
  ~CParallelogram(void);


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