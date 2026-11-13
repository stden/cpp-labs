#include <iostream.h>
#include <conio.h>

template< class T>
class CStack {
  int size, //Size of stack
      top;//Top of stack
  T* stackPtr;

  int isEmpty() {
    return top == -1;
  };
  int isFull() {
    return top == size - 1;
  };

 public:
  CStack(int = 10);
  ~CStack() {
    delete [] stackPtr;
  };
  int push(T&);
  int pop(T&);
};

template<class T>
CStack<T>::CStack(int s) {
  size = s > 0 ? s : 10;
  top = -1;
  stackPtr = new T[size];
}

template<class T>
int CStack<T>::push(T& pushValue) {
  if (!isFull()) {
    stackPtr[++top] = pushValue;
    return 1;
  }

  return 0;
}

template<class T>
int CStack<T>::pop(T& popValue) {
  if (!isEmpty()) {
    popValue = stackPtr[top--];
    return 1;
  }

  return 0;
}




int main() {
  clrscr();
  CStack<double> doubleStack(5);
  double f = 1.1;
  cout << "pushing elements in to the stack\n";

  while (doubleStack.push(f)) {
    cout << f << " ";
    f += 1.1;
  }

  cout << "\nStack is full\n";
  cout << "Extraction elements from stack\n";

  while (doubleStack.pop(f))
    cout << f << " ";

  cout << "\nStack is empty\n";

  CStack<int> intStack;
  int i = 1;
  cout << "pushing elements in to the stack\n";

  while(intStack.push(i)) {
    cout << i << " ";
    i++;
  }

  cout << "\nStack is full\n";
  cout << "Extraction elements from stack\n";

  while (intStack.pop(i))
    cout << i << " ";

  cout << "\nStack is empty\n";
  getch();
  return 0;
}