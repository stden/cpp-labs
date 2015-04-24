// g_framework.cpp - обеспечивает связь между операционной системой и классами программы

#define EXTERN


#include "g_model.h"
#include "g_view.h"
#include "g_controller.h"

//using namespace g_framework;


// обработка сообщений операционной системы
//LRESULT WINAPI MsgProc(
//  HWND hwnd,
//  UINT msg,
//WPARAM wparam,
//LPARAM lparam);

//namespace g_framework{
LRESULT WINAPI MsgProc(
  HWND hwnd,
  UINT msg,
  WPARAM wparam,
  LPARAM lparam) {
  if (!handlemsg(hwnd, msg, wparam, lparam)) {
    switch(msg) {
      case WM_DESTROY:
        gameclear(); // удаление игровых данных
        cleard3d(); // удаление данных директа(является методом класс q_view)
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
  return (g_main(hinstance, hprevinstance, lpcmdline, ncmdshow));
}


//}