// Файл: Scene.cpp
// Релизация класса: Набор изображений "Тонкий стакан с кольцом в витрине"
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "Scene.h"

CScene::CScene(
  const CCountedPoint& leftBottom, const CCountedPoint& rightTop,
  const CCountedPoint& x, const CCountedPoint& y,
  const double& bottom, const double& hBottom, const double& lessSide):
  CGlassCase(leftBottom,rightTop),
  CGlassR(x,y,bottom,hBottom,lessSide)
{
  cout << " Scene created" << endl;
}

void CScene::MoveToPoint(const CCountedPoint& point)
{
  CCountedPoint basePoint = m_bottom.getPoint(0);

  double dx = point.getX() - basePoint.getX();
  double dy = point.getY() - basePoint.getY();

  MovedXdY(dx, dy);
}

void CScene::MovedXdY(double x, double y)
{
  cout << "CScene::MovedXdY(" << x << "," << y << ")" << endl;
  CGlassR::MovedXdY(x,y);
  if(!GlassInGlassCase()){
    cout << "Error: Glass outside Glass Case borders" << endl;
    CGlassR::MovedXdY(-x,-y);
  }
}

CScene::~CScene(void)
{
  cout << " Scene destroyed" << endl;
}

