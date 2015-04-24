#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include <cmath>

using namespace std;

class oTpe3ok {
  int x, y, dlina;
  float u;
 public:
  oTpe3ok() {
    x = 0;
    y = 0;
    u = 0;
    dlina = 0;
  };

  oTpe3ok(int a, int b, float c, int d) {
    x = a;
    y = b;
    u = c;
    dlina = d;
  };

  void noMeH9Tb(int a, int b, float c, int d) {
    x += a;
    y += b;
    u += c;
    dlina += d;
  };

  void HapucoBaTb() {
    moveto(x, y);
    lineto(x + int(dlina * cos(u)), y - int(dlina * sin(u)));
  };

  void cgBuHyTb(int a, int b) {
    clearviewport();
    noMeH9Tb(a, b, 0, 0);
    HapucoBaTb();
  };
  void noBepHyTb(float c) {
    clearviewport();
    noMeH9Tb(0, 0, c, 0);
    HapucoBaTb();
  };

};

class JIy4: public oTpe3ok {
 public:
  JIy4(): oTpe3ok() {};
  JIy4(int a, int b, float c): oTpe3ok(a, b, c, 1000) {};

  void HapucoBaTb() {
    oTpe3ok::HapucoBaTb();
  };
};

class JIuHu9: public JIy4 {
 public:
  JIuHu9(): JIy4() {};
  JIuHu9(int a, int b, float c): JIy4(a, b, c) {};

  void HapucoBaTb() {
    JIy4::HapucoBaTb();
    noMeH9Tb(0, 0, 3.14, 0);
    JIy4::HapucoBaTb();
    noMeH9Tb(0, 0, -3.14, 0);
  };

  void cgBuHyTb(int a, int b) {
    JIy4::cgBuHyTb(a, b);
    HapucoBaTb();
  };
  void noBepHyTb(float c) {
    JIy4::noBepHyTb(c);
    HapucoBaTb();
  };
};

int main() {
  int v;
  JIuHu9 A(100, 100, 1.5);
  JIy4 B(100, 100, 1.5);
  oTpe3ok C(100, 100, 1.5, 60);
M:
  cout << "1.JIuHu9\n2.JIy4\n3.oTpe3ok\n4.BbIxog\nBbI5epuTe: ";
  cin >> v;

  switch(v) {
    case 1:
      initwindow(400, 300);
      A.HapucoBaTb();
      system("PAUSE");
      A.cgBuHyTb(20, 40);
      system("PAUSE");
      A.noBepHyTb(2.5);
      system("PAUSE");
      closegraph();
      goto M;
      break;

    case 2:
      initwindow(400, 300);
      B.HapucoBaTb();
      system("PAUSE");
      B.cgBuHyTb(20, 40);
      system("PAUSE");
      B.noBepHyTb(2.5);
      system("PAUSE");
      closegraph();
      goto M;
      break;

    case 3:
      initwindow(400, 300);
      C.HapucoBaTb();
      system("PAUSE");
      C.cgBuHyTb(20, 40);
      system("PAUSE");
      C.noBepHyTb(2.5);
      system("PAUSE");
      closegraph();
      goto M;
      break;

    case 4:
      goto E;
      break;

    default:
      goto M;
  };

E:
  return EXIT_SUCCESS;
}
