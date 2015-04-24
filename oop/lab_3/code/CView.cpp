//Файл : CView.cpp
//Реализация класса "Вид на стенд с замкнутыми поршневыми механизмами"
//Автор : Монько А.О.
//Дата : 22.05.2010 Редакция : 1.0


#include "CView.h"
#include <iostream.h>
#include <conio.h>


CView :: CView (CPoint _P1, double _P1P2, CPoint _P3)
  : CStand(_P1, _P1P2, _P3),
    CPistonCollection() {}


CView :: CView ()
  : CStand(),
    CPistonCollection()   {}




CView :: ~CView () {}


int CView :: inv () {
  return (invColl() && invStand());
}



void CView :: SetCollectionP1(CPoint P0) {
  CPistonCollection :: SetP1(P0);

}

void CView :: SetStandP1(CPoint P0) {
  CStand :: SetP(P0);

}


void CView :: MoveCollection (double dx, double dy) {
  CPistonCollection :: Move(dx, dy);
}

void CView :: MoveStand (double dx, double dy) {
  CStand :: MoveStand(dx, dy);
}

void CView :: Add(CPistonMechanism* P) const {
  CPistonCollection :: Add(P);
}

void CView :: Add(const CPistonCollection& C) const {

  for (int i = 0; i < C.GetCollection().GetSize(); i++)
    CPistonCollection :: Add(C.GetCollection().GetElemByNum(i)->GetValue());
}

int CView :: isOnStand (CPistonMechanism* P) const {
  return isIn(P->GetPoints());
}


void CView :: PrintView () {
  CStand :: Print ();
  cout << "Press any key to see more" << endl;
  getch();
  Collection.GetFirst();

  for (int i = 0; i < Collection.GetSize(); i++, Collection.NextCur())
    if (isOnStand(Collection.GetCur()->GetValue())) Collection.GetCur()->GetValue()->Print();
}

void CView :: Print () {
  CStand :: Print ();
  cout << "Press any key to see more" << endl;
  getch();
  CPistonCollection :: Print();
}




