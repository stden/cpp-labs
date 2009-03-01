/* g_model.h - ����� �������� ������ ����
Model (Game World � �� ����� ��� DirectX, �� ����� ��� ����������, ����, ����� ��� �������� �������) 
� ��, ��� ������� � ������� �����, � ���������/����������� �����, � ������� unit'�� 
	���� � Map � ������ ������ ����
		���������� (Save) / �������� (Load) �� ����� �����
		��������� ��������� ����� (RandomMap)
	������ � Tile � ���� ������ ����
	Unit � ������� ����� ��� ���� unit'��
		���������� ������ ��������� / �������� ���������. ����������� ����� Load / Save � �����.
			HeroUnit � ��������� Unit, ������� ����� ��������� � ����������
				����������� ������������� ������ Load/Save � �����.
*/
#pragma once
//#ifndef G_MODELH

#include "mapclass.h"

class g_model{
public:
	mapclass worldmap;
	g_model();
	bool init(std::string mapname);
	void clear();
};

g_model::g_model(){


}

bool g_model::init(std::string mapname){
	if (worldmap.loadmap(mapname)) return true;
	return false;
}

void g_model::clear(){

}

//#define G_MODELH 1
//#endif