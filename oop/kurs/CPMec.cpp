// Файл: CPMec.cpp
// Реализация класса "поршневой механизм"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CPMec.h"
#include <iostream.h>
#include <conio.h>-


int CPistonMechanism :: debug = 0;
int CPistonMechanism :: total = 0;
int CPistonMechanism :: current = 0;

void CPistonMechanism :: AddPoints() {
  MainPoints.Append(new CLNode<CPoint>(Cup.GetLeftSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetLeftSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetLeftSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetLeftSide().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetBottomSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetBottomSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetBottomSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetBottomSide().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetRightSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetRightSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetRightSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Cup.GetRightSide().GetP4()));

  MainPoints.Append(new CLNode<CPoint>(Piston.GetPiston().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Piston.GetPiston().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(Piston.GetPiston().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(Piston.GetPiston().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(Piston.GetStock().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(Piston.GetStock().GetP2()));
}

CPistonMechanism :: CPistonMechanism(double x1, double y1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength)
    : Cup(x1, y1, leftwidth, leftheight, bottomwidth, bottomheight, rightwidth),
    Piston(x1 + leftwidth, y2, bottomwidth, pistonheight, stocklength) {


  AddPoints();

  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
    cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
    cout << "RightCupSide : "; Cup.GetRightSide().Print();
    cout << "Piston : "; Piston.GetPiston().Print();
    cout << "Stock : "; Piston.GetStock().Print(); cout << endl << " created";
  }
}

CPistonMechanism :: CPistonMechanism(CPoint P1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength)
    : Cup(P1.GetX(), P1.GetY(), leftwidth, leftheight, bottomwidth, bottomheight, rightwidth),
    Piston(P1.GetX() + leftwidth, y2, bottomwidth, pistonheight, stocklength) {

  AddPoints();


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
    cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
    cout << "RightCupSide : "; Cup.GetRightSide().Print();
    cout << "Piston : "; Piston.GetPiston().Print();
    cout << "Stock : "; Piston.GetStock().Print(); cout << endl << " created";
  }
}

CPistonMechanism :: CPistonMechanism(const CCup& _cup, const CPiston& _piston)
    : Cup(_cup.GetLeftSide().GetP1(), _cup.GetLeftSide().GetWidth(), _cup.GetLeftSide().GetHeight(),
          _cup.GetBottomSide().GetWidth(), _cup.GetBottomSide().GetHeight(),
          _cup.GetRightSide().GetWidth()),
    Piston(_piston.GetPiston().GetP1(), _piston.GetPiston().GetWidth(), _piston.GetPiston().GetHeight(), _piston.GetStock().GetL()) {

  AddPoints();


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
    cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
    cout << "RightCupSide : "; Cup.GetRightSide().Print();
    cout << "Piston : "; Piston.GetPiston().Print();
    cout << "Stock : "; Piston.GetStock().Print(); cout << endl << " created";
  }
}

CPistonMechanism :: CPistonMechanism()
    : Cup(),
    Piston() {

  AddPoints();


  id = ++total;
  ++current;

  if (debug) {
    cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
    cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
    cout << "RightCupSide : "; Cup.GetRightSide().Print();
    cout << "Piston : "; Piston.GetPiston().Print();
    cout << "Stock : "; Piston.GetStock().Print(); cout << endl << " created";
  }
}

CPistonMechanism :: ~CPistonMechanism() {
  if (debug) {
    cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
    cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
    cout << "RightCupSide : "; Cup.GetRightSide().Print();
    cout << "Piston : "; Piston.GetPiston().Print();
    cout << "Stock : "; Piston.GetStock().Print(); cout << endl << " deleted";
  }
  --current;
}

int CPistonMechanism :: inv() {
  return (Cup.inv() && Piston.inv() && (Piston.GetPiston().GetWidth() == Cup.GetBottomSide().GetP1().d(Cup.GetBottomSide().GetP2())) &&
          (Cup.GetBottomSide().GetP1().d(Piston.GetPiston().GetP3()) >= 0) && (Piston.GetPiston().GetP3().GetY() >= Cup.GetBottomSide().GetP1().GetY()) &&
          (Piston.GetPiston().GetP1().GetY() <= Cup.GetLeftSide().GetP2().GetY()) &&
          (Piston.GetStock().GetL() >= Cup.GetLeftSide().GetHeight() - Cup.GetBottomSide().GetHeight() - Piston.GetPiston().GetHeight()) &&
          (Cup.GetLeftSide().GetP1() == MainPoints.GetElemByNum(0)->GetValue() &&
           Cup.GetLeftSide().GetP2() == MainPoints.GetElemByNum(1)->GetValue() &&
           Cup.GetLeftSide().GetP3() == MainPoints.GetElemByNum(2)->GetValue() &&
           Cup.GetLeftSide().GetP4() == MainPoints.GetElemByNum(3)->GetValue() &&
           Cup.GetBottomSide().GetP1() == MainPoints.GetElemByNum(4)->GetValue() &&
           Cup.GetBottomSide().GetP2() == MainPoints.GetElemByNum(5)->GetValue() &&
           Cup.GetBottomSide().GetP3() == MainPoints.GetElemByNum(6)->GetValue() &&
           Cup.GetBottomSide().GetP4() == MainPoints.GetElemByNum(7)->GetValue() &&
           Cup.GetRightSide().GetP1() == MainPoints.GetElemByNum(8)->GetValue() &&
           Cup.GetRightSide().GetP2() == MainPoints.GetElemByNum(9)->GetValue() &&
           Cup.GetRightSide().GetP3() == MainPoints.GetElemByNum(10)->GetValue() &&
           Cup.GetRightSide().GetP4() == MainPoints.GetElemByNum(11)->GetValue() &&
           Piston.GetPiston().GetP1() == MainPoints.GetElemByNum(12)->GetValue() &&
           Piston.GetPiston().GetP2() == MainPoints.GetElemByNum(13)->GetValue() &&
           Piston.GetPiston().GetP3() == MainPoints.GetElemByNum(14)->GetValue() &&
           Piston.GetPiston().GetP4() == MainPoints.GetElemByNum(15)->GetValue() &&
           Piston.GetStock().GetP1() == MainPoints.GetElemByNum(16)->GetValue() &&
           Piston.GetStock().GetP2() == MainPoints.GetElemByNum(17)->GetValue()));
}

void CPistonMechanism :: RefreshPoints() {
  CLNode<CPoint>* tN = MainPoints.GetFirst();
  tN->SetValue(Cup.GetLeftSide().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetLeftSide().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetLeftSide().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetLeftSide().GetP4());

  tN = tN->GetNext();
  tN->SetValue(Cup.GetBottomSide().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetBottomSide().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetBottomSide().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetBottomSide().GetP4());

  tN = tN->GetNext();
  tN->SetValue(Cup.GetRightSide().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetRightSide().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetRightSide().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cup.GetRightSide().GetP4());

  tN = tN->GetNext();
  tN->SetValue(Piston.GetPiston().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetPiston().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetPiston().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetPiston().GetP4());

  tN = tN->GetNext();
  tN->SetValue(Piston.GetStock().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetStock().GetP2());

}


void CPistonMechanism:: SetP1(double x, double y) {

  double tL = 0;

  tL = Cup.GetBottomSide().GetP1().d(Piston.GetPiston().GetP3());
  Cup.SetP1(x, y);
  Piston.SetP1(Cup.GetBottomSide().GetP1().GetX(), Cup.GetBottomSide().GetP1().GetY() + tL + Piston.GetPiston().GetHeight());
  RefreshPoints();

}

void CPistonMechanism :: SetP1(CPoint P0) {
  double tL = 0;

  tL = CPoint(Cup.GetBottomSide().GetP1()).d(Piston.GetPiston().GetP3());
  Cup.SetP1(P0);
  Piston.SetP1(Cup.GetBottomSide().GetP1().GetX(), Cup.GetBottomSide().GetP1().GetY() + tL + Piston.GetPiston().GetHeight());
  RefreshPoints();
}


void CPistonMechanism :: Move(double dx, double dy) {
  Cup.Move(dx, dy);
  Piston.Move(dx, dy);
  RefreshPoints();
}

int CPistonMechanism :: MovePiston(double dy) {
  double td;
  if (dy >= 0) {

    if (dy <= Piston.GetPiston().GetP1().d(Cup.GetLeftSide().GetP2())) {
      Piston.Move(0, dy);
      RefreshPoints();
      return 1;
    }
  } else {
    if ((-dy <= Piston.GetPiston().GetP3().d(Cup.GetBottomSide().GetP1()))) {
      Piston.Move(0, dy);
      RefreshPoints();
      return 1;
    }
  }
  return 0;
}

const CCup& CPistonMechanism :: GetCup() const {
  return Cup;
}

const CPiston& CPistonMechanism :: GetPiston() const {
  return Piston;
}



const CircleList<CPoint>& CPistonMechanism :: GetPoints()  const {
  return MainPoints;
}

void CPistonMechanism :: Print() const {
  cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
  getch();
  cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
  getch();
  cout << "RightCupSide : "; Cup.GetRightSide().Print();
  getch();
  cout << "Piston : "; Piston.GetPiston().Print();
  cout << "Stock : "; Piston.GetStock().Print();
  getch();
  cout << "Main Points : " << endl;
  cout << "-------------------" << endl;
  MainPoints.Print();
  cout << "-------------------" << endl;
  getch();

}

void CPistonMechanism :: setDebug(int d) {
  debug = d;
}

int CPistonMechanism :: getID() {
  return id;
}

int CPistonMechanism :: getCurrent() {
  return current;
}

int CPistonMechanism :: getTotal() {
  return total;
}

ostream& operator<<(ostream& output, const CPistonMechanism& P) {

  output << "LeftCupSide : " << P.GetCup().GetLeftSide();
  output << "BottomCupSide : " << P.GetCup().GetBottomSide();
  output << "RightCupSide : " << P.GetCup().GetRightSide();
  output << "Piston : " << P.GetPiston().GetPiston();
  output << "Stock : P1" << P.GetPiston().GetStock().GetP1() << ", P2" << P.GetPiston().GetStock().GetP2() << ", L = " << P.GetPiston().GetStock().GetL() << endl;
  output << "Main Points : " << endl;
  output << "-------------------" << endl;
  if (P.GetPoints().GetSize() == 0) {
    cout << endl << "The List is empty" << endl;
    return output;
  }

  short i = 0;
  CLNode <CPoint>* temp = P.GetPoints().GetFirst();

  while (i < P.GetPoints().GetSize() && temp) {
    output << "Element " << i << ": " << temp->GetValue() << endl;
    i++;
    temp = temp->GetNext();
  }

  output << endl << endl;
  output << "-------------------" << endl;

  return output;
}

