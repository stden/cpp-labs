#include <iostream.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.14159265358979323246864

//Liniya,luch,otrezok
//Metodi':narisovat',sdvinut',povernut' 

class TLine{
  public:
  int x0,y0,xmax,ymax;
  int color;
  float alfa;   
  TLine(float,int);
  void sdvig(int);
  void povorot(float);
  void show();
};

TLine::TLine(float a,int tcolor){
      alfa=a;
      color=tcolor;
      x0=0;
      y0=0;
      xmax=getmaxx();
      ymax=ceil(tan(alfa)*xmax);
};
void TLine::sdvig(int z)
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
 void sdvig(int,int);
};

TLuch::TLuch(float a,int c,int x,int y): TLine(a,c)
{
 x0=x;
 y0=y;
};

void TLuch::sdvig(int z1, int z)
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

void Reload()
{
   clrscr;
   getch();
};

void main()
{
int gdriver=DETECT, gmode;
initgraph(&gdriver,&gmode,"");

TLine line1(0.1,7);
  setcolor(7);
  outtextxy(200,10,"line1");
  line1.show();
  line1.sdvig(100);        //sdvig po y+100
  getch();
  outtextxy(200,110,"line2=line(y+100)");
  line1.show();
  line1.povorot(0.3);     //povorot na 0.3
  getch();
  outtextxy(400,210,"line3=line2(rate 0.3)");
  line1.show();
  getch();
clrscr();

TLuch luch1(0.4,3,100,100);
  getch();
  setcolor(3);
  outtextxy(120,100,"luch1");
  luch1.show();
  luch1.sdvig(50,100);
  getch();
  outtextxy(200,200,"luch2(x+50;y+100)");
  luch1.show();
  luch1.povorot(0.3);
  getch();
  outtextxy(280,300,"luch3(rate 0.3)");
  luch1.show();
  getch();
clrscr();

TOtr otr1(0.2,5,100,100,300);
  getch();
  setcolor(5);
  outtextxy(140,100,"otrezok1");
  otr1.show();
  otr1.sdvig(100,50);
  getch();
  outtextxy(240,150,"otrezok2(x+100;y+50)");
  otr1.show();
  otr1.povorot(1.9);
  getch();
  outtextxy(140,250,"otrezok3(rate 1.9)");
  otr1.show();
getch();
cleardevice();
closegraph();
};
