#ifndef _MyMVTBase_h_
#define _MyMVTBase_h_

#include "XMVTable.h"

template <class Owner, class T>
class MyMVTBase : public XMVTable<Owner, T> {
  // == user stuff ================================
  // Multimethod overrides
 public:

  void linkPPP( Point*, Point*, Point* ) {}
  void linkPP( Point*, Point* ) {}
  void linkPS( Point*, Segment* ) {}
  void linkSS( Segment*, Segment* ) {}

  // == internal stuff ============================
  // Multimethod overhead
 protected:

  struct X_linkPPP : XMethod<Owner, T> {
    enum { argc = 3 };

    int* argList_get( bool fc, int& ac ) {
      ac = argc;
      static int lst[] = { Point::typeId, Point::typeId, Point::typeId };

      if ( fc )
        std::sort( lst, lst + argc );

      return lst;
    }

    void call( Owner& o, T* objs[] ) {
      int i = argc - 1;
      T* args[argc];
      std::copy( objs, objs + argc, args );
      o.linkPPP( (Point*)_arg_pop( args, i, Point::typeId ),
                 (Point*)_arg_pop( args, i, Point::typeId ),
                 (Point*)_arg_pop( args, i, Point::typeId ) );
    }

    const char* dsc_get() {
      return "Make Triangle";
    }
  } x_linkPPP;

  struct X_linkPP : XMethod<Owner, T> {
    enum { argc = 2 };

    int* argList_get( bool fc, int& ac ) {
      ac = argc;
      static int lst[] = { Point::typeId, Point::typeId };

      if ( fc )
        std::sort( lst, lst + argc );

      return lst;
    }

    void call( Owner& o, T* objs[] ) {
      int i = argc - 1;
      T* args[argc];
      std::copy( objs, objs + argc, args );
      o.linkPP( (Point*)_arg_pop( args, i, Point::typeId ),
                (Point*)_arg_pop( args, i, Point::typeId ) );
    }

    const char* dsc_get() {
      return "Make Line";
    }
  } x_linkPP;

  struct X_linkPS : XMethod<Owner, T> {
    enum { argc = 2 };

    int* argList_get( bool fc, int& ac ) {
      ac = argc;
      static int lst[] = { Point::typeId, Segment::typeId };

      if ( fc )
        std::sort( lst, lst + argc );

      return lst;
    }

    void call( Owner& o, T* objs[] ) {
      int i = argc - 1;
      T* args[argc];
      std::copy( objs, objs + argc, args );
      o.linkPS( (Point*)_arg_pop( args, i, Point::typeId ),
                (Segment*)_arg_pop( args, i, Segment::typeId ) );
    }

    const char* dsc_get() {
      return "Make Triangle";
    }
  } x_linkPS;

  struct X_linkSS : XMethod<Owner, T> {
    enum { argc = 2 };

    int* argList_get( bool fc, int& ac ) {
      ac = argc;
      static int lst[] = { Segment::typeId, Segment::typeId };

      if ( fc )
        std::sort( lst, lst + argc );

      return lst;
    }

    void call( Owner& o, T* objs[] ) {
      int i = argc - 1;
      T* args[argc];
      std::copy( objs, objs + argc, args );
      o.linkSS( (Segment*)_arg_pop( args, i, Segment::typeId ),
                (Segment*)_arg_pop( args, i, Segment::typeId ) );
    }

    const char* dsc_get() {
      return "Make Box";
    }
  } x_linkSS;


  // Another overhead
 public:

  enum { _mms_size = 4 };
  Method* _mms[_mms_size];

  MyMVTBase() {
    int i = 0;
    _mms[i++] = &x_linkPPP;
    _mms[i++] = &x_linkPP;
    _mms[i++] = &x_linkPS;
    _mms[i++] = &x_linkSS;
  }
};

#endif // _MyMVTBase_h_