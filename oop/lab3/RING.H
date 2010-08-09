// файл Ring.h
// проект класса "Кольцо"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _RING_H
#define _RING_H

#include <iostream.h>
#include "CoPoint.h"

class CRing : public CCountedPoint
{

  // Радиус
  double m_R;

public:
  /*
  * Конструктор
  */
  CRing(double _x = 0,double _y = 0,double _R = 0);

  /*
  * Конструктор копирования
  */
  CRing(const CRing&);

  /*
  * Деструктор
  */
  ~CRing();

  /*
  * Получение радиуса
  */
  double getR() const;

  /*
  * Установка радиуса
  */
  void setR(const double& value);

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );
};

/*
* Оператор вывода в поток
*/
ostream& operator << (ostream& s, const CRing& P);

#endif /* CRing_H */
