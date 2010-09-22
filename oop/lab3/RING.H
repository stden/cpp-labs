// файл Ring.h
// проект класса "Кольцо"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _RING_H
#define _RING_H

#include <iostream.h>
#include "CoPoint.h"

class CRing {

  // Радиус
  double m_R_B;

  double m_R_S;

  //Абсцисса точки
  double m_x;

  //Ордината точки
  double m_y;

public:
  /*
  * Конструктор
  */
  CRing(double _x,double _y,double _R_B,double _R_S);

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
  double getR_B() const;
  double getR_S() const;

  /*
  * Установка радиуса
  */
  void setR_B(const double& value);
  void setR_S(const double& value);

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );


  /*
  * Смещение точки
  */
  void MovedXdY(double dx,double dy);

  /*
  * Перемещение в заданную точку
  */
  void MoveToPoint(double x, double y);

  double getX() const { return m_x; };
  double getY() const { return m_y; };
  void setX(double value){ m_x=value; };
  void setY(double value){ m_y=value; };

};

/*
* Оператор вывода в поток
*/
ostream& operator << (ostream& s, const CRing& P);

#endif /* CRing_H */
