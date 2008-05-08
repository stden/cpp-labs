/* g_model.h - класс хранени€ модели игры
Model (Game World Ц не знает про DirectX, не знает про  лавиатуру, ћышь, знает про файловую систему) 
Ц всЄ, что св€зано с игровым миром, с загрузкой/сохранением карты, с логикой unit'ов 
	ѕоле Ц Map Ц массив клеток пол€
		—охранение (Save) / загрузка (Load) из файла карты
		√енератор случайной карты (RandomMap)
	 летка Ц Tile Ц одна клетка пол€
	Unit Ц базовый класс дл€ всех unit'ов
		—охранение своего состо€ни€ / загрузка состо€ни€. ¬иртуальный метод Load / Save в поток.
			HeroUnit Ц наследник Unit, которым можно управл€ть с клавиатуры
				ƒополненные перегруженные методы Load/Save в поток.
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