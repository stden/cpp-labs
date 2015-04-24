#ifndef SHAPES_H__INCLUDED_
#define SHAPES_H__INCLUDED_

class Shape {
 public:

  Shape() : state_(ShapeNormal) {}
  virtual int typeId_get() = 0;
  virtual void draw(CDC&) = 0;

  CPen& getPen();
  void select();
  void activate(bool);
  bool isSelected();
  virtual bool hitTest(CPoint) {
    return false;
  }
  enum {
    ShapeNormal   = 0,
    ShapeSelected   = 1 << 0,
    ShapeHighlighted  = 1 << 1
  };

  int state_;
};

class Point : public Shape {
  friend class MyMVT;

 public:
  Point() : a_(0, 0) {}
  Point(CPoint p) : a_(p) {}

  void draw(CDC&);
  bool hitTest(CPoint);

  enum { typeId = 1 };
  int typeId_get() {
    return typeId;
  }
 private:
  CPoint a_;
};

class Segment : public Shape {
  friend class MyMVT;

 public:
  Segment() : a_(0, 0), b_(0, 0) {}
  Segment(CPoint a, CPoint b) : a_(a), b_(b) {}
  ~Segment() {}

  void draw(CDC&);
  bool hitTest(CPoint);

  enum { typeId = 2 };
  int typeId_get() {
    return typeId;
  }
 private:
  CPoint a_, b_;
};

/* class Triangle : public Shape {
public:
  Triangle() : s1_(), s2_(), s3_() {}
  Triangle(const Triangle &t) : s1_(t.s1_), s2_(t.s2_), s3_(t.s3_) {}
  ~Triangle();

  void draw(CDC&);
  bool hitTest(CPoint p) {
    return s1_.hitTest(p) || s2_.hitTest(p) || s3_.hitTest(p);
  }
private:
  Segment s1_, s2_, s3_;
}; */

class Figure : public Shape {
 public:
  std::vector<CPoint> pts;

  int typeId_get() {
    ASSERT(0);
    return 0;
  }
  void lineAdd( CPoint a, CPoint b );
  void draw( CDC& dc );
};

#endif