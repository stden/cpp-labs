// Файл: CPMec.h
//Проект класса "стакан"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0

#ifndef CPMEC_H
#define CPMEC_H

#include <iostream.h>
#include "CPoint.h"
#include "CPiston.h"
#include "CCup.h"
#include "CList.h"
#include "CListN.h"


class CPistonMechanism {
protected:
  CircleList<CPoint> MainPoints;
  CPiston Piston;
  CCup Cup;
  static int debug;
  static int total;
  int id;
  static int current;
  void  AddPoints();
public:

  /*Конструкторы*/
  ---------- -
  CPistonMechanism(CPoint, double, double, double, double, double, double, double, double);
  CPistonMechanism(double, double, double, double, double, double, double, double, double, double);
  CPistonMechanism(const CCup& _cup, const CPiston& _piston);
  CPistonMechanism(); // Constructor without parametrs
  ---------- -

  /*Деструктор*/
  ---------- -
  ~CPistonMechanism();
  ---------- -


  /**/

  virtual int inv();  // Инвариант
  virtual  void RefreshPoints();

  ------------ -
  virtual  void SetP1(double, double);
  virtual   void SetP1(CPoint); // Задание точки P1
  virtual   void Move(double, double); // Плоскопараллельное перемещение на dx dy
  virtual int MovePiston(double);  // Перемещение поршня внутри механизма
  virtual  const CircleList<CPoint>& GetPoints() const;
  const CCup& GetCup() const;
  const CPiston& GetPiston() const;

  ------------ -

  virtual void Print() const;
  virtual void setDebug(int);
  virtual  int getID();
  virtual  int GetCurrent();
  virtual  int GetTotal();

  friend ostream& operator<<(ostream& output, const CPistonMechanism&);

};



#endif