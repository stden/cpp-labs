#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include "CSection.h"
#include "CPoint.h"
#include "CRect.h"
#include "CList.h"
#include "CListN.h"
#include "CPiston.h"
#include "CCup.h"
#include "CPMec.h"
#include "CPColl.h"
#include "CCover.h"
#include "CTria.h"
#include "CStand.h"
#include "CPCMec.h"
#include "CView.h"




void main () {
{

        cout << endl<<endl<<"-----------------------------------------------"<<endl;
        cout << "Programm is creating the view on collection of schematic images of"<<endl
             << "closed piston mechanisms which can be moved or placed in point"<<endl
             << "Programmed by : Artyom Mon'ko"<<endl<<endl
             << "----------------Press any key to continue or ESC to exit----------------"<<endl;

         while(1) {
          int key = getch();
          if (key == 27) return; // Waiting for some action
	  else break;
	}


	int flag = 1;
        int ViewCreated = 0;
	char* buffer = new char[80];
	int menu = 0;
	CPistonCollection c;
        CPistonMechanism* p;
        CView *v;
	while (flag) {
        cout    << "1.Create View"<<endl
                << "2.Add Mechanism to Collection"<<endl
                << "3.Delete Mechanism from Collection"<<endl
                << "4.Move Collection and Stand"<<endl
                << "5.Place Collection and Stand into Point"<<endl
                << "6.Place Collection into Point"<<endl
                << "7.Place Stand into Point"<<endl
	            << "8.Move Collection"<<endl
                << "9.Move Stand"<<endl
                << "10.Move Piston of element"<<endl
                << "11.Move every Piston"<<endl
                << "12.Print View"<<endl
                << "13.Print Collection"<<endl
	        << "14.Exit"<<endl;

	cin >> buffer;

	if ((atoi(buffer) == 0) || (atoi(buffer) < 1 || atoi(buffer) > 14)) {
		cout << "Invalid input, try again : "<<endl;
		continue;
	}

	else {
	    menu = (int)atoi(buffer);

	    switch (menu) {
               case 1: {
	       double x1 = 0,y1 = 0, _P1P2,x3,y3;



	       cout << "Enter x value of point P1 : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		x1 = atof(buffer);


		cout << "Enter y value of point P1 : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		y1 = atof(buffer);

                cout << "Enter lenght of P1P2 side : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		_P1P2 = atof(buffer);

                cout << "Enter x value of point P3 : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		x3 = atof(buffer);


		cout << "Enter y value of point P3 : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		y3 = atof(buffer);

                v = new CView(CPoint(x1,y1),_P1P2,CPoint(x3,y3));

               if (v->inv()) {ViewCreated = 1;cout << "View is created"<<endl;}
                else cout << "View do not created due to some input errors"<<endl;
				
				if(c.GetLength() > 0) v->Add(c);

               break;
               }

	       case 2: {
	       double x1 = 0,y1 = 0, lwidth,lheight,bwidth,bheight,rwidth,y2,pheight,slen,cover_height,hole_width;


	       cout << "Enter x value of point P1(A) : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		x1 = atof(buffer);


		cout << "Enter y value of point P1(A) : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		y1 = atof(buffer);

                cout << "Enter width of left side : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		lwidth = atof(buffer);

                cout << "Enter height of left side : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		lheight = atof(buffer);

                cout << "Enter width of bottom side : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		bwidth = atof(buffer);

                cout << "Enter height of bottom : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		bheight = atof(buffer);

                cout << "Enter width of right side : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		rwidth = atof(buffer);

                cout << "Enter y value of piston point P1(I) : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		y2 = atof(buffer);

                cout << "Enter piston height : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		pheight = atof(buffer);

                cout << "Enter stock length : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		slen = atof(buffer);

                cout << "Enter cover height : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		cover_height = atof(buffer);

                cout << "Enter hole's width : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}

		hole_width = atof(buffer);

                p = new CClosedPistonMechanism(x1,y1,lwidth,lheight,bwidth,bheight,rwidth,y2,pheight,slen,cover_height,hole_width);

                if (p->inv()){
                 c.Add(p);
                 if (ViewCreated) v->Add(p);
                 cout << "Closed Piston Mechanism Added"<<endl;}
                else cout << "Closed Piston Mechanism not added due to some input errors"<<endl;


               break;
               }

               case 3: {
               cout << "Enter number of element : ";

	       while (1) {
		cin >> buffer;
		if (atoi(buffer) == 0 && buffer[0] != '0') {
			cout << "Invalind input, try again : ";
			continue;
		}
		else break;
		}
                c.Delete(atoi(buffer));
                if (ViewCreated) v->Delete(atoi(buffer));
                if (c.invColl()) cout << "Element deleted"<<endl;
               break;
               }

               case 4: {
               double dx,dy;

               cout << "Enter dx :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dx = atof(buffer);

                cout << "Enter dy :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dy = atof(buffer);


                if (ViewCreated) {
                        v->MoveCollectionAndStand(dx,dy);

                        if (v->inv()) cout << "Collection and stand are moved by dx = "<<dx<<", dy = "<<dy<<endl;
                }
                else {
                        c.Move(dx,dy);
                        if (c.invColl()) cout << "Collection is moved by dx = "<<dx<<", dy = "<<dy<<endl;
                }


               break;
               }

                case 5: {

               double x,y;
               cout << "Enter P1 "<<endl;
               cout << "Enter x :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                x = atof(buffer);

                cout << "Enter y :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                y = atof(buffer);


                if (ViewCreated) {
                        v->SetCollectionAndStandP1(CPoint(x,y));
                       
                        if (v->inv()) cout << "Collection and stand are placed to Point("<<x<<";"<<y<<")"<<endl;
                }
                else {
                        c.SetP1(CPoint(x,y));
                        if (c.invColl()) cout << "Collection is placed to Point("<<x<<";"<<y<<")"<<endl;
                }


               break;
               }

               case 6: {

               double x,y;
               cout << "Enter P1 "<<endl;
               cout << "Enter x :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                x = atof(buffer);

                cout << "Enter y :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                y = atof(buffer);


                if (ViewCreated) {
                        v->SetCollectionP1(CPoint(x,y));
                        if (v->inv()) cout << "Collection is placed to Point("<<x<<";"<<y<<")"<<endl;
                }
                else {
                        c.SetP1(CPoint(x,y));
                        if (c.invColl()) cout << "Collection is placed to Point("<<x<<";"<<y<<")"<<endl;
                }

               break;
               }

               case 7: {

               double x,y;
               cout << "Enter P1 "<<endl;
               cout << "Enter x :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                x = atof(buffer);

                cout << "Enter y :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                y = atof(buffer);

                if (ViewCreated) {
                        v->SetStandP1(CPoint(x,y));
                        if (v->inv()) cout << "Stand is placed to Point("<<x<<";"<<y<<")"<<endl;
                }
                else cout << "View is not created"<<endl;

               break;
               }

               case 8: {
               double dx,dy;

               cout << "Enter dx :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dx = atof(buffer);

                cout << "Enter dy :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dy = atof(buffer);


                if (ViewCreated) {
                        v->MoveCollection(dx,dy);
                        if (v->inv()) cout << "Collection is moved by dx = "<<dx<<", dy = "<<dy<<endl;
                }
                else {
                        c.Move(dx,dy);
                        if (c.invColl()) cout << "Collection is moved by dx = "<<dx<<", dy = "<<dy<<endl;
                }
               break;
               }

               case 9: {
               double dx,dy;

               cout << "Enter dx :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dx = atof(buffer);

                cout << "Enter dy :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dy = atof(buffer);


                if (ViewCreated) {
                        v->MoveStand(dx,dy);
                        if (v->inv()) cout << "Stand is moved by dx = "<<dx<<", dy = "<<dy<<endl;
                }
                else
                cout << "View is not created"<<dy<<endl;
               break;
               }
		
		case 10: {
               double dy, index = 0;

               cout << "Index of element :  "<<endl;
               while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                index = atof(buffer);

                cout << "Enter dy :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dy = atof(buffer);


                if (ViewCreated) {
                        v->GetCollection().GetElemByNum(index)->GetValue()->MovePiston(dy);
                        if (v->inv()) cout << "Piston of "<< index<< "'th element is moved by dy = "<<dy<<endl;
                        else cout << "Piston didn't move"<<endl;
                }
                else {
                        c.GetCollection().GetElemByNum(index)->GetValue()->MovePiston(dy);
                        if (c.invColl()) cout << "Piston of "<< index<< "'th element is moved by dy = "<<dy<<endl;
                        else cout << "Piston didn't move"<<endl;
                }

               break;
               }

               case 11: {
               double dy;

                cout << "Enter dy :  "<<endl;
                while (1) {
                cin >> buffer;
                if (atoi(buffer) == 0 && buffer[0] != '0') {
                        cout << "Invalind input, try again : ";
                        continue;
                }
                else break;
                }

                dy = atof(buffer);

                if (ViewCreated) {
                        v->MovePiston(dy);
                        if (v->inv()) cout << "Pistons moved by dy = "<<dy<<endl;
                        else cout << "Piston didn't move"<<endl;
                }
                else {
                        c.MovePiston(dy);
                        if (c.invColl()) cout << "Pistons moved by dy = "<<dy<<endl;
                        else cout << "Piston didn't move"<<endl;
                }

               break;
               }

               case 12: {
               if(ViewCreated) v->PrintView();
                else cout << "View is not created"<<endl;
               break;
               }

               case 13: {
                //CPistonMechanism* pm = new CClosedPistonMechanism(3,10,1,7,4,2,1,8,2,6,2,1);
                if(ViewCreated) v->Print();
                else c.Print();

               break;
               }

               case 14: {
               flag = 0;
	       break;
               }

            }

        }


}
}
}










