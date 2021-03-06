/* g_view.h - класс отвечающий за прорисовку графики
View (имеет ссылку на Model и знает всё про DirectX(инициализация и использование), создает инициализирует и рисует окно)
  всё, что связано с отрисовкой в окне с загрузкой текстур,
  границы видимого окна на карте(MiniMap).
  Текстуры
  Есть процедура загрузки текстуры из файла, которая возвращает индекс текстуры в глобальном массиве текстур
  Дополнительные параметры
*/

#include <Windows.h>
#include <mmsystem.h>
#include <E:\\!Студенты\\DXSDK\\Include\\d3dx9.h>
#include <assert.h>
#include <string>
#include <winuser.h>

#pragma once
//#ifndef G_VIEWH
//#include "g_controller.h"
#include "g_model.h"

#include "scrmapclass.h"
#include "minimapclass.h"

#define D3DFVF_TILEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct TILEVERTEX {
  FLOAT x, y, z;
  DWORD color;
  FLOAT tu, tv;
};

// структура, хранящая параметры инициализации окна
struct w_init_params {
  std::string wintitle;
  int w_xstart, w_ystart; // координаты верхнего левого угла окна
  int c_xsize, c_ysize; // размеры клиентской области создаваемого окна
  int w_xsize, w_ysize; // размеры создаваемого окна
};

// структура, хранящая параметры инициализации директа
struct d3d_init_params {
  DWORD rd_clearflags; //
  D3DCOLOR backgroundcolor; // цвет фона
  bool enableAutoDepthStencil; // определение использования буферами глубины директом
  D3DFORMAT autoDepthStencilFormat; // тип буфера глубины
  bool enableD3DLighting; // отключение освещения
  D3DCULL cullMode; // отключение отсечения невидимых частей
};


static const char* GAME_WINDOW_CLASS_NAME = "GAME";

class g_view {
 private:
  std::string mapname;

  // свойства директа
  LPDIRECT3D9 direct3d;
  LPDIRECT3DDEVICE9 d3ddevice; // устройство рендеринга
  LPDIRECT3DVERTEXBUFFER9 vertexbuffer; // глобальный вертексный буффер
  LPDIRECT3DTEXTURE9* ptexture; // указатель на массив текстур

  D3DXMATRIX worldmatrix; // мировая матрица
  D3DXMATRIX viewmatrix; // матрица отображения
  D3DXMATRIX projectionmatrix; // матрица проецирования
  bool worldmatrixd;
  bool viewmatrixd; // изменилась ли матрица отображения
  bool projectionmatrixd;

  int* mchtotexture; // массив ставящий в соответсвтие текстуру символу рисования

  w_init_params winitparams; // структура, хранящая параметры инициализации окна
  d3d_init_params d3dinitparams; // структура, хранящая параметры инициализации директа

  // указатель на модель
  g_model* model;
  // указатель на контроллек
  void* controller;
 public:
  scrmap scr_map; // данные о отображении карты в окне, вся карта не помещается на экран
  minimap m_map; // мини-карта
  int koltextures; // количество загруженных текстур в массиве mchtotexture
 private:
  HRESULT initd3d(HWND hwnd); // инициализация директа

  DWORD rd_clearflags(); // получение флагов устройства рендеринга
  D3DCOLOR backgroundcolor(); // получение цвета фона

  void setd3dpresent_params(D3DPRESENT_PARAMETERS* d3dpp); // инициализируем структуру для создания устройства директа

  LPDIRECT3DDEVICE9 d3drenderingdevice(); // получение указателя на утройство рендеринга
  LPDIRECT3DVERTEXBUFFER9 d3dvertexbuffer(); // получение вертексного буфера
  void d3dvertexbuffer(LPDIRECT3DVERTEXBUFFER9 pvertexbuffer); // установка вертексного буфера

  void      viewmatr(D3DMATRIX newviewmatrix); // установка новой матрицы
  D3DMATRIX viewmatr(); // получение текуцей матрицы отображения
  void      projectionmatr(D3DMATRIX newprojectionmatrix);
  D3DMATRIX projectionmatr();
  void      worldmatr(D3DMATRIX newworldmatrix);
  D3DMATRIX worldmatr();

  int loadtexture(std::string mapname, std::string name); // загрузка текстуры с заданным именем, возвращает индекс текстуры в массиве текстур
  void setmchtotexture(std::string mapname); // загружаем текстуры в массив текстур
  int gettextureindex(char ch);// получение индекса текстуры в глобальном массиве текстур по символу на карте

  bool predd3dinit(); // выполняем необходимую инициализацию до инициализации директа
  bool postd3dinit(HWND hwnd, HINSTANCE hist, WNDPROC msg); // выполняем необходимую инициализацию после инициализации директа

  void drawobject(float x, float y, float xsize, float ysize, int numlayer, LPDIRECT3DTEXTURE9* ptexture);
  bool renderframe(); // рисование кадра
  bool rendermap();
  bool renderminimap();
 public:
  g_view();
  bool init(w_init_params w_params, d3d_init_params d3d_params,
            std::string map_name, g_model* pmodel, void* pcontroller); // инициализация начальными значениями
  void render();
  // вызывается функцией WinMain, создает окно, запускает функцию инициализации директа,
  // запускает цикл обработки сообщений
  int WINAPI g_main(
    HINSTANCE hist,
    HINSTANCE,
    LPSTR,
    INT);
  void cleard3d(); // удаление созданных устройств и переменных директа
  ~g_view();
};
// паблик методы класса view
g_view::g_view() {
  direct3d = NULL;
  d3ddevice = NULL;
  vertexbuffer = NULL;

  memset(&winitparams, 0, sizeof(winitparams));
  memset(&d3dinitparams, 0, sizeof(d3dinitparams));

  viewmatrixd = true;
  projectionmatrixd = true;

  // переделать на динамическое изменение размеров массива текстур!!!
  //ptexture=NULL;
  koltextures = 0;
  ptexture = new LPDIRECT3DTEXTURE9[100];
  mchtotexture = new int[100];
}

bool g_view::init(w_init_params w_params, d3d_init_params d3d_params,
                  std::string map_name, g_model* pmodel, void* pcontroller) {
  winitparams = w_params;
  d3dinitparams = d3d_params;
  mapname = map_name;
  model = pmodel;
  controller = pcontroller;
  scr_map.init(0, 0, w_params.w_xsize / model->worldmap.m_tilesize, w_params.w_ysize / model->worldmap.m_tilesize,
               model->worldmap.m_xsize, model->worldmap.m_ysize);

  return true;
}

void g_view::render() {
  d3drenderingdevice()->Clear(
    0, NULL,
    rd_clearflags(),
    backgroundcolor(),
    1.0f, 0);

  if(SUCCEEDED(d3drenderingdevice()->BeginScene())) {
    // если матрицы изменились...
    if (worldmatrixd) {
      d3drenderingdevice()->SetTransform(D3DTS_WORLD, &worldmatr());
      worldmatrixd = false;
    }

    if (viewmatrixd) {
      //d3drenderingdevice()->SetTransform(D3DTS_VIEW, &viewmatr());
      viewmatrixd = false;
    }

    if (projectionmatrixd) {
      d3drenderingdevice()->SetTransform(D3DTS_PROJECTION, &projectionmatr());
      projectionmatrixd = false;
    }

    renderframe(); // рисование кадра
    d3drenderingdevice()->EndScene();
  }

  d3drenderingdevice()->Present(NULL, NULL, NULL, NULL);
}

LRESULT WINAPI MsgProc(
  HWND hwnd,
  UINT msg,
  WPARAM wparam,
  LPARAM lparam);
void msgwin();
// вызывается функцией WinMain
INT WINAPI g_view::g_main(HINSTANCE hist,
                          HINSTANCE,
                          LPSTR,
                          INT) {
  bool noerr = true;
  RECT rc;
  WNDCLASSEX wc;
  HWND hwnd;

  if (noerr) {
    // регистрация класска окна
    WNDCLASSEX tmpwc = {
      sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
      GAME_WINDOW_CLASS_NAME, NULL
    };
    wc = tmpwc;

    if (RegisterClassEx(&wc) == 0)
      return 0;
  }

  if (noerr) {
    hwnd = CreateWindow(
             GAME_WINDOW_CLASS_NAME,
             winitparams.wintitle.c_str(),
             WS_OVERLAPPEDWINDOW,
             winitparams.w_xstart,
             winitparams.w_ystart,
             winitparams.w_xsize,
             winitparams.w_ysize, // установка левого верхнего угла и размеров окна
             GetDesktopWindow(),
             NULL, wc.hInstance, NULL);
  }

  GetClientRect(hwnd, &rc);
  winitparams.c_xsize = rc.right;
  winitparams.c_ysize = rc.bottom;

  // если окно успешно создано...
  if ((noerr) && (hwnd != NULL)) {
    // инициализация до директа
    if (!predd3dinit())
      noerr = false;
  }

  // если все хорошо, инициализируем директ и вызываем функцию инициализации после директа
  if ((noerr) && (SUCCEEDED(initd3d(hwnd))))
    noerr = postd3dinit(hwnd, wc.hInstance, MsgProc);

  // инициализация игры
  //if (noerr){
  //  noerr=gameinit();
  //}
  // если до сих пор все ок, то отображаем окно и запускаем цикл обработки сообщений
  if (noerr) {
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while(msg.message != WM_QUIT) {
      if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      } else {
        msgwin();
        //controller->updframe(); // обновление фоновой страницы(является методом класса g_controller)
        render(); // ее прорисовка
      }
    }
  }

  UnregisterClass(GAME_WINDOW_CLASS_NAME, wc.hInstance);

  return 0;
}



void g_view::cleard3d() {
  // освобождение вершинного буфера
  if(vertexbuffer != NULL) vertexbuffer->Release();

  // освобождение устройства рендеринга
  if(d3drenderingdevice() != NULL) d3drenderingdevice()->Release();

  // освобождение объекта директа
  if(direct3d != NULL)
    direct3d->Release();
}

g_view::~g_view() {
  delete []ptexture;
  delete []mchtotexture;
}


// приватные методы класса view
// инициализация директа
HRESULT g_view::initd3d(HWND hwnd) {
  HRESULT hr = S_OK;
  D3DPRESENT_PARAMETERS d3dpp;

  // создаем объект директа
  if((direct3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    hr = E_FAIL;
  else
    setd3dpresent_params(&d3dpp);

  // пытаемся создать устройство использующее HAL
  if ((hr == S_OK) && (FAILED(direct3d->CreateDevice(
                                D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
                                D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                &d3dpp, &d3ddevice)))) {
    // если не получилось, пробуем использовать HEL (программную эмуляцию)
    if(FAILED(direct3d->CreateDevice(
                D3DADAPTER_DEFAULT,
                D3DDEVTYPE_REF,
                hwnd,
                D3DCREATE_HARDWARE_VERTEXPROCESSING,
                &d3dpp,
                &d3ddevice)))
      hr = E_FAIL; // HEL
  } // HAL

  if (hr == S_OK) {
    // отключение отсечения невидимых частей
    d3ddevice->SetRenderState(D3DRS_CULLMODE, d3dinitparams.cullMode);
    // отключение освещения директа
    d3ddevice->SetRenderState(D3DRS_LIGHTING, d3dinitparams.enableD3DLighting);
  }

  return hr;
}


inline DWORD g_view::rd_clearflags() {
  return (d3dinitparams.rd_clearflags);
}


inline D3DCOLOR g_view::backgroundcolor() {
  return (d3dinitparams.backgroundcolor);
}

// инициализируем структуру для создания устройства директа
void g_view::setd3dpresent_params(D3DPRESENT_PARAMETERS* d3dpp) {
  ZeroMemory(d3dpp, sizeof(D3DPRESENT_PARAMETERS)); // обнулили для начала
  d3dpp->Windowed = true; // работаем в окне??? (вынести настройку работы в структуру d3d_init_params!!!!)
  d3dpp->SwapEffect = D3DSWAPEFFECT_DISCARD; // переключение видеостраниц, старую страницу не сохраняем
  d3dpp->BackBufferFormat = D3DFMT_UNKNOWN; // формат неактивной видеостраницы

  // определение использования буферами глубины директом
  if (d3dinitparams.enableAutoDepthStencil == true) {
    d3dpp->EnableAutoDepthStencil = TRUE;
    d3dpp->AutoDepthStencilFormat = d3dinitparams.autoDepthStencilFormat;
  }
}



inline LPDIRECT3DDEVICE9 g_view::d3drenderingdevice(void) {
  return (d3ddevice);
}


inline LPDIRECT3DVERTEXBUFFER9 g_view::d3dvertexbuffer(void) {
  return (vertexbuffer);
}


inline void g_view::d3dvertexbuffer(LPDIRECT3DVERTEXBUFFER9 pvertexbuffer) {
  vertexbuffer = pvertexbuffer;
}

inline void g_view::viewmatr(D3DMATRIX newviewmatrix) {
  viewmatrix = newviewmatrix;
  viewmatrixd = true; // отмечаем, что матрица изменилась
}
inline D3DMATRIX g_view::viewmatr() {
  return (viewmatrix);
}

inline void g_view::projectionmatr(D3DMATRIX newprojectionmatrix) {
  projectionmatrix = newprojectionmatrix;
  projectionmatrixd = true;
}
inline D3DMATRIX g_view::projectionmatr() {
  return (projectionmatrix);
}

inline void g_view::worldmatr(D3DMATRIX newworldmatrix) {
  worldmatrix = newworldmatrix;
  worldmatrixd = true;
}
inline D3DMATRIX g_view::worldmatr() {
  return (worldmatrix);
}


bool g_view::predd3dinit() {
  return true;
}
bool g_view::postd3dinit(HWND hwnd, HINSTANCE hist, WNDPROC msg) {
  // будем использовать миникарту
  m_map.init(hwnd, hist, msg, 0, 0, 200, 200);

  // загрузка текстур для катры mapname
  setmchtotexture(mapname);

  // инициализация вертексного буфера для работы с картой
  TILEVERTEX tilevertex[] = {
    {  0.5f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f},
    { -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f},
    {  0.5f,  0.5f, 0.0f, 0xffffffff, 1.0f, 0.0f},
    { -0.5f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f}
  };
  LPDIRECT3DVERTEXBUFFER9 temppointer = NULL;

  if(FAILED(d3drenderingdevice()->CreateVertexBuffer(
              4 * sizeof(TILEVERTEX),
              0,
              D3DFVF_TILEVERTEX,
              D3DPOOL_DEFAULT,
              &temppointer,
              NULL)))
    return false;
  else
    d3dvertexbuffer(temppointer);

  VOID* tempbufferpointer;

  if(FAILED(d3dvertexbuffer()->Lock(
              0, 4 * sizeof(TILEVERTEX),
              (void**)&tempbufferpointer, 0)))
    return false;

  memcpy(tempbufferpointer, tilevertex, 4 * sizeof(TILEVERTEX));
  d3dvertexbuffer()->Unlock();

  D3DXMATRIX  matproj;

  // Установка ортогональной проекции, т.е двухмерная графика в трехменом пространстве
  D3DXMatrixOrthoLH(&matproj, (float)winitparams.w_xsize, (float)winitparams.w_ysize, 0, 1);
  projectionmatr(matproj);
  return true;
}



int g_view::loadtexture(std::string mapname, std::string name) {
  if(!FAILED(D3DXCreateTextureFromFile(d3drenderingdevice(), ("maps\\" + mapname + "_textures\\" + name).c_str(), &ptexture[koltextures]))) {
    koltextures++;
    return koltextures - 1;
  }

  return (-1); // текстуру загрузить не удалось
}
void g_view::setmchtotexture(std::string mapname) {
  std::ifstream f(("maps\\" + mapname + ".set").c_str());
  char ch;
  char texturename[100], buf[100];

  while (!f.eof()) {
    f >> ch; // прочитали символ
    f >> texturename; // прочитали имя текстуры
    mchtotexture[loadtexture(mapname, texturename)] = ch;
    f >> buf; // прочитали комментарий
  }
}

int g_view::gettextureindex(char ch) {
  for (int i = 1; i < koltextures; i++) {
    if (mchtotexture[i] == ch)
      return i;
  }

  return 0;
}


void g_view::drawobject(float x, float y, float xsize, float ysize, int numlayer, LPDIRECT3DTEXTURE9* ptexture) {
  D3DXMATRIX  saveworldmatr = worldmatr();
  D3DXMATRIX  matworld;
  D3DXMATRIX  matrotation;
  D3DXMATRIX  mattranslation;
  D3DXMATRIX  matscale;
  D3DXMatrixIdentity(&mattranslation);
  D3DXMatrixScaling(&matscale, xsize, ysize, 1.0f);
  D3DXMatrixMultiply(&mattranslation, &mattranslation, &matscale);
  D3DXMatrixRotationZ(&matrotation, 0.0f);
  D3DXMatrixMultiply(&matworld, &mattranslation, &matrotation);
  matworld._41 = x; // X-Pos
  matworld._42 = y; // Y-Pos
  d3drenderingdevice()->SetTransform(D3DTS_WORLD, &matworld);
  d3drenderingdevice()->SetTexture(0, *ptexture);
  d3drenderingdevice()->SetStreamSource(0, d3dvertexbuffer(), 0, sizeof(TILEVERTEX));
  d3drenderingdevice()->SetFVF(D3DFVF_TILEVERTEX);
  d3drenderingdevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

  d3drenderingdevice()->SetTexture(0, NULL);
  // восстанавливаем сохраненную мировую матрицу, потому что она изменилась
  worldmatr(saveworldmatr);
}
bool g_view::renderframe() {
  if (m_map.initm)
    renderminimap();

  rendermap();
  return true;
}

bool g_view::rendermap() {
  d3drenderingdevice()->Clear(
    0, NULL,
    rd_clearflags(),
    backgroundcolor(),
    1.0f, 0);
  int m_xsize = model->worldmap.m_xsize;
  int m_ysize = model->worldmap.m_ysize;
  int i_w, j_w; // тайловые экранные координаты
  float x, y;
  float t_size;

  for (int i = scr_map.xstart; i < scr_map.xstart + scr_map.xsize; i++) {
    for (int j = scr_map.ystart; j < scr_map.ystart + scr_map.ysize; j++) {
      i_w = i - scr_map.xstart;
      j_w = j - scr_map.ystart;
      t_size = model->worldmap.m_tile[i][j].fgetsize(0);
      x = -winitparams.w_xsize / 2 + i_w * t_size + t_size / 2; // X-Pos
      y = winitparams.w_ysize / 2 - j_w * t_size - t_size / 2; // Y-Pos
      drawobject(x, y, t_size, t_size, 0, &ptexture[gettextureindex(model->worldmap.m_tile[i][j].igetvalue(0))]);
    }
  }

  return true;
}

bool g_view::renderminimap() {
  RECT rectDest;
  RECT rectSrc;
  int m_xsize = model->worldmap.m_xsize;
  int m_ysize = model->worldmap.m_ysize;
  float x, y;
  float t_xsize, t_ysize;

  d3drenderingdevice()->BeginScene();

  // рисуем на большой карте то, что будет показано на маленькой
  for (int i = 0; i < m_xsize; i++) {
    for (int j = 0; j < m_ysize; j++) {
      t_xsize = (float)winitparams.w_xsize / m_xsize; //model->worldmap.m_tile[i][j].fgetsize(0);
      t_ysize = (float)winitparams.w_ysize / m_ysize; //model->worldmap.m_tile[i][j].fgetsize(0);

      x = -winitparams.w_xsize / 2 + i * t_xsize + t_xsize / 2; // X-Pos
      y = winitparams.w_ysize / 2 - j * t_ysize - t_ysize / 2; // Y-Pos

      drawobject(x, y, t_xsize, t_ysize, 0, &ptexture[gettextureindex(model->worldmap.m_tile[i][j].igetvalue(0))]);

      // рисуем границу того, что видно на экране
      if (i >= scr_map.xstart && i < scr_map.xstart + scr_map.xsize &&
          j >= scr_map.ystart && j < scr_map.ystart + scr_map.ysize)
        if (j == scr_map.ystart || j == scr_map.ystart + scr_map.ysize - 1)
          drawobject(x, y, t_xsize, t_ysize, 0, &ptexture[1]);
        else if (i == scr_map.xstart || i == scr_map.xstart + scr_map.xsize - 1)
          drawobject(x, y, t_xsize, t_ysize, 0, &ptexture[1]);
    }
  }

  // Область окна копию которого делаем
  rectSrc.top = 0;
  rectSrc.bottom = (long)(winitparams.c_ysize);
  rectSrc.left = 0;
  rectSrc.right = (long)(winitparams.c_xsize);

  // Область окна в которое рисуем
  rectDest.top = 0;
  rectDest.bottom = m_map.c_ysize;
  rectDest.left = 0;
  rectDest.right = m_map.c_xsize;
  d3drenderingdevice()->EndScene();
  d3drenderingdevice()->Present( &rectSrc, &rectDest, m_map.hwnd, NULL );
  return true;
}

//#define G_VIEWH 1
//#endif