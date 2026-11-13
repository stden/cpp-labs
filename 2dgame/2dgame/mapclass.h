// mapclass.h - класс содержащий информацию о карте мира

#include <fstream>
#pragma once
//#ifndef MAPCLASSH

#include "tileclass.h"

class mapclass {
  //private:
 public:
  tileclass** m_tile;
  int m_xsize;
  int m_ysize;
  int m_kollayers;
  int m_tilesize;
 public:
  bool mapinit();
  bool loadmap(std::string mapname);
  ~mapclass();
};

bool mapclass::mapinit() {
  m_tile = new tileclass*[m_xsize];

  for(int i = 0; i < m_xsize; i++)
    m_tile[i] = new tileclass[m_ysize];

  for(int i = 0; i < m_xsize; i++) {
    for(int j = 0; j < m_ysize; j++) {
      // Выделяем для каждого блока один слой
      m_tile[i][j].vsetnumlayers(m_kollayers);
      // Присваиваем каждому блоку значение 0 в нулевом слое
      m_tile[i][j].vsetvalue('-', 0);
      // Устанавливаем размер блока равным 64 пикселам
      m_tile[i][j].vsetsize((float)m_tilesize, 0);
    }
  }

  return true;
}
bool mapclass::loadmap(std::string mapname) {
  std::ifstream f(("maps\\" + mapname + ".map").c_str());
  char ch;
  f >> m_xsize;
  f >> m_ysize;
  f >> m_tilesize;
  f >> m_kollayers;
  mapinit();

  for (int i = 0; i < m_kollayers; i++) {
    int m_i = 0;
    int m_j = 0;
    f.get(ch);
    f.get(ch);

    while(m_i < m_xsize) {
      f.get(ch);

      if (m_j < m_ysize) {
        m_tile[m_j][m_i].vsetvalue(ch, i);
        m_j++;
      } else {
        m_i++;
        m_j = 0;
      }
    }
  }

  return true;
}

mapclass::~mapclass() {
  //  for(int i=0; i<m_xsize; i++){
  //    delete [](m_tile[i]);
  //  };
  //delete []m_tile;
}

//#define MAPCLASSH 1
//#endif