//Файл : CPoint.h
//Проект класса "точка"
//Автор : Монько А.О.
//Дата : 22.02.2010 Редакция : 1.0

#ifndef CPOINT_H
#define CPOINT_H

#include <iostream.h>


class CPoint {
 private:
  double x;
  double y;
  static unsigned int debug;
  static unsigned int total;
  unsigned int id;
  static unsigned int current;
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
  void Move (double, double);
  double GetX() const;
  double GetY() const;

  void Print();

  // Point Relations
  double d( CPoint);         // Distance
  double d(CPoint, CPoint);
  double d2( CPoint);        // Distance^2
  int nCheck( CPoint, CPoint);


  void SetDebug (unsigned int);
  unsigned int GetID ();
  unsigned int GetCurrent();
  unsigned int GetTotal();

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
  friend ostream& operator<<( ostream& output, const CPoint& P);
  friend istream& operator>>( istream&, CPoint&);




};





#endif