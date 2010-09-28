// Файл: CTria.cpp
// Реализация класса "тупоугольный треугольник"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.05.2010 Редакция: 1.0


#include "CTria.h"
#include <iostream.h>
#include <math.h>


int CTriangle :: debug = 0;
int CTriangle :: total = 0;
int CTriangle :: current = 0;


CTriangle :: CTriangle(CPoint _P1, double _P1P2, CPoint _P3) {

  P1 = _P1;
  P3 = _P3;

  if (P3.nCheck(P1, CPoint(P1.GetX(), P1.GetY() + 1)) > 0) {
    P2.SetX(P1.GetX() + _P1P2);
    P2.SetY(P1.GetY());
  }

  else {
    P2.SetX(P1.GetX() - _P1P2);
    P2.SetY(P1.GetY());
  }



  P1P2 = _P1P2;
  P2P3 = P2.d(P3);
  P3P1 = P3.d(P1);

  id = ++total;
  ++current;

  if (debug) cout << "Triangle " << P1 << "," << P2 << "," << P3 << " created" << endl;
}

CTriangle :: CTriangle() {
  P1 = CPoint(0, 0);
  P3 = CPoint(-5, -5);
  double _P1P2 = 6;

  if (P3.nCheck(P1, CPoint(P1.GetX(), P1.GetY() + 1)) > 0) {
    P2.SetX(P1.GetX() + _P1P2);
    P2.SetY(P1.GetY());

  }

  else {
    P2.SetX(P1.GetX() - _P1P2);
    P2.SetY(P1.GetY());
  }



  P1P2 = _P1P2;
  P2P3 = P2.d(P3);
  P3P1 = P3.d(P1);

  id = ++total;
  ++current;

  if (debug) cout << "Triangle " << P1 << "," << P2 << "," << P3 << " created" << endl;
}


CTriangle :: ~CTriangle() {
  if (debug) cout << "Triangle " << P1 << "," << P2 << "," << P3 << " deleted" << endl;
  --current;
}

int CTriangle :: inv() {
  return ((P1 >= -1000 && P1 <= 1000) && (P2 >= -1000 && P2 <= 1000) &&
          (P3 >= -1000 && P3 <= 1000) && (P1.GetY() == P2.GetY()) &&
          (fabs((P1.GetY() - P2.GetY())*(P1.GetY() - P3.GetY()) + (P2.GetX() - P1.GetX())*(P3.GetX() - P1.GetX())) != 0));
}


void CTriangle :: SetP1(double x, double y) {

  if (P1.GetY() >= P3.GetY()) {
    P1 = CPoint(x, y);
    P2 = CPoint(P1.GetX() + P1P2, P1.GetY());
    P3.SetX(-0.5*((pow(P3P1, 2) - pow(P2P3, 2) - pow(P1.GetX(), 2) + pow(P2.GetX(), 2)) / (P1.GetX() - P2.GetX())));
    P3.SetY(((P1.GetY() * P1.GetX()) - (P1.GetY() * P2.GetX()) +
             sqrt((2 * P3P1 * P3P1 * P1.GetX() * P1.GetX() - 4 * P2.GetX() * P1.GetX() * P3P1 * P3P1 - 4 * P2.GetX() * P1.GetX() * P2P3 * P2P3 + 4 * pow(P2.GetX(), 3) * P1.GetX() + 4 * P2.GetX() * pow(P1.GetX(), 3)
                   - pow(P2.GetX(), 4) - 6 * P2.GetX() * P2.GetX() * P1.GetX() * P1.GetX() + 2 * P3P1 * P3P1 * P2P3 * P2P3 - pow(P2P3, 4) +
                   2 * P2.GetX() * P2.GetX() * P3P1 * P3P1 + 2 * P2.GetX() * P2.GetX() * P2P3 * P2P3 + 2 * P2P3 * P2P3 * P1.GetX() * P1.GetX() - pow(P3P1, 4) - pow(P1.GetX(), 4))) / 0.2e1) / (P1.GetX() - P2.GetX()));

  }

  else {
    P1 = CPoint(x, y);
    P2 = CPoint(P1.GetX() + P1P2, P1.GetY());
    P3.SetX(-0.5*((pow(P3P1, 2) - pow(P2P3, 2) - pow(P1.GetX(), 2) + pow(P2.GetX(), 2)) / (P1.GetX() - P2.GetX())));
    P3.SetY(((P1.GetY() * P1.GetX()) - (P1.GetY() * P2.GetX()) -
             sqrt((2 * P3P1 * P3P1 * P1.GetX() * P1.GetX() - 4 * P2.GetX() * P1.GetX() * P3P1 * P3P1 - 4 * P2.GetX() * P1.GetX() * P2P3 * P2P3 + 4 * pow(P2.GetX(), 3) * P1.GetX() + 4 * P2.GetX() * pow(P1.GetX(), 3)
                   - pow(P2.GetX(), 4) - 6 * P2.GetX() * P2.GetX() * P1.GetX() * P1.GetX() + 2 * P3P1 * P3P1 * P2P3 * P2P3 - pow(P2P3, 4) +
                   2 * P2.GetX() * P2.GetX() * P3P1 * P3P1 + 2 * P2.GetX() * P2.GetX() * P2P3 * P2P3 + 2 * P2P3 * P2P3 * P1.GetX() * P1.GetX() - pow(P3P1, 4) - pow(P1.GetX(), 4))) / 0.2e1) / (P1.GetX() - P2.GetX()));
  }



}

void CTriangle :: SetP1(CPoint P0) {
  if (P1.GetY() >= P3.GetY()) {
    P1 = P0;
    P2 = CPoint(P1.GetX() + P1P2, P1.GetY());
    P3.SetX(-0.5*((pow(P3P1, 2) - pow(P2P3, 2) - pow(P1.GetX(), 2) + pow(P2.GetX(), 2)) / (P1.GetX() - P2.GetX())));
    P3.SetY(((P1.GetY() * P1.GetX()) - (P1.GetY() * P2.GetX()) +
             sqrt((2 * P3P1 * P3P1 * P1.GetX() * P1.GetX() - 4 * P2.GetX() * P1.GetX() * P3P1 * P3P1 - 4 * P2.GetX() * P1.GetX() * P2P3 * P2P3 + 4 * pow(P2.GetX(), 3) * P1.GetX() + 4 * P2.GetX() * pow(P1.GetX(), 3)
                   - pow(P2.GetX(), 4) - 6 * P2.GetX() * P2.GetX() * P1.GetX() * P1.GetX() + 2 * P3P1 * P3P1 * P2P3 * P2P3 - pow(P2P3, 4) +
                   2 * P2.GetX() * P2.GetX() * P3P1 * P3P1 + 2 * P2.GetX() * P2.GetX() * P2P3 * P2P3 + 2 * P2P3 * P2P3 * P1.GetX() * P1.GetX() - pow(P3P1, 4) - pow(P1.GetX(), 4))) / 0.2e1) / (P1.GetX() - P2.GetX()));

  }

  else {
    P1 = P0;
    P2 = CPoint(P1.GetX() + P1P2, P1.GetY());
    P3.SetX(-0.5*((pow(P3P1, 2) - pow(P2P3, 2) - pow(P1.GetX(), 2) + pow(P2.GetX(), 2)) / (P1.GetX() - P2.GetX())));
    P3.SetY(((P1.GetY() * P1.GetX()) - (P1.GetY() * P2.GetX()) -
             sqrt((2 * P3P1 * P3P1 * P1.GetX() * P1.GetX() - 4 * P2.GetX() * P1.GetX() * P3P1 * P3P1 - 4 * P2.GetX() * P1.GetX() * P2P3 * P2P3 + 4 * pow(P2.GetX(), 3) * P1.GetX() + 4 * P2.GetX() * pow(P1.GetX(), 3)
                   - pow(P2.GetX(), 4) - 6 * P2.GetX() * P2.GetX() * P1.GetX() * P1.GetX() + 2 * P3P1 * P3P1 * P2P3 * P2P3 - pow(P2P3, 4) +
                   2 * P2.GetX() * P2.GetX() * P3P1 * P3P1 + 2 * P2.GetX() * P2.GetX() * P2P3 * P2P3 + 2 * P2P3 * P2P3 * P1.GetX() * P1.GetX() - pow(P3P1, 4) - pow(P1.GetX(), 4))) / 0.2e1) / (P1.GetX() - P2.GetX()));
  }


}

int CTriangle :: isIn(CPoint P) const {
  if (P == P1 || P == P2 || P == P3) return 1;
  else {
    int ab = P.nCheck(P1, P2);
    int bc = P.nCheck(P2, P3);
    int cd = P.nCheck(P3, P1);

    // Если точка за пределами фигуры...
    if (ab > 0 || bc > 0 || cd > 0) return 0;

  }

  return 1;
}


void CTriangle :: Move(double dx, double dy) {
  P1.SetX(P1.GetX() + dx);
  P1.SetY(P1.GetY() + dy);
  P2.SetX(P2.GetX() + dx);
  P2.SetY(P2.GetY() + dy);
  P3.SetX(P3.GetX() + dx);
  P3.SetY(P3.GetY() + dy);
}

CPoint CTriangle :: GetP1() const {
  return P1;
}

CPoint CTriangle :: GetP2() const {
  return P2;
}

CPoint CTriangle :: GetP3() const {
  return P3;
}


void CTriangle :: Print() {
  cout << "Triangle " << P1 << "," << P2 << "," << P3 << endl;
  cout << "P1P2 = " << P1P2 << ", P2P3 = " << P2P3 << ", P3P1 = " << P3P1 << endl;
}

void CTriangle :: setDebug(int d) {
  debug = d;
}

int CTriangle :: getID() {
  return id;
}

int CTriangle :: getCurrent() {
  return current;
}

int CTriangle :: getTotal() {
  return total;
}



