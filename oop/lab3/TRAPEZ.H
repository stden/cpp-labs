// Файл: Trapez.h
// Объявление класса Трапеция (перевёрнутая)
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0
#ifndef _TRAPEZ_H_
#define _TRAPEZ_H_


#include "CoPoint.h"
#include "CoList.h"

class CTrapezium  {
private:
CList<CCountedPoint> m_list;

//Количество экземпляров класса прямоугольник
  static int countreal;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

public:

  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя точка, l - Длина меньшего основания
  */
  CTrapezium(const CCountedPoint& x, const CCountedPoint& y, const double& l);

  ~CTrapezium(void);

  void MovedXdY (double dx, double dy);
  void MoveToPoint (const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints () { return m_list; }
  const CCountedPoint& getPoint (int index);

  static int getCount() { return countreal; }

  int getId () { return m_id; }

  void GetBorders( double *minx,double *maxx,double *miny,double *maxy );

  friend ostream& operator << (ostream& s, CTrapezium& r);

};

#endif

