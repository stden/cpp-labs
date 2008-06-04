#include <cstdlib>
#include <iostream>
#include <conio.h>

using namespace std;

class matrix
{
      int** e;
      int s,c;
      public:
             matrix()
             {s=0;
              c=0;
             };

             matrix(int x,int y)
             {
                    s=x;
                    c=y;
                    e=new int*[s];
                    for (int i=0;i<s;i++)
                    {
                        e[i]=new int[c];
                        for (int j=0;j<c;j++) e[i][j]=0;
                    };
             };

             matrix(const matrix& x)
             {
                    s=x.s;
                    c=x.c;
                    e=new int*[s];
                    for (int i=0;i<s;i++)
                    {
                       e[i]=new int[c];
                       for (int j=0;j<c;j++) e[i][j]=x.e[i][j];
                    };

             };

             matrix& operator~()
             {
                    matrix temp(*this);
                    for (int i=0;i<s;i++) delete[]e[i];
                    delete[]e;
                    s=temp.c;
                    c=temp.s;
                    e=new int*[s];
                    for (int i=0;i<s;i++)
                    {
                       e[i]=new int[c];
                       for (int j=0;j<c;j++) e[i][j]=temp.e[j][i];
                    };
                    return *this;
             };

             matrix& operator-()
             {
                    for (int i=0;i<s;i++)
                        for (int j=0;j<c;j++)
                            e[i][j]=-e[i][j];
                    return *this;
             };

             matrix& operator=(const matrix& x)
             {
                 if (this->s!=0)
                 {
                    for (int i=0;i<s;i++) delete[]e[i];
                    delete[]e;
                 };
                 s=x.s;
                 c=x.c;
                 e=new int*[s];
                 for (int i=0;i<s;i++)
                 {
                     e[i]=new int[c];
                    for (int j=0;j<c;j++) e[i][j]=x.e[i][j];
                 };
                 return *this;
             };

             friend const matrix operator+(const matrix&,const matrix&);
             friend const matrix operator-(const matrix&,const matrix&);
             friend const matrix operator*(const matrix&,const matrix&);
             friend ostream& operator<<(ostream&,matrix);
             friend istream& operator>>(istream&,matrix&);

             ~matrix()
             {
                    for (int i=0;i<s;i++) delete[]e[i];
                    delete[]e;
             };
};

ostream& operator<<(ostream& os,matrix x)
{
        for (int i=0;i<x.s;i++)
        {
            cout<<"\n";
            for (int j=0;j<x.c;j++)
                os<<x.e[i][j]<<" ";
        };
        cout<<"\n";
        return os;
};

istream& operator>>(istream& is,matrix& x)
{
        for (int i=0;i<x.s;i++)
        {
            cout<<"BBeguTe 3Ha4eHue "<<i+1<<" cTpoku (4epe3 npo5eJI)\n";
            for (int j=0;j<x.c;j++)
                cin>>x.e[i][j];
        };
        return is;
};

const matrix operator+(const matrix& x,const matrix& y)
{matrix A;
if (x.s!=y.s||x.c!=y.c) {cout<<"CJIo}I{eHue He Bo3Mo}I{Ho\n";return A;};
   A=x;
   for (int i=0;i<x.s;i++)
       for (int j=0;j<x.c;j++)
           A.e[i][j]+=y.e[i][j];
   return A;
};

const matrix operator-(const matrix& x,const matrix& y)
{matrix A;
   if (x.s!=y.s||x.c!=y.c) {cout<<"BbI4uTaHUe He Bo3Mo}I{Ho\n";return A;};
   A=x;
   for (int i=0;i<A.s;i++)
       for (int j=0;j<A.c;j++)
           A.e[i][j]-=y.e[i][j];
   return A;
};

const matrix operator*(const matrix& x,const matrix& y)
{matrix A(x.s,x.c);
   if (x.c!=x.s) {cout<<"yMHo}I{eHue He Bo3Mo}I{Ho\n";return A;};
   for (int i=0;i<A.s;i++)
       for (int j=0;j<A.c;j++)
           for (int k=0;k<x.c;k++)
               A.e[i][j]+=x.e[i][k]*y.e[k][j];
   return A;
};



int main()
{
    int x,y;
    cout<<"BBeguTe pa3MepHocTb MaTpuu,u(x y): ";
    cin>>x>>y;

    matrix A(x,y);
    cin>>A;
    matrix B(A);
    matrix S,PR,RAZ;
    ~B;
    cout<<"ucxogHa9 MaTpuu,a: "<<A<<"\nTpaHcnoHupoBaHHa9 MaTpuu,a: "<<B;
    S=A+B;
    PR=A*B;
    RAZ=A-B;
    cout<<"CyMMa: "<<S;
    cout<<"npou3BegeHue: "<<PR;
    cout<<"Pa3HocTb: "<<RAZ;

    system("PAUSE");
    return EXIT_SUCCESS;
}
