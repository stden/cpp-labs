// ����: Scene.h
// ������� �����: ����� ����ࠦ���� "������ �⠪�� � ����殬 � ���ਭ�"
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#ifndef _SCENE_H
#define _SCENE_H

#include "GlassR.h"
#include "GlassC.h"
#include "GlList.h"

// ����� ����ࠦ����: ���ਭ� � �⠪�� � ����殬 ����� ���
// �ᯮ������ ������⢥���� ��᫥�������
class CScene : public CGlassCase, public CGlassList {
 public:

  /*
  * ���������
  * leftBottom - ����� ������ �窠, rightTop - �ࠢ�� ������
  */
  CScene(const CCountedPoint& leftBottom, const CCountedPoint& rightTop) :
    CGlassCase(leftBottom, rightTop) {
    cout << "Scene created" << endl;
  }

  /*
  * ��������
  */
  ~CScene() {
    cout << "Scene destroyed" << endl;
  }

  /*
  * ��।������ � �������� ���
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
  * �������� �� ������� �����
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
    } else
      cout << "Glass #" << glassID << " not found!";
  };

  void MovedXdY(double x, double y) {
    cout << "CScene::MovedXdY(" << x << "," << y << ")" << endl;

    for (List.goFirst(); List.hasNext(); List.goNext()) {
      List.getValue()->MovedXdY(x, y);

      if (!GlassInGlassCase(List.getValue())) {
        cout << "Error: Glass outside Glass Case borders" << endl;
        List.getValue()->MovedXdY(-x, -y);
      }
    }
  }

  /*
  * ��室���� �� �⠪�� ����� ���ਭ�?
  */
  int GlassInGlassCase(CGlass* glass) {
    assert(glass != NULL);
    // ����砥� ���न���� "����뢠�饣� ��אַ㣮�쭨��" ��� �⠪���
    double minx, maxx, miny, maxy;
    glass->GetBorders(&minx, &maxx, &miny, &maxy);
    cout << " Glass borders: " <<
         "  minx = " << minx << "  maxx = " << maxx <<
         "  miny = " << miny << "  maxy = " << maxy << endl;
    // �����頥�, ��室���� �� "����뢠�騩 ��אַ㣮�쭨�" ����� ���ਭ�
    return InGlassCase(minx, maxx, miny, maxy);
  };

  /*
  * �뢮� � ��⮪
  */
  friend ostream& operator << (ostream& s, CScene& r) {
    s << endl << "=== SCENE === " << endl
      << (CGlassList&)r << endl
      << (CGlassCase&)r << endl;
    return s;
  }

  void inv() {
  }
};


#endif