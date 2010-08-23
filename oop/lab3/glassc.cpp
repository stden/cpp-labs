// Файл: GlassC.cpp
// Релизация класса: Glass case - Витрина
// Автор: Волынко Е. ст. гр. 7304
// Дата: 16.05.10, Редакция: 1.0

#include <iostream.h>
#include <conio.h>
#include "GlassC.h"

CGlassCase::CGlassCase(const CCountedPoint& leftBottom, const CCountedPoint& rightTop):
  m_leftBottom(leftBottom), m_rightTop(rightTop)
{
  cout << " Glass Case created" << endl;
}

CGlassCase::~CGlassCase(void)
{
  cout << " Glass Case destroyed" << endl;
}

