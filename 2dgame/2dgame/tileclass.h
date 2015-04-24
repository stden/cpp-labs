// tileclass.h - ����� �������������� �������� ����� �����
#pragma once
//#ifndef TILECLASSH
class tileclass {
 private:
  char* t_ivalue; // ������ ��� �������� �������� �����, �� �����
  int t_inumlayers;
  float* t_frotx; // �������� ������� �����
  float* t_fsize; // ������ �����
 public:
  tileclass();

  bool unittile();
  void vsetvalue(char value, int layer); // ��������� �������� �����
  void vsetnumlayers(int layers); // ��������� ���������� �����
  void vsetrotation(float frot, int layer); // ��������� ���� �������� (�� ������������)
  void vsetsize(float fsize, int layer); // ��������� ������� �����
  char igetvalue(int layer); // ��������� �������� �����
  float fgetrot(int layer); // ��������� ���� ��������  (�� ������������)
  float fgetsize(int layer); // ��������� ������� �����
  ~tileclass();
};

tileclass::tileclass() {
  // ������������� ���������� ����������
  t_inumlayers = 0;
  t_ivalue = NULL;
  t_frotx = NULL;
  t_fsize = NULL;
}

bool tileclass::unittile() {
  return true;
}

// ��������� �������� �����
void tileclass::vsetvalue(char value, int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return;

  // ������������� ��������
  t_ivalue[layer] = value;
}

// ��������� ���������� �����
void tileclass::vsetnumlayers(int layers) {
  // ����������� ����� ���������� ������ �����
  if(t_ivalue)
    delete []t_ivalue;

  if(t_frotx)
    delete []t_frotx;

  if(t_fsize)
    delete []t_fsize;

  // �������� ������ ��� ������ �����
  t_ivalue = new char[layers];
  memset(t_ivalue, 0, layers * sizeof(int));

  t_frotx = new float[layers];
  memset(t_frotx, 0, layers * sizeof(int));

  t_fsize = new float[layers];
  memset(t_fsize, 0, layers * sizeof(int));

  // ������������� ���������� �����
  t_inumlayers = layers;
}

// ��������� ���� ��������
void tileclass::vsetrotation(float frot, int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return;

  t_frotx[layer] = frot;
}
// ��������� ������� �����
void tileclass::vsetsize(float fsize, int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return;

  t_fsize[layer] = fsize;
}

// ��������� �������� �����
char tileclass::igetvalue(int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return(-1);

  // ���������� ��������
  return(t_ivalue[layer]);
}

// ��������� ���� ��������
float tileclass::fgetrot(int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return(-1.0f);

  return(t_frotx[layer]);
}

// ��������� ������� �����
float tileclass::fgetsize(int layer) {
  // ��������� ������������ ���������� ������ ����
  if(layer >= t_inumlayers)
    return(-1.0f);

  return(t_fsize[layer]);
}

tileclass::~tileclass() {
  // ����������� ����� �����, ���� �� ��� �������
  if(t_ivalue)
    delete [] t_ivalue;

  if(t_frotx)
    delete [] t_frotx;

  if(t_fsize)
    delete [] t_fsize;
}


//#define TILECLASSH 1
//#endif