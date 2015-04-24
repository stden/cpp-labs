// g_framework.cpp - ������������ ����� ����� ������������ �������� � �������� ���������

#define EXTERN


#include "g_model.h"
#include "g_view.h"
#include "g_controller.h"

//using namespace g_framework;


// ��������� ��������� ������������ �������
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
        gameclear(); // �������� ������� ������
        cleard3d(); // �������� ������ �������(�������� ������� ����� q_view)
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