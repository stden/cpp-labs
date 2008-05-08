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
#include "mapclass.h"

#ifndef G_MODELH

class g_model{
public:
	mapclass worldmap;

	g_model();
	bool init(int m_xsize, int m_ysize);
	void clear();
};

g_model::g_model(){


}

bool g_model::init(int m_xsize, int m_ysize){
	//if (worldmap.mapinit()) return true;
	return true;
}

void g_model::clear(){

}

#define G_MODELH 1
#endif