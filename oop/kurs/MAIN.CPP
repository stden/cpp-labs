// Файл: Main.cpp
// Основная программа
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция : 1.0

#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "CPoint.h"
#include "CoList.h"
#include "Glass.h"
#include "GlassR.h"
#include "Scene.h"
#include "CMsg.h"
#include "CServer.h"
#include "CClient.h"
#include "CSView.h"
#include "GlList.h"
#include "debug.h"

float InputFloat(char *prompt) {
  char buffer[255];
  cout << prompt << ": ";
  while (1) {
    cin >> buffer;
    if (atoi(buffer) == 0 && buffer[0] != '0') {
      cout << "Invalind input, try again : ";
      continue;
    } else
      break;
  }
  return atof(buffer);
}

void check_input(char *temp, int *k, int *flag) {
  if ((atoi(temp) > 0) && (atoi(temp) < 100)) {
    *k = atoi(temp);
    *flag = 0;
  } else {
    cout << "Error input\n" << "try again";
  }
}

double input_double(char *name) {
  double k;
  while (1) {
    cout << name << " ";
    char temp[10];
    cin  >> temp;
    if (sscanf(temp, "%lf", &k))
      return k;
    cout << "Error input\n" << "try again\n";
  }
}

int input_int(char *name) {
  int k;
  while (1) {
    cout << name << " ";
    char temp[10];
    cin  >> temp;
    if (sscanf(temp, "%d", &k))
      return k;
    cout << "Error input\n" << "try again\n";
  }
}

void inputPoint(CCountedPoint& p) {
  p.setX(input_double("    Input x:"));
  p.setY(input_double("    Input y:"));
}


// Input value from "cin" with error checking
template <class T>
T input(char *prompt, T min, T max) {
  T value;
  do {
    cout << prompt << " " << min << ".." << max << ": ";
    while (!(cin >> value)/* && !cin.eof()*/) {
      cerr << "Error: invalid input " << value << ", try again: ";
      cin.clear();
      cin.ignore(cin.rdbuf()->in_avail());
    }
    if (value < min)
      cerr << "Error: Required value >= " << min << endl;
    if (value > max)
      cerr << "Error: Required value <= " << max << endl;
  } while (value < min || value > max);
  return value;
}

void addGlass(CServerView* s, int withRing) {
  int inGlass;
  do {
    double bottomLength, hBottom, lessSide;
    CCountedPoint bottom, top;
    cout << "  Input left bottom point:" << endl;
    inputPoint(bottom);
    cout << "  Input left hight point:" << endl;
    inputPoint(top);

    bottomLength = input_double("  Input the less foundation length:");
    hBottom = input_double("  Input the less foundation heigth:");
    lessSide = input_double("  Input the less rib length:");
    cout << endl;

    CGlass *glass;
    if (withRing)
      glass = new CGlassR(bottom, top, bottomLength, hBottom, lessSide);
    else
      glass = new CGlass(bottom, top, bottomLength, hBottom, lessSide);

    inGlass = s->GlassInGlassCase(glass);
    if (inGlass) {
      s->insert(glass);
    } else {
      cout << "  Glass isn't inside Glass Case" << endl;
      delete glass;
    };
  } while (!inGlass);
  cout << "Glass added!" << endl;
}

void main() {
  clrscr();
  VERBOSE_OUT = 0;
  CGlassList c;
  assert(c.size() == 0);
  // Создаём тестовый стакан
  CGlass* gl = new CGlass(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  double minx = MAXDOUBLE, maxx = MINDOUBLE, miny = MAXDOUBLE, maxy = MINDOUBLE;
  gl->GetBorders(&minx, &maxx, &miny, &maxy);
  assert(minx == -1);
  assert(maxx == -1 + 2*2 + 5);
  assert(miny == 1);
  assert(maxy == 5);
  c.insert(gl);
  assert(c.size() == 1);
  c.Delete(gl->getID());
  assert(c.size() == 0);
  delete gl;
  CGlassR* glr = new CGlassR(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  minx = MAXDOUBLE;
  maxx = MINDOUBLE;
  miny = MAXDOUBLE;
  maxy = MINDOUBLE;
  gl->GetBorders(&minx, &maxx, &miny, &maxy);
  assert(minx == -1);
  assert(maxx == -1 + 2*2 + 5);
  assert(miny == 1);
  assert(maxy == 5);



  VERBOSE_OUT = 1;

  cout << endl << endl
       << "-----------------------------------------------" << endl;
  cout << "Programm is creating the view on collection of schematic images of" << endl
       << "closed piston Glasss which can be moved or placed in point" << endl
       << "Server->Client->Server system of message exchange is used." << endl
       << "Programmed by: Evgeny Volinko" << endl << endl
       << "----------------Press any key to continue or ESC to exit----------------" << endl;

  while (1) {
    int key = getch();
    if (key == 27) return; // Waiting for some action
    else break;
  }

  int menu = 0;
  CServerView *view = NULL;
  //CServer server;
  CList<CClient*> clients;
  do {
    cout << endl
         << "=== Main Menu ===" << endl
         << "1. Create Glass Case" << endl
         << "2. Add Glass to Collection" << endl
         << "3. Add Glass with Ring to Collection" << endl
         << "4. Add Client Closed Glass to Collection" << endl
         << "5. Delete Glass from Collection" << endl
         << "6. Move Collection and Stand" << endl
         << "7. Place Collection and Stand into Point" << endl
         << "8. Place Collection into Point" << endl
         << "9. Place Stand into Point" << endl
         << "10. Move Collection" << endl
         << "11. Move Stand" << endl
         << "12. Move Piston of element" << endl
         << "13. Move every Piston" << endl
         << "14. Print View" << endl
         << "15. Print Collection" << endl
         << "16. Exit" << endl;

    menu = input("Your choice", 1, 16);
    switch (menu) {
      case 1: {
        // Создаём Витрину
        CCountedPoint leftBottom, // Левый нижний угол витрины
        rightTop; // Правый верхний угол витрины
        cout << "  Input glass case left bottom point:" << endl;
        inputPoint(leftBottom);
        int error; // Признак ошибки
        do {
          cout << "  Input glass case right top point:" << endl;
          inputPoint(rightTop);
          error = (rightTop.getX() <= leftBottom.getX()) ||
                  (rightTop.getY() <= leftBottom.getY());
          if (error)
            cout << "   Error: wrong coordinates " << endl;
        } while (error);

        view = new CServerView(leftBottom, rightTop);

        if (view->inv()) {
          // if (c.GetLength() > 0) v->Add(c);
          cout << "View is created" << endl;
        } else cout << "View do not created due to some input errors" << endl;
        break;
      }
      case 2:
        addGlass(view, 0);
        break;
      case 3:
        addGlass(view, 1);
        break;
      case 5: {
        int id = input_int("Enter number of element : ");
        c.Delete(id);
        if (view != NULL)
          view->Delete(id);
        cout << "Element deleted" << endl;
        break;
      }
      case 6: {
        double
        dx = InputFloat("Enter dx"),
             dy = InputFloat("Enter dy");
        if (view != NULL) {
          view->MovedXdY(dx, dy);
          if (view->inv())
            cout << "Collection are moved by dx = " << dx << ", dy = " << dy << endl;
        } else {
          c.MovedXdY(dx, dy);
          cout << "Collection is moved by dx = " << dx << ", dy = " << dy << endl;
        }
        break;
      }
      case 7: {
        double x, y;
        cout << "Enter P1 " << endl;
        x = InputFloat("Enter x :  ");
        y = InputFloat("Enter y :  ");
        if (view != NULL) {
          view->MoveToPoint(x, y);
          if (view->inv()) cout << "Collection and stand are placed to Point(" << x << ";" << y << ")" << endl;
        } else {
          c.MoveToPoint(CCountedPoint(x, y));
          cout << "Collection is placed to Point(" << x << ";" << y << ")" << endl;
        }
        break;
      }

      case 9: {
        cout << "Enter P1 " << endl;
        double
        x = InputFloat("Enter x :  "),
            y = InputFloat("Enter y :  ");

        if (view != NULL) {
          view->MoveGlassCaseToPoint(CCountedPoint(x, y));
          if (view->inv()) cout << "Stand is placed to Point(" << x << ";" << y << ")" << endl;
        } else cout << "View is not created" << endl;

        break;
      }

      case 10: {
        double
        dx = InputFloat("Enter dx :  "),
             dy = InputFloat("Enter dy :  ");

        if (view != NULL) {
          view->MoveCollection(dx, dy);
          if (view->inv()) cout << "Collection is moved by dx = " << dx << ", dy = " << dy << endl;
        } else {
          c.MovedXdY(dx, dy);
          cout << "Collection is moved by dx = " << dx << ", dy = " << dy << endl;
        }
        break;
      }

      case 11: {
        double
        dx = InputFloat("Enter dx"),
             dy = InputFloat("Enter dy");


        if (view != NULL) {
          view->MoveStand(dx, dy);
          if (view->inv()) cout << "Stand is moved by dx = " << dx << ", dy = " << dy << endl;
        } else
          cout << "View is not created" << dy << endl;
        break;
      }

      case 12: {
        double dy, index = 0;
        index = input_int("Index of element");
        dy = InputFloat("Enter dy");
        if (view != NULL) {
          view->GetCollection().getByID(index)->MovedXdY(dy, 0);
          if (view->inv()) cout << "Piston of " << index << "'th element is moved by dy = " << dy << endl;
          else cout << "Piston didn't move" << endl;
        } else {
          c.getByID(index)->MovedXdY(dy, 0);
          cout << "Piston of " << index << "'th element is moved by dy = " << dy << endl;
        }
        break;
      }

      case 14: {
        if (view != NULL)
          view->Print();
        else
          cout << "View is not created" << endl;
        break;
      }

      case 15: {
        if (view != NULL)
          view->Print();
        else
          cout << c << endl;

        break;
      }

      default:
        cout << "menu = " << menu << endl;
        break;
    }
  } while (menu != 16);
}
