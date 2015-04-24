#include <iostream.h>
#include <stdio.h>
#include <conio.h>
//матрица целых чисел
class TMatrix {
 public:
  int** p;
  int nstr, nstb;
  TMatrix operator=(TMatrix);
  TMatrix operator+=(TMatrix);
  TMatrix operator-=(TMatrix);
  TMatrix operator*=(TMatrix);
  TMatrix operator+(TMatrix);
  TMatrix operator-(TMatrix);
  TMatrix operator*(TMatrix);
  TMatrix operator[](int);
  friend istream& operator >> (istream&, TMatrix&);
  friend ostream& operator << (ostream&, TMatrix&);
  TMatrix(int**, int, int);
  TMatrix();
  TMatrix(TMatrix&);
  ~TMatrix();
  int outarray(ostream&);
  int inarray (istream&);
};

TMatrix::TMatrix(int** x, int n, int m) {
  p = x;
  nstr = n;
  nstb = m;
}
TMatrix::TMatrix() {
  nstr = 0;
  nstb = 0;
  p = NULL;
};
TMatrix::TMatrix(TMatrix& m) {
  nstr = m.nstr;
  nstb = m.nstb;
  p = new int* [nstr];

  for(int i = 0; i < nstr; i++)
    p[i] = new int[nstb];

  for(i = 0; i < nstr; i++)
    for(int j = 0; j < nstb; j++)
      p[i][j] = m.p[i][j];
};
TMatrix::~TMatrix() {
  delete[]p;
};

int TMatrix::outarray(ostream& os) {
  if(!os) return 0;

  for(int i = 0; i < nstr; i++) {
    cout << endl;

    for(int j = 0; j < nstb; j++)
      cout << p[i][j] << " ";
  };

  cout << endl;

  return 1;
};
istream& operator >> (istream& is, TMatrix& m) {
  m.inarray(is);
  return is;
};

int TMatrix::inarray(istream& is) {
  textattr(2);

  if(!is) return 0;

  do {
    do {
      cputs("Vvedite kolichestvo strok matricu: <5");
      scanf("%d", &nstr);
      cputs("Vvedite kolichestvo stolbcov matricu: <5");
      scanf("%d", &nstb);
    } while(nstr >= 5 || nstb >= 5);

    if(nstr != nstb || nstr >= 5 || nstb >= 5) {
      puts("oshibka:");
      puts("kol-vo strok dolgno ravnyatsya kol-vu stolbcov!!!");
      puts("ili bit' <5");
    };
  } while(nstr != nstb);

  p = new int* [nstr];

  for(int i = 0; i < nstr; i++)
    p[i] = new int[nstb];

  for(i = 0; i < nstr; i++)
    for(int j = 0; j < nstb; j++) {
      textattr(11);
      cprintf("Vvedite [%d][%d] element of matrix:", i, j);
      cin >> p[i][j];
    };

  return 1;
};

ostream& operator << (ostream& os, TMatrix& m) {
  m.outarray(os);
  return os;
};
//operacii
TMatrix TMatrix::operator=(TMatrix m) {
  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        p[i][j] = m.p[i][j];
  }

  return *this;
};

TMatrix TMatrix::operator+=(TMatrix m) {
  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        p[i][j] += m.p[i][j];
  }

  return *this;
};
TMatrix TMatrix::operator-=(TMatrix m) {
  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        p[i][j] -= m.p[i][j];
  }

  return *this;
};
/*TMatrix TMatrix::operator*=(TMatrix m)
{
  if(nstr==m.nstr&&nstb==m.nstb)
   { for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
         for(int k=0;k<nstr;k++)
            {
               p[i][k]*=m.p[k][j];
             }
   }
 return *this;
};*/
TMatrix TMatrix::operator+(TMatrix m) {
  TMatrix x = m;

  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        x.p[i][j] = p[i][j] + m.p[i][j];
  }

  return x;
};
TMatrix TMatrix::operator-(TMatrix m) {
  TMatrix x = m;

  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        x.p[i][j] = p[i][j] - m.p[i][j];
  }

  return x;
};
TMatrix TMatrix::operator*(TMatrix m) {
  TMatrix x = m;

  for(int i = 0; i < nstr; i++)
    for(int j = 0; j < nstb; j++)
      x.p[i][j] = 0;

  if(nstr == m.nstr && nstb == m.nstb) {
    for(int i = 0; i < nstr; i++)
      for(int j = 0; j < nstb; j++)
        for(int k = 0; k < nstr; k++)
          x.p[i][j] += p[i][k] * m.p[k][j];
  }

  return x;
};

/*TMatrix TMatrix::operator*(TMatrix m)
{ TMatrix x=m;
  if(nstr==m.nstr&&nstb==m.nstb)
   { for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          x.p[i][j]=p[i][j]*m.p[i][j];
   }
 return x;
};
*/
TMatrix TMatrix::operator[](int n) {
  TMatrix x;
  x.nstr = 1;
  x.nstb = nstb;

  for(int i = 0; i < nstb; i++)
    x.p[0][i] = p[i][n - 1];

  return x;
};
// MAIN:

void main() {
  TMatrix matr;
  //  TMatrix q;
  clrscr();
  cin >> matr;
  //  q=matr[1];
  //  cout<<q;
  //  cout<<matr[1]<<endl;
  TMatrix matr1 = matr;
  TMatrix matr2 = matr;
  textattr(303);
  cputs("matrix:                                                                 (->A)");
  cout << matr;
  textattr(303);
  cputs("Rabota constructora copirovaniya matrix :                               (->B)");
  cout << matr1 << endl;
  matr += matr2;
  textattr(303);
  cputs("A+=B                                                                    (->C)");
  cout << matr << endl;
  matr1 -= matr;
  textattr(303);
  cputs("B-=C                                                                    (->D)");
  cout << matr1 << endl;
  matr2 = matr;
  textattr(303);
  cputs("E=C                                                                     (->E)");
  cout << matr2 << endl;
  matr2 = matr1 * matr;
  textattr(303);
  cputs("F=D*E                                                                   (->F)");
  cout << matr2 << endl;
  textattr(303);
  cputs("D:");
  cout << matr1 << endl;
  textattr(303);
  cputs("C:");
  cout << matr << endl;
  matr2 = matr1 + matr;
  textattr(303);
  cputs("F=D+C");
  cout << matr2 << endl;
  matr2 = matr1 - matr;
  textattr(303);
  cputs("F=D-C");
  cout << matr2 << endl;
  /*  matr2*=matr1;
    textattr(303);
    cputs("F*=D");
    cout<<matr2<<endl; */
  getch();
  getchar();
};
