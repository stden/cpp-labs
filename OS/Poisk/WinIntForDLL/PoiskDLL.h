/*
Для подключения
#include "PoiskDLL.h"
#pragma comment(lib, "PoiskDLL.lib")
*/

#ifdef DLL_NONCLIENT_BUILD
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif


#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>


class DLL_EXPORT ListP {
 public:
  char    PathP[MAX_PATH];
  ListP*   next;

  ListP*  add(LPCSTR* PatH, ListP*  fest);
  ListP*  del( ListP*  delt, ListP* fest);
  static void   WrCons(ListP* lp);
};

class DLL_EXPORT ListF {
 public:
  WIN32_FIND_DATA  WFD;
  HANDLE       HD;
  char             PathP[MAX_PATH];
  ListF*      next;

  static ListF*  add(WIN32_FIND_DATA* WFD, HANDLE* HD, LPCSTR*  PathP, ListF*  fest);
  static void   WrCons(ListF* lf);
  static ListF*  del( ListF*  delt, ListF* fest);
};

class DLL_EXPORT ListL {
 public:
  ListF*  spisok;
  ListL*  next;

  static ListL*  add(ListF*  lf, ListL*  fest);
  static void   WrCons(ListL* ll);
};


class DLL_EXPORT Poisk {
 public:
  Poisk() ;

  bool  inVlos;     // искать во вложеных
  bool  inTabul;    // имеет ли значение табуляция параметра
  bool    inIFI;      // и/или при поиске если true то И
  bool    CRC32;
  bool  MD5;
  bool  SHA256;
  bool  BITscan;
  LPCSTR  inParametr;   // параметр поиска
  ListP* inListP;   // список папок для поиска
  ListF* inListF;   // список фаелов после поиска
  ListL* inListL;   // список списков
  DWORD   inFile;     // параметры поиска фаила
  DWORD   inDerek;    // параметры поиска деректории

  ListL* PoiskDubl( bool inVlosP, bool inTabulP, bool inIFIP, LPCSTR inParametrP, ListP*  inListPP, DWORD   inFileP, DWORD   inDerekP);
  ListL* PoiskDubl(void);

 protected:
  void  TreeBP(LPCSTR  LP);
  void  TreeB (LPCSTR  LP);
  void    OneL  (void)      ;
  void   PP(void);
  void   ListCleen(void);
  bool   AtribBool(DWORD* WFD, DWORD* par); //Возможно косяк со смещением проверить!!!!!!!!

};

