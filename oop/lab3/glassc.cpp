// ����: GlassC.cpp
// �������� �����: Glass case - ���ਭ�
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, �������: 1.0

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

