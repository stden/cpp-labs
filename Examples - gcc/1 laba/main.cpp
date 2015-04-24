#include <iostream>
#include <conio.h>
#include <math.h>
using namespace std;
class gpo5b {
 public:
  int ch, zn;
  void BBog(i) {
    clrscr();
    gotoxy(1, 3);
    cout << "BBeguTe " << i << "-Io gpo5b: -----";
    gotoxy(23, 2);
    cin >> ch;
    gotoxy(23, 2);
    cout << ch;

    while (1) {
      clrscr();
      gotoxy(1, 3);
      cout << "BBeguTe " << i << "-Io gpo5b: -----";
      gotoxy(23, 2);
      cout << ch;
      gotoxy(23, 4);
      cin >> zn;
      gotoxy(23, 4);
      cout << zn;

      if (zn == 0);
      else break;
    }
  };
  void BbIBog(int x, int y) {
    gotoxy(x, y);
    cout << "-----";
    gotoxy(x + 2, y - 1);
    cout << ch;
    gotoxy(x + 2, y + 1);
    cout << zn;
  };
  void cokpaT() {
    int i = 0;

    if (ch < zn) i = abs(ch);
    else if (zn < ch) i = abs(zn);
    else {
      ch = 1;
      zn = 1;
      i = 1;
    };

    while (i > 1) {
      if (fmod(ch, i) == 0)
        if (fmod(zn, i) == 0) {
          ch = ch / i;
          zn = zn / i;
          i = 1;
        };

      i--;
    };
  };
  gpo5b nJIIoc(gpo5b x) {
    gpo5b s;

    if (x.zn != zn) {
      x.ch = x.ch * zn;
      ch = ch * x.zn;
      x.zn = x.zn * zn;
      zn = x.zn;
    };

    s.ch = x.ch + ch;

    s.zn = x.zn;

    s.cokpaT();

    return s;
  };
  gpo5b MuHyc(gpo5b x) {
    gpo5b s;

    if (x.zn != zn) {
      x.ch = x.ch * zn;
      ch = ch * x.zn;
      x.zn = x.zn * zn;
      zn = x.zn;
    };

    s.ch = ch - x.ch;

    s.zn = x.zn;

    s.cokpaT();

    return s;
  };
  gpo5b yMHoJiLuTb(gpo5b x) {
    gpo5b s;
    s.ch = ch * x.ch;
    s.zn = zn * x.zn;
    s.cokpaT();
    return s;
  };
  gpo5b pa3geJIuTb(gpo5b x) {
    gpo5b s;
    s.ch = ch * x.zn;
    s.zn = zn * x.ch;
    s.cokpaT();
    return s;
  };


};
gpo5b x, y, z;
int main() {
  x.BBog(1);
  y.BBog(2);
  clrscr();
  gotoxy(1, 3);
  cout << "gpo5b 1: ";
  x.BbIBog(10, 3);
  gotoxy(20, 3);
  cout << "gpo5b #2: ";
  y.BbIBog(30, 3);
  gotoxy(1, 8);
  cout << "---------------------------------------";
  gotoxy(1, 10);
  cout << "cyMMa gpo5eu': ";
  z = x.nJIIoc(y);
  z.BbIBog(15, 10);
  gotoxy(1, 13);
  cout << "pa3HocTb gpo5eu': ";
  z = x.MuHyc(y);
  z.BbIBog(18, 13);
  gotoxy(1, 16);
  cout << "npou3BegeHue gpo5eu': ";
  z = x.yMHoJiLuTb(y);
  z.BbIBog(22, 16);
  gotoxy(1, 19);
  cout << "oTHoLLIeHue gpo5eu': ";
  z = x.pa3geJIuTb(y);
  z.BbIBog(21, 19);




  gotoxy(1, 25);
  system("PAUSE");
  return 0;
}
