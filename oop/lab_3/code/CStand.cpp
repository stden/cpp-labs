//Файл : CStand.cpp
//Реализация класса "стенд"
//Автор : Монько А.О.
//Дата : 22.02.2010 Редакция : 1.0


#include "CStand.h"
#include <iostream.h>


unsigned int CStand :: debug = 0;
unsigned int CStand :: total = 0;
unsigned int CStand :: current = 0;

void CStand :: AddPoints () {
	MainPoints.Append(new CLNode<CPoint>(Stand.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Stand.GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Stand.GetP3()));

}

CStand :: CStand (CPoint _P1, double _P1P2, CPoint _P3)
 : Stand(_P1, _P1P2, _P3) {


	AddPoints();

	id = ++total;
	++current;

       if (debug) cout << "Stand " << Stand.GetP1() << "," << Stand.GetP2() << "," << Stand.GetP3() << " created" << endl;
}

CStand :: CStand () : Stand() {


	AddPoints();

	id = ++total;
	++current;

       if (debug) cout << "Stand " << Stand.GetP1() << "," << Stand.GetP2() << "," << Stand.GetP3() << " created" << endl;
}



CStand :: ~CStand () {
        if (debug) cout << "Stand " << Stand.GetP1() << "," << Stand.GetP2() << "," << Stand.GetP3() << " deleted" << endl;
	--current;
}

int CStand :: invStand () {
return (Stand.inv() && MainPoints.GetElemByNum(0)->GetValue() == Stand.GetP1()
                    && MainPoints.GetElemByNum(1)->GetValue() == Stand.GetP2()
                    && MainPoints.GetElemByNum(2)->GetValue() == Stand.GetP3());
}

void CStand :: RefreshPoints () {
  CLNode<CPoint>* tN = MainPoints.GetFirst();
  tN->SetValue(Stand.GetP1());
  tN = tN->GetNext();
  tN->SetValue(Stand.GetP2());
  tN = tN->GetNext();
  tN->SetValue(Stand.GetP3());


}


void CStand:: SetP(double x, double y) {

        Stand.SetP1(x,y);
        RefreshPoints();

}

void CStand :: SetP(CPoint P0) {

        Stand.SetP1(P0);
        RefreshPoints();
}


void CStand :: MoveStand (double dx, double dy) {
        Stand.Move(dx,dy);
        RefreshPoints();
}

int CStand :: isIn (const CircleList<CPoint>& Points) const {
        for (int i = 0;i < Points.GetSize();i++) {
             if (Stand.isIn(Points.GetElemByNum(i)->GetValue()) == 0) return 0;
        }

return 1;
}


const CTriangle& CStand :: GetStand() const {
        return Stand;
}



const CircleList<CPoint>& CStand :: GetPoints ()  const{
        return MainPoints;
}

void CStand :: Print () {
	 cout << "Stand id = " << id <<endl;
         Stand.Print();
         cout << "Main Points : "<<endl;
         cout<<"-------------------"<<endl;
         MainPoints.Print();
         cout <<"-------------------"<<endl;

}

void CStand :: SetDebug (unsigned int d) {
        debug = d;
}

unsigned int CStand :: GetID () {
        return id;
}

unsigned int CStand :: GetCurrent () {
        return current;
}

unsigned int CStand :: GetTotal () {
        return total;
}


