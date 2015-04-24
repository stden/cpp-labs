#include "StdAfx.h"
#include "Shapes.h"
#include <math.h>

static CPen penSel(PS_SOLID, 3, RGB(10, 180, 10));
static CPen penHl(PS_SOLID, 3, RGB(255, 25, 255));
static CPen penNorm(PS_SOLID, 3, RGB(100, 100, 255));
static CBrush brush(RGB(255, 255, 255));

bool Shape::isSelected() {
  return (state_ & ShapeSelected);
}

CPen& Shape::getPen() {
  if ( state_ & ShapeHighlighted )
    return penHl;
  else if ( state_ & ShapeSelected )
    return penSel;

  return penNorm;
}

void Shape::select() {
  state_ ^= ShapeSelected;
}

void Shape::activate( bool actv ) {
  if ( actv )
    state_ |= ShapeHighlighted;
  else
    state_ &= ~ShapeHighlighted;
}

void Point::draw(CDC& dc) {
  dc.SelectObject( getPen() );
  //dc.SelectObject( brush );
  dc.Ellipse( a_.x - 3, a_.y - 3, a_.x + 3, a_.y + 3 );
}

bool Point::hitTest( CPoint p ) {
  CRect r( a_.x - 3, a_.y - 3, a_.x + 3, a_.y + 3 );
  return r.PtInRect( p );
}

void Segment::draw(CDC& dc) {
  dc.SelectObject( getPen() );
  dc.MoveTo( a_ );
  dc.LineTo( b_ );
}

bool Segment::hitTest( CPoint p ) {
  CRect rc(a_, b_);
  rc.NormalizeRect();
  rc.InflateRect(5, 5);

  double d = abs((b_.y - a_.y) * p.x + (a_.x - b_.x) * p.y + (b_.x * a_.y - a_.x * b_.y)) /
             sqrt((b_.y - a_.y) * (b_.y - a_.y) + (a_.x - b_.x) * (a_.x - b_.x));

  return rc.PtInRect(p) && d <= 5;
}

void Figure::lineAdd( CPoint a, CPoint b ) {
  pts.push_back( a );
  pts.push_back( b );
}

void Figure::draw( CDC& dc ) {
  dc.SelectObject( penHl );
  int sz = pts.size() / 2;

  for ( int i = 0; i < sz; i++ ) {
    dc.MoveTo( pts[i * 2] );
    dc.LineTo( pts[i * 2 + 1] );
  }
}
