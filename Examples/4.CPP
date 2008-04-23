#include <iostream.h>
#include <stdio.h>
#include <conio.h>
class CMatrix
{
 public:
 int** p;
 int nstr, nstb;
 CMatrix operator=(CMatrix);
 CMatrix operator+(CMatrix);
 CMatrix operator-(CMatrix);
 CMatrix operator*(CMatrix);
 CMatrix operator+=(CMatrix);
 CMatrix operator-=(CMatrix);
 CMatrix operator*=(CMatrix); 
 CMatrix operator[](int);
 friend istream & operator >> (istream &, CMatrix &);
 friend ostream & operator << (ostream &, CMatrix &);
 CMatrix(int**,int,int);
 CMatrix();
 CMatrix(CMatrix &);
 ~CMatrix();
 int outarray(ostream &);
 int inarray (istream &);
};

CMatrix::CMatrix(int** x,int n, int m)
{
  p=x;
  nstr=n;
  nstb=m;
}
CMatrix::CMatrix()
{
  nstr=0;
  nstb=0;
  p=NULL;
};
CMatrix::CMatrix(CMatrix& m)
{
  nstr=m.nstr;
  nstb=m.nstb;
  p=new int*[nstr];
  for(int i=0;i<nstr;i++)
    p[i]=new int[nstb];
  for(i=0;i<nstr;i++)
    for(int j=0;j<nstb;j++)
       p[i][j]=m.p[i][j];
};
CMatrix::~CMatrix()
{
 delete[]p;
};

ostream & operator << (ostream &os, CMatrix &m)
{
  m.outarray(os);
  return os;
};

istream & operator >> (istream &is, CMatrix &m)
{
  m.inarray(is);
  return is;
};

int CMatrix::outarray(ostream& os)
{
  if(!os) return 0;
  for(int i=0;i<nstr;i++)
   { cout<<endl;
     for(int j=0;j<nstb;j++)
        cout<<p[i][j]<<" ";
    };
  cout<<endl;
  return 1;
};

int CMatrix::inarray(istream& is)
{
  if(!is) return 0;
  do{
     do{
	 cputs("Vvedite kolichestvo strok: <5 ");
	 scanf("%d",&nstr);
	 cputs("Vvedite kolichestvo stolbcov: <5 ");
	 scanf("%d",&nstb);
       }
     while(nstr>=5||nstb>=5);
     if(nstr!=nstb || nstr>=5||nstb>=5)
       { puts("ERROR!:");
	 puts("kol-vo strok dolgno ravnyatsya kol-vu stolbcov!!!");
	 puts("ili bit' <5");};
    }
  while(nstr!=nstb);
     p=new int*[nstr];
  for(int i=0;i<nstr;i++)
    p[i]=new int[nstb];
  for(i=0;i<nstr;i++)
    for(int j=0;j<nstb;j++)
      {
	cprintf("Vvedite [%d][%d] element of matrix:",i,j);
        cin>>p[i][j];
      };
  return 1;
};

//---------------------------------------------------------------------------
CMatrix CMatrix::operator=(CMatrix m)
{
  if(nstr==m.nstr&&nstb==m.nstb)
   {
     for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          p[i][j]=m.p[i][j];
   }
 return *this;
};


CMatrix CMatrix::operator+(CMatrix m)
{ CMatrix x=m;
  if(nstr==m.nstr&&nstb==m.nstb)
   { for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          x.p[i][j]=p[i][j]+m.p[i][j];
   }
 return x;
};
CMatrix CMatrix::operator-(CMatrix m)
{ CMatrix x=m;
  if(nstr==m.nstr&&nstb==m.nstb)
   { for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          x.p[i][j]=p[i][j]-m.p[i][j];
   }
 return x;
};

CMatrix CMatrix::operator+=(CMatrix m)
{
  if(nstr==m.nstr && nstb==m.nstb)
   {
     for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          p[i][j]+=m.p[i][j];
   }
 return *this;
};

CMatrix CMatrix::operator*(CMatrix m)
{
  CMatrix x=m;
  for(int i=0;i<nstr;i++)
    for(int j=0;j<nstb;j++)
       {
         x.p[i][j]=0;
       }
  if(nstr==m.nstr && nstb==m.nstb)
   { for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
         for(int k=0;k<nstr;k++)
            {
               x.p[i][j]+=p[i][k]*m.p[k][j];
             }
   }
 return x;
};


CMatrix CMatrix::operator-=(CMatrix m)
{
  if(nstr==m.nstr&&nstb==m.nstb)
   {
     for(int i=0;i<nstr;i++)
       for(int j=0;j<nstb;j++)
          p[i][j]-=m.p[i][j];
   }
 return *this;
};
CMatrix CMatrix::operator*=(CMatrix m)
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
};

CMatrix CMatrix::operator[](int n)
{ CMatrix x;
  x.nstr=1;
  x.nstb=nstb;
  for(int i=0;i<nstb;i++)
    x.p[0][i]=p[i][n-1];
 return x;
};
// MAIN:

void main()
{
  CMatrix matr;
  clrscr();
  cin>>matr;
  cputs("matrix:                                                                 (->A)");
  cout<<matr;

  cputs("Rabota constructora copirovaniya matrix :                               (->B)");
  CMatrix matr1=matr;
  cout<<matr1<<endl;

  matr+=matr1;
  cputs("A+=B                                                                    (->A)");
  cout<<matr<<endl;
  getch();

  matr1-=matr;
  cputs("B-=A                                                                    (->B)");
  cout<<matr1<<endl;
  getch();

  CMatrix matr2=matr;
  matr2=matr1*matr;
  cputs("C=B*A                                                                   (->C)");
  cout<<matr2<<endl;
  getch();

  matr2=matr1+matr;
  cputs("C=B+A");
  cout<<matr2<<endl;
  getch();

  matr2=matr1-matr;
  cputs("C=B-A");
  cout<<matr2<<endl;
  getch();

  matr2*=matr1;
  cputs("C*=B");
  cout<<matr2<<endl;
  getch();
};
