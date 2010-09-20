// Файл: CPiston.cpp
// Реализация класса "поршень"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 22.02.2010 Редакция: 1.0


#include "CPiston.h"
#include <iostream.h>


int CPiston :: debug = 0;
int CPiston :: total = 0;
int CPiston :: current = 0;


CPiston :: CPiston (double x1, double y1, double _width, double _height, double _length) : Piston(x1,y1,_width,_height),
Stock((x1 + x1 + _width)/2,(y1 + y1)/2,_length)  {

        MainPoints.Append(new CLNode<CPoint>(Piston.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP4()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP2()));

	id = ++total;
	++current;

       if (debug) cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<< " created"<<endl;
}

CPiston :: CPiston (CPoint P0, double _width, double _height,double _length) : Piston(P0.GetX(),P0.GetY(),_width,_height),
Stock((P0.GetX() + P0.GetX() + _width)/2,(P0.GetY() + P0.GetY())/2,_length) {

	MainPoints.Append(new CLNode<CPoint>(Piston.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP4()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP2()));

	id = ++total;
	++current;

        if (debug) cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<< " created"<<endl;
}

CPiston :: CPiston (CPoint P0, double wh): Piston(P0.GetX(),P0.GetY(),wh,wh),
Stock((P0.GetX() + P0.GetX() + wh)/2,(P0.GetY() + P0.GetY())/2,wh) {

        MainPoints.Append(new CLNode<CPoint>(Piston.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP4()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP2()));

	id = ++total;
	++current;

        if (debug) cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<< " created"<<endl;
}

CPiston :: CPiston (): Piston(0,1,1,1),
Stock(1/2,1,1) {

        MainPoints.Append(new CLNode<CPoint>(Piston.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Piston.GetP4()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Stock.GetP2()));

	id = ++total;
	++current;

       if (debug) cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<< " created"<<endl;
}


CPiston :: ~CPiston () {
       if (debug) cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<< " deleted"<<endl;
	--current;
}

int CPiston :: inv () {
return (Stock.inv() && Piston.inv() &&
        (Stock.GetP1().GetX() == (Piston.GetP1().GetX() + Piston.GetP2().GetX())/2) &&
        (Stock.GetP1().GetY() == (Piston.GetP1().GetY() + Piston.GetP2().GetY())/2));
}

void CPiston :: RefreshPoints () {
  CLNode<CPoint>* tN = MainPoints.GetFirst();
  tN->SetValue(Piston.GetP1());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetP2());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetP3());
  tN = tN->GetNext();
  tN->SetValue(Piston.GetP4());
  tN = tN->GetNext();
  tN->SetValue(Stock.GetP1());
  tN = tN->GetNext();
  tN->SetValue(Stock.GetP2());

}


void CPiston :: SetP1(double x, double y) {

        Piston.SetP1(x,y);
        Stock.SetP1((Piston.GetP1().GetX() + Piston.GetP2().GetX())/2,(Piston.GetP1().GetY() + Piston.GetP2().GetY())/2);
        RefreshPoints();

}

void CPiston :: SetP1(CPoint P0) {
        Piston.SetP1(P0);
        Stock.SetP1((Piston.GetP1().GetX() + Piston.GetP2().GetX())/2,P0.GetY());
        RefreshPoints();
}


void CPiston :: Move (double dx, double dy) {
        Piston.SetP1(Piston.GetP1().GetX() + dx,Piston.GetP1().GetY() + dy);
        Stock.SetP1(Stock.GetP1().GetX() + dx,Stock.GetP1().GetY() + dy);
        RefreshPoints();
}

double CPiston :: GetWidth() const {
        return Piston.GetWidth();
}

double CPiston :: GetHeight() const {
        return Piston.GetHeight();
}

double CPiston :: GetLength() const {
        return Stock.GetL();
}

CRectangle CPiston :: GetPiston() const {
        return Piston;
}

CSection CPiston :: GetStock() const {
        return Stock;
}

const CircleList<CPoint>& CPiston :: GetPoints ()  const{
        return MainPoints;
}

void CPiston :: Print () {
	cout << "Piston : id = " << id << " " << Piston.GetP1() << "," << Piston.GetP2() <<
        "," << Piston.GetP3() << "," << Piston.GetP4() <<
        " Width = "<< Piston.GetWidth() << ", Height = " << Piston.GetHeight()<< endl <<
        "Stock - P1"<<Stock.GetP1() << ", P2" << Stock.GetP2()<<", L = " << Stock.GetL()<<endl;
        cout << "Main Points : "<<endl<<"-------------------"<<endl;
        MainPoints.Print();
        cout <<"-------------------"<<endl;

}

void CPiston :: setDebug(int d) {
        debug = d;
}

int CPiston :: getID() {
        return id;
}

int CPiston :: getCurrent() {
        return current;
}

int CPiston :: getTotal() {
        return total;
}


