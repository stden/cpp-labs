// Файл: CSection.h
//Проект класса "отрезок"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0

#ifndef CSECTION_H
#define CSECTION_H

#include <iostream.h>
#include "CPoint.h"



class CSection {
private:
  CPoint P1, P2;
  double L;
  static int debug;
  static int total;
  int id;
  static int current;
public:

  /*Конструкторы*/
  //-------------------------------------------------
  CSection(double, double, double); // x1 y1 y2
  CSection(CPoint, double); // p1 y2
  CSection();
  //-------------------------------------------------

  /*Деструктор*/
  //-------------------------------------------------
  ~CSection();
  //-------------------------------------------------


  /**/

  int inv();  // Инвариант

  //---------------------------------------------------
  void SetP1(double, double);
  void SetP1(CPoint); // Задание точки P1
  void SetL(double);
  void Move(double, double); // Плоскопараллельное перемещение на dx dy
  CPoint GetP1() const;
  CPoint GetP2() const;
  double GetL() const;
  //---------------------------------------------------

  void Print();
  void setDebug(int);
  int getID();
  int GetCurrent();
  int GetTotal();

  // Point Relations
  double d(CPoint);          // Расстояние от точки до прямой
  double d2(CPoint);         // Квадрат расстояния от точки до прямой
  int isLeft(CPoint);
  int isOn(CPoint);
  int isParallel(const CSection&);

  // Операторы

  CSection& operator = (CSection&);
  int operator == (CSection&);

};



#endif