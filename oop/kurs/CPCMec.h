// Файл: CPСMec.h
//Проект класса "закрытый поршневой механизм"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.05.2010 Редакция: 1.0

#ifndef CPCMEC_H
#define CPCMEC_H

#include <iostream.h>
#include "CPoint.h"
#include "CPMec.h"
#include "CCover.h"
#include "CList.h"
#include "CListN.h"


class CClosedPistonMechanism : public CPistonMechanism {
private:
  CircleList<CPoint> MainPoints;
  CCover Cover;
  void  AddPoints();
public:

  /*Конструкторы*/
  ---------- -
  CClosedPistonMechanism(CPoint, double, double, double, double, double, double, double, double, double, double);
  CClosedPistonMechanism(double, double, double, double, double, double, double, double, double, double, double, double);
  CClosedPistonMechanism(); // Constructor without parametrs
  ---------- -

  /*Деструктор*/
  ---------- -
  virtual ~CClosedPistonMechanism();
  ---------- -


  /**/
  int inv();  // Инвариант
  void RefreshPoints();

  ------------ -
  void SetP1(double, double);
  void SetP1(CPoint); // Задание точки P1
  void Move(double, double); // Плоскопараллельное перемещение на dx dy
  const CircleList<CPoint>& GetPoints() const;
  const CCover& GetCover() const;

  ------------ -

  virtual void Print() const;


  friend ostream& operator<<(ostream& output, const CClosedPistonMechanism&);

};



#endif