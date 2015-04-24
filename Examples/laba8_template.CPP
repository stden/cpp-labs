#include <iostream.h>
#include <stdlib.h>

enum bool {false, true};

template<class T> class Q {
 private:
  struct QEl {
    QEl* next;
    T elem;
  }* s;

  int len, n;

 public:
  Q();
  ~Q() {};
  bool full();
  void init(int );
  void print();
  void add();
  void rem();


};


template<class T> Q <T> ::Q() {
  s = 0;
  n = 0;
  len = 0;
}

template<class T> Q <T> ::~Q() {
  QEl* temp = s;

  while (s) {
    delete temp;
    s = s->next;
    temp = s;
  }

  delete s;
}


template<class T>bool Q<T>::full() {
  if (n == len) return true;
  else return false;
}

template<class T>void Q<T>::init(int length) {
  len = length;
  s = 0;
}

template<class T>void Q<T>::print() {
  if (s == 0) cout << "Queue(" << len << ") is EMPTY!\n";
  else {
    QEl* f = s;
    cout << "Queue(" << len << "):\n";

    while (f != 0) {
      cout << f->elem << '\n';
      f = f->next;
    }

    cout << "###\n";
  }
}

template<class T> void Q<T>::add(void) {
  QEl* f = s, *temp = new QEl;

  T i;
  cout << "Input element: \n";
  cin >> i;
  temp->elem = i;
  temp->next = 0;

  if (s != 0) {
    while (f->next != 0)
      f = f->next;

    f->next = temp;
  } else
    s = temp;

  ++n;
}

template<class T>void Q<T>::rem() {
  if (s == 0) cout << "You can't remove any element: Queue is EMPTY!\n";
  else {
    QEl* f = s;
    s = s->next;
    delete f;
    --n;
  }
}






void main() {
  Q<int> q;
  int el;
  char choise;
  bool exit = false;
  bool init = false;

  while (!exit) {
    cout << "1. Init Queue\n";
    cout << "2. Print Queue\n";
    cout << "3. Add Element\n";
    cout << "4. Remove Element\n";
    cout << "5. Exit\n";
    cout << "--> ";
    cin >> choise;

    switch (choise) {
      case '1': {
        cout << "Input lenght of QUEUE\n ";
        int num;
        cin >> num;
        q.init(num);
        init = true;
        break;
      }

      case '2': {
        if (!init) cout << "First you must INIT Queue!\n";
        else
          q.print();

        break;
      }

      case '3': {
        if (!init) cout << "First you must INIT Queue!\n";
        else if (q.full()) cout << "You can't add any element: Queue is FULL!\n";
        else
          q.add();

        break;
      }

      case '4': {
        if (!init) cout << "First you must INIT Queue!\n";
        else
          q.rem();

        break;
      }

      case '5': {
        exit = true;
        break;
      }

      default:
        cout << "WRONG CHOISE!\n";
    } // switch

    cout << '\n';
  } //while
} //main