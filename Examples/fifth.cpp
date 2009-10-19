#include <iostream.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358979323246864

//Line,luch,otrezok
//Metodi':narisovat',sdvinut',povernut'
class TLine{
public:
  int x0,y0,xmax,ymax;
  int color;
  float alfa;
  TLine(float,int);
  void move(int);
  void povorot(float);
  void show();
};

TLine::TLine(float a,int c)
{     alfa=a;
      color=c;
      x0=0;
      y0=0;
      xmax=getmaxx();
      ymax=ceil(tan(alfa)*xmax);
};
void TLine::move(int z)
{
   y0+=z;
   ymax+=z;
};

void TLine::povorot(float s)
{
  ymax+=ceil(tan(s+alfa)*xmax/2);
};

void TLine::show()
{
 setcolor(color);
 line(x0,y0,xmax,ymax);
};

class TLuch:public TLine
{
 public:
 TLuch(float,int,int,int);
 void move(int,int);
};

TLuch::TLuch(float a,int c,int x,int y): TLine(a,c)
{
 x0=x;
 y0=y;
};

void TLuch::move(int z1, int z)
{
   x0+=z1;
   xmax+=z1;
   y0+=z;
   ymax+=z;
};

class TOtr:public TLuch
{
public:
int dlina;
TOtr(float,int,int,int,int);
void povorot(float);
};

TOtr::TOtr(float a,int c,int x,int y,int d): TLuch(a,c,x,y)
{
   dlina=d;
   ymax=sin(alfa)*dlina+y0;
   xmax=cos(alfa)*dlina+x0;
};

void TOtr::povorot(float s)
{
   ymax=sin(alfa+s)*dlina+y0;
   xmax=cos(alfa+s)*dlina+x0;
};

void main()
{
int gdriver=DETECT, gmode, errorcode;
initgraph(&gdriver,&gmode,"c:\\PROGRAMS\\bc\\bgi");
TLine line1(0,8);
  line1.show();
  line1.move(100);
  line1.show();
  line1.move(100);
  line1.povorot(0.4);
  line1.show();
TLuch luch1(0.7,2,50,50);
  luch1.show();
  luch1.move(200,200);
  luch1.show();
  luch1.move(100,100);
  luch1.povorot(0.3);
  luch1.show();
TOtr otr1(0.0,900,100,100,200);
  otr1.show();
  otr1.move(100,50);
  otr1.show();
  otr1.move(50,50);
  otr1.show();
  otr1.povorot(1.57);
  otr1.show();
getch();
cleardevice();
closegraph();
};
