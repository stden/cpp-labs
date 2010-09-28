// Файл: CRect.cpp
// Реализация класса "прямоугольник"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CRect.h"
#include <iostream.h>


int CRectangle :: debug = 0;
int CRectangle :: total = 0;
int CRectangle :: current = 0;


CRectangle :: CRectangle(double x1, double y1, double _width, double _height) {
  P1.SetX(x1);
  P1.SetY(y1);

  P2.SetX(x1 + _width);
  P2.SetY(y1);

  P3.SetX(x1);
  P3.SetY(y1 - _height);

  P4.SetX(x1 + _width);
  P4.SetY(y1 - _height);

  Width = _width;
  Height = _height;

  id = ++total;
  ++current;

  if (debug) cout << "Rectangle " << P1 << "," << P2 << "," << P3 << "," << P4 << " created" << endl;
}

CRectangle :: CRectangle(CPoint P0, double _width, double _height) {
  P1 = P0;
  P1 = P0;

  P2.SetX(P0.GetX() + _width);
  P2.SetY(P0.GetY());

  P3.SetX(P0.GetX());
  P3.SetY(P0.GetY() - _height);

  P4.SetX(P0.GetX() + _width);
  P4.SetY(P0.GetY() - _height);

  Width = _width;
  Height = _height;
  id = ++total;
  ++current;

  if (debug) cout << "Rectangle " << P1 << "," << P2 << "," << P3 << "," << P4 << " created" << endl;
}

CRectangle :: CRectangle(CPoint P0, double wh) {
  P1 = P0;

  P2.SetX(P0.GetX() + wh);
  P2.SetY(P0.GetY());

  P3.SetX(P0.GetX());
  P3.SetY(P0.GetY() - wh);

  P4.SetX(P0.GetX() + wh);
  P4.SetY(P0.GetY() - wh);

  Width = wh;
  Height = wh;
  id = ++total;
  ++current;

  if (debug) cout << "Rectangle " << P1 << "," << P2 << "," << P3 << "," << P4 << " created" << endl;
}



CRectangle :: CRectangle() {
  CPoint P0(0, 0);
  P1 = P0;
  P1 = P0;

  P2.SetX(P0.GetX() + 1);
  P2.SetY(P0.GetY());

  P3.SetX(P0.GetX());
  P3.SetY(P0.GetY() - 1);

  P4.SetX(P0.GetX() + 1);
  P4.SetY(P0.GetY() - 1);

  Width = 1;
  Height = 1;
  id = ++total;
  ++current;

  if (debug) cout << "Rectangle " << P1 << "," << P2 << "," << P3 << "," << P4 << " created" << endl;
}


CRectangle :: ~CRectangle() {
  if (debug) cout << "Rectangle " << P1 << "," << P2 << "," << P3 << "," << P4 << " deleted" << endl;
  --current;
}

int CRectangle :: inv() {
  return ((P1 >= -1000 && P1 <= 1000) && (P2 >= -1000 && P2 <= 1000) &&
          (P3 >= -1000 && P3 <= 1000) && (P4 >= -1000 && P4 <= 1000));
}


void CRectangle :: SetP1(double x, double y) {

  P1.SetX(x);
  P1.SetY(y);

  P2.SetX(x + Width);
  P2.SetY(y);

  P3.SetX(x);
  P3.SetY(y - Height);

  P4.SetX(x + Width);
  P4.SetY(y - Height);

}

void CRectangle :: SetP1(CPoint P0) {
  P1 = P0;
  P1 = P0;

  P2.SetX(P0.GetX() + Width);
  P2.SetY(P0.GetY());

  P3.SetX(P0.GetX());
  P3.SetY(P0.GetY() - Height);

  P4.SetX(P0.GetX() + Width);
  P4.SetY(P0.GetY() - Height);
}


void CRectangle :: Move(double dx, double dy) {
  P1.SetX(P1.GetX() + dx);
  P1.SetY(P1.GetY() + dy);
  P2.SetX(P2.GetX() + dx);
  P2.SetY(P2.GetY() + dy);
  P3.SetX(P3.GetX() + dx);
  P3.SetY(P3.GetY() + dy);
  P4.SetX(P4.GetX() + dx);
  P4.SetY(P4.GetY() + dy);
}

CPoint CRectangle :: GetP1() const {
  return P1;
}

CPoint CRectangle :: GetP2() const {
  return P2;
}

CPoint CRectangle :: GetP3() const {
  return P3;
}

CPoint CRectangle :: GetP4() const {
  return P4;
}

double CRectangle :: GetWidth() const {
  return Width;
}

double CRectangle :: GetHeight() const {
  return Height;
}

void CRectangle :: Print() {
  cout << "Rectangle : id = " << id << " " << P1 << "," << P2 << "," << P3 << "," << P4 <<
       " Width = " << Width << ", Height = " << Height << endl;
}

void CRectangle :: setDebug(int d) {
  debug = d;
}

int CRectangle :: getID() {
  return id;
}

int CRectangle :: getCurrent() {
  return current;
}

int CRectangle :: getTotal() {
  return total;
}

ostream& operator<<(ostream& output, const CRectangle& R) {

  output << "Rectangle : id = " << R.getID() << " " << R.GetP1() << "," << R.GetP2() << "," << R.GetP3() << "," << R.GetP4() <<
  " Width = " << R.GetWidth() << ", Height = " << R.GetHeight() << endl;
  return output;
}




