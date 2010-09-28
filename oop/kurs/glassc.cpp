// ����: GlassC.cpp
// �������� �����: Glass case - ���ਭ�
// ����: ���뭪� �. ��. ��. 7304
// ���: 16.05.10, �������: 1.0

#include <iostream.h>
#include <conio.h>
#include "GlassC.h"
#include "debug.h"

CGlassCase::CGlassCase(const CCountedPoint& leftBottom, const CCountedPoint& rightTop):
    m_leftBottom(leftBottom), m_rightTop(rightTop),
    m_Height(rightTop.getY() - leftBottom.getY()), // ���᫥��� �����
    m_Width(rightTop.getX() - leftBottom.getX()) { // ���᫥��� �ਭ�
  VERBOSE_OUT && cout << " Glass Case created" << endl;
}

CGlassCase::~CGlassCase(void) {
  VERBOSE_OUT && cout << " Glass Case destroyed" << endl;
}

