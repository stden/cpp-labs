// файл Point
// проект класса "точка"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, редакция 1.0.

#ifndef _POINT_H
#define _POINT_H

#include <iostream.h>

class CCountedPoint {
  //Абсцисса точки
  double m_x;

  //Ордината точки
  double m_y;

  //Количество экземпляров класса Точка
  static int m_count;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

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
  * Получить количество экземпляров класса
  */
  static int getCount() {
    return m_count;
  }

  /*
  * Смещение точки
  */
  void move(double dx, double dy);


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

#endif /* CCountedPoint_H */