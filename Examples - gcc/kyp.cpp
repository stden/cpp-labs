#include <windows.h>
#include <iostream>
#include <conio.h>

using namespace std;
class CTPOKA {
 private:
  char* str;
  int len;
 public:
  CTPOKA(): len(0) {
    str = new char[1];
    *str = '\0';
  }
  CTPOKA(CTPOKA& s): len(s.len) {
    str = new char [len + 1];
    strcpy(str, s.str);
  }
  CTPOKA(char* s) {
    str = new char[strlen(s) + 1];
    len = strlen(s);
    strcpy(str, s);
  }
  ~CTPOKA() {
    delete[] str;
  }
  void show();
  CTPOKA operator=(const CTPOKA);

  operator char* ();
  friend ostream& operator<<(ostream&, const CTPOKA&);


};
void CTPOKA::show() {
  if(len > 0) {
    for(int i = 0; i < strlen(str); i++)
      cout << *(str + i);
  }
}
CTPOKA CTPOKA::operator=(const CTPOKA s) {
  if(&s != this) {
    delete[] str;
    str = new char[strlen(s.str) + 1];
    len = s.len;
    strcpy(str, s.str);
  }

  return *(this);
}
CTPOKA:: operator char* () {
  return (str);
}
ostream& operator<<(ostream& os, const CTPOKA& s) {
  for(int i = 0; i < strlen(s.str); i++)
    os << *((s.str) + i);

  return(os);
}

class KMF {
 private:
  int x, y, i, j, color;
  CTPOKA text;
 public:
  KMF() {
    x = 0;
    y = 0;
    i = 0;
    j = 0;
    color = 0;
    text;
  };
  ~KMF() {
    x = 0;
    y = 0;
    i = 0;
    j = 0;
    color = 0;
    text;
  };
  KMF(int a, int b, int d, int e, int c, CTPOKA t) {
    x = a;
    y = b;
    i = d;
    j = e;
    color = c;
    t = text;
  };
  KMF(KMF& S) {
    x = S.x;
    y = S.y;
    i = S.i;
    j = S.j;
    color = S.color;
    text = S.text;
  };
  void HapucoBaTbK(int x, int y, int i, int j, int color) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);

    for (int y1 = y; y1 < j; y1++) {
      gotoxy(x + (i - x), y1 + 1);
      printf("%c", 179);
      gotoxy(x, y1 + 1);
      printf("%c", 179);
    }

    for (int x1 = x; x1 < i; x1++) {
      gotoxy(x1 + 1, y);
      printf("%c", 196);
      gotoxy(x1 + 1, y + (j - y));
      printf("%c", 196);
    }

    gotoxy(x, y);
    printf("%c", 218);
    gotoxy(x, y + (j - y));
    printf("%c", 192);
    gotoxy(x + (i - x), y + (j - y));
    printf("%c", 217);
    gotoxy(x + (i - x), y);
    printf("%c", 191);
  }
  void HapucoBaTbtxt(int x, int y, int color, CTPOKA txt) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
    gotoxy(x, y);
    cout << txt;
  }
  void HapucoBaTbFoH(int x, int y, int i, int j, int color) {
    CTPOKA npo5eJI(" ");

    for (int x1 = x; x1 < i; x1++)
      for (int y1 = y; y1 < j; y1++)
        HapucoBaTbtxt(x1, y1, color, npo5eJI);
  }
};
class MuHIo4 {
 private:
  KMF paMka2;
  int kakou;

 public:
  MuHIo4() {
    kakou = 0;
  };
  ~MuHIo4() {
    kakou = 0;
  };
  MuHIo4(int c) {
    kakou = c;
  };
  MuHIo4(MuHIo4& S) {
    kakou = S.kakou;
  };
  void zHa4M4(int a) {
    kakou = a;
  };
  void nepegBurM4() {

    CTPOKA txt1(" Put the flag "), txt4(" Remove the flag");
    paMka2.HapucoBaTbFoH(55, 21, 75, 28, 15);
    paMka2.HapucoBaTbK(55, 21, 75, 28, 15);
    paMka2.HapucoBaTbK(56, 22, 74, 24, 31);
    paMka2.HapucoBaTbtxt(57, 23, 15, txt1);
    paMka2.HapucoBaTbK(56, 25, 74, 27, 15);
    paMka2.HapucoBaTbtxt(57, 26, 15, txt4);
    kakou = 4;
    int i = 1;

    while(i == 1) {
      switch(getch()) {
        case 72:
          paMka2.HapucoBaTbK(56, 22, 74, 24, 31);
          paMka2.HapucoBaTbtxt(57, 23, 15, txt1);
          paMka2.HapucoBaTbK(56, 25, 74, 27, 15);
          paMka2.HapucoBaTbtxt(57, 26, 15, txt4);
          kakou = 4;
          zHa4M4(kakou);
          break;

        case 80:
          paMka2.HapucoBaTbK(56, 22, 74, 24, 15);
          paMka2.HapucoBaTbtxt(57, 23, 15, txt1);
          paMka2.HapucoBaTbK(56, 25, 74, 27, 31);
          paMka2.HapucoBaTbtxt(57, 26, 15, txt4);
          kakou = 3;
          zHa4M4(kakou);
          break;

        case 27:
          kakou = 0;
          zHa4M4(kakou);
          i = 0;
          break;

        case 32:
          i = 0;
          break;


      }
    }

    paMka2.HapucoBaTbFoH(55, 21, 76, 29, 144);

  }
  int zHa4M4() {
    return kakou;
  };


};

class MuHIo3 {
 private:
  KMF paMka2;
  int kakou;

 public:
  MuHIo3() {
    kakou = 0;
  };
  ~MuHIo3() {
    kakou = 0;
  };
  MuHIo3(int c) {
    kakou = c;
  };
  MuHIo3(MuHIo3& S) {
    kakou = S.kakou;
  };
  void zHa4M3(int a) {
    kakou = a;
  };
  void nepegBurM3() {

    CTPOKA txt1(" Open cage "), txt4(" Flag ");
    paMka2.HapucoBaTbFoH(40, 15, 54, 22, 15);
    paMka2.HapucoBaTbK(40, 15, 54, 22, 15);
    paMka2.HapucoBaTbK(41, 16, 53, 18, 31);
    paMka2.HapucoBaTbtxt(42, 17, 15, txt1);
    paMka2.HapucoBaTbK(41, 19, 53, 21, 15);
    paMka2.HapucoBaTbtxt(42, 20, 15, txt4);
    kakou = 1;
    int i = 1;

    while(i == 1) {
      switch(getch()) {
        case 72:
          paMka2.HapucoBaTbK(41, 16, 53, 18, 31);
          paMka2.HapucoBaTbtxt(42, 17, 15, txt1);
          paMka2.HapucoBaTbK(41, 19, 53, 21, 15);
          paMka2.HapucoBaTbtxt(42, 20, 15, txt4);
          kakou = 1;
          zHa4M3(kakou);
          break;

        case 80:
          paMka2.HapucoBaTbK(41, 16, 53, 18, 15);
          paMka2.HapucoBaTbtxt(42, 17, 15, txt1);
          paMka2.HapucoBaTbK(41, 19, 53, 21, 31);
          paMka2.HapucoBaTbtxt(42, 20, 15, txt4);
          kakou = 2;
          break;

        case 27:
          i = 0;
          zHa4M3(2);
          break;

        case 32:
          MuHIo4 m;

          if (kakou == 1) {
            i = 0;
            zHa4M3(1);
          } else {
            m.nepegBurM4();

            if (m.zHa4M4() == 0) i = 1;

            if (m.zHa4M4() == 3) {
              i = 0;
              zHa4M3(3);
            };

            if (m.zHa4M4() == 4) {
              i = 0;
              zHa4M3(4);
            };
          }

          break;


      }
    }

    paMka2.HapucoBaTbFoH(40, 15, 55, 23, 144);
  }
  int zHa4M3() {
    return kakou;
  };


};

class MaTp {
 private:
  typedef int sType[9];
  typedef sType Matrix[9];
  Matrix ty;
  KMF kl;
  int x, y, z, c, d, yrag, Heyrag, ocT;
 public:
  MaTpuua() {
    x = 0;
    y = 0;

    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++) ty[i][j] = 0;

  }
  void BBog() {
    x = 9;
    y = 9;

    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++)
        if (i == j) ty[i][j] = 10;
        else ty[i][j] = 0;
    };

    ty[2][7] = 10;
  }
  void BbI4ucJIMuH() {
    int x1, y1;
    x = 9;
    y = 9;

    for (x1 = 0; x1 < x; x1++) {
      for (y1 = 0; y1 < y; y1++) {
        if (ty[x1][y1] == 0) {
          int okp = 0;

          if (x1 > 0) if (y1 > 0) if (x1 < 9) if (y1 < 9) {
                  if (ty[x1 - 1][y1 - 1] == 10)okp++;

                  if (ty[x1 - 1][y1] == 10)okp++;

                  if (ty[x1 - 1][y1 + 1] == 10)okp++;

                  if (ty[x1][y1 - 1] == 10)okp++;

                  if (ty[x1][y1 + 1] == 10)okp++;

                  if (ty[x1 + 1][y1 - 1] == 10)okp++;

                  if (ty[x1 + 1][y1] == 10)okp++;

                  if (ty[x1 + 1][y1 + 1] == 10)okp++;
                }

          if (x1 == 0) if (y1 == 0) {
              if (ty[x1 + 1][y1] == 10)okp++;

              if (ty[x1][y1 + 1] == 10)okp++;

              if (ty[x1 + 1][y1 + 1] == 10)okp++;
            }

          if (x1 == 9) if (y1 == 0) {
              if (ty[x1 - 1][y1] == 10)okp++;

              if (ty[x1][y1 + 1] == 10)okp++;

              if (ty[x1 - 1][y1 + 1] == 10)okp++;
            }

          if (x1 == 0) if (y1 == 9) {
              if (ty[x1 + 1][y1] == 10)okp++;

              if (ty[x1][y1 - 1] == 10)okp++;

              if (ty[x1 + 1][y1 - 1] == 10)okp++;
            }

          if (x1 == 9) if (y1 == 9) {
              if (ty[x1 - 1][y1] == 10)okp++;

              if (ty[x1][y1 - 1] == 10)okp++;

              if (ty[x1 - 1][y1 - 1] == 10)okp++;
            }

          if (y1 == 0) if (x1 > 0) if (x1 < 8) {
                if (ty[x1 - 1][y1 + 1] == 10)okp++;

                if (ty[x1 - 1][y1] == 10)okp++;

                if (ty[x1 + 1][y1 + 1] == 10)okp++;

                if (ty[x1 + 1][y1] == 10)okp++;

                if (ty[x1][y1 + 1] == 10)okp++;
              }

          if (y1 == 9) if (x1 > 1) if (x1 < 8) {
                if (ty[x1 - 1][y1 - 1] == 10)okp++;

                if (ty[x1 - 1][y1] == 10)okp++;

                if (ty[x1 + 1][y1 - 1] == 10)okp++;

                if (ty[x1 + 1][y1] == 10)okp++;

                if (ty[x1][y1 - 1] == 10)okp++;
              }

          if (x1 == 0) if (y1 > 0) if (y1 < 8) {
                if (ty[x1 + 1][y1 - 1] == 10)okp++;

                if (ty[x1 + 1][y1] == 10)okp++;

                if (ty[x1 + 1][y1 + 1] == 10)okp++;

                if (ty[x1][y1 - 1] == 10)okp++;

                if (ty[x1][y1 + 1] == 10)okp++;
              }

          if (x1 == 9) if (y1 > 1) if (y1 < 9) {
                if (ty[x1 - 1][y1 + 1] == 10)okp++;

                if (ty[x1 - 1][y1] == 10)okp++;

                if (ty[x1 - 1][y1 - 1] == 10)okp++;

                if (ty[x1][y1 + 1] == 10)okp++;

                if (ty[x1][y1 - 1] == 10)okp++;
              }

          ty[x1][y1] = okp;
        }
      }

    }

  }
  void gocka() {
    kl.HapucoBaTbFoH(1, 7, 81, 34, 144);
    x = 36;
    y = 33;
    int x2, y2;

    for (x2 = 2 ; x2 < x; x2 = x2 + 4)
      for (y2 = 7; y2 < y; y2 = y2 + 3)
        kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);

  }
  void npoBepka(int x, int y) {
    if (ty[x][y] > 10) d = 1;
    else d = 0;
  }

  void nepeMeLLIeHue(int x2, int y2) {
    yrag = 10;
    Heyrag = 1;
    ocT = 81;
    CTPOKA MuHa("*"), FJIar("P");
    kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);
    int i = 1;
    z = 0;
    c = 0;

    while(i == 1) {
      switch(getch()) {
        case 72:
          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
          y2 = y2 - 3;

          if(y2 < 7) y2 = 7;

          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);

          if (c > 1) {
            z = z;
            c = c - 1;
          } else
            c = 0;


          break;

        case 80:
          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
          y2 = y2 + 3;

          if(y2 > 31) y2 = 31;

          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);

          if (c < 7) {
            z = z;
            c = c + 1;
          } else
            c = 8;

          break;

        case 77:
          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
          x2 = x2 + 4;

          if(x2 > 34) x2 = 34;

          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);

          if (z < 7) {
            z = z + 1;
            c = c;
          } else
            z = 8;

          break;

        case 75:
          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
          x2 = x2 - 4;

          if(x2 < 2) x2 = 2;

          kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);

          if (z > 1) {
            z = z - 1;
            c = c;
          } else
            z = 0;

          break;

        case 27:
          i = 0;
          break;

        case 32:
          MuHIo3 m;
          int a ;
          a = ty[z][c];

          if (ty[z][c] > 199)
            a = ty[z][c] - 200;

          if (a < 11) {
            m.nepegBurM3();

            if (m.zHa4M3() == 0)
              i = 0;;

            if (m.zHa4M3() == 1) {
              i = 1;
              ty[z][c] = ty[z][c] + 100;

              if (ty[z][c] < 110) {
                ocT = ocT - 1;
                kl.HapucoBaTbFoH(x2 + 1, y2 + 1, x2 + 3, y2 + 2, 112);
                kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 112);
                gotoxy(x2 + 1, y2 + 1);
                cout << ty[z][c] - 100;
              };

              if (ty[z][c] == 110) {
                kl.HapucoBaTbFoH(x2 + 1, y2 + 1, x2 + 3, y2 + 2, 192);
                kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 192);
                kl.HapucoBaTbtxt(x2 + 1, y2 + 1, 192, MuHa);
                kl.HapucoBaTbFoH(10, 15, 10, 15, 10);
                gotoxy(10, 15);
                cout << "LUSER!-=)";
                system("PAUSE");

                i = 0;
              };

            };

            if (m.zHa4M3() == 4) {
              i = 1;
              ty[z][c] = ty[z][c] + 200;
              kl.HapucoBaTbFoH(x2 + 1, y2 + 1, x2 + 3, y2 + 2, 15);
              kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
              kl.HapucoBaTbtxt(x2 + 1, y2 + 1, 15, FJIar);

              if (ty[z][c] == 210) {
                yrag = yrag - 1;
                ocT = ocT - 1;
              } else Heyrag = Heyrag + 1;
            };

            if (m.zHa4M3() == 3) {
              if (ty[z][c] == 210) {
                yrag = yrag + 1;
                ocT = ocT + 1;
                i = 1;
              } else Heyrag = Heyrag - 1;

              ty[z][c] = ty[z][c] - 200;
              kl.HapucoBaTbFoH(x2 + 1, y2 + 1, x2 + 3, y2 + 2, 144);
              kl.HapucoBaTbK(x2, y2, x2 + 3, y2 + 2, 144);
            };
          } else
            i = 1;

          gotoxy(1, 1);
          cout << ocT << " " << yrag << " " << ocT - yrag;

          if ((ocT - yrag) == 0) {
            i = 0;
            kl.HapucoBaTbFoH(10, 15, 10, 15, 10);
            gotoxy(10, 15);
            cout << "WINER!-=)";
            system("PAUSE");
          }

          if (yrag == 0) {
            i = 0;
            kl.HapucoBaTbFoH(10, 15, 10, 15, 10);
            gotoxy(10, 15);
            cout << "WINER!-=)";
            system("PAUSE");

          }


          break;

      }
    }
  }


};

class MuHIo2 {
 private:
  KMF paMka2;
  int kakou;

 public:
  MuHIo2() {
    kakou = 0;
  };
  ~MuHIo2() {
    kakou = 0;
  };
  MuHIo2(int c) {
    kakou = c;
  };
  MuHIo2(MuHIo2& S) {
    kakou = S.kakou;
  };
  void zHa4M2(int a) {
    kakou = a;
  };
  void nepegBurM2() {

    CTPOKA txt1(" Start "), txt2(" Exit ");
    paMka2.HapucoBaTbK(1, 7, 14, 14, 15);
    paMka2.HapucoBaTbK(2, 8, 13, 10, 31);
    paMka2.HapucoBaTbtxt(3, 9, 15, txt1);
    paMka2.HapucoBaTbK(2, 11, 13, 13, 15);
    paMka2.HapucoBaTbtxt(3, 12, 15, txt2);
    kakou = 1;
    int i = 1;

    while(i == 1) {
      switch(getch()) {
        case 72:
          paMka2.HapucoBaTbK(2, 8, 13, 10, 31);
          paMka2.HapucoBaTbtxt(3, 9, 15, txt1);
          paMka2.HapucoBaTbK(2, 11, 13, 13, 15);
          paMka2.HapucoBaTbtxt(3, 12, 15, txt2);
          kakou = 1;
          zHa4M2(kakou);
          break;

        case 80:
          paMka2.HapucoBaTbK(2, 8, 13, 10, 15);
          paMka2.HapucoBaTbtxt(3, 9, 15, txt1);
          paMka2.HapucoBaTbK(2, 11, 13, 13, 31);
          paMka2.HapucoBaTbtxt(3, 12, 15, txt2);
          kakou = 2;
          zHa4M2(kakou);
          break;

        case 27:
          i = 0;
          break;

        case 32:

          i = 0;
          break;


      }
    }
  }
  int zHa4M2() {
    return kakou;
  };


};
class MuHIo1 {
 private:
  KMF paMka1 ;

  int kakou;

 public:
  MuHIo1() {
    kakou = 0;
  };
  ~MuHIo1() {
    kakou = 0;
  };
  MuHIo1(int c) {
    kakou = c;
  };
  MuHIo1(MuHIo1& S) {
    kakou = S.kakou;
  };
  void nepegBurM1() {

    CTPOKA txt1(" New Game"), txt2("?");
    paMka1.HapucoBaTbFoH(1, 1, 81, 26, 1);
    paMka1.HapucoBaTbK(1, 1, 80, 5, 15);
    paMka1.HapucoBaTbK(2, 2, 13, 4, 31);
    paMka1.HapucoBaTbtxt(3, 3, 15, txt1);
    paMka1.HapucoBaTbK(14, 2, 16, 4, 15);
    paMka1.HapucoBaTbtxt(15, 3, 15, txt2);
    kakou = 1;
    int i = 1;

    while(i == 1) {
      switch(getch()) {
        case 77:
          paMka1.HapucoBaTbK(2, 2, 13, 4, 15);
          paMka1.HapucoBaTbtxt(3, 3, 15, txt1);
          paMka1.HapucoBaTbK(14, 2, 16, 4, 31);
          paMka1.HapucoBaTbtxt(15, 3, 15, txt2);
          kakou = 2;
          break;

        case 75:
          paMka1.HapucoBaTbK(2, 2, 13, 4, 31);
          paMka1.HapucoBaTbtxt(3, 3, 15, txt1);
          paMka1.HapucoBaTbK(14, 2, 16, 4, 15);
          paMka1.HapucoBaTbtxt(15, 3, 15, txt2);
          kakou = 1;
          break;

        case 27:
          i = 0;
          break;

        case 32:
          MuHIo2 m1;
          MaTp m2;

          if (kakou == 1) m1.nepegBurM2();

          if (m1.zHa4M2() == 1) {
            m2.BBog();
            m2.BbI4ucJIMuH();

            m2.gocka();
            m2.nepeMeLLIeHue(2, 7);
            i = 1;
            paMka1.HapucoBaTbFoH(1, 7, 81, 34, 1);
          } else i = 0;


          break;


      }
    }
  }
  void zHa4M1(int a) {
    kakou = a;
  };
  int zHa4M1() {
    return kakou;
  };


};

int main() {
  MuHIo1 w;
  w.nepegBurM1();

  /*------------------------------------------------------
      gotoxy(1,25);
      system("PAUSE");
      return 0; */
}



