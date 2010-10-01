// Файл: Scene.h
// Объявление класса: Набор изображений "Тонкий стакан с кольцом в витрине"
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _SCENE_H
#define _SCENE_H

#include "GlassR.h"
#include "GlassC.h"
#include "GlList.h"

// Набор изображений: витрина и стакан с кольцом внутри неё
// Используется множественное наследование
class CScene : public CGlassCase, public CGlassList {
public:

  /*
  * Конструктор
  * leftBottom - левая нижняя точка, rightTop - правая верхняя
  */
  CScene(const CCountedPoint& leftBottom, const CCountedPoint& rightTop) :
      CGlassCase(leftBottom, rightTop) {
    cout << "Scene created" << endl;
  }

  /*
  * Деструктор
  */
  ~CScene() {
    cout << "Scene destroyed" << endl;
  }

  /*
  * Передвинуть в заданную точку
  */
  void MoveToPoint(const CCountedPoint& point, int glassID) {
    CCountedPoint basePoint = getByID(glassID)->getBasePoint();

    double dx = point.getX() - basePoint.getX();
    double dy = point.getY() - basePoint.getY();

    MovedXdY(dx, dy, glassID);
  };

  void MoveToPoint(const CCountedPoint& point) {
    CCountedPoint basePoint = getFirst()->getBasePoint();

    double dx = point.getX() - basePoint.getX();
    double dy = point.getY() - basePoint.getY();

    MovedXdY(dx, dy);
  }

  /*
  * Сдвинить на заданный вектор
  */
  void MovedXdY(double x, double y, int glassID) {
    cout << "CScene::MovedXdY(" << x << "," << y << "," << glassID
         << ")" << endl;
    CGlass* glass = getByID(glassID);
    if (glass != NULL) {
      glass->MovedXdY(x, y);
      if (!GlassInGlassCase(glass)) {
        cout << "Error: Glass outside Glass Case borders" << endl;
        glass->MovedXdY(-x, -y);
      }
    } else {
      cout << "Glass #" << glassID << " not found!";
    }
  };

  void MovedXdY(double x, double y) {
    cout << "CScene::MovedXdY(" << x << "," << y << ")" << endl;
    for (List.goFirst();List.hasNext();List.goNext()) {
      List.getValue()->MovedXdY(x, y);
      if (!GlassInGlassCase(List.getValue())) {
        cout << "Error: Glass outside Glass Case borders" << endl;
        List.getValue()->MovedXdY(-x, -y);
      }
    }
  }

  /*
  * Находится ли стакан внутри витрины?
  */
  int GlassInGlassCase(CGlass *glass) {
    assert(glass != NULL);
    // Получаем координаты "описывающего прямоугольника" для стакана
    double minx, maxx, miny, maxy;
    glass->GetBorders(&minx, &maxx, &miny, &maxy);
    cout << " Glass borders: " <<
         "  minx = " << minx << "  maxx = " << maxx <<
         "  miny = " << miny << "  maxy = " << maxy << endl;
    // Возвращаем, находятся ли "описывающий прямоугольник" внутри витрины
    return InGlassCase(minx, maxx, miny, maxy);
  };

  /*
  * Вывод в поток
  */
  friend ostream& operator << (ostream& s, CScene& r) {
    s << endl << "=== SCENE === " << endl
    << (CGlassList&)r << endl
    << (CGlassCase&)r << endl;
    return s;
  }

  void inv(){
  }
};


#endif