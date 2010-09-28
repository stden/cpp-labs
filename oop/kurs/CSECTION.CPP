// Файл: CSection.cpp
// Реализация класса "отрезок"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CSection.h"
#include <iostream.h>
#include <math.h>


int CSection :: debug = 0;
int CSection :: total = 0;
int CSection :: current = 0;


CSection :: CSection(double x1, double y1, double len) {
  P1.SetX(x1);
  P1.SetY(y1);
  P2.SetX(x1);
  P2.SetY(y1 + len);

  L = len;
  id = ++total;
  ++current;

  if (debug) cout << "Section " << P1 << " -- " << P2 << ", Length = " << L << " created" << endl;
}

CSection :: CSection(CPoint P0, double len) {
  P1.SetX(P0.GetX());
  P1.SetY(P0.GetY());
  P2.SetX(P0.GetX());
  P2.SetY(P0.GetY() + len);

  L = len;
  id = ++total;
  ++current;

  if (debug) cout << "Section " << P1 << " -- " << P2 << ", Length = " << L << " created" << endl;
}

CSection :: CSection() {
  P1.SetX(0);
  P1.SetY(0);
  P2.SetX(1);
  P2.SetY(1);

  L = fabs(P2.GetY() - P1.GetY());
  id = ++total;
  ++current;

  if (debug) cout << "Section " << P1 << " -- " << P2 << ", Length = " << L << " created" << endl;
}

CSection::~CSection() {
  if (debug) cout << "Section " << P1 << " -- " << P2 << ", Length = " << L << " deleted" << endl;
  --current;
}

int CSection :: inv() {
  return ((P1 >= -1000 && P1 <= 1000) && (P2 >= -1000 && P2 <= 1000) && (P1.GetX() == P2.GetX()) && (L));
}


void CSection :: SetP1(double x, double y) {
  P1.SetX(x);
  P1.SetY(y);
  P2.SetX(x);
  P2.SetY(y + L);
}

void CSection :: SetP1(CPoint P0) {
  P1.SetX(P0.GetX());
  P1.SetY(P0.GetY());
  P2.SetX(P0.GetX());
  P2.SetY(P0.GetY() + L);
}

void CSection :: SetL(double L0) {
  if (L0) L = L0;
}

void CSection :: Move(double dx, double dy) {
  P1.SetX(P1.GetX() + dx);
  P1.SetY(P1.GetY() + dy);
  P2.SetX(P2.GetX() + dx);
  P2.SetY(P2.GetY() + dy);
}

CPoint CSection :: GetP1() const {
  return P1;
}

CPoint CSection :: GetP2() const {
  return P2;
}

double CSection :: GetL() const {
  return L;
}


int CSection::isOn(CPoint P) {      // Euclidean distance
  if (P1.GetX() - P2.GetX() == 0) return 0;
  double p = (P.GetX() - P2.GetX()) / (P1.GetX() - P2.GetX());

  return ((P1.GetY() * p + (1 - p) * P2.GetY() == P.GetY()) && ((p >= 0) && (p <= 1)));
}

int CSection :: isParallel(const CSection& s) {
  if (((P2.GetX() - P1.GetX())*(s.GetP2().GetY() - s.GetP1().GetY()) - (P2.GetY() - P1.GetY())*(s.GetP2().GetX() - s.GetP1().GetX())) == 0) return 1;
  else return 0;

  return 0;
}


int CSection::isLeft(CPoint P) {
  return ((P1.GetX() - P.GetX()) * (P2.GetY() - P.GetY()) - (P2.GetX() - P.GetX()) * (P1.GetY() - P.GetY()));
}





CSection& CSection :: operator=(CSection & S) {

  P1 = S.GetP1();
  P2 = S.GetP2();

  return *this;
}


int CSection :: operator == (CSection &s) {
  return (P1 == s.P1) && (P2 == s.P2);
}

void CSection :: Print() {
  cout << "P1" << P1 << " -- P2" << P2 << ", L = " << L << endl;
}

void CSection :: setDebug(int d) {
  debug = d;
}

int CSection :: getID() {
  return id;
}

int CSection :: getCurrent() {
  return current;
}

int CSection :: getTotal() {
  return total;
}





