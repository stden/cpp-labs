### Простейший пример ###
``` cpp
#include <iostream>

using namespace std;

int main(int argc,char* argv[]){
  for(int i=0;i<argc;i++)
    cout << i << ") " << argv[i] << endl;
  return 0;
}
```

Вызов из командной строки:
```
C:\MinGW\bin>c++ a.cpp


C:\MinGW\bin>a.exe 3.2 4.5 dsrsdf "C:\Program Files"
0) C:\MinGW\bin\a.exe
1) 3.2
2) 4.5
3) dsrsdf
4) C:\Program Files
```

### Вывод размеров стандартных типов ###
``` cpp
#include <iostream>
#include <strings.h>

using namespace std;

#define show(t) cout << "  sizeof(" << #t << ") = " << sizeof(t) << endl;
#define cond(t) if(!strcmp(type,#t)) show(t);

int main(int argc,char* argv[]){
  if(argc == 1){
    cout << "Syntax: a.exe <types>" << endl;
  } else {
    for(int i=0;i<argc;i++){
      char* type = argv[i];
      cout << i << ". " << argv[i] << endl;
      cond(char);
      cond(short);
      cond(int);
      cond(long);
      cond(float);
      cond(double);
      cond(long double);
    }
  }
  cout << endl << "List:" << endl;
  show(char);
  cout << "Integer types: " << endl;
  show(short); 
  show(int); 
  show(long);
  cout << "Float point types: " << endl;
  show(float);  
  show(double); 
  show(long double); 
  return 0;
}
```

### Вывод программы ###
```
0. C:\MinGW\bin\a.exe
1. char
  sizeof(char) = 1
2. double
  sizeof(double) = 8

List:
  sizeof(char) = 1
Integer types:
  sizeof(short) = 2
  sizeof(int) = 4
  sizeof(long) = 4
Float point types:
  sizeof(float) = 4
  sizeof(double) = 8
  sizeof(long double) = 12
```
