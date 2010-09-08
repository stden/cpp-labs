//Файл : CPMec.cpp
//Реализация класса "поршневой механизм"
//Автор : Монько А.О.
//Дата : 22.02.2010 Редакция : 1.0


#include "CPCMec.h"
#include <iostream.h>
#include <conio.h>

void CClosedPistonMechanism :: AddPoints () {
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

        MainPoints.Append(new CLNode<CPoint>(Cover.GetCover().GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetCover().GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetCover().GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetCover().GetP4()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetHole().GetP1()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetHole().GetP2()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetHole().GetP3()));
        MainPoints.Append(new CLNode<CPoint>(Cover.GetHole().GetP4()));
}

CClosedPistonMechanism :: CClosedPistonMechanism (double x1, double y1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength,double cover_height,double hole_width)
 : CPistonMechanism(x1,y1,leftwidth,leftheight,bottomwidth,bottomheight,rightwidth,y2,pistonheight,stocklength),
   Cover(CPoint(x1,y1 + cover_height),leftwidth + bottomwidth + rightwidth,cover_height,hole_width)
     {


	AddPoints();

	id = ++total;
	++current;

       if (debug){ cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
         cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
         cout << "RightCupSide : "; Cup.GetRightSide().Print();
         cout << "Piston : "; Piston.GetPiston().Print();
         cout << "Stock : "; Piston.GetStock().Print(); cout <<endl<<
         cout << "Cover : "; Cover.GetCover().Print(); cout << endl;
         cout << "Hole : "; Cover.GetHole().Print(); cout <<" created";
       }
}

CClosedPistonMechanism :: CClosedPistonMechanism (CPoint P1, double leftwidth, double leftheight, double bottomwidth, double bottomheight, double rightwidth, double y2, double pistonheight, double stocklength, double cover_height, double hole_width)
 : CPistonMechanism(P1,leftwidth,leftheight,bottomwidth,bottomheight,rightwidth,y2,pistonheight,stocklength),
   Cover(CPoint(P1.GetX(),P1.GetY() + cover_height),leftwidth + bottomwidth + rightwidth,cover_height,hole_width)
   {

        AddPoints();


	id = ++total;
	++current;

      if (debug){ cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
         cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
         cout << "RightCupSide : "; Cup.GetRightSide().Print();
         cout << "Piston : "; Piston.GetPiston().Print();
         cout << "Stock : "; Piston.GetStock().Print(); cout <<endl<<
         cout << "Cover : "; Cover.GetCover().Print(); cout << endl;
         cout << "Hole : "; Cover.GetHole().Print(); cout <<" created";
       }
}



CClosedPistonMechanism :: CClosedPistonMechanism ()
 :  Cover()
   {

        AddPoints();


	id = ++total;
	++current;

      if (debug){ cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
         cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
         cout << "RightCupSide : "; Cup.GetRightSide().Print();
         cout << "Piston : "; Piston.GetPiston().Print();
         cout << "Stock : "; Piston.GetStock().Print(); cout <<endl<<
         cout << "Cover : "; Cover.GetCover().Print(); cout << endl;
         cout << "Hole : "; Cover.GetHole().Print(); cout <<" created";
       }
}

CClosedPistonMechanism :: ~CClosedPistonMechanism () {
        if (debug){ cout << "LeftCupSide : "; Cup.GetLeftSide().Print();
         cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
         cout << "RightCupSide : "; Cup.GetRightSide().Print();
         cout << "Piston : "; Piston.GetPiston().Print();
         cout << "Stock : "; Piston.GetStock().Print(); cout <<endl<<
         cout << "Cover : "; Cover.GetCover().Print(); cout << endl;
         cout << "Hole : "; Cover.GetHole().Print(); cout <<" deleted";
       }
	--current;
}

int CClosedPistonMechanism :: inv () {
return (Cup.inv() && Piston.inv() &&  (Piston.GetPiston().GetWidth() == Cup.GetBottomSide().GetP1().d(Cup.GetBottomSide().GetP2())) &&
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
         Piston.GetStock().GetP2() == MainPoints.GetElemByNum(17)->GetValue() &&
         Cover.GetCover().GetP1() == MainPoints.GetElemByNum(18)->GetValue() &&
         Cover.GetCover().GetP2() == MainPoints.GetElemByNum(19)->GetValue() &&
         Cover.GetCover().GetP3() == MainPoints.GetElemByNum(20)->GetValue() &&
         Cover.GetCover().GetP4() == MainPoints.GetElemByNum(21)->GetValue() &&
         Cover.GetHole().GetP1() == MainPoints.GetElemByNum(22)->GetValue() &&
         Cover.GetHole().GetP2() == MainPoints.GetElemByNum(23)->GetValue() &&
         Cover.GetHole().GetP3() == MainPoints.GetElemByNum(24)->GetValue() &&
         Cover.GetHole().GetP4() == MainPoints.GetElemByNum(25)->GetValue()) && Cover.inv());
}

void CClosedPistonMechanism :: RefreshPoints () {
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

  tN = tN->GetNext();
  tN->SetValue(Cover.GetCover().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetCover().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetCover().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetCover().GetP4());

  tN = tN->GetNext();
  tN->SetValue(Cover.GetHole().GetP1());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetHole().GetP2());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetHole().GetP3());
  tN = tN->GetNext();
  tN->SetValue(Cover.GetHole().GetP4());

}


void CClosedPistonMechanism:: SetP1(double x, double y) {

        double tL = 0;

        tL = Cup.GetBottomSide().GetP1().d(Piston.GetPiston().GetP3());
        Cup.SetP1(x,y);
        Piston.SetP1(Cup.GetBottomSide().GetP1().GetX(),Cup.GetBottomSide().GetP1().GetY() + tL + Piston.GetPiston().GetHeight());
        Cover.SetP1(CPoint(x,y+Cover.GetCover().GetHeight()));
        RefreshPoints();

}

void CClosedPistonMechanism :: SetP1(CPoint P0) {
        double tL = 0;

        tL = CPoint(Cup.GetBottomSide().GetP1()).d(Piston.GetPiston().GetP3());
        Cup.SetP1(P0);
        Piston.SetP1(Cup.GetBottomSide().GetP1().GetX(),Cup.GetBottomSide().GetP1().GetY() + tL + Piston.GetPiston().GetHeight());
        Cover.SetP1(CPoint(P0.GetX(),P0.GetY()+Cover.GetCover().GetHeight()));
        RefreshPoints();
}


void CClosedPistonMechanism :: Move (double dx, double dy) {
        Cup.Move(dx,dy);
        Piston.Move(dx,dy);
        Cover.Move(dx,dy);
        RefreshPoints();
}

const CCover& CClosedPistonMechanism :: GetCover() const {
        return Cover;
}

const CircleList<CPoint>& CClosedPistonMechanism :: GetPoints ()  const{
        return MainPoints;
}

void CClosedPistonMechanism :: Print () {
	 cout << "ClosedPistonMechanism id = "<< id <<endl <<
         "LeftCupSide : "; Cup.GetLeftSide().Print();
         cout << "BottomCupSide : "; Cup.GetBottomSide().Print();
         cout << "RightCupSide : "; Cup.GetRightSide().Print();
         getch();
         cout << "Piston : "; Piston.GetPiston().Print();
         cout << "Stock : "; Piston.GetStock().Print();
         cout << "Cover : "; Cover.GetCover().Print(); cout << endl;
         cout << "Hole : "; Cover.GetHole().Print(); cout << endl;
         getch();
         cout << "Main Points : "<<endl;
         cout<<"-------------------"<<endl;
         MainPoints.Print();
         cout <<"-------------------"<<endl;
	 getch();

}


ostream& operator<<(ostream& output,const CClosedPistonMechanism& P) {

         output << "ClosedPistonMechanism id = " << P.GetID() << endl;
         output << "LeftCupSide : " << P.GetCup().GetLeftSide();
         output << "BottomCupSide : " << P.GetCup().GetBottomSide();
         output << "RightCupSide : " << P.GetCup().GetRightSide();
         output << "Piston : " << P.GetPiston().GetPiston();
         output<< "Stock : P1"<<P.GetPiston().GetStock().GetP1() << ", P2" << P.GetPiston().GetStock().GetP2()<<", L = " << P.GetPiston().GetStock().GetL()<<endl;
         cout << "Cover : " << P.GetCover().GetCover() << endl;
         cout << "Hole : " << P.GetCover().GetHole() << endl;
         output << "Main Points : "<<endl;
         output<<"-------------------"<<endl;
          if(P.GetPoints().GetSize() == 0){
			cout<<endl<<"The List is empty"<<endl;
			return output;
		}

	short i = 0;
	CLNode <CPoint>* temp = P.GetPoints().GetFirst();

	while (i < P.GetPoints().GetSize() && temp) {
		output << "Element "<<i<<": "<< temp->GetValue()<<endl;
                i++;
		temp = temp->GetNext();
	}

	output <<endl<<endl;
         output <<"-------------------"<<endl;

 	return output;
} 
