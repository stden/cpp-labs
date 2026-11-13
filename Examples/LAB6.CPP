#include <iostream.h>
#include <conio.h>
#include <graphics.h>

class CScreen {
 public:
  virtual void draw() = 0;
};
//---------------------------\\
class CFigure: public CScreen {
 public:
  virtual void draw() = 0;
};

//----------------------------------------------------\\

class CRectangle: public CFigure {
  int a,//storona1
      b,//storona2
      x0,//nach tochk
      y0;
 public:
  CRectangle(int, int, int, int);
  void draw();

};

CRectangle::CRectangle(int x, int y, int dlina, int shirina) {
  a = dlina;
  b = shirina;
  x0 = x;
  y0 = y;
};


void CRectangle::draw() {
  rectangle(x0, y0, x0 + a, y0 + b);
}

//--------------------------------------------------------\\

class CSquare: public CRectangle {
 public:
  CSquare(int, int, int);
  void draw();
};

CSquare::CSquare(int x, int y, int dlina): CRectangle(x, y, dlina, dlina) {};

void CSquare::draw() {
  CRectangle::draw();
}

//----------------------------------------------------------\\

class CEllipse: public CFigure {
  int x0,//nach
      y0,//tochki
      rx,//radius x
      ry;// radius y
 public:
  CEllipse(int, int, int, int);
  void draw();
};

CEllipse::CEllipse(int x, int y, int radx, int rady) {
  x0 = x;
  y0 = y;
  rx = radx;
  ry = rady;
}

void CEllipse::draw() {
  ellipse(x0, y0, 0, 360, rx, ry);
}

//---------------------------------------------------------\\

class CCircle: public CEllipse {
 public:
  CCircle(int, int, int);
  void draw();
};

CCircle::CCircle(int x, int y, int rad): CEllipse(x, y, rad, rad) {}

void CCircle::draw() {
  CEllipse::draw();
}

int main() {
  int n;
  cout << "kol-vo elementov: ";
  cin >> n;
  int gdriver = DETECT, gmode, errorcode;
  initgraph(&gdriver, &gmode, "c:\\bc\\bgi");
  CScreen* r[4];
  r[0] = new CRectangle(1, 1, 100, 50);
  r[1] = new CSquare(100, 50, 50);
  r[2] = new CEllipse(150, 150, 20, 40);
  r[3] = new CCircle(320, 300, 100);

  for (int i = 0; i < 4; i++)
    r[i]->draw();

  getch();
  return 0;
}