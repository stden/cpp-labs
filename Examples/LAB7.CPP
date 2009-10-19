#include <iostream.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

const double pi=3.141592653589793;


class CParall
{
   public:
     double a,b;
     double alfa;
     CParall(double,double,double);
     double setalfa(double);
     double seta(double);
     double setb(double);
     double perimetr();
     double square();
};

CParall::CParall(double x,double y,double z)
{
   a=x;
   b=y;
   alfa=z;
};

double CParall::setalfa(double z)
{
   alfa=z;
   return alfa;
};

double CParall::seta(double x)
{
   a=x;
   return a;
};

double CParall::setb(double y)
{
   b=y;
   return b;
};

double CParall::perimetr()
{ return 2*a+2*b;};

double CParall::square()
{return a*b*sin(alfa);};

//------------------------------------------------\\

class CRect: virtual public CParall
{
   public:
     CRect(double,double);
};

CRect::CRect(double x,double y):CParall(x,y,pi/2){};

//---------------------------------------------------\\

class CRhomb:virtual public CParall
{
   public:
     CRhomb(double,double);
     void seta(double);
};

CRhomb::CRhomb(double x,double z):CParall(x,x,z){};

void CRhomb::seta(double x)
{
   a=x;
   b=x;
};

//-----------------------------------------------------\\

class CSquare: public CRect, public CRhomb
{
   public:
     CSquare(double);
     CRhomb::seta;
};

CSquare::CSquare(double x):CParall(x,x,pi/2),CRhomb(x,pi/2),CRect(x,x){};

void main()
{ int a;
  CParall paral1(5,10,pi/6);
  CRect pryam1(5,7);
  CRhomb romb1(4,pi/10);
  CSquare kvad1(3);
  clrscr();//
  cout<<"Parallelogram: a="<<paral1.a<<"b="<<paral1.b<<"alfa="<<
paral1.alfa<<" Perimetr="<<paral1.perimetr()<<
"Ploschad="<<paral1.square()<<endl;
  paral1.seta(4);
  cout<<"Parallelogram: a="<<paral1.a<<"b="<<paral1.b<<"alfa="<<
paral1.alfa<<" Perimetr="<<paral1.perimetr()<<
"Ploschad="<<paral1.square()<<endl;
  paral1.setb(11);
  cout<<"Parallelogram: a="<<paral1.a<<"b="<<paral1.b<<"alfa="<<
paral1.alfa<<" Perimetr="<<paral1.perimetr()<<
"Ploschad="<<paral1.square()<<endl;
  paral1.setalfa(pi/10);
  cout<<"Parallelogram: a="<<paral1.a<<"b="<<paral1.b<<"alfa="<<
paral1.alfa<<" Perimetr="<<paral1.perimetr()<<
"Ploschad="<<paral1.square()<<endl;
  cout<<endl;
  cout<<"Pryamougol'nik: a="<<pryam1.a<<"b="<<pryam1.b<<" Perimetr="<<
pryam1.perimetr()<<"Ploschad="<<pryam1.square()<<endl;
  pryam1.seta(6);
  cout<<"Pryamougol'nik: a="<<pryam1.a<<"b="<<pryam1.b<<" Perimetr="<<
pryam1.perimetr()<<"Ploschad="<<pryam1.square()<<endl;
  pryam1.setb(10);
  cout<<"Pryamougol'nik: a="<<pryam1.a<<"b="<<pryam1.b<<" Perimetr="<<
pryam1.perimetr()<<"Ploschad="<<pryam1.square()<<endl;
  cout<<endl;
  cout<<"Romb: a="<<romb1.a<<"b="<<romb1.b<<" Perimetr="<<
romb1.perimetr()<<"Ploschad="<<romb1.square()<<endl;
  romb1.seta(5);
  cout<<"Romb: a="<<romb1.a<<"b="<<romb1.b<<" Perimetr="<<
romb1.perimetr()<<"Ploschad="<<romb1.square()<<endl;
  romb1.setalfa(pi/6);
  cout<<"Romb: a="<<romb1.a<<"b="<<romb1.b<<" Perimetr="<<
romb1.perimetr()<<"Ploschad="<<romb1.square()<<endl;
  cout<<endl;
  cout<<"Kvadrat: a="<<kvad1.a<<" Perimetr="<<kvad1.perimetr()<<
  "Ploschad="<<kvad1.square()<<endl;
  kvad1.seta(4);
  cout<<"Kvadrat: a="<<kvad1.a<<" Perimetr="<<kvad1.perimetr()<<
  "Ploschad="<<kvad1.square()<<endl;
  cout<<endl;
  getchar();
};
