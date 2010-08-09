//file main.cpp
//main file
//Author: Volinko Evgeniy
//Date: 15.02.2010 version: 1.0

#include <stdlib.h>
#include <stdio.h>
#include "Glass.h"
#include "CService.h"

void check_input(char *temp,int *k, int *flag){
  if ((atoi(temp) > 0) && (atoi(temp) < 100)){
    *k = atoi(temp);
    *flag = 0;
  } else{
    cout << "Error input\n"<< "try again";
  }
}

double input_double(char *name){
  double k;
  while (1){
    cout << name << " ";
    char temp[10];
    cin  >> temp;
    if(sscanf(temp,"%lf",&k))
      return k;
    cout << "Error input\n"<< "try again\n";
  }
}

void inputPoint(CCountedPoint& p)
{
  double x, y;
  x = input_double("    Input x:");
  y = input_double("    Input y:");
  p.setX(x);
  p.setY(y);
}

void addGlass(CService& s, int toBegin = 0)
{
  double bottomLength, hBottom, lessSide;
  CCountedPoint bottom, top;


  cout<<"  Input left bottom point:" << endl;
  inputPoint(bottom);
  cout<<"  Input left hight point:" << endl;
  inputPoint(top);


  bottomLength = input_double("  Input the less foundation length:");
  hBottom = input_double("  Input the less foundation heigth:");
  lessSide = input_double("  Input the less rib length:");

  CGlass glass(bottom, top, bottomLength, hBottom, lessSide);

  if(toBegin)
    s.insertBegin(glass);
  else
    s.insert(glass);
}

void main()
{
  int i, k;
  int flag;
  char *temp = new char[5];

  cout<<"Project of service"<<endl;
  cout<<"Author: Volinko Evgeniy"<<endl<<"Group:7304";
  cout<<endl<<endl<<endl<<endl;
  CService s;

  //Input number of elements
  flag = 1;
  while (flag){
	  cout << "Input number of elements: ";
	  cin  >> temp;
	  check_input(temp, &k,&flag);
	  cout << "\n";
  };

	  i = 0;
  //Input value of elements
  while (i < k){
    cout << "Input element " << (i+1) << ": " << endl;
    addGlass(s);
    i++;
  };

  cout << endl << endl;

  cout << endl << "Our service:" << endl;
  s.print();

  int a;

  do {
    cout<<"\n\n===========MAIN MENU===========";
    cout<<"\nPress 1 to add glass to end;";
	cout<<"\nPress 2 to add glass to begin;";
	cout <<"\nPress 3 to move glasses by dx dy";
	cout <<"\nPress 4 to place glasses to point";
	cout <<"\nPress 5 to print";
	cout<<"\nPress 0 to exit;\n";
	cout<<"===============================\n";
	cin >>a;

   switch(a){
     case 1:
       addGlass(s);
       break;
     case 2:
       addGlass(s, 1);
       break;
     case 3:
       double dx = input_double("Enter dx:"),
	      dy = input_double("Enter dy:");
       s.MovedXdY(dx,dy);
       break;
     case 4:
       double x = input_double("Enter x:"),
	      y = input_double("Enter y:");
       s.MoveToPoint(CCountedPoint(x,y));
       break;

     case 5:
      s.print();
       break;
     case 0:
       break;
     default:
       cout << "Out of menu :)" << endl;
   }

	//Out lists
	cout << endl << "Service: " << endl;
	s.print();
	cout<<endl;
	} while (a!=0);
}