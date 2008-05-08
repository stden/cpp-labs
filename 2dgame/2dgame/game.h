// game.h - �����, �������� ��� ���������� MVC � �������������� �� ��������� ������������� � �����������������

#include "g_controller.h"

class game{
public:
	g_model model;
	g_view   view;
	g_controller controller;

	bool init(std::string initwintitle, int w_xsize, int w_ysize, int m_xsize, int m_ysize);
	void clear();
};

bool game::init(std::string initwintitle, int w_xsize, int w_ysize, int m_xsize, int m_ysize){
	w_init_params w_params;
	w_params.wintitle=initwintitle;
	w_params.w_xstart=10;
	w_params.w_ystart=10;
	w_params.w_xsize=w_xsize;
	w_params.w_ysize=w_ysize;

    d3d_init_params d3d_params;
	d3d_params.rd_clearflags=D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER;
	d3d_params.backgroundcolor=D3DCOLOR_XRGB(0,0,0);
    d3d_params.enableAutoDepthStencil=true;
    d3d_params.autoDepthStencilFormat=D3DFMT_D16;
    d3d_params.enableD3DLighting=false;
    d3d_params.cullMode=D3DCULL_NONE;

    if (model.init(m_xsize, m_ysize)&&view.init(w_params, d3d_params, &model)&&controller.init(&model, &view)){
		return true;
	}
	return false;
}

void game::clear(){
	model.clear();
	view.cleard3d();
}
