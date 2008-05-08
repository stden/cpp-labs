/* g_controller - класс изменений состояния игры и взаимодействия с игроком
Controller (имеет ссылки на Model и View, знает про Клавиатуру, про другие события приложения,
умеет вызывать диалоги ОС и т.д.)
	обработка событий (нажатий клавиш, движение мыши)
	события в Model (вызов по этим событиям методов View)
	вызов перерисовки View при resize окна
	при прочих изменениях
*/
#include "g_view.h"

#ifndef G_CONTROLLERH

class g_controller{
private:
	// указатель на модель
	g_model *model;
	// указатель на вью
	g_view *view;
public:
	bool init(g_model *pmodel, g_view *pview); // инициализация
	bool handlemsg(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam); // обработка сообщений
	bool updframe(); // обновление модели	
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