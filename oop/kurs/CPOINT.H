// Файл: CPoint.h
//Проект класса "точка"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0

#ifndef CPOINT_H
#define CPOINT_H

#include <iostream.h>


class CPoint {
private:
  double x;
  double y;
  static int debug;
  static int total;
  int id;
  static int current;
public:
  CPoint(double, double);
  CPoint();
  CPoint(double);
  ~CPoint();
  int inv();
  CPoint operator + (CPoint&);
  CPoint operator-(CPoint&);

  void SetX(double);
  void SetY(double);
  void Move(double, double);
  double GetX() const;
  double GetY() const;

  void Print();

  // Point Relations
  double d(CPoint);          // Distance
  double d(CPoint, CPoint);
  double d2(CPoint);         // Distance^2
  int nCheck(CPoint, CPoint);


  void setDebug(int);
  int getID();
  int GetCurrent();
  int GetTotal();

  // одинаковы ли точки ?

// CPoint operator = (CPoint&);
  int operator == (CPoint);
  int operator!= (CPoint&);
  int operator== (double);
  int operator!= (double);
  int operator< (CPoint&);
  int operator> (CPoint&);
  int operator> (double);
  int operator< (double);
  int operator<= (double);
  int operator>= (double);
  int operator>= (CPoint&);
  int operator<= (CPoint&);
  friend ostream& operator<<(ostream& output, const CPoint& P);
  friend istream& operator>>(istream&, CPoint&);




};





#endif