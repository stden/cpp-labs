#include <iostream>

// Операции сравнения
template<class T> bool comp(T c1, T c2){ return c1>c2; } // Общая функция стравнения
bool comp(char* str1, char* str2){ return strcmp(str1,str2)>0; } // Специализированная функция сравнения

template <class T>
class Vector {
  T *data; // массив данных
  int size; // размер массива данных
public:
  Vector(int _size){ size = _size; data = new T[size]; };
  ~Vector(){ delete []data; }
  T& operator[](int i){ return data[i]; } 
  void Sort(){
	for(int i=0;i<size;i++)  
	  for(int j=i+1;j<size;j++)
		if(comp(data[i],data[j])){
		  T swap = data[i];
		  data[i] = data[j];
		  data[j] = swap;
		}  
  }
  void Show(){
    for(int i=0;i<size;i++)
	  std::cout << data[i] << std::endl;	  
  }
};

void test_char(){
  Vector<char> vc(4);
  vc[0] = 'b'; vc[1] = 'c'; vc[2] = 'a'; vc[3] = 'd';  
  vc.Sort();  
  vc.Show();
}

void test_int(){
  Vector<int> vc(4);
  vc[0] = 3; vc[1] = 5; vc[2] = 2; vc[3] = 1;  
  vc.Sort();  
  vc.Show();
}

void test_string(){
  Vector<char*> vc(4);
  vc[0] = "test1"; vc[1] = "sdgf"; vc[2] = "xv"; vc[3] = "df";  
  vc.Sort();
  vc.Show();
}

int main() { 
  test_char();
  test_int();
  test_string();	
  return 0;
}
