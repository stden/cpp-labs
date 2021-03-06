// ����: �service.cpp
// ��������� ����� �⠪��
// ����: ���뭪� �.
// ���: 16.05.10, �������: 1.0

#include <conio.h>
#include <iostream.h>
#include "GlList.h"

CGlassList :: CGlassList() {
  cout << "GlassList created" << endl;
}

CGlassList :: ~CGlassList() {
  cout << "GlassList deleted" << endl;
}


void CGlassList::MoveToPoint(const CCountedPoint& point) {
  for (List.goFirst(); List.hasNext(); List.goNext())
    List.getValue()->MoveToPoint(point);
}

void CGlassList::MovedXdY(double x, double y) {
  cout << "CGlassList::MovedXdY(" << x << "," << y << ")" << endl;

  for (List.goFirst(); List.hasNext(); List.goNext())
    List.getValue()->MovedXdY(x, y);
}

ostream& operator << (ostream& s, CGlassList& service) {
  s << "  " << "GlassList: " << endl;

  if (service.List.isEmpty()) {
    s << "    List is empty";
    return s;
  }

  for (service.List.goFirst(); service.List.hasNext(); service.List.goNext())
    s << *service.List.getValue();

  return (s);
}
