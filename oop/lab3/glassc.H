// ����: GlassC.h
// ������� �����: Glass case - ���ਭ�
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.1

#ifndef _GLASSC_H
#define _GLASSC_H

#include "CoPoint.h"
#include "CoList.h"

// "���ਭ�" ����� ��� ��אַ㣮�쭨��
class CGlassCase {
 private :
  // ������ ���� � ���孨� �ࠢ� 㣮� ���ਭ�
  CCountedPoint m_leftBottom, m_rightTop;

  double m_Height; // ���� ���ਭ�
  double m_Width; // ��ਭ� ���ਭ�

 public:

  /*
  * ���������
  * leftBottom - ����� ������ �窠, rightTop - �ࠢ�� ������
  */
  CGlassCase(const CCountedPoint& leftBottom, const CCountedPoint& rightTop);

  /*
  * ��������
  */
  ~CGlassCase();

  /*
  * �஢�ઠ, ����頥��� �� ��אַ㣮�쭨� � ������묨 ���न��⠬� ����� ���ਭ�
  */
  int InGlassCase(double minx, double maxx, double miny, double maxy) {
    return (m_leftBottom.getX() <= minx) && (m_leftBottom.getY() <= miny) &&
           (m_rightTop.getX() >= maxx) && (m_rightTop.getY() >= maxy);
  };

  /*
  * ������� ����� ���ਭ�
  */
  double getHeight() {
    return m_rightTop.getY() - m_leftBottom.getY();
    // return m_Height;
  }

  /*
  * ��⠭����� ����� ���ਭ�
  */
  void setHeight(double value) {
    m_Height = value;
    m_rightTop.setY(m_leftBottom.getY() + value);
  }

  /*
  * ������� �ਭ� ���ਭ�
  */
  double getWidth() {
    return m_rightTop.getX() - m_leftBottom.getX();
    // return m_Width;
  }

  /*
  * ��⠭����� �ਭ� ���ਭ�
  */
  void setWidth(double value) {
    m_Width = value;
    m_rightTop.setX(m_leftBottom.getX() + value);
  }

  /*
  * �뢮� ��ࠬ��஢ ���ਭ� � ��⮪
  */
  friend ostream& operator << (ostream& s, CGlassCase& r) {
    s << "  " << "���ਭ�: " << r.m_leftBottom << " " << r.m_rightTop
      << " ���� " << r.getHeight() << "  ��ਭ� " << r.getWidth() << endl;
    return s;
  }
};


#endif