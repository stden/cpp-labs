//Файл : CPiston.cpp
//Реализация класса "крышка"
//Автор : Монько А.О.
//Дата : 22.02.2010 Редакция : 1.0


#include "CCover.h"
#include <iostream.h>


unsigned int CCover :: debug = 0;
unsigned int CCover :: total = 0;
unsigned int CCover :: current = 0;


CCover :: CCover (CPoint P0, double cover_width, double cover_height, double hole_width) : Cover(P0.GetX(), P0.GetY(), cover_width, cover_height),
  Hole(P0.GetX() + cover_width / 2 - hole_width / 2, P0.GetY(), hole_width, cover_height) {

  MainPoints.Append(new CLNode<CPoint>(Cover.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP2()));

  id = ++total;
  ++current;

  if (debug) cout << "Cover  " << Cover.GetP1() << "," << Cover.GetP2() <<
                    "," << Cover.GetP3() << "," << Cover.GetP4() <<
                    " Width = " << Cover.GetWidth() << ", Height = " << Cover.GetHeight() << endl <<
                    "Hole " << Hole.GetP1() << "," << Hole.GetP2() <<
                    "," << Hole.GetP3() << "," << Hole.GetP4() <<
                    " Width = " << Cover.GetWidth() << " created" << endl;
}


CCover :: CCover (): Cover(0, 1, 1, 1),
  Hole(0.4, 1, 0.1, 1) {

  MainPoints.Append(new CLNode<CPoint>(Cover.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Cover.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Hole.GetP2()));

  id = ++total;
  ++current;

  if (debug) cout << "Cover  " << Cover.GetP1() << "," << Cover.GetP2() <<
                    "," << Cover.GetP3() << "," << Cover.GetP4() <<
                    " Width = " << Cover.GetWidth() << ", Height = " << Cover.GetHeight() << endl <<
                    "Hole " << Hole.GetP1() << "," << Hole.GetP2() <<
                    "," << Hole.GetP3() << "," << Hole.GetP4() <<
                    " Width = " << Cover.GetWidth() << " created" << endl;
}


CCover :: ~CCover () {
  if (debug) cout << "Cover  " << Cover.GetP1() << "," << Cover.GetP2() <<
                    "," << Cover.GetP3() << "," << Cover.GetP4() <<
                    " Width = " << Cover.GetWidth() << ", Height = " << Cover.GetHeight() << endl <<
                    "Hole " << Hole.GetP1() << "," << Hole.GetP2() <<
                    "," << Hole.GetP3() << "," << Hole.GetP4() <<
                    " Width = " << Cover.GetWidth() << " deleted" << endl;

  --current;
}

int CCover :: inv () {
  return (Cover.inv() && Hole.inv() && (Cover.GetHeight() == Hole.GetHeight())
          && (Hole.GetWidth() < Cover.GetWidth()) && (Hole.GetWidth() / 2 <= 1));
}

void CCover :: RefreshPoints () {
  CLNode<CPoint>* tN = MainPoints.GetFirst();
  tN->SetValue(Cover.GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetP4());
  tN = tN->GetNext();
  tN->SetValue(Hole.GetP1());
  tN = tN->GetNext();
  tN->SetValue(Hole.GetP2());
  tN = tN->GetNext();
  tN->SetValue(Hole.GetP3());
  tN = tN->GetNext();
  tN->SetValue(Hole.GetP4());


}


void CCover :: SetP1(double x, double y) {
  double d = Cover.GetP1().d(Hole.GetP1());
  Cover.SetP1(x, y);
  Hole.SetP1(Cover.GetP1().GetX() + d, Cover.GetP1().GetY());
  RefreshPoints();

}

void CCover :: SetP1(CPoint P0) {
  double d = Cover.GetP1().d(Hole.GetP1());
  Cover.SetP1(P0);
  Hole.SetP1(Cover.GetP1().GetX() + d, Cover.GetP1().GetY());
  RefreshPoints();
}


void CCover :: Move (double dx, double dy) {
  Cover.SetP1(Cover.GetP1().GetX() + dx, Cover.GetP1().GetY() + dy);
  Hole.SetP1(Hole.GetP1().GetX() + dx, Hole.GetP1().GetY() + dy);
  RefreshPoints();
}

CRectangle CCover :: GetHole() const {
  return Hole;
}

CRectangle CCover :: GetCover() const {
  return Cover;
}

const CircleList<CPoint>& CCover :: GetPoints ()  const {
  return MainPoints;
}

void CCover :: Print () {
  cout << "Cover " << Cover.GetP1() << "," << Cover.GetP2() <<
       "," << Cover.GetP3() << "," << Cover.GetP4() <<
       " Width = " << Cover.GetWidth() << ", Height = " << Cover.GetHeight() << endl <<
       "Hole " << Hole.GetP1() << "," << Hole.GetP2() <<
       "," << Hole.GetP3() << "," << Hole.GetP4() <<
       " Width = " << Cover.GetWidth() << endl;
}

void CCover :: SetDebug (unsigned int d) {
  debug = d;
}

unsigned int CCover :: GetID () {
  return id;
}

unsigned int CCover :: GetCurrent () {
  return current;
}

unsigned int CCover :: GetTotal () {
  return total;
}

