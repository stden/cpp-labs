// Файл: CPColl.cpp
// Реализация класса "набор поршневых механизмов"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CPColl.h"
#include <iostream.h>


int CPistonCollection :: debug = 0;
int CPistonCollection :: total = 0;
int CPistonCollection :: current = 0;


CPistonCollection :: CPistonCollection() : /*MainPoints(),*/ Collection(), Length(0) {
  id = ++total;
  ++current;
  if (debug)cout << "Collection id = " << id << " Length = " << Length << " created";

}


CPistonCollection :: ~CPistonCollection() {
  if (debug)cout << "Collection id = " << id << " Length = " << Length << " deleted";
  --current;
}



/*void CPistonCollection :: RefreshPoints () {
Collection.GetFirst();
//MainPoints.GetFirst();
for (int i = 0;i < Length;i++,Collection.NextCur()) {
  for (int j = 0;j < 18;j++) {
        MainPoints.SetCur(Collection.GetCur()->GetValue()->GetPoints().GetElemByNum(j)->GetValue());
        MainPoints.NextCur();
   }
}

}*/

int CPistonCollection :: invColl() {
  Collection.GetFirst();
  int r = 1;
  for (int i = 0;i < Length;i ++, Collection.NextCur()) {
    r = Collection.GetCur()->GetValue()->inv();
    if (r == 0) return 0;
  }


  return 1;
}

void CPistonCollection :: Add(CPistonMechanism* P) {

  Collection.Append(new CLNode<CPistonMechanism*>(P));

  /*MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetLeftSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetLeftSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetLeftSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetLeftSide().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetBottomSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetBottomSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetBottomSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetBottomSide().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetRightSide().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetRightSide().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetRightSide().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(P->GetCup().GetRightSide().GetP4()));

  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetPiston().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetPiston().GetP2()));
  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetPiston().GetP3()));
  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetPiston().GetP4()));
  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetStock().GetP1()));
  MainPoints.Append(new CLNode<CPoint>(P->GetPiston().GetStock().GetP2()));*/

  ++Length;
}

void CPistonCollection :: Delete(int N) {

  Collection.GetFirst();
//     MainPoints.GetFirst();

  if ((N > 0) && (N < Collection.GetSize()) && Collection.GetSize() > 0) {
    for (int i = 0;i < Collection.GetSize();i++) {
      if (i == N) {
        Collection.RemoveCur();
        //for (int k = 0; k < 18;k++){ MainPoints.RemoveCur(); MainPoints.NextCur(); }
        return;
      }

      Collection.NextCur();
      //      for (int j = 0; j < 18;j++) MainPoints.NextCur();
    }
  }

}


void CPistonCollection :: SetP1(double x, double y) {

  Collection.GetFirst();
  for (int i = 0; i < Length; i++, Collection.NextCur())
    Collection.GetCur()->GetValue()->SetP1(x, y);

  // RefreshPoints();

}

void CPistonCollection :: SetP1(CPoint P0) {
  double tL = 0;

  Collection.GetFirst();
  for (int i = 0; i < Length; i++, Collection.NextCur())
    Collection.GetCur()->GetValue()->SetP1(P0);

  // RefreshPoints();
}


void CPistonCollection :: Move(double dx, double dy) {
  Collection.GetFirst();
  for (int i = 0; i < Length; i++, Collection.NextCur())
    Collection.GetCur()->GetValue()->Move(dx, dy);

  //RefreshPoints();
}

void CPistonCollection :: MovePiston(double dy) {
  Collection.GetFirst();
  for (int i = 0; i < Length; i++, Collection.NextCur())
    Collection.GetCur()->GetValue()->MovePiston(dy);

  // RefreshPoints();
}

int CPistonCollection :: GetLength() const {
  return Length;
}

/*const CircleList<CPoint>& CPistonCollection :: GetPoints ()  const{
        return MainPoints;
}  */

const CircleList<CPistonMechanism*>& CPistonCollection :: GetCollection()  const {
  return Collection;
}

void CPistonCollection :: Print() {
  if (Collection.GetSize() == 0) {
    cout << endl << "The List is empty" << endl;
    return;
  }

  short i = 0;
  CLNode <CPistonMechanism*> * temp = Collection.GetFirst();

  while (i < Collection.GetSize() && temp) {
    cout << "Element " << i << ": ";temp->GetValue()->Print(); cout << endl;
    i++;
    temp = temp->GetNext();
  }

  cout << endl << endl;


  /* MainPoints.Print();
   cout <<"-------------------"<<endl;*/

}

void CPistonCollection :: setDebug(int d) {
  debug = d;
}

int CPistonCollection :: getID() {
  return id;
}

int CPistonCollection :: getCurrent() {
  return current;
}

int CPistonCollection :: getTotal() {
  return total;
}


