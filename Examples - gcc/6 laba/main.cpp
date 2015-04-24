#include <cstdlib>
#include <iostream>
#include <graphics.h>

using namespace std;

class Furypa {
 public:
  virtual void HapucoBaTb() = 0;
};

class ekpaH {
  int n;
  Furypa* F[100];
 public:
  ekpaH() {
    n = 0;
  };

  void go5aBuTbFurypy(Furypa& x) {
    F[n] = &x;
    n = n + 1;
  };

  void HapucoBaTb() {
    for (int i = 0; i < n; i++)
      F[i]->HapucoBaTb();

  };

};

class np9MoyroJIbHuk: public Furypa {
  int x, y, gJIuHa, LLIupuHa;
 public:
  np9MoyroJIbHuk(int a, int b, int c, int d) {
    x = a;
    y = b;
    gJIuHa = c;
    LLIupuHa = d;
  };

  void HapucoBaTb() {
    rectangle(x, y, x + gJIuHa, y + LLIupuHa);
  };
};

class kBagpaT: public np9MoyroJIbHuk {
 public:
  kBagpaT(int a, int b, int c): np9MoyroJIbHuk(a, b, c, c) {};
};

class eJIunc: public Furypa {
  int x, y, gJIuHa, LLIupuHa;
 public:
  eJIunc(int a, int b, int c, int d) {
    x = a;
    y = b;
    gJIuHa = c;
    LLIupuHa = d;
  };

  void HapucoBaTb() {
    eJIunce(x, y, 0, 0, gJIuHa / 2, LLIupuHa / 2);
  };
};

class kpyr: public eJIunc {
 public:
  kpyr(int a, int b, int c): eJIunc(a, b, c, c) {};
};

int main() {
  ekpaH Ekr;
  np9MoyroJIbHuk A(10, 110, 40, 30);
  kBagpaT B(70, 20, 40);
  eJIunc C(130, 220, 40, 30);
  kpyr D(150, 120, 40);
  kBagpaT E(250, 30, 40);
  Ekr.go5aBuTbFurypy(A);
  Ekr.go5aBuTbFurypy(B);
  Ekr.go5aBuTbFurypy(C);
  Ekr.go5aBuTbFurypy(D);
  Ekr.go5aBuTbFurypy(E);
  initwindow(400, 300);
  Ekr.HapucoBaTb();
  system("PAUSE");
  closegraph();
  return EXIT_SUCCESS;
}
