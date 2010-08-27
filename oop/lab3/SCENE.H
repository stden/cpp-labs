// Файл: Scene.h
// Объявление класса: Набор изображений "Тонкий стакан с кольцом в витрине"
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0

#ifndef _SCENE_H
#define _SCENE_H

#include "GlassR.h"
#include "GlassC.h"

// Набор изображений: витрина и стакан с кольцом внутри неё
// Используется множественное наследование
class CScene : public CGlassCase, public CGlassR { 
public:

  /*
  * Конструктор
  * leftBottom - левая нижняя точка, rightTop - правая верхняя
  */
  CScene(const CCountedPoint& leftBottom, const CCountedPoint& rightTop,
    const CCountedPoint& x, const CCountedPoint& y,
    const double& bottom, const double& hBottom, const double& lessSide);

  /*
  * Деструктор
  */
  ~CScene();

  /*
  * Передвинуть в заданную точку
  */
  void MoveToPoint(const CCountedPoint& point);

  /*
  * Сдвинить на заданный вектор
  */
  void MovedXdY(double x, double y);

  /*
  * Находится ли стакан внутри витрины?
  */
  int GlassInGlassCase(){
    // Получаем координаты "описывающего прямоугольника" для стакана
    double minx,maxx,miny,maxy;
    GetBorders(&minx,&maxx,&miny,&maxy);
    cout << " Glass borders: " <<
       "  minx = " << minx << "  maxx = " << maxx <<
       "  miny = " << miny << "  maxy = " << maxy << endl;
    // Возвращаем, находятся ли "описывающий прямоугольник" внутри витрины
    return InGlassCase(minx,maxx,miny,maxy);
  };

  /*
  * Вывод в поток
  */
  friend ostream& operator << (ostream& s, CScene& r) {
    s << "  " << "Витрина со стаканом: ";
    s << CGlassCase(r) << endl;
    s << CGlassR(r) << endl;
    return s;
  }

};


#endif