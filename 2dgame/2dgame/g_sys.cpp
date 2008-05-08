// g_sys.cpp - ������������ ����� ����� ������������ �������� � �������� ���������

#include "game.h"

game rgame;

LRESULT WINAPI MsgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wparam,
    LPARAM lparam){
    if (!(rgame.controller.handlemsg(hwnd, msg, wparam, lparam))){
        switch(msg){
            case WM_DESTROY:
                rgame.clear(); // �������� ������� ������
                PostQuitMessage(0);
                return 0;
        }
    }
    return DefWindowProc(hwnd,msg,wparam,lparam);
}

INT WINAPI WinMain(
    HINSTANCE hinstance,
    HINSTANCE hprevinstance,
    LPSTR lpcmdline,
    INT ncmdshow){
		// ������ ��������� ���� � ������� ���
		rgame.init("2dgame",640,640,10,10);
		return (rgame.view.g_main(hinstance, hprevinstance, lpcmdline, ncmdshow));
}
