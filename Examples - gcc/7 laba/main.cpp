#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

class napaJIJIeJIorpaMM
{
      float dl,sh,u;
      public:
             napaJIJIeJIorpaMM(float a,float b,float c)
             {dl=a;sh=b;u=c;};
             void noMeH9Tb(float a,float b,float c)
             {dl+=a;sh+=b;u+=c;};
             virtual float nepuMeTp()
             {return 2*(dl+sh);};
             virtual float nJIoLLIagb()
             {return dl*sh*sin(u);};
};

class np9MoyroJIbHuk:virtual public napaJIJIeJIorpaMM
{
      public:
             np9MoyroJIbHuk(float a,float b):napaJIJIeJIorpaMM(a,b,1.571){};
             void noMeH9Tb(float a,float b)
             {napaJIJIeJIorpaMM::noMeH9Tb(a,b,0);};
};

class poM5:virtual public napaJIJIeJIorpaMM
{
     public:
            poM5(float a,float c):napaJIJIeJIorpaMM(a,a,c){};
            void noMeH9Tb(float a,float c)
            {napaJIJIeJIorpaMM::noMeH9Tb(a,a,c);};
};

class kBagpaT:public np9MoyroJIbHuk,public poM5
{
      public:
            kBagpaT(float a):napaJIJIeJIorpaMM(a,a,1.571),np9MoyroJIbHuk(a,a),poM5(a,1.571){};
            void noMeH9Tb(float a)
            {np9MoyroJIbHuk::noMeH9Tb(a,a);};
};

int main()
{
    kBagpaT A(30);
    cout<<"nepuMeTp= "<<A.nepuMeTp()<<"\n";
    cout<<"nJIoLLIagb= "<<A.nJIoLLIagb()<<"\n";
    A.noMeH9Tb(50);
    cout<<"nepuMeTp= "<<A.nepuMeTp()<<"\n";
    cout<<"nJIoLLIagb= "<<A.nJIoLLIagb()<<"\n";
    system("PAUSE");
    return EXIT_SUCCESS;
}
