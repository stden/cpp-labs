// tileclass.h - ����� �������������� �������� ����� �����

class tileclass{
   private:
      char *t_ivalue; // ������ ��� �������� �������� �����, �� �����
      int t_inumlayers; 
      float *t_frotx; // �������� ������� �����
      float *t_fsize; // ������ �����
public:
	   tileclass();
	   ~tileclass();
	   bool unittile();
	   char igetvalue(int layer);
	   void vsetvalue(char value, int layer);
	   float fgetrot(int layer);
	   void vsetrotation(float frot, int layer);
	   float fgetsize(int layer);
	   void vsetsize(float fsize, int layer);
	   void vsetnumlayers(int layers);
	   //void drawtile(float fxpos, float fypos,LPDIRECT3DTEXTURE9* ptexture,int numlayer);
};

tileclass::tileclass(){
   // ������������� ���������� ����������
   t_inumlayers=0;
   t_ivalue=NULL;
   t_frotx=NULL;
   t_fsize=NULL;
}

bool tileclass::unittile(){
/*
	TILEVERTEX tilevertex[]={
        {  0.5f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f},
        { -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f},
        {  0.5f,  0.5f, 0.0f, 0xffffffff, 1.0f, 0.0f},
		{ -0.5f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f}
    };
	LPDIRECT3DVERTEXBUFFER9 tempPointer=NULL;
	// Create the interface object buffer
	if(FAILED(theApp.D3DRenderingDevice()->CreateVertexBuffer( 
		4*sizeof(TILEVERTEX),
		0, 
		D3DFVF_TILEVERTEX,
		D3DPOOL_DEFAULT, 
		&tempPointer,
		NULL))){
		return false;
	}
	else{
        theApp.D3DVertexBuffer(tempPointer);
    }
	VOID* tempBufferPointer;
	// Lock it first.
    if(FAILED(theApp.D3DVertexBuffer()->Lock(
            0,4*sizeof(TILEVERTEX),
            (void**)&tempBufferPointer,0))){
        return false;
    }
    // Copy the vertices into the vertex buffer.
    memcpy(tempBufferPointer,tilevertex,4*sizeof(TILEVERTEX));
    // Now unlock the vertex buffer.
    theApp.D3DVertexBuffer()->Unlock();
  
	return (true);
	*/
	return true;
}

// ��������� ���������� �����
void tileclass::vsetnumlayers(int layers){
   // ����������� ����� ���������� ������ �����
   if(t_ivalue)
   	   delete []t_ivalue;
   if(t_frotx)
   	   delete []t_frotx;
   if(t_fsize)
   	   delete []t_fsize;
   // �������� ������ ��� ������ �����
   t_ivalue=new char[layers];
   memset(t_ivalue, 0, layers*sizeof(int));

   t_frotx=new float[layers];
   memset(t_frotx, 0,layers*sizeof(int));

   t_fsize=new float[layers];
   memset(t_fsize, 0,layers*sizeof(int));

   // ������������� ���������� �����
   t_inumlayers=layers;
}

// ��������� �������� �����
char tileclass::igetvalue(int layer){
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return(-1);
   }
   // ���������� ��������
   return(t_ivalue[layer]);
}

// ��������� �������� �����
void tileclass::vsetvalue(char value, int layer){
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return;
   }
   // ������������� ��������
   t_ivalue[layer]=value;
}

// ��������� ���� ��������
void tileclass::vsetrotation(float frot, int layer){
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return;
   }
   t_frotx[layer]=frot;
}
// ��������� ������� �����
void tileclass::vsetsize(float fsize, int layer){
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return;
   }
   t_fsize[layer]=fsize;
}

// ��������� ���� �������� 
float tileclass::fgetrot(int layer){
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return(-1.0f);
   }
   return(t_frotx[layer]);
}

// ��������� ������� �����
float tileclass::fgetsize(int layer)
{
   // ��������� ������������ ���������� ������ ����
   if(layer>=t_inumlayers){
	   return(-1.0f);
   }
   return(t_fsize[layer]);
}

tileclass::~tileclass(){
   // ����������� ����� �����, ���� �� ��� �������
   if(t_ivalue)
	   delete [] t_ivalue;
   if(t_frotx)
	   delete [] t_frotx;
   if(t_fsize)
	   delete [] t_fsize;
}

/*
void tileclass::drawtile(float fxpos, float fypos,LPDIRECT3DTEXTURE9* ptexture,int numlayer){
	D3DXMATRIX	matworld;
	D3DXMATRIX	matrotation;
	D3DXMATRIX	mattranslation;
	D3DXMATRIX	matscale;
	
	// Set default position,scale,rotation
	D3DXMatrixIdentity(&mattranslation);
	// Scale the tile
	D3DXMatrixScaling(&matscale, fgetsize(numlayer), fgetsize(numlayer), 1.0f);
	D3DXMatrixMultiply(&mattranslation, &mattranslation, &matscale);
	// Rotate the tile
	D3DXMatrixRotationZ(&matrotation, 0.0f);
	D3DXMatrixMultiply(&matworld, &mattranslation, &matrotation);
	
	// Move the tile
	matworld._41 = fxpos-fgetsize(numlayer)/2;	// X-Pos
	matworld._42 = fypos-fgetsize(numlayer)/2;	// Y-Pos
	
	// Set matrix
	theApp.D3DRenderingDevice()->SetTransform(D3DTS_WORLD, &matworld);
	// Set the texture to use
	theApp.D3DRenderingDevice()->SetTexture(0, *ptexture);
	// Use the tile vertex buffer
	theApp.D3DRenderingDevice()->SetStreamSource(0, theApp.D3DVertexBuffer(), 0, sizeof(TILEVERTEX));
	// Use the tile vertex format
	theApp.D3DRenderingDevice()->SetFVF(D3DFVF_TILEVERTEX);
	// Display the quad
	theApp.D3DRenderingDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	// Dereference texture
	theApp.D3DRenderingDevice()->SetTexture(0, NULL);
}
*/