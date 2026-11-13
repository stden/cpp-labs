// Файл: CoPoint.h
// Проект класса "Точка"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _COPOINT_H
#define _COPOINT_H

#include <iostream.h>

class CCountedPoint {
 protected:
  //Абсцисса точки
  double m_x;

  //Ордината точки
  double m_y;

 public:

  /*
  * Конструктор
  */
  CCountedPoint(double _x = 0, double _y = 0);

  /*
  * Конструктор копирования
  */
  CCountedPoint(const CCountedPoint&);


  /*
  * Смещение точки
  */
  void MovedXdY(double dx, double dy);


  /*
  * Поворот точки относительно точки
  */
  void round(const CCountedPoint&, int);

  /*
  * Получение абсциссы точки
  */
  double getX() const;

  /*
  * Получение ординаты точки
  */
  double getY() const;

  /*
  * Установка абсциссы точки
  */
  void setX(const double& value);

  /*
  * Установка ординаты точки
  */
  void setY(const double& value);

  /*
  * Деструктор
  */
  ~CCountedPoint();
};

/*
* Оператор вывода в поток
*/
ostream& operator << (ostream& s, const CCountedPoint& P);

#endif