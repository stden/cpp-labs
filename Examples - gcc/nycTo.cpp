#include <windows.h>
#include <cstdlib>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;
class MuHa
{
        int x,y,color;
        public:
             MuHa()
             {
                   x=0;y=0;color=0;
             };

             ~MuHa()
             {
                   x=0;y=0;color=0;
             };

             MuHa(int a,int b,int c)
             {
                   x=a;y=b;color=c;
             };

             MuHa(MuHa& S)
             {
                   x=S.x;y=S.y;color=S.color;
             };
             void HapucoBaTbMuHy(int x,int y, int color)
             {
                HANDLE hConsole;
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, color);
                gotoxy(x,y);
                printf("%c",15);

             }
};
class kJIeTka
{
        int x, y, color, kaka9;
        public:
                kJIeTka()
                {
                        x=0;y=0;color=0;kaka9=0;
                };
                ~kJIeTka()
                {
                        x=0;y=0;color=0;kaka9=0;
                };
                kJIeTka(int a,int b,int c)
                {
                        x=a;y=b;color=c;kaka9=0;
                };
                kJIeTka(kJIeTka& S)
                {
                        x=S.x;y=S.y;color=S.color;kaka9=S.kaka9;
                };
                void HapucoBaTbkJIeTky(int x, int y, int color)
                {
                        HANDLE hConsole;
                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, color);
                        gotoxy(x+3,y+1);
                        printf("%c",179);
                        gotoxy(x,y+1);
                        printf("%c",179);
                        gotoxy(x,y+2);
                        printf("%c",192);
                        gotoxy(x+3,y+2);
                        printf("%c",217);
                        gotoxy(x,y);
                        printf("%c",218);
                        gotoxy(x+1,y);
                        printf("%c",196);
                        gotoxy(x+2,y);
                        printf("%c",196);
                        gotoxy(x+1,y+2);
                        printf("%c",196);
                        gotoxy(x+2,y+2);
                        printf("%c",196);
                        gotoxy(x+3,y);
                        printf("%c",191);
                        gotoxy(x+2,y+1);
                        cout<<" ";
                        gotoxy(x+1,y+1);
                        cout<<" ";
                }
                int coordx()
                {
                        return x;
                };
                int coordy()
                {
                        return y;
                };
                void peremestit(int a,int b)
                {
                        x=a;
                        y=b;
                };
                void zHa4(int a)
                {
                        kaka9=a;
                };

                int zHa4()
                {return kaka9;};

};
class MaTpuua
{
        typedef int sType[9];
        typedef sType Matrix[9];
        Matrix ty;
        MuHa Mu;
        kJIeTka kl;
        int x, y,p,z,c,l, koJIBoMuH,koJIBoyrag;
        public:
                MaTpuua()
                {
                        x=0;y=0;
                        for (int i=0;i<9;i++)
                                for (int j=0;j<9;j++) ty[i][j]=0;

                }
                void BBog()
                {
                        x=9;y=9;
                        for (int i=0;i<x;i++)
                        {
                                for (int j=0;j<y;j++)
                                if (i==j) ty[i][j]=10; else ty[i][j]=0;
                        };
                        ty[2][7]=10;
                }
                void BbI4ucJIMuH()
                {
                        int x1,y1;
                        x=9;y=9;
                        for (x1=0;x1<x;x1++)
                        {
                                for (y1=0;y1<y;y1++)
                                {
                                        if (ty[x1][y1]==0)
                                        {
                                                int okp=0;
                                                if (x1>0) if (y1>0) if (x1<9) if (y1<9)
                                                {
                                                        if (ty[x1-1][y1-1]==10)okp++;
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1-1][y1+1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                        if (ty[x1+1][y1-1]==10)okp++;
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1+1][y1+1]==10)okp++;
                                                }
                                                if (x1==0) if (y1==0)
                                                {
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                        if (ty[x1+1][y1+1]==10)okp++;
                                                }
                                                if (x1==9) if (y1==0)
                                                {
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                        if (ty[x1-1][y1+1]==10)okp++;
                                                }
                                                if (x1==0) if (y1==9)
                                                {
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                        if (ty[x1+1][y1-1]==10)okp++;
                                                }

                                                if (x1==9) if (y1==9)
                                                {
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                        if (ty[x1-1][y1-1]==10)okp++;
                                                }

                                                if (y1==0) if (x1>0) if (x1<8)
                                                {
                                                        if (ty[x1-1][y1+1]==10)okp++;
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1+1][y1+1]==10)okp++;
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                }
                                                if (y1==9) if (x1>1) if (x1<8)
                                                {
                                                        if (ty[x1-1][y1-1]==10)okp++;
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1+1][y1-1]==10)okp++;
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                }
                                                if (x1==0) if (y1>0) if (y1<8)
                                                {
                                                        if (ty[x1+1][y1-1]==10)okp++;
                                                        if (ty[x1+1][y1]==10)okp++;
                                                        if (ty[x1+1][y1+1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                }
                                                if (x1==9) if (y1>1) if (y1<9)
                                                {
                                                        if (ty[x1-1][y1+1]==10)okp++;
                                                        if (ty[x1-1][y1]==10)okp++;
                                                        if (ty[x1-1][y1-1]==10)okp++;
                                                        if (ty[x1][y1+1]==10)okp++;
                                                        if (ty[x1][y1-1]==10)okp++;
                                                }
                                                ty[x1][y1]=okp;
                                        }
                                }

                        }

                }
                void BbiBog()
                {
                        for (int i=0;i<x;i++)
                        {
                                cout<<"\n";
                                for (int j=0;j<y;j++)
                                        cout<<ty[i][j]<<"  ";
                                cout<<"\n";

                        }

                }
                void zAkpBbiBog()
                {
                        for (int i=0;i<x;i++)
                        {
                                cout<<"\n";
                                for (int j=0;j<y;j++)
                                        if (ty[i][j]!=10) if (ty[i][j]!=0) cout<<ty[i][j]<<"  ";
                                        else
                                                cout<<" ";
                                cout<<"\n";

                        }

                }

        void gocka()
        {
                x=34;
                y=27;
                int x2,y2;
                for (x2= 1; x2 <x; x2= x2 + 4)
                        for (y2= 1; y2 <y; y2= y2 + 3)
                        {
                                kl.HapucoBaTbkJIeTky(x2,y2,144);

                        }
        }
        void MuHIoBbI5op()
        {
                        p=1;
                        HANDLE hConsole;
                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        gotoxy(40,10);
                        SetConsoleTextAttribute(hConsole, 224);
                        cout<<"oTkpbITb kJIeTky" ;
                        gotoxy(40,13);
                        SetConsoleTextAttribute(hConsole, 112);
                        cout<<"nocTaBuTb FJIar";
                        int i=1;
                        while(i==1)
                        {
                                switch(getch())
                                {
                                        case 72:
                                                gotoxy(40,10);
                                                SetConsoleTextAttribute(hConsole, 224);
                                                cout<<"oTkpbITb kJIeTky";
                                                gotoxy(40,13);
                                                SetConsoleTextAttribute(hConsole, 112);
                                                cout<<"nocTaBuTb FJIar";
                                                p=1;
                                                break;

                                        case 80:
                                                if (koJIBoyrag<11)
                                                {
                                                p=2;
                                                gotoxy(40,10);
                                                SetConsoleTextAttribute(hConsole, 112);
                                                cout<<"oTkpbITb kJIeTky";
                                                gotoxy(40,13);
                                                SetConsoleTextAttribute(hConsole, 224);
                                                cout<<"nocTaBuTb FJIar" ;
                                                }
                                                break;

                                        case 27:
                                                i=0;
                                                break;
                                        case 32:
                                                i =0;
                                                break;

                        }
                }

        }

        void npoBepka(int x, int y)
        {
                if (ty[x][y]>10) l=1;else l=0;
        }
        void nepeMeLLIeHue(int x2, int y2, int m1,int m2)
        {
                        HANDLE hConsole;
                        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 112);
                        gotoxy(40,2);
                        cout<<"KoJIu4ecTbo fJIaroB: "<<11-koJIBoyrag;
                koJIBoMuH=10;
                kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                int i;
                i=1;
                z=m1;c=m2;
                while(i==1)
                {
                        gotoxy(40,10);
                        SetConsoleTextAttribute(hConsole, 112);
                        cout<<"oTkpbITb kJIeTky" ;
                        gotoxy(40,13);
                        SetConsoleTextAttribute(hConsole, 112);
                        cout<<"nocTaBuTb FJIar";
                        switch(getch())
                        {
                                case 72:


                                        npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,144);
	                                y2= y2 - 3;
	                                if(y2<2) y2=2;
                                        if (c>0) npoBepka(z,c-1);
                                        if (c==0) npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                        if (c>1)
                                        {
                                                z=z;
                                                c=c-1;
                                        }
                                        else
                                                c=0;


	                                break;

                                case 80:
                                        npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,144);
	                                y2= y2 + 3;
	                                if(y2>26) y2=26;

                                        if (c<8) npoBepka(z,c+1);
                                        if (c==8) npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                        if (c<7)
                                        {
                                                z=z;
                                                c=c+1;
                                        }
                                        else
                                                c=8;

	                                break;

                                case 77:
                                        npoBepka(z,c);
                                        if (l==0)
                                        kl.HapucoBaTbkJIeTky(x2-1,y2-1,144);
	                                x2= x2 + 4;
	                                if(x2>34) x2=34;
                                        if (z<8) npoBepka(z+1,c);
                                        if (z==8) npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                        if (z<7)
                                        {
                                                z=z+1;
                                                c=c;
                                        }
                                        else
                                                z=8;
	                                break;

                                case 75:
                                        npoBepka(z,c);
                                        if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,144);
	                                x2= x2 - 4;
	                                if(x2<2) x2 = 2;
                                        if (z>0) npoBepka(z-1,c);
                                        if (z==0) npoBepka(z,c);
	                                if (l==0) kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                        if (z>1)
                                        {
                                                z=z-1;
                                                c=c;
                                        }
                                        else
                                                z=0;

	                                break;

                                case 27:
                                        i=0;
                                        break;
                                case 32:
                                        if (ty[z][c]<11) MuHIoBbI5op();
                                        if (p==1)
                                        {
                                                ty[z][c]=ty[z][c] + 100;
                                                kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                                gotoxy(x2,y2);
                                                if (ty[z][c]==110)
                                                {

                                                        Mu.HapucoBaTbMuHy(x2,y2,20);
                                                        gotoxy(10,14);
                                                        SetConsoleTextAttribute(hConsole, 10);
                                                        cout<<"LUSER!-=)";
                                                        system("PAUSE");
                                                i=0;
                                                }
                                                if (ty[z][c]!=100) cout<<ty[z][c]-100;
                                                else
                                                        cout<<" ";
                                        }
                                        if (p==2)
                                        {
                                                SetConsoleTextAttribute(hConsole, 1);
                                                gotoxy(40,2);
                                                cout<<"                                    ";
                                                SetConsoleTextAttribute(hConsole, 112);
                                                gotoxy(40,2);
                                                cout<<"KoJIu4ecTbo fJIaroB: "<<10-koJIBoyrag;
                                                ty[z][c]=ty[z][c] + 200;
                                                kl.HapucoBaTbkJIeTky(x2-1,y2-1,112);
                                                gotoxy(x2,y2);
                                                printf("%c",20);
                                                koJIBoyrag=koJIBoyrag+1;
                                        } ;
                                        if (ty[z][c]==210) koJIBoMuH=koJIBoMuH-1;
                                        if (koJIBoMuH==0)
                                        {
                                                        gotoxy(10,14);
                                                        SetConsoleTextAttribute(hConsole, 10);
                                                        cout<<"WINER!-=)";
                                                        system("PAUSE");
                                                i=0;
                                        }

                                        break;

                        }
                }
        }

};
int main()
{   MaTpuua g;
    g.BBog();
    g.BbI4ucJIMuH();
    g.gocka();
    g.nepeMeLLIeHue(2,2,0,0);


    return 0;
}



