#ifndef _MYMVT_h_
#define _MYMVT_h_

#include "Shapes.h"
#include "MyMVTBase.h"

class MyMVT : public MyMVTBase<MyMVT, Shape> {
 public:

  Figure figure;

 public:

  void linkPPP( Point*, Point*, Point* );
  void linkPP( Point*, Point* );
  void linkPS( Point*, Segment* );
  void linkSS( Segment*, Segment* );
  //void linkSSX( Segment*,Segment* );

};

#endif