#include <iostream>

using namespace std;

class cTpoka
{
       char* S;
       size_t len;
       public:
       cTpoka()
       {
               S=NULL;
               len=0;
       };
       cTpoka(char* x)
       {
               len=strlen(x);
               S=new char[len+1];
               strcpy(S,x);
       };
       cTpoka(cTpoka& x)
       {
               len=x.len;
               S=new char[len+1];
               strcpy(S,x.S);
       };
       void BBog()
       {
               char x[30];
               cin>>x;
               len=strlen(x);
               S=new char[len+1];
               strcpy(S,x);
       };
       void BbIBog()
       {
               cout<<S<<"\n";
       };
       cTpoka& operator=(cTpoka x)
       {
            cTpoka s;
            if(this==&x) return *this;
            if(len!=x.len)
            {
                 delete[]S;
                 len=x.len;
                 S=new char[len+1];
            };
            strcpy(S,x.S);
            return *this;
        };
       cTpoka operator+(cTpoka& x)
       {
               cTpoka s;
               s.len=len+x.len;
               s.S=new char[s.len+1];
               strcpy(s.S,S);
               strcat(s.S,x.S);
               return s;
       };
       cTpoka& operator+=(cTpoka& x)
       {
        *this=*this+x;
        return *this;
       };
       cTpoka operator-(cTpoka& x)
       {
         cTpoka s;
         s.len=len-x.len;
         s.S=new char[s.len];
         for (int i=0;i<len;i++)
         {
              for (int j=0;j<x.len;j++)
              {
                  if (S[i+j]!=x.S[j]) goto A;
              };
              for (int k=0;k<i;k++)
                s.S[k]=S[k];
              for (int l=i+x.len;l<len;l++)
                s.S[l-x.len]=S[l];
              if ((i+x.len)==len) s.S[i]='\0';
              A:
              continue;
         };
              return s;
         return *this;
       };

       cTpoka& operator-=(cTpoka& x)
       {
       *this=*this-x;
       return *this;
       };

       operator char*() { return S; };
};


int main()
{
        cTpoka a,b,c;
        cout<<"BBeguTe nepByIo cTpoky: \n";
        a.BBog();
        cout<<"BBeguTe BTopyIo cTpoky: \n";
        b.BBog();
        cout<<"BBeguTe TpeTbIo cTpoky: \n";
        c.BBog();
        cout<<"npucBauBaHue '=' nepBou' cTpoku TpeTeu'\n";
        c=a;
        c.BbIBog();
        cout<<"cJio}I{eHue '+' u '+=' nepBou' cTpoku u BTopou'\n";
        c=a+b;
        c.BbIBog();
        c=a;
        c+=b;
        c.BbIBog();
        cout<<"ygaJIeHue '-' u '-=' u3 nepBou' cTpoku, BTopou'\n";
        c=a-b;
        c.BbIBog();
        c=a;
        c-=b;
        c.BbIBog();
        system("PAUSE");
	return 0;
}
