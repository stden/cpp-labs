/* g_controller - ����� ��������� ��������� ���� � �������������� � �������
Controller (����� ������ �� Model � View, ����� ��� ����������, ��� ������ ������� ����������,
����� �������� ������� �� � �.�.)
	��������� ������� (������� ������, �������� ����)
	������� � Model (����� �� ���� �������� ������� View)
	����� ����������� View ��� resize ����
	��� ������ ����������
*/
#include "g_view.h"

#ifndef G_CONTROLLERH

class g_controller{
private:
	// ��������� �� ������
	g_model *model;
	// ��������� �� ���
	g_view *view;
public:
	bool init(g_model *pmodel, g_view *pview); // �������������
	bool handlemsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam); // ��������� ���������
	bool updframe(); // ���������� ������	
};

bool g_controller::init(g_model *pmodel, g_view *pview){
	model=pmodel;
	view=pview;
	return true;
}

bool g_controller::handlemsg(HWND hwnd,
			   				 UINT msg,
			   				 WPARAM wparam,
			   				 LPARAM lparam){
    return (false);
}

bool g_controller::updframe(){
     return (true);
}

#define G_CONTROLLERH 1
#endif