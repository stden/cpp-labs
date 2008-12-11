// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Функции ----------------------------------------------------------------------------
void ClearScreen();

int main(int argc, char* argv[])
{
	BOOL Flag = 1, FCom;
	char Buffer[100], Path1[100], Path2[100], *Pos;
	DWORD SizePath;

	ClearScreen();
	do{
		SizePath = GetCurrentDirectory(100, Path1);
		cout << Path1 << '>';

		cin >> Buffer;
		ClearScreen(); FCom = 0;

		if(memcmp(Buffer, "cread-", 6) == 0){
			memcpy(Path1, Buffer+6, strlen(Buffer+6)+1); FCom = 1;
			if(CreateDirectory(Path1, NULL)) 
				cout << "Directory is created." << endl; else cout << "Failed." << endl;
		}
		if(memcmp(Buffer, "deled-", 6) == 0){
			memcpy(Path1, Buffer+6, strlen(Buffer+6)+1); FCom = 1;
			if(RemoveDirectory(Path1)) 
				cout << "Directory is deleted." << endl; else cout << "Failed." << endl;
		}
		if(memcmp(Buffer, "copyf-", 6) == 0){
			Pos = strchr(Buffer+6, '-');
			if(Pos){
				memcpy(Path1, Buffer+6, (int)Pos-(int)(Buffer+6)); Path1[(int)Pos-(int)(Buffer+6)] = 0;
				memcpy(Path2, Pos+1, strlen(Pos+1)+1); FCom = 1;
				if(CopyFile(Path1, Path2, FALSE)) 
					cout << "File is copyed." << endl; else cout << "Failed." << endl;
			}else FCom = 0;
		}
		if(memcmp(Buffer, "delef-", 6) == 0){
			memcpy(Path1, Buffer+6, strlen(Buffer+6)+1); FCom = 1;
			if(DeleteFile(Path1)) 
				cout << "File is deleted." << endl; else cout << "Failed." << endl;
		}
		if(memcmp(Buffer, "movef-", 6) == 0){
			Pos = strchr(Buffer+6, '-');
			if(Pos){
				memcpy(Path1, Buffer+6, (int)Pos-(int)(Buffer+6)); Path1[(int)Pos-(int)(Buffer+6)] = 0;
				memcpy(Path2, Pos+1, strlen(Pos+1)+1); FCom = 1;
				if(MoveFile(Path1, Path2)) 
					cout << "File is moved." << endl; else cout << "Failed." << endl;
			}else FCom = 0;
		}
		if(memcmp(Buffer, "movefe-", 7) == 0){
			Pos = strchr(Buffer+7, '-');
			if(Pos){
				memcpy(Path1, Buffer+7, (int)Pos-(int)(Buffer+7)); Path1[(int)Pos-(int)(Buffer+7)] = 0;
				memcpy(Path2, Pos+1, strlen(Pos+1)+1); FCom = 1;
				if(MoveFileEx(Path1, Path2, MOVEFILE_REPLACE_EXISTING)) 
					cout << "File is moved." << endl; 
				else{ 
					cout << "Failed."; 
					if(GetLastError()==ERROR_CALL_NOT_IMPLEMENTED) cout << "NT only."; cout << endl;}
			}else FCom = 0;
		}
		if(memcmp(Buffer, "cd-", 3) == 0){
			memcpy(Path1, Buffer+3, strlen(Buffer+3)+1); FCom = 1;
			if(SetCurrentDirectory(Path1)) 
				cout << "Ok." << endl; else cout << "Invalid path." << endl;
		}
		if(memcmp(Buffer, "clr", 3) == 0){ ClearScreen(); FCom = 1;}
		if(memcmp(Buffer, "exit", 4) == 0){ Flag = 0; FCom = 1;}
		if(FCom == 0) cout << "Invalid command." << endl;
	}while(Flag == 1);

	return 0;
}


void ClearScreen()
{
	for(unsigned int i=0;i<25;i++) cout << endl;
}
