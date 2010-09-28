// Файл: CCup.cpp
// Реализация класса "стакан"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CCup.h"
#include <iostream.h>


int CCup :: debug = 0;
int CCup :: total = 0;
int CCup :: current = 0;


CCup :: CCup(double x1, double y1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth)
    : LeftCupSide(x1, y1, leftwidth, leftheight),
    BottomCupSide(x1 + leftwidth, y1 - leftheight + bottomheight, bottomwidth, bottomheight),
    RightCupSide(x1 + leftwidth + bottomwidth, y1 - leftheight + leftheight, rightwidth, leftheight)  {

  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP4()));


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftSide : "; LeftCupSide.Print();
    cout << "BottomSide : "; BottomCupSide.Print();
    cout << "RightSide : "; RightCupSide.Print(); cout << "created";
  }
}

CCup :: CCup(CPoint P0, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth)
    : LeftCupSide(P0.GetX(), P0.GetY(), leftwidth, leftheight),
    BottomCupSide(P0.GetX() + leftwidth, P0.GetY() - leftheight + bottomheight, bottomwidth, bottomheight),
    RightCupSide(P0.GetX() + leftwidth + bottomwidth, P0.GetY() - leftheight + leftheight, rightwidth, leftheight)  {

  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP4()));


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftSide : "; LeftCupSide.Print();
    cout << "BottomSide : "; BottomCupSide.Print();
    cout << "RightSide : "; RightCupSide.Print(); cout << "created";
  }
}

CCup :: CCup()
    : LeftCupSide(0, 1, 1, 1),
    BottomCupSide(1, 1, 1, 1),
    RightCupSide(2, 1, 1, 1)  {

  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(LeftCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(BottomCupSide.GetP4()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP1()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP2()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP3()));
  MainPoints.Append(new CLNode<CPoint>(RightCupSide.GetP4()));


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftSide : "; LeftCupSide.Print();
    cout << "BottomSide : "; BottomCupSide.Print();
    cout << "RightSide : "; RightCupSide.Print(); cout << "created";
  }
}

CCup :: ~CCup() {
  if (debug) {
    cout << "LeftSide : "; LeftCupSide.Print();
    cout << "BottomSide : "; BottomCupSide.Print();
    cout << "RightSide : "; RightCupSide.Print(); cout << "deleted";
  }
  --current;
}

int CCup :: inv() {
  return (LeftCupSide.inv() && BottomCupSide.inv() && RightCupSide.inv() &&
          (LeftCupSide.GetHeight() == RightCupSide.GetHeight()) &&
          (LeftCupSide.GetP1() == MainPoints.GetElemByNum(0)->GetValue() &&
           LeftCupSide.GetP2() == MainPoints.GetElemByNum(1)->GetValue() &&
           LeftCupSide.GetP3() == MainPoints.GetElemByNum(2)->GetValue() &&
           LeftCupSide.GetP4() == MainPoints.GetElemByNum(3)->GetValue() &&
           BottomCupSide.GetP1() == MainPoints.GetElemByNum(4)->GetValue() &&
           BottomCupSide.GetP2() == MainPoints.GetElemByNum(5)->GetValue() &&
           BottomCupSide.GetP3() == MainPoints.GetElemByNum(6)->GetValue() &&
           BottomCupSide.GetP4() == MainPoints.GetElemByNum(7)->GetValue() &&
           RightCupSide.GetP1() == MainPoints.GetElemByNum(8)->GetValue() &&
           RightCupSide.GetP2() == MainPoints.GetElemByNum(9)->GetValue() &&
           RightCupSide.GetP3() == MainPoints.GetElemByNum(10)->GetValue() &&
           RightCupSide.GetP4() == MainPoints.GetElemByNum(11)->GetValue()));
}

void CCup :: RefreshPoints() {
  CLNode<CPoint>* tN = MainPoints.GetFirst();
  tN->SetValue(LeftCupSide.GetP1());
  tN = tN->GetNext();
  tN->SetValue(LeftCupSide.GetP2());
  tN = tN->GetNext();
  tN->SetValue(LeftCupSide.GetP3());
  tN = tN->GetNext();
  tN->SetValue(LeftCupSide.GetP4());

  tN = tN->GetNext();
  tN->SetValue(BottomCupSide.GetP1());
  tN = tN->GetNext();
  tN->SetValue(BottomCupSide.GetP2());
  tN = tN->GetNext();
  tN->SetValue(BottomCupSide.GetP3());
  tN = tN->GetNext();
  tN->SetValue(BottomCupSide.GetP4());

  tN = tN->GetNext();
  tN->SetValue(RightCupSide.GetP1());
  tN = tN->GetNext();
  tN->SetValue(RightCupSide.GetP2());
  tN = tN->GetNext();
  tN->SetValue(RightCupSide.GetP3());
  tN = tN->GetNext();
  tN->SetValue(RightCupSide.GetP4());

}


void CCup :: SetP1(double x, double y) {

  LeftCupSide.SetP1(x, y);
  BottomCupSide.SetP1(x + LeftCupSide.GetWidth(), y - LeftCupSide.GetHeight() + BottomCupSide.GetHeight());
  RightCupSide.SetP1(x + LeftCupSide.GetWidth() + BottomCupSide.GetWidth(), y);
  RefreshPoints();

}

void CCup :: SetP1(CPoint P0) {
  LeftCupSide.SetP1(P0);
  BottomCupSide.SetP1(P0.GetX() + LeftCupSide.GetWidth(), P0.GetY() - LeftCupSide.GetHeight() + BottomCupSide.GetHeight());
  RightCupSide.SetP1(P0.GetX() + LeftCupSide.GetWidth() + BottomCupSide.GetWidth(), P0.GetY());
  RefreshPoints();
}


void CCup :: Move(double dx, double dy) {
  LeftCupSide.SetP1(LeftCupSide.GetP1().GetX() + dx, LeftCupSide.GetP1().GetY() + dy);
  BottomCupSide.SetP1(BottomCupSide.GetP1().GetX() + dx, BottomCupSide.GetP1().GetY() + dy);
  RightCupSide.SetP1(RightCupSide.GetP1().GetX() + dx, RightCupSide.GetP1().GetY() + dy);
  RefreshPoints();
}

CRectangle CCup :: GetLeftSide() const {
  return LeftCupSide;
}

CRectangle CCup :: GetBottomSide() const {
  return BottomCupSide;
}

CRectangle CCup :: GetRightSide() const {
  return RightCupSide;
}

const CircleList<CPoint>& CCup :: GetPoints()  const {
  return MainPoints;
}

void CCup :: Print() {
  cout << "LeftSide : "; LeftCupSide.Print();
  cout << "BottomSide : "; BottomCupSide.Print();
  cout << "RightSide : "; RightCupSide.Print();
  cout << "Main Points : " << endl;
  cout << "-------------------" << endl;
  MainPoints.Print();
  cout << "-------------------" << endl;

}

void CCup :: setDebug(int d) {
  debug = d;
}

int CCup :: getID() {
  return id;
}

int CCup :: getCurrent() {
  return current;
}

int CCup :: getTotal() {
  return total;
}

