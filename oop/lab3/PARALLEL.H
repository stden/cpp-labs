// Файл: Parallel.h
// Объявление класса Параллелограмм
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _PARALLEL_H
#define _PARALLEL_H

#include "CoPoint.h"
#include "CoList.h"

/*
 * Параллелограмм лежащий на меньшем ребре
 */
class CParallelogram {
private:
CList<CCountedPoint> m_list;

public:
  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, l - Длина меньшего ребра
  */
  CParallelogram(const CCountedPoint& x, const CCountedPoint& y, const double& l);

  /*
  * Деструктор
  */
  ~CParallelogram(void);


  void MovedXdY (double dx, double dy);
  void MoveToPoint (const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints () { return m_list; }
  const CCountedPoint& getPoint (int index);

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );

  friend ostream& operator << (ostream& s, CParallelogram& r);
};

#endif