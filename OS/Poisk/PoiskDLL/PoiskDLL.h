/*
��� �����������
#include "PoiskDLL.h"
#pragma comment(lib, "PoiskDLL.lib")
*/

#ifdef DLL_NONCLIENT_BUILD
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif


#include <windows.h>
#include <iostream> 
#include <fstream>
#include <string>


class DLL_EXPORT ListP
{
public:
	char    PathP[MAX_PATH];	
	ListP   *next;

	ListP  *add(LPCSTR *PatH, ListP  *fest);	
	ListP*  del( ListP*  delt, ListP* fest);
	static void   WrCons(ListP *lp);
};

class DLL_EXPORT ListF
{
public:
	WIN32_FIND_DATA  WFD;
	HANDLE			 HD;
	char             PathP[MAX_PATH]; 
	ListF			 *next;

	static ListF  *add(WIN32_FIND_DATA *WFD,HANDLE *HD,LPCSTR  *PathP, ListF  *fest);
	static void   WrCons(ListF *lf);
	static ListF*  del( ListF*  delt, ListF* fest); 
};

class DLL_EXPORT ListL
{
public:
	ListF  *spisok;
	ListL  *next;

	static ListL  *add(ListF  *lf, ListL  *fest);
	static void   WrCons(ListL *ll);				
};


class DLL_EXPORT Poisk
{
public:
	Poisk() ;

	bool	inVlos;			// ������ �� ��������
	bool	inTabul;		// ����� �� �������� ��������� ���������
	bool    inIFI;			// �/��� ��� ������ ���� true �� �
	bool    CRC32;
	bool	MD5;
	bool	SHA256;
	bool	BITscan;
	LPCSTR	inParametr;		// �������� ������
	ListP	*inListP;		// ������ ����� ��� ������
	ListF	*inListF;		// ������ ������ ����� ������
	ListL	*inListL;		// ������ �������
	DWORD   inFile;			// ��������� ������ �����
	DWORD   inDerek;		// ��������� ������ ����������
	
	ListL	*PoiskDubl( bool inVlosP,bool inTabulP, bool inIFIP, LPCSTR	inParametrP, ListP	*inListPP, DWORD   inFileP, DWORD   inDerekP);	
	ListL	*PoiskDubl(void);																		

protected:
	void	TreeBP(LPCSTR  LP);	
	void	TreeB (LPCSTR  LP);
	void    OneL  (void)      ;
	void   PP(void);
	void   ListCleen(void);													
	bool   AtribBool(DWORD *WFD,DWORD *par); //�������� ����� �� ��������� ���������!!!!!!!!

};


unsigned pathCRC(char* path1);
void pathSHA256(char* path1, char *out2);
void pathMD5(char* path1, char *out2);
bool pathBIT(char* path1, char *path2);


