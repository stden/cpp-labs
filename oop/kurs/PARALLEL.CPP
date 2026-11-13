// Файл: Parallel.cpp
// Релизация класса Параллелограмм
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include "Parallel.h"

void CParallelogram :: MovedXdY(double dx, double dy) {
  for (m_list.goFirst(); m_list.hasNext(); m_list.goNext())
    m_list.getValue().MovedXdY(dx, dy);
}

void CParallelogram :: MoveToPoint(const CCountedPoint& P) {
  m_list.goFirst();

  double dx = P.getX() - m_list.getValue().getX();
  double dy = P.getY() - m_list.getValue().getY();

  MovedXdY(dx, dy);
}

ostream& operator << (ostream& s, CParallelogram& r) {
  s << "  " << "Parallelogram: ";

  for (r.getPoints().goFirst(); r.getPoints().hasNext(); r.getPoints().goNext())
    s << r.getPoints().getValue() << " ";

  s << endl;
  return (s);
}


const CCountedPoint& CParallelogram :: getPoint(int index) {
  m_list.goFirst();

  for (index; index > 1; index--)
    m_list.goNext();

  return m_list.getValue();
}

void CParallelogram :: GetBorders(double* minx, double* maxx, double* miny, double* maxy) {
  getPoints().goFirst();

  do {
    double x = getPoints().getValue().getX();
    double y = getPoints().getValue().getY();

    if (x > *maxx) *maxx = x;

    if (x < *minx) *minx = x;

    if (y > *maxx) *maxy = y;

    if (y < *minx) *miny = y;
  } while (getPoints().goNext());
};
