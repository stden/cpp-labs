/* g_controller - класс изменений состо€ни€ игры и взаимодействи€ с игроком
Controller (имеет ссылки на Model и View, знает про  лавиатуру, про другие событи€ приложени€,
умеет вызывать диалоги ќ— и т.д.)
  обработка событий (нажатий клавиш, движение мыши)
  событи€ в Model (вызов по этим событи€м методов View)
  вызов перерисовки View при resize окна
  при прочих изменени€х
*/
#pragma once
//#ifndef G_CONTROLLERH

#include "g_view.h"

class g_controller {
 private:
  bool x;
  // указатель на модель
  g_model* model;
  // указатель на вью
  g_view* view;
 public:
  bool init(g_model* pmodel, g_view* pview); // инициализаци€
  bool handlemsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam); // обработка сообщений
  bool updframe(); // обновление модели
};

bool g_controller::init(g_model* pmodel, g_view* pview) {
  model = pmodel;
  view = pview;
  x = true;
  return true;
}

bool g_controller::handlemsg(HWND hwnd,
                             UINT msg,
                             WPARAM wparam,
                             LPARAM lparam) {
  //updframe();
  switch(msg) {
    case WM_KEYDOWN:
      switch(wparam) {
        case VK_LEFT:
          // Ќажата стрелка влево.
          view->scr_map.dxstart(-1);
          break;

        case VK_RIGHT:
          // Ќажата стрелка враво.
          view->scr_map.dxstart(1);
          break;

        case VK_UP:
          // Ќажата стрелка вверх.
          view->scr_map.dystart(-1);
          break;

        case VK_DOWN:
          // Ќажата стрелка вниз.
          view->scr_map.dystart(1);
          break;

        // ќбработка других не-буквенных клавиш.
        default:
          break;
      }

    case WM_LBUTTONDOWN:
      if (hwnd == view->m_map.hwnd) {
        if (LOWORD(lparam) / 4 > 2 && LOWORD(lparam) / 4 < view->scr_map.m_xsize - view->scr_map.xsize / 2)view->scr_map.xstart = LOWORD(lparam) / 4 - 3;

        if (HIWORD(lparam) / 4 >= 0 && HIWORD(lparam) / 4 < view->scr_map.m_ysize - view->scr_map.ysize / 2 - 3)view->scr_map.ystart = HIWORD(lparam) / 4;
      };

    case WM_MOUSEMOVE:
      switch(wparam) {
        case MK_LBUTTON:
          if (hwnd == view->m_map.hwnd) {
            if (LOWORD(lparam) / 4 > 2 && LOWORD(lparam) / 4 < view->scr_map.m_xsize - view->scr_map.xsize / 2)view->scr_map.xstart = LOWORD(lparam) / 4 - 3;

            if (HIWORD(lparam) / 4 >= 0 && HIWORD(lparam) / 4 < view->scr_map.m_ysize - view->scr_map.ysize / 2 - 3)view->scr_map.ystart = HIWORD(lparam) / 4;
          };

          break;

        default:
          break;
      };



  }

  return (false);
}

bool g_controller::updframe() {
  if (x) {
    x = false;
    model->worldmap.m_tile[10][10].vsetvalue('#', 0);
  } else {
    x = true;
    model->worldmap.m_tile[10][10].vsetvalue('0', 0);
  }

  return (true);
}

//#define G_CONTROLLERH 1
//#endif