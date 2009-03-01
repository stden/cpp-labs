// tileclass.h - класс обеспечивающий хранение тайла карты
#pragma once
//#ifndef TILECLASSH
class tileclass{
private:
      char *t_ivalue; // массив для хранения значений блока, по слоям
      int t_inumlayers; 
      float *t_frotx; // заданный поворот блока
      float *t_fsize; // размер блока
public:
	   tileclass();
	   
	   bool unittile();
	   void vsetvalue(char value, int layer); // Установка значения блока
	   void vsetnumlayers(int layers); // Установка количества слоев
	   void vsetrotation(float frot, int layer); // Установка угла поворота (НЕ ИСПОЛЬЗУЕТСЯ)
	   void vsetsize(float fsize, int layer); // Установка размера блока
	   char igetvalue(int layer); // Получение значения блока
	   float fgetrot(int layer); // Получение угла поворота  (НЕ ИСПОЛЬЗУЕТСЯ)
	   float fgetsize(int layer); // Получение размера блока
	   ~tileclass();
};

tileclass::tileclass(){
   // Инициализация внутренних переменных
   t_inumlayers=0;
   t_ivalue=NULL;
   t_frotx=NULL;
   t_fsize=NULL;
}

bool tileclass::unittile(){
	return true;
}

// Установка значения блока
void tileclass::vsetvalue(char value, int layer){
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return;
   }
   // Устанавливаем значение
   t_ivalue[layer]=value;
}

// Установка количества слоев
void tileclass::vsetnumlayers(int layers){
   // Освобождаем ранее выделенные буферы слоев
   if(t_ivalue)
   	   delete []t_ivalue;
   if(t_frotx)
   	   delete []t_frotx;
   if(t_fsize)
   	   delete []t_fsize;
   // Выделяем память для буфера слоев
   t_ivalue=new char[layers];
   memset(t_ivalue, 0, layers*sizeof(int));

   t_frotx=new float[layers];
   memset(t_frotx, 0,layers*sizeof(int));

   t_fsize=new float[layers];
   memset(t_fsize, 0,layers*sizeof(int));

   // Устанавливаем количество слоев
   t_inumlayers=layers;
}

// Установка угла поворота
void tileclass::vsetrotation(float frot, int layer){
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return;
   }
   t_frotx[layer]=frot;
}
// Установка размера блока
void tileclass::vsetsize(float fsize, int layer){
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return;
   }
   t_fsize[layer]=fsize;
}

// Получение значения блока
char tileclass::igetvalue(int layer){
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return(-1);
   }
   // Возвращаем значение
   return(t_ivalue[layer]);
}

// Получение угла поворота 
float tileclass::fgetrot(int layer){
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return(-1.0f);
   }
   return(t_frotx[layer]);
}

// Получение размера блока
float tileclass::fgetsize(int layer)
{
   // Проверяем правильность указанного номера слоя
   if(layer>=t_inumlayers){
	   return(-1.0f);
   }
   return(t_fsize[layer]);
}

tileclass::~tileclass(){
   // Освобождаем буфер слоев, если он был выделен
   if(t_ivalue)
	   delete [] t_ivalue;
   if(t_frotx)
	   delete [] t_frotx;
   if(t_fsize)
	   delete [] t_fsize;
}


//#define TILECLASSH 1
//#endif