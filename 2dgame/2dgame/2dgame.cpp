#include "g_view.h"
//#include "mapclass.h"
//#include "audioclass.h"

//using namespace g_framework;

#define VERTEX_TYPE_SPECIFIER (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct vertex{
    FLOAT x,y,z;   
    DWORD color;     
	FLOAT tx,ty;
};

bool g_load(){
    game.g_init("test");
    return (true);
}

bool pred3dinit(){
    return (true);
}

bool postd3dinit(){
    return (true);
}

bool gameinit(){

ptexture=new LPDIRECT3DTEXTURE9[1];
	if(FAILED(D3DXCreateTextureFromFile(game.d3drenderingdevice(), "1.bmp", &ptexture[0]))){
	}

	const int nv=4;
    // Initialize three vertices for a triangle
    vertex theVerteces[nv] ={
        {  0.2f, 0.0f, 0.0f, 0xffffffff, 1.0f, 1.0f},
        {  0.0f, 0.0f, 0.0f, 0xffffffff, 0.0f, 1.0f},
        {  0.2f, 0.2f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{  0.0f, 0.2f, 0.0f, 0xffffffff, 0.0f, 0.0f}
    };

    LPDIRECT3DVERTEXBUFFER9 tempPointer=NULL;
    // Create the vertex buffer.
    // If it can't be created...
    if(FAILED(
        game.d3drenderingdevice()->CreateVertexBuffer(
            nv*sizeof(vertex),
            0,VERTEX_TYPE_SPECIFIER,
            D3DPOOL_DEFAULT,&tempPointer,NULL))){
        // The sample can't be run.
        return false;
    }
    else{
    
	game.d3dvertexbuffer(tempPointer);
    }

    //
    // Fill the vertex buffer.
    //
    VOID* tempBufferPointer;
    // Lock it first.
    if(FAILED(
        game.d3dvertexbuffer()->Lock(
            0,nv*sizeof(vertex),
            (void**)&tempBufferPointer,0))){
        return false;
    }
    // Copy the vertices into the vertex buffer.
    memcpy(tempBufferPointer,theVerteces,nv*sizeof(vertex));
    // Now unlock the vertex buffer.
    game.d3dvertexbuffer()->Unlock();
  
 
	return (true);
}


bool gameclear()
{
    return (true);
}
