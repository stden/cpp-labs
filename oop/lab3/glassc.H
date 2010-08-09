// Файл: GlassC.h
// Объявление класса: Glass case
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.1

#ifndef _GLASSC_H
#define _GLASSC_H

#include "CoPoint.h"
#include "CoList.h"

class CGlassCase
{
private :
  CList<CCountedPoint> m_list;

  // Количество экземпляров класса
  static int countreal;

  // Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;

public:

  /*
  * Конструктор
  * x - левая нижняя точка, y - правая верхняя
  */
  CGlassCase(const CCountedPoint& x, const CCountedPoint& y);

  void MovedXdY (double dx, double dy);
  void MoveToPoint (const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints () { return m_list; }
  const CCountedPoint& getPoint (int index);

  static int getCount() { return countreal; }
 
  int getId () { return m_id; }

  /*
  * Деструктор
  */
  ~CGlassCase();

friend ostream& operator << (ostream& s, CGlassCase& r)
{
  s << "  " << "Витрина: " << ": " << endl;
  r.getPoints().goFirst();

  do{
    s << "    (" << r.getPoints().getElem().getValue() << "), " << endl;
  }while(r.getPoints().goNext());
  s << endl;

  return (s);
}

};


#endif