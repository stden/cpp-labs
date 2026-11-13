#ifndef _XMVTABLE_h_
#define _XMVTABLE_h_

template <class Owner, class T>
struct XMethod {
  virtual int* argList_get( bool fc, int& sz )  = 0;
  virtual void call( Owner& o, T* args[] )    = 0;
  virtual const char* dsc_get()         = 0;
 public:
  void*  userData;
 public:
  XMethod() : userData(0) {}
};

template <class Owner, class T>
class XMVTable {
 public:

  typedef XMethod<Owner, T>    Method;
  typedef std::vector<T*>     v_args;
  typedef std::vector<Method*>  v_method;

 protected:

  v_args    _args;
  v_method  _methods;

  bool    _firstCall;

 public:

  XMVTable() : _firstCall(true) {}

 public:

  Owner& owner_get() {
    return *static_cast<Owner*>( this );
  }

  void args_set( T* objs[], size_t n ) {
    Owner& o = owner_get();
    _args.assign( objs, objs + n );
    std::sort( _args.begin(), _args.end(), _id_less );
    _methods.clear();

    // find methods
    for ( int i = 0; i < Owner::_mms_size; i++ ) {
      int argc;
      Method* mm = o._mms[i];
      int* arglst = mm->argList_get( _firstCall, argc );

      if ( n == argc ) {
        bool eq = true;

        for ( int j = 0; j < n; j++ ) {
          if ( arglst[j] != _args[j]->typeId_get() ) {
            eq = false;
            break;
          }
        }

        if ( eq )
          _methods.push_back( mm );
      }
    }

    _firstCall = false;
  }

  size_t  method_count() const {
    return _methods.size();
  }
  Method* method_get( int idx ) {
    return _methods[idx];
  }
  void  invoke( Method* m ) {
    m->call( owner_get(), &_args.front() );
  }

 public:

  static bool _id_less( T* a, T* b ) {
    return a->typeId_get() < b->typeId_get();
  }

  static T* _arg_pop( T* args[], int& sz, int typeId ) {
    for ( int i = 0; i <= sz; i++ ) {
      if ( args[i]->typeId_get() == typeId ) {
        T* arg = args[i];
        args[i] = args[(sz--)];
        return arg;
      }
    }

    return NULL; // unreacheable!
  }
};

#endif // _XMVTABLE_h_