
```
// Подключение библиотеки
#include <iostream.h> // Библиотека для потокового ввода-вывода
#include <conio.h> // Библиотека для консольного ввода-вывода (используем одну функцию getch())

// Объявление базового класса
class A {
  // Инкапсуляция
  public: // Аттрибуты и методы, доступные извне класса (всем)
    int public_var_A; 
    void public_method(){
      // Из методов класса A доступны все 3 переменные
      public_var_A = 1;
      private_var_A = 2;
      protected_var_A = 3;
    }
  protected:
    int protected_var_A;
  private: // Аттрибуты и методы, доступные только из самого класса
    int private_var_A;
};


// B - наследник A
class Default : A {
  public:
    // Метод в наследнике класса
    void m(){
      public_var_A = 1;
      // Переменная private напрямую из наследника недоступна
      // private_var_A = 2; // Ошибка компиляции: is not accessible
      // Но на самом деле переменная есть и к ней можно
      // обратиться при помощи метода класса A
      public_method();
      // При этом к своей private-переменной мы можем спокойно обратиться
      private_var_Default = 123;
      protected_var_A = 3;
    }
  protected:
    int protected_var_Default;
  private:
    int private_var_Default;
};

// C - наследник A
class Public : public A {
  void m(){
    public_var_A = 1;
    // private_var_A = 1;
    protected_var_A = 3;
  }
};

class Public_X : Public {
  void m(){
    public_var_A = 1;
    // private_var_A = 1;
    protected_var_A = 3;
  }
};

// C - наследник A
class Private : private A {
 void m(){
   public_var_A = 1;
   // private_var_A = 1;
   protected_var_A = 3;
 }
};

class Private_X : Private {
  void m(){
    // public_var_A = 1;
    // private_var_A = 1;
    // protected_var_A = 3;
  }
};

// C - наследник A
class Protected : protected A {
 void m(){
   public_var_A = 1;
   // private_var_A = 1;
   protected_var_A = 3;
 }
};

class Protected_X : Protected {
  void m(){
    public_var_A = 1;
    // private_var_A = 1;
    protected_var_A = 3;
  }
};

int main(int argc, char* argv[]) {
  // Создаём экземпляр класса A
  A a;
  // public-переменная класса A доступна отовсюду
  a.public_var_A = 1;
  // a.protected_var_A = 2; // not accessible
  // a.private_var_A = 3; // not accessible
  Default b;
  // b.public_var_A = 1;
  // b.protected_var_A = 2; // not accessible
  // b.private_var_A = 3; // not accessible
  Public c;
  c.public_var_A = 1;
  // c.protected_var_A = 2; // not accessible
  // c.private_var_A = 3; // not accessible
  Private d;
  // d.public_var_A = 1;
  // d.protected_var_A = 2; // not accessible
  // d.private_var_A = 3; // not accessible
  Protected e;
  // e.public_var_A = 1;
  // e.protected_var_A = 2; // not accessible
  // e.private_var_A = 3; // not accessible
  getch();
  return 0;
}
```