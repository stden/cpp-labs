//file main.cpp
//main file
//Author: Volinko Evgeniy
//Date: 15.02.2010 version: 1.0

#include <stdlib.h>
#include <stdio.h>
#include "Scene.h"
#include "CoList.h"

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

void addGlass(CScene& s, int withRing) {
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

    inGlass = s.GlassInGlassCase(glass);
    if (inGlass) {
      s.insert(glass);
    } else {
      cout << "  Glass isn't inside Glass Case" << endl;
      delete glass;
    };
  } while (!inGlass);
  cout << "Glass added!" << endl;
}

void main() {
//  CList<int> l;
  //l.size();

  char *temp = new char[5];

  cout << "Project of service" << endl;
  cout << "Author: Volinko Evgeniy" << endl << "Group:7304";
  cout << endl << endl << endl;

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

  CScene scene(leftBottom, rightTop);
  cout << endl << endl;

  int menu, glassID;
  do {
    cout << scene << endl;
    cout << "\n\n===========MAIN MENU===========";
    cout << "\nPress 1 to add glass";
    cout << "\nPress 2 to add glass with ring";
    cout << "\nPress 3 to move glass by dx dy";
    cout << "\nPress 4 to place glass to point";
    cout << "\nPress 5 to move all glasses by dx dy";
    cout << "\nPress 6 to place all glasses to point";
    cout << "\nPress 7 to print";
    cout << "\nPress 0 to exit;\n";
    cout << "===============================\n";
    cin >> menu;

    double dx, dy, x, y;
    switch (menu) {
      case 1:
        addGlass(scene, 0);
        break;
      case 2:
        addGlass(scene, 1);
        break;
      case 3:
        glassID = input_int("Glass id:");
        dx = input_double("Enter dx:"),
             dy = input_double("Enter dy:");
        scene.MovedXdY(dx, dy, glassID);
        break;
      case 4:
        glassID = input_int("Glass id:");
        x = input_double("Enter x:"),
            y = input_double("Enter y:");
        scene.MoveToPoint(CCountedPoint(x, y), glassID);
        break;
      case 5:
        dx = input_double("Enter dx:"),
             dy = input_double("Enter dy:");
        scene.MovedXdY(dx, dy);
        break;
      case 6:
        x = input_double("Enter x:"),
            y = input_double("Enter y:");
        scene.MoveToPoint(CCountedPoint(x, y));
        break;
      case 7:
        cout << scene << endl;
        break;
      case 0:
        break;
      default:
        cout << "Out of menu :)" << endl;
    }
  } while (menu != 0);
  delete[] temp;
}