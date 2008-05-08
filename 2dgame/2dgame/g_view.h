/* g_view.h - класс отвечающий за прорисовку графики
View (имеет ссылку на Model и знает всё про DirectX(инициализация и использование), создает инициализирует и рисует окно)
	всё, что связано с отрисовкой в окне с загрузкой текстур,
	границы видимого окна на карте(MiniMap).
	Текстуры
	Есть процедура загрузки текстуры из файла, которая возвращает индекс текстуры в глобальном массиве текстур
	Дополнительные параметры
*/

#include <Windows.h>
#include <mmsystem.h>
#include <C:\\DXSDK2\\Include\\d3dx9.h>
#include <assert.h>
#include <string>

#include "g_model.h"

#define D3DFVF_TILEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct TILEVERTEX{
    FLOAT x, y, z;      
    DWORD color;      
    FLOAT tu,tv;	  
};

// структура, хранящая параметры инициализации окна
struct w_init_params{
	std::string wintitle;
	int w_xstart, w_ystart; // координаты верхнего левого угла окна
	int w_xsize, w_ysize; // размеры создаваемого окна
};

// структура, хранящая параметры инициализации директа
struct d3d_init_params{
    DWORD rd_clearflags; // 
    D3DCOLOR backgroundcolor; // цвет фона
    bool enableAutoDepthStencil; // определение использования буферами глубины директом
    D3DFORMAT autoDepthStencilFormat; // тип буфера глубины
    bool enableD3DLighting; // отключение освещения
    D3DCULL cullMode; // отключение отсечения невидимых частей
};
#ifndef G_VIEWH

static const char *GAME_WINDOW_CLASS_NAME="GAME";

class g_view{
private:
	// свойства окна
	//std::string wintitle;
	//int w_xstart, w_ystart; // координаты верхнего левого угла окна
	//int w_xsize, w_ysize; // размеры создаваемого окна

	// свойства директа
	LPDIRECT3D9 direct3d;
	LPDIRECT3DDEVICE9 d3ddevice; // устройство рендеринга
	LPDIRECT3DVERTEXBUFFER9 vertexbuffer; // глобальный вертексный буффер
	LPDIRECT3DTEXTURE9 *ptexture; // указатель на массив текстур
	int *mchtotexture; // массив ставящий в соответсвтие текстуру символу рисования
public:
	int koltextures;
private:
	w_init_params winitparams; // структура, хранящая параметры инициализации окна
	d3d_init_params d3dinitparams; // структура, хранящая параметры инициализации директа

	D3DXMATRIX worldmatrix; // мировая матрица
	D3DXMATRIX viewmatrix; // матрица отображения
	D3DXMATRIX projectionmatrix; // матрица проецирования

	bool viewmatrixd; // изменилась ли матрица отображения
	bool projectionmatrixd;
	bool worldmatrixd;

	// указатель на модель
	g_model *model;
public:
	g_view();
	bool init(w_init_params w_params, d3d_init_params d3d_params, g_model *pmodel); // инициализация начальными значениями
	LPDIRECT3DDEVICE9 d3drenderingdevice(); // получение указателя на утройство рендеринга
	LPDIRECT3DVERTEXBUFFER9 d3dvertexbuffer(); // получение вертексного буфера
	void d3dvertexbuffer(LPDIRECT3DVERTEXBUFFER9 pvertexbuffer); // установка вертексного буфера

	DWORD rd_clearflags(); // получение флагов устройства рендеринга
	D3DCOLOR backgroundcolor(); // получение цвета фона

	void      viewmatr(D3DMATRIX newviewmatrix); // установка новой матрицы
	D3DMATRIX viewmatr(); // получение текуцей матрицы отображения
	void      projectionmatr(D3DMATRIX newprojectionmatrix);
	D3DMATRIX projectionmatr();

	void      worldmatr(D3DMATRIX newworldmatrix);
	D3DMATRIX worldmatr();

 	// вызывается функцией WinMain
	int WINAPI g_main(
		HINSTANCE hist,
		HINSTANCE,
		LPSTR,
		INT);
	
	HRESULT initd3d(HWND hwnd); // инициализация директа
	void setd3dpresent_params(D3DPRESENT_PARAMETERS *d3dpp); // инициализируем структуру для создания устройства директа
	bool predd3dinit(); // выполняем необходимую инициализацию до инициализации директа
	void setmchtotexture(std::string mapname);
	bool postd3dinit(); // выполняем необходимую инициализацию после инициализации директа
	void render();
	bool renderframe(); // рисование кадра
	bool rendermap();
	int  loadtexture(std::string mapname, std::string name); // загрузка текстуры с заданным именем, возвращает индекс текстуры в массиве текстур
	int gettextureindex(char ch);// получение индекса текстуры в глобальном массиве текстур по символу на карте
	void cleard3d(); // удаление созданных устройств и переменных директа
	~g_view();
};

g_view::g_view(){
    direct3d=NULL;
    d3ddevice=NULL;
    vertexbuffer=NULL;
	
	memset(&winitparams, 0, sizeof(winitparams));
	memset(&d3dinitparams, 0, sizeof(d3dinitparams));
    
	viewmatrixd=true;
    projectionmatrixd=true;

	// переделать на динамическое изменение размеров массива текстур!!!
	//ptexture=NULL;
	koltextures=0;
	ptexture=new LPDIRECT3DTEXTURE9[100];
	mchtotexture=new int[100];
}

bool g_view::init(w_init_params w_params, d3d_init_params d3d_params, g_model *pmodel){
    winitparams=w_params;
	d3dinitparams=d3d_params;
	model=pmodel;
    return true;
}

inline LPDIRECT3DDEVICE9 g_view::d3drenderingdevice(void){
    return (d3ddevice);
}

inline LPDIRECT3DVERTEXBUFFER9 g_view::d3dvertexbuffer(void){
    return (vertexbuffer);
}

inline void g_view::d3dvertexbuffer(LPDIRECT3DVERTEXBUFFER9 pvertexbuffer){
    vertexbuffer=pvertexbuffer;
}

inline DWORD g_view::rd_clearflags(){
    return (d3dinitparams.rd_clearflags);
}

inline D3DCOLOR g_view::backgroundcolor(){
	return (d3dinitparams.backgroundcolor);
}

inline void g_view::viewmatr(D3DMATRIX newviewmatrix){
    viewmatrix=newviewmatrix;
    viewmatrixd=true; // отмечаем, что матрица изменилась
}
    
inline D3DMATRIX g_view::viewmatr(){
    return (viewmatrix);
}

inline void g_view::projectionmatr(D3DMATRIX newprojectionmatrix){
    projectionmatrix=newprojectionmatrix;
    projectionmatrixd=true;
}
    
inline D3DMATRIX g_view::projectionmatr(){
    return (projectionmatrix);
}

inline void g_view::worldmatr(D3DMATRIX newworldmatrix){
    worldmatrix=newworldmatrix;
    worldmatrixd=true;
}
    
inline D3DMATRIX g_view::worldmatr(){
    return (worldmatrix);
}

LRESULT WINAPI MsgProc(
    HWND hwnd,
    UINT msg,
    WPARAM wparam,
    LPARAM lparam);
// вызывается функцией WinMain
INT WINAPI g_view::g_main(HINSTANCE hist,
				  HINSTANCE,
				  LPSTR,
				  INT){
		bool noerr=true;
		WNDCLASSEX wc;
		HWND hwnd;
		if (noerr){
			// регистрация класска окна
			WNDCLASSEX tmpwc={ 
				sizeof(WNDCLASSEX),CS_CLASSDC,MsgProc,0L,0L,
				GetModuleHandle(NULL),NULL,NULL,NULL,NULL,
				GAME_WINDOW_CLASS_NAME,NULL 
			};
			wc=tmpwc;
			if (RegisterClassEx(&wc)==0){
				return 0;
			}
		}
		if (noerr){
			hwnd=CreateWindow(
				GAME_WINDOW_CLASS_NAME,
				(LPCSTR)winitparams.wintitle.c_str(),
				WS_OVERLAPPEDWINDOW,
				winitparams.w_xstart,
				winitparams.w_ystart,
				winitparams.w_xsize,
				winitparams.w_ysize, // установка левого верхнего угла и размеров окна 
				GetDesktopWindow(),
				NULL,wc.hInstance,NULL);
		}
		// если окно успешно создано...
		if ((noerr)&&(hwnd!=NULL)){
			// инициализация до директа
			if (!predd3dinit()){
    			noerr=false;
    		}
    	}
		// если все хорошо, инициализируем директ и вызываем функцию инициализации после директа
    	if ((noerr)&&(SUCCEEDED(initd3d(hwnd)))){
    		noerr=postd3dinit();
    	}
		// инициализация игры
		//if (noerr){
    	//	noerr=gameinit(); 
		//}
		// если до сих пор все ок, то отображаем окно и запускаем цикл обработки сообщений
		if (noerr){
			ShowWindow(hwnd,SW_SHOWDEFAULT);
			UpdateWindow(hwnd);
			MSG msg;
			ZeroMemory(&msg,sizeof(msg));
			while(msg.message!=WM_QUIT){
				if(PeekMessage(&msg,NULL,0U,0U,PM_REMOVE)){
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else{
					//controller->updframe(); // обновление фоновой страницы(является методом класса g_controller)
					render(); // ее прорисовка
				}
			}
		}
		UnregisterClass(GAME_WINDOW_CLASS_NAME,wc.hInstance);
		return 0;
}
bool g_view::predd3dinit(){
	return true;
}
void g_view::setmchtotexture(std::string mapname){
	std::ifstream f(("maps\\"+mapname+".set").c_str());
	char ch;
	char texturename[100],buf[100];
	while (!f.eof()){
		f>>ch; // прочитали символ
		f>>texturename; // прочитали имя текстуры
		mchtotexture[loadtexture(mapname,texturename)]=ch;
		f>>buf; // прочитали комментарий
	}
}
bool g_view::postd3dinit(){
	std::string mapname="m1";
	setmchtotexture(mapname);
	model->worldmap.loadmap(mapname);

	TILEVERTEX tilevertex[]={
        {  0.5f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f},
        { -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f},
        {  0.5f,  0.5f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{ -0.5f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f}
    };
	LPDIRECT3DVERTEXBUFFER9 temppointer=NULL;
	if(FAILED(d3drenderingdevice()->CreateVertexBuffer( 
		4*sizeof(TILEVERTEX),
		0, 
		D3DFVF_TILEVERTEX,
		D3DPOOL_DEFAULT, 
		&temppointer,
		NULL))){
		return false;
	}
	else{
        d3dvertexbuffer(temppointer);
    }
	VOID* tempbufferpointer;
	if(FAILED(d3dvertexbuffer()->Lock(
            0,4*sizeof(TILEVERTEX),
            (void**)&tempbufferpointer,0))){
        return false;
    }
    memcpy(tempbufferpointer,tilevertex,4*sizeof(TILEVERTEX));
    d3dvertexbuffer()->Unlock();

	D3DXMATRIX	matproj;
	
	// Установка ортогональной проекции, т.е двухмерная графика в трехменом пространстве
	D3DXMatrixOrthoLH(&matproj, (float)winitparams.w_xsize, (float)winitparams.w_ysize, 0, 1);
	projectionmatr(matproj);
	return true;
}

// инициализация директа
HRESULT g_view::initd3d(HWND hwnd){
    HRESULT hr=S_OK;
    D3DPRESENT_PARAMETERS d3dpp; 

	// создаем объект директа
	if((direct3d=Direct3DCreate9(D3D_SDK_VERSION))==NULL){
        hr=E_FAIL;
    }
    else{
		setd3dpresent_params(&d3dpp);
    }
	// пытаемся создать устройство использующее HAL
    if ((hr==S_OK)&&(FAILED(direct3d->CreateDevice(
							D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hwnd,
							D3DCREATE_HARDWARE_VERTEXPROCESSING,
							&d3dpp,&d3ddevice)))){
			// если не получилось, пробуем использовать HEL (программную эмуляцию)
			if(FAILED(direct3d->CreateDevice(
					D3DADAPTER_DEFAULT,
            		D3DDEVTYPE_REF,
            		hwnd,
            		D3DCREATE_HARDWARE_VERTEXPROCESSING,
            		&d3dpp,
            		&d3ddevice))){
						hr=E_FAIL;
        } // HEL
    } // HAL
    if (hr==S_OK){
		// отключение отсечения невидимых частей
		d3ddevice->SetRenderState(D3DRS_CULLMODE, d3dinitparams.cullMode);
		// отключение освещения директа
		d3ddevice->SetRenderState(D3DRS_LIGHTING, d3dinitparams.enableD3DLighting);
    }
    return hr;
}

// инициализируем структуру для создания устройства директа
void g_view::setd3dpresent_params(D3DPRESENT_PARAMETERS *d3dpp){
    ZeroMemory(d3dpp,sizeof(D3DPRESENT_PARAMETERS)); // обнулили для начала
    d3dpp->Windowed=true; // работаем в окне??? (вынести настройку работы в структуру d3d_init_params!!!!)
    d3dpp->SwapEffect=D3DSWAPEFFECT_DISCARD; // переключение видеостраниц, старую страницу не сохраняем
    d3dpp->BackBufferFormat=D3DFMT_UNKNOWN; // формат неактивной видеостраницы

	// определение использования буферами глубины директом
    if (d3dinitparams.enableAutoDepthStencil==true){
        d3dpp->EnableAutoDepthStencil=TRUE;
        d3dpp->AutoDepthStencilFormat=d3dinitparams.autoDepthStencilFormat;
    }
}

void g_view::render(){
    d3drenderingdevice()->Clear(
        0,NULL,
        rd_clearflags(),
        backgroundcolor(),
        1.0f,0);
    if(SUCCEEDED(d3drenderingdevice()->BeginScene())){
		// если матрицы изменились...
		if (worldmatrixd){
			d3drenderingdevice()->SetTransform(D3DTS_WORLD, &worldmatr());
			worldmatrixd=false;
		}
		if (viewmatrixd){
			//d3drenderingdevice()->SetTransform(D3DTS_VIEW, &viewmatr());
			viewmatrixd=false;
		}
		if (projectionmatrixd){
			d3drenderingdevice()->SetTransform(D3DTS_PROJECTION, &projectionmatr());
			projectionmatrixd=false;
		}

		renderframe(); // рисование кадра
        d3drenderingdevice()->EndScene();
    }
    d3drenderingdevice()->Present(NULL,NULL,NULL,NULL);
}

bool g_view::renderframe(){

	rendermap();

    return true;
}

bool g_view::rendermap(){
	int m_xsize=model->worldmap.getx();
	int m_ysize=model->worldmap.gety();
	
	D3DXMATRIX	saveworldmatr=worldmatr();
	D3DXMATRIX	saveviewmatr=viewmatr();
	D3DXMATRIX	saveprojectionmatr=projectionmatr();

	D3DXMATRIX	matworld;
	D3DXMATRIX	matrotation;
	D3DXMATRIX	mattranslation;
	D3DXMATRIX	matscale;		

	for (int i=0; i<m_xsize; i++){
		for (int j=0; j<m_xsize; j++){
			D3DXMatrixIdentity(&mattranslation);
			D3DXMatrixScaling(&matscale, model->worldmap.m_tile[i][j].fgetsize(0),
				model->worldmap.m_tile[i][j].fgetsize(0), 1.0f);
			D3DXMatrixMultiply(&mattranslation, &mattranslation, &matscale);
			D3DXMatrixRotationZ(&matrotation, 0.0f);
			D3DXMatrixMultiply(&matworld, &mattranslation, &matrotation);

			matworld._41=(float)(-winitparams.w_xsize/2
				+i*model->worldmap.m_tile[i][j].fgetsize(0))
				+model->worldmap.m_tile[i][j].fgetsize(0)/2;	// X-Pos
			
			matworld._42=(float)( winitparams.w_ysize/2
				-j*model->worldmap.m_tile[i][j].fgetsize(0))
				-model->worldmap.m_tile[i][j].fgetsize(0)/2; // Y-Pos

			d3drenderingdevice()->SetTransform(D3DTS_WORLD, &matworld);
			d3drenderingdevice()->SetTexture(0, ptexture[gettextureindex(model->worldmap.m_tile[i][j].igetvalue(0))]);//ptexture[0]);
			d3drenderingdevice()->SetStreamSource(0, d3dvertexbuffer(), 0, sizeof(TILEVERTEX));
			d3drenderingdevice()->SetFVF(D3DFVF_TILEVERTEX);
			d3drenderingdevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			d3drenderingdevice()->SetTexture(0, NULL);
			worldmatr(saveworldmatr);
			viewmatr(saveviewmatr);
			projectionmatr(saveprojectionmatr);
		}
	}
	return true;
}

int g_view::gettextureindex(char ch){
	for (int i=1;i<koltextures;i++){
		if (mchtotexture[i]==ch)
			return i;
	}
	return 0;
}

int g_view::loadtexture(std::string mapname, std::string name){
	if(!FAILED(D3DXCreateTextureFromFile(d3drenderingdevice(), ("maps\\"+mapname+"_textures\\"+name).c_str(), &ptexture[koltextures]))){
		koltextures++;	
		return koltextures-1;
	}
	return (-1); // текстуру загрузить не удалось
}

void g_view::cleard3d(){
	// освобождение вершинного буфера
	if(vertexbuffer!=NULL) vertexbuffer->Release();
	// освобождение устройства рендеринга
    if(d3drenderingdevice()!=NULL) d3drenderingdevice()->Release();
	// освобождение объекта директа
    if(direct3d!=NULL)
        direct3d->Release();
}

g_view::~g_view(){
	delete []ptexture;
	delete []mchtotexture;
}

#define G_VIEWH 1
#endif