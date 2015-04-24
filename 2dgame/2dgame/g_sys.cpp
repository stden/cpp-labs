// g_sys.cpp - обеспечивает связь между операционной системой и классами программы

#include "game.h"

game rgame;

LRESULT WINAPI MsgProc(
  HWND hwnd,
  UINT msg,
  WPARAM wparam,
  LPARAM lparam) {
  if (!(rgame.controller.handlemsg(hwnd, msg, wparam, lparam))) {
    switch(msg) {
      case WM_DESTROY:
        rgame.clear(); // удаление игровых данных
        PostQuitMessage(0);
        return 0;
    }
  }

  return DefWindowProc(hwnd, msg, wparam, lparam);
}

INT WINAPI WinMain(
  HINSTANCE hinstance,
  HINSTANCE hprevinstance,
  LPSTR lpcmdline,
  INT ncmdshow) {
  // задаем параметры окна ,создаем его запускаем игру с картой
  if (rgame.init("2dgame", 800, 800, "m2"))
    return (rgame.view.g_main(hinstance, hprevinstance, lpcmdline, ncmdshow));

  return 0;
}

void msgwin() {
  rgame.controller.updframe();
}
