// Файл: Main.cpp
// Основная программа
// Автор: Волынко Е. ст. гр. 7304
// Дата: 20.09.2010 Редакция : 1.0

#include <iostream.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include "CoList.h"
#include "Scene.h"
#include "CMsg.h"
#include "CServer.h"
#include "CClient.h"
#include "CSView.h"
#include "GlList.h"
#include "debug.h"
#include "Glass.h"
#include "GlassR.h"
#include "CGlass.h"
#include "CGlassR.h"

// Input value from "cin" with error checking
template <class T>
T input(char *prompt, T min, T max) {
  T value;
  do {
    cout << prompt << " " << min << ".." << max << ": ";
    while (!(cin >> value) && !cin.eof()) {
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

void inputPoint(const char* s, CCountedPoint& p) {
  cout << "  Input " << s << " point:" << endl;
  p.setX(input_double("    Input x:"));
  p.setY(input_double("    Input y:"));
}

int inputClientID(char *prompt) {
  if (CClient::getTotal() < 1) {
    cout << "Register at least one client at first" << endl;
    return 0;
  };
  return input(prompt, 1, CClient::getTotal());
}

CList<CClient*> clients;

CClient* clientByID(int id) {
  for (clients.goFirst();clients.hasNext();clients.goNext())
    if (clients.getValue()->getID() == id)
      return clients.getValue();
  return NULL;
}

const DEBUG_MODE = 1;

void addGlass(CServerView* s, int withRing, int client = 0) {
  int inGlass;
  do {
    double bottomLength, hBottom, lessSide;
    CCountedPoint bottom, top;

    if(DEBUG_MODE){
      bottom = CCountedPoint(1,1);
      top = CCountedPoint(-1,5);
      bottomLength = 5;
      hBottom = 1;
      lessSide = 1;
    } else {
     inputPoint("left bottom", bottom);
      inputPoint("left hight", top);
      bottomLength = input_double("  Input the less foundation length:");
      hBottom = input_double("  Input the less foundation heigth:");
      lessSide = input_double("  Input the less rib length:");
    }
    cout << endl;

    CGlass *glass;
    if (!client) {
      if (withRing)
        glass = new CGlassR(bottom, top, bottomLength, hBottom, lessSide);
      else
        glass = new CGlass(bottom, top, bottomLength, hBottom, lessSide);
    } else {
      if (withRing)
        glass = new CClientGlassR(bottom, top, bottomLength, hBottom, lessSide);
      else
        glass = new CClientGlass(bottom, top, bottomLength, hBottom, lessSide);
      assert( glass->getID() == ((CClient *)glass)->getID() );
      cout << "Glass->getID() " << glass->getID() << endl;
      clients.insert((CClient *)glass);
      cout << "Client->getID() " << ((CClient *)glass)->getID() << endl;
    }

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

  CServerView c(CCountedPoint(-10,-10),CCountedPoint(20,20));
  assert(c.size() == 0);
  // Создаём тестовый стакан
  CGlass gl(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  assert(gl.getID() == 1);
  double minx = MAXDOUBLE, maxx = MINDOUBLE, miny = MAXDOUBLE, maxy = MINDOUBLE;
  gl.GetBorders(&minx, &maxx, &miny, &maxy);
  assert(minx == -1);
  assert(maxx == -1 + 2*2 + 5);
  assert(miny == 1);
  assert(maxy == 5);
  c.insert(&gl);
  assert(c.size() == 1);
  c.Delete(gl.getID());
  assert(c.size() == 0);

  CGlassR glr(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  assert(glr.getID() == 2);
  minx = MAXDOUBLE;
  maxx = MINDOUBLE;
  miny = MAXDOUBLE;
  maxy = MINDOUBLE;
  glr.GetBorders(&minx, &maxx, &miny, &maxy);
  assert(minx == -1);
  assert(maxx == -1 + 2*2 + 5);
  assert(miny == 1);
  assert(maxy == 5);
  c.Delete(glr.getID());

  CClientGlass cgl(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  assert( cgl.getID() == 3 );
  c.insert(&cgl);

  CClientGlassR cglr(CCountedPoint(1, 1), CCountedPoint(-1, 5), 5, 1, 1);
  c.insert(&cglr);

  c.Delete(cgl.getID());
  c.Delete(cglr.getID());

  VERBOSE_OUT = 1;

  cout << endl << endl
       << "-----------------------------------------------" << endl;
  cout << "Programm is creating the view on collection of glasses images" << endl
       << "which can be moved or placed in point" << endl
       << "Client -> Server -> Client system of message exchange is used." << endl
       << "Programmed by: Evgeny Volinko" << endl << endl;

  int menu = 0;

  // Создаём Витрину
  CCountedPoint leftBottom, // Левый нижний угол витрины
    rightTop; // Правый верхний угол витрины
  if(DEBUG_MODE){
    leftBottom = CCountedPoint(-10,-10);
    rightTop = CCountedPoint(20,20);
  } else {
  cout << "=== Create Glass Case ===" << endl;
  // Создаём Витрину
  inputPoint("glass case left bottom", leftBottom);
  int error; // Признак ошибки
  do {
    inputPoint("glass case right top", rightTop);
    error = (rightTop.getX() <= leftBottom.getX()) ||
            (rightTop.getY() <= leftBottom.getY());
    if (error)
      cout << "   Error: wrong coordinates " << endl;
  } while (error);
  }
  CServerView view(leftBottom, rightTop);

  CList<CClient*> clients;
  do {
    cout << "View contains: " << view.size() << endl;
    view.Print();
    cout << endl
         << "=== Main Menu ===" << endl
         << "1. Add Glass to Collection" << endl
         << "2. Add Glass with Ring to Collection" << endl
         << "3. Add Client Glass to Collection" << endl
         << "4. Add Client Glass with Ring to Collection" << endl
         << "5. Delete Glass from Collection" << endl
         << "6. Move Collection and Glass Case" << endl
         << "7. Place Collection and Glass Case into Point" << endl
         << "8. Place Collection into Point" << endl
         << "9. Place Glass Case into Point" << endl
         << "10. Move Collection" << endl
         << "11. Move Glass Case" << endl
         << "12. Print View" << endl
         << "13. Registrate on server" << endl
         << "14. Registrate all clients on server" << endl
         << "15. Unregistrate client from server" << endl
         << "16. Unregistrate all clients from server" << endl
         << "17. Exit" << endl;

    menu = input("Your choice", 1, 17);
    switch (menu) {
      case 1:
        cout << "=== 1. Add Glass to Collection ===" << endl;
        addGlass(&view, 0);
        break;
      case 2:
        cout << "=== 2. Add Glass with Ring to Collection ===" << endl;
        addGlass(&view, 1);
        break;
      case 3:
        cout << "=== 3. Add Client Glass to Collection ===" << endl;
        addGlass(&view, 0, 1);
        break;
      case 4:
        cout << "=== 4. Add Client Glass with Ring to Collection ===" << endl;
        addGlass(&view, 1, 1);
        break;
      case 5: {
        cout << "=== 5. Delete Glass from Collection ===" << endl;
        int id = input_int("Enter number of element : ");
        c.Delete(id);
        view.Delete(id);
        cout << "Element deleted" << endl;
        break;
      }
      case 6: {
        cout << "=== 6. Move Collection and Glass Case ===" << endl;
        double dx = InputFloat("Enter dx");
        double dy = InputFloat("Enter dy");
        view.MovedXdY(dx, dy);
        cout << "Collection are moved by dx = " << dx << ", dy = " << dy << endl;
        break;
      }
      case 7: {
        cout << "=== 7. Place Collection and Glass Case into Point ===" << endl;
        cout << "Enter point" << endl;
        double x = InputFloat("Enter x");
        double y = InputFloat("Enter y");
        view.MoveToPoint(x, y);
        cout << "Collection and Glass Case are placed to Point(" << x << ";" << y << ")" << endl;
        break;
      }
      case 8: {
        cout << "=== 8. Place Collection into Point ===" << endl;
        cout << "Enter Point " << endl;
        double x = InputFloat("Enter x");
        double y = InputFloat("Enter y");

        view.MoveCollectionToPoint(CCountedPoint(x, y));
        cout << "ClassCase is placed to Point(" << x << ";" << y << ")" << endl;
        break;
      }
      case 9: {
        cout << "=== 9. Place Glass Case into Point ===" << endl;
        cout << "Enter Point " << endl;
        double x = InputFloat("Enter x");
        double y = InputFloat("Enter y");

        view.MoveGlassCaseToPoint(CCountedPoint(x, y));
        cout << "ClassCase is placed to Point(" << x << ";" << y << ")" << endl;
        break;
      }
      case 10: {
        cout << "=== 10. Move Collection ===" << endl;
        double dx = InputFloat("Enter dx");
        double dy = InputFloat("Enter dy");
        view.MoveCollection(dx, dy);
        cout << "Collection is moved by dx = " << dx << ", dy = " << dy << endl;
        break;
      }
      case 11: {
        cout << "=== 11. Move Glass Case ===" << endl;
        double dx = InputFloat("Enter dx");
        double dy = InputFloat("Enter dy");
        view.GlassCaseMovedXdY(dx, dy);
        cout << "Glass Case is moved by dx = " << dx << ", dy = " << dy << endl;
        break;
      }
      case 12: {
        cout << "=== 12. Print View ===" << endl;
        view.Print();
        break;
      }
      case 13: {
        cout << "== 13. Registrate on server ==" << endl;
        int id = inputClientID("Enter id of client to register");
        CClient* cl = clientByID(id);
        if (cl == NULL) {
          cout << "Client #" << id << " not exists!" << endl;
          break;
        }
        view.Register(cl);
        assert(view.GetClientByID(id) == cl);
        assert(cl->getServer() != NULL);
        break;
      }
      case 14: {
        cout << "== 14. Registrate all clients on server ==" << endl;
        for (clients.goFirst();clients.hasNext();clients.goNext()) {
          cout << "Try to register: " << clients.getValue()->getID() << endl;
          view.Register(clients.getValue());
          assert(view.GetClientByID(clients.getValue()->getID()) ==
                 clients.getValue());
        };
        break;
      };
      case 15: {
        cout << "== 15. Unregistrate client from server ==" << endl;
        int id = inputClientID("Enter id of client to unregister");
        view.Unregister(id);
        assert(view.GetClientByID(id) == NULL);
        break;
      };
      case 16:
        cout << "== 16. Unregistrate all clients from server ==" << endl;
        view.UnregisterAll();
        break;
      case 17:
        cout << "== 17. Exit ==" << endl;
        break;
      default:
        cout << "menu = " << menu << endl;
        break;
    }
  } while (menu != 17);
}
