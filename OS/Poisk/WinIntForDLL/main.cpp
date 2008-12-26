#include "Header.h"


int Horres;
int Vertres;

HWND *HWtest;

HANDLE f1;
CRITICAL_SECTION sec;
DWORD WINAPI fun1(LPVOID v);

BOOL SaveFile(LPSTR pszFileName);

char masschar[4][26];
bool massbool[4];

char masschar2[2][80];
bool massbool2[2]; 


void addwrite(char* buf);
void addwrite2(char* buf);


BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wparam, LPARAM lparam);

HINSTANCE HI;
LPCSTR Name = "CleenMF";
LPSTR Title = "Добавить папку...";//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
char Buffer[MAX_PATH];//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
bool OpenDir;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
Poisk  p;

HWND Ed1, Ed2,B1, B2, StatusBar;

bool ChooseFolder(HWND hwnd, LPSTR lpszTitle, LPSTR lpBuffer);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

  strcpy (masschar[0],"MD5");
  strcpy (masschar[1],"SHA");
  strcpy (masschar[2],"CRC");
  strcpy (masschar[3],"побитовое сравнение");

  p.inListP = NULL;
  p.inVlos = false;
  p.inTabul = false;

  massbool[0] = false;
  massbool[1] = false;
  massbool[2] = false;
  massbool[3] = false;


  strcpy (masschar2[0],"Искать во вложенных папках. ");
  strcpy (masschar2[1]," Учитывать регистр ввода маски для поиска. ");
  massbool2[0] = false;
  massbool2[1] = false;


  HWND HW;
  MSG msg; //для работы с сообщениями

  HI = hInstance; // идентификатор приложения

  HDC hdc=0;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

  WNDCLASS wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.style = NULL; /*CS_HREDRAW | CS_VREDRAW*/  //Не забыть после добавления LayOuta
  wc.lpfnWndProc = (WNDPROC)WndProc;
  wc.hInstance = HI; 
  wc.hIcon = LoadIcon(HI, MAKEINTRESOURCE (IDI_ICON1)  );
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
  wc.lpszClassName = Name;

  RegisterClass(&wc); // Создаем и регистрируем оконный класс
  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  HDC hDCScreen = GetDC(NULL);
  Horres = GetDeviceCaps(hDCScreen, HORZRES);
  Vertres = GetDeviceCaps(hDCScreen, VERTRES);
  ReleaseDC(NULL, hDCScreen);

  Horres = 11*Horres/12;
  Vertres = 11*Vertres/12;

  //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


  HW = CreateWindow(
    Name,
    "KeePClean",
    WS_OVERLAPPEDWINDOW |WS_VISIBLE, // Если хочеш во весь экран добавь сюда WS_MAXIMIZE
    //WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, // Старый Стиль окна
    CW_USEDEFAULT, 0, // Горизонтальная и вертикальная позиции окна
    Horres, Vertres, 
    NULL, // Хендл родительского окна
    NULL, // Хендл меню
    HI, 
    NULL); 

  ShowWindow(HW, SW_SHOW);
  UpdateWindow(HW); 
  // Стандартный цикл обработки сообщений
  while(GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return msg.wParam;
}

// Оконная процедура
LRESULT CALLBACK WndProc(HWND hw, UINT msg, WPARAM wparam, LPARAM lparam)
{
  RECT rcClient;
  HWtest = &hw;

  switch(msg)
  {
  case WM_CREATE:

    CreateWindow("button","Добавить",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,0,0,0,0,hw,(HMENU)ID_BUTTONn3,HI,NULL);
    CreateWindow("button","Обзор...",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,0,0,0,0,hw,(HMENU)ID_BUTTONn2,HI,NULL);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    B1 = CreateWindow("button","Запуск",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,0,0,0,0,hw,(HMENU)ID_BUTTONn1,HI,NULL);
    B2 = CreateWindow("button","Save",WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE,0,0,0,0,hw,(HMENU)ID_BUTTONn4,HI,NULL);
    CreateWindow("listbox", NULL, WS_VISIBLE|WS_CHILD|WS_HSCROLL|WS_VSCROLL |WS_BORDER,0,0,0,0, hw, (HMENU)ID_LISTBOX1, HI, NULL);
    CreateWindow("button","Параметры", BS_GROUPBOX|WS_CHILD|WS_VISIBLE|DS_3DLOOK,0,0,0,0,hw,(HMENU)ID_GROUPBOX1, HI, NULL);
    CreateWindow("button","Задание", BS_GROUPBOX|WS_CHILD|WS_VISIBLE|DS_3DLOOK,0,0,0,0,hw,(HMENU)ID_GROUPBOX2, HI, NULL);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    CreateWindow("button","Вложенные папки", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT, 0 ,0,0,0 , hw, (HMENU)ID_CHECKBOX1, HI, NULL);
    CreateWindow("button","Учитывать регистр", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,0,0,0,0, hw, (HMENU)ID_CHECKBOX2, HI, NULL);
    CreateWindow("button","Проверять CRC", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,0,0,0,0, hw, (HMENU)ID_CHECKBOX3, HI, NULL);
    CreateWindow("button","Проверять SHA", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT , 0,0,0,0, hw, (HMENU)ID_CHECKBOX4, HI, NULL);
    CreateWindow("button","Проверять MD5", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT , 0,0,0,0, hw, (HMENU)ID_CHECKBOX5, HI, NULL);
    CreateWindow("button","Проверять bit", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT,0,0,0,0, hw, (HMENU)ID_CHECKBOX6, HI, NULL);

    SendMessage(GetDlgItem(hw,ID_LISTBOX1), LB_SETHORIZONTALEXTENT, 1600, 0); // WS_HSCROLL -- НЕ работает

    Ed1 = CreateWindowEx(NULL,"EDIT", "c:\\test\\", WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 0,0,0,0, hw, (HMENU)ID_EDIT1, HI, NULL);
    Ed2 = CreateWindow ("EDIT", "*.*", WS_CHILD|WS_VISIBLE|WS_BORDER|WS_TABSTOP|ES_AUTOHSCROLL, 0,0,0,0 , hw, (HMENU)ID_EDIT2, HI, NULL);
    StatusBar = CreateWindow ("STATIC", "", WS_CHILD | WS_VISIBLE, 0, 0, 0,0, hw, (HMENU)ID_STATUSBAR1, HI, NULL);
    CreateWindow ("STATIC", "Искать в:", WS_CHILD | WS_VISIBLE, 0,0,0,0, hw, (HMENU)ID_STATIC1 , HI, NULL);
    CreateWindow ("STATIC", "Маска:", WS_CHILD | WS_VISIBLE, 0,0,0,0, hw,(HMENU)ID_STATIC2, HI, NULL);

    CreateWindow ("STATIC", "", WS_CHILD | WS_VISIBLE, 0,0,0,0, hw, (HMENU)ID_STATIC3 , HI, NULL);
    CreateWindow ("STATIC", "", WS_CHILD | WS_VISIBLE, 0,0,0,0, hw,(HMENU)ID_STATIC4, HI, NULL);

    return(0);

  case WM_COMMAND:
    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_BUTTONn1))
    {

      SetDlgItemText(hw, ID_STATUSBAR1, "");
      p.inListF = NULL;
      p.inListL = NULL;

      char str1[MAX_PATH];
      char str2[MAX_PATH];
      GetWindowText(Ed1,str1,MAX_PATH);  
      GetWindowText(Ed2,str2,MAX_PATH);

      LPCSTR tepmDel;
      tepmDel = str1;

      p.inListP = p.inListP->add(&tepmDel,p.inListP);
      p.inParametr = str2;

      DWORD  IDT;

      InitializeCriticalSection(&sec); 

      EnableWindow(B1, false);
      EnableWindow(GetDlgItem(hw, ID_BUTTONn2), false);
      EnableWindow(B2, false);
      EnableWindow(GetDlgItem(hw, ID_BUTTONn3), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX1), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX2), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX3), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX4), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX5), false);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX6), false);
      EnableWindow(GetDlgItem(Ed1, ID_EDIT1), false);
      EnableWindow(GetDlgItem(hw, ID_EDIT2), false);

      LPVOID w = NULL;

      f1 = CreateThread(NULL,0/*раз ст*/, /*(LPTHREAD_START_ROUTINE)*/  fun1,w,/* CREATE_SUSPENDED*/0, &IDT ); 



      p.PoiskDubl();
      ListL *temp = NULL;
      temp = p.inListL;
      char tc[MAX_PATH + MAX_PATH];
      ListF *temp2 = NULL;

      SendDlgItemMessage(hw, ID_LISTBOX1, LB_RESETCONTENT, 0, NULL);

      int coldubl = 0;

      while(temp)
      {
        SendDlgItemMessage(hw, ID_LISTBOX1, LB_ADDSTRING, 0, (LPARAM)"****************************************************");
        coldubl++;
        temp2 = temp->spisok;
        while(temp2)
        {
          strcpy(tc, temp2->PathP);
          strcat(tc, "     ");
          strcat(tc, temp2->WFD.cFileName);
          SendDlgItemMessage(hw, ID_LISTBOX1, LB_ADDSTRING, 0, (LPARAM)tc);
          temp2 = temp2->next;
        };		

        temp = temp->next;
      };

      p.inListP = NULL;

      TerminateThread(f1,0);					 
      CloseHandle(f1);
      DeleteCriticalSection(&sec);

      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      EnableWindow(B1, true);
      EnableWindow(GetDlgItem(hw, ID_BUTTONn2), true);
      if (p.inListL)
        EnableWindow(B2, true);
      EnableWindow(GetDlgItem(hw, ID_BUTTONn3), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX1), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX2), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX3), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX4), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX5), true);
      EnableWindow(GetDlgItem(hw, ID_CHECKBOX6), true);
      EnableWindow(GetDlgItem(hw, ID_EDIT1), true);
      EnableWindow(GetDlgItem(hw, ID_EDIT2), true);
      if (!p.inListL)
        SetDlgItemText(hw, ID_STATUSBAR1, "Дубликатов не найдено");
      else
      {
        if (coldubl == 1)
          strcpy(tc,"Найдена одна группа дубликатов");
        else
          wsprintf(tc, "Найдены %d группы дубликатов",coldubl);
        SetDlgItemText(hw, ID_STATUSBAR1,tc);
      }
    }

    if ((HIWORD(wparam)== BN_CLICKED) &&(LOWORD(wparam) == ID_BUTTONn2))//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    {//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      OpenDir=ChooseFolder(hw,Title,Buffer);
      if (OpenDir)
        SetDlgItemText(hw, ID_EDIT1, Buffer);
      //MessageBox(NULL,Buffer,Buffer,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    }//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!


    if ((HIWORD(wparam)== BN_CLICKED) &&(LOWORD(wparam) == ID_BUTTONn4))//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    {
      if (p.inListL)
      {
        //!!!!!!!!!!!!!!!!!!!!!!!!
        OPENFILENAME ofn;
        char szFileName[MAX_PATH];

        ZeroMemory(&ofn, sizeof(ofn));
        strcpy (szFileName,"");

        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = hw;
        ofn.lpstrFilter = "Текстовый файл (*.txt)\0*.txt\0Все файлы \0*.*\0\0";
        ofn.lpstrFile = szFileName;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrDefExt = "txt";
        ofn.Flags = OFN_EXPLORER|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
        if(GetSaveFileName(&ofn))
          if(!SaveFile(szFileName))
            MessageBox(NULL, "Ошибка при сохранении.", "Error", MB_OK | MB_ICONEXCLAMATION);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


      }
      else
        EnableWindow(B2, false);


    }


    if ((HIWORD(wparam)== BN_CLICKED) &&(LOWORD(wparam) == ID_BUTTONn3))
    {
      if (!p.inListP)
        SendDlgItemMessage(hw, ID_LISTBOX1, LB_RESETCONTENT, 0, NULL);

      char str1[MAX_PATH];
      GetWindowText(Ed1,str1,MAX_PATH);  
      LPCSTR tepmDel;
      tepmDel = str1;
      p.inListP = p.inListP->add(&tepmDel,p.inListP);
      SendDlgItemMessage(hw, ID_LISTBOX1, LB_ADDSTRING, 0, (LPARAM)p.inListP->PathP);


    }

    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX1)) 
    {
      char buf[MAX_PATH];
      if ( p.inVlos)
      {

        massbool2[0] = false;
        addwrite2(buf);
        SetDlgItemText(hw, ID_STATIC3, buf);
        p.inVlos = false;
      }
      else
      {
        massbool2[0] = true;
        addwrite2(buf);
        SetDlgItemText(hw, ID_STATIC3, buf);
        p.inVlos = true;
      }
    }



    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX2)) 
    {
      char buf[MAX_PATH];
      if ( p.inTabul)
      {

        massbool2[1] = false;
        addwrite2(buf);
        SetDlgItemText(hw, ID_STATIC3, buf);
        p.inTabul = false;
      }
      else
      {
        massbool2[1] = true;
        addwrite2(buf);
        SetDlgItemText(hw, ID_STATIC3, buf);
        p.inTabul = true;
      }
    }
    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX3)) 
    {
      char buf[MAX_PATH];
      if ( p.CRC32)
      {

        massbool[2] = false;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.CRC32 = false;
      }
      else
      {
        massbool[2] = true;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.CRC32 = true;
      }
    }

    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX4)) 
    {
      char buf[MAX_PATH];
      if ( p.SHA256)
      {

        massbool[1] = false;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.SHA256 = false;
      }
      else
      {
        massbool[1] = true;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.SHA256 = true;
      }
    }
    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX5)) 
    {
      char buf[MAX_PATH];
      if ( p.MD5)
      {

        massbool[0] = false;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.MD5 = false;
      }
      else
      {
        massbool[0] = true;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.MD5 = true;
      }
    }

    if ((HIWORD(wparam)==0) && (LOWORD(wparam) == ID_CHECKBOX6)) 
    {
      char buf[MAX_PATH];
      if ( p.BITscan)
      {

        massbool[3] = false;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.BITscan = false;
      }
      else
      {
        massbool[3] = true;
        addwrite(buf);
        SetDlgItemText(hw, ID_STATIC4, buf);
        p.BITscan = true;
      }
    }

    return 0;

  case WM_SIZE:

    GetClientRect(hw, &rcClient);
    EnumChildWindows(hw, EnumChildProc, (LPARAM) &rcClient);
    return 0;


  case WM_DESTROY:
    PostQuitMessage(0);
    return(0);
  }
  return DefWindowProc(hw, msg, wparam, lparam);
}


BOOL CALLBACK EnumChildProc(HWND hwndChild, LPARAM lParam)
{
  LPRECT rcParent;
  int i1 = 0, i2 = 0, i3 = 0, i4 = 0, idChild;


  idChild = GetWindowLong(hwndChild, GWL_ID);
  rcParent = (LPRECT) lParam;

  Horres  = rcParent->right - rcParent->left;
  Vertres = rcParent->bottom - rcParent->top;

  switch (idChild)
  {
  case ID_BUTTONn4:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/((280+100)/2));
      i2 = Vertres-Vertres*10/12+Vertres*0.8-Vertres/(800/70);													 
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/50);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

      if (!p.inListL)
        EnableWindow(B2, false);
      else
        EnableWindow(B2, true);

      break;
    }
  case ID_BUTTONn1:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/((280+100)/2));
      i2 = Vertres-Vertres*11/12+Vertres*0.8-Vertres/(800/70);													 
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/50);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }

  case ID_BUTTONn2:
    {
      i1 = Horres/2-Horres/(1280/150);
      i2 = (Vertres-Vertres*11/12-Vertres/(800/25))/2	;
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/25);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }

  case ID_BUTTONn3:
    {
      i1 = Horres/2-Horres/(1280/30);
      i2 = (Vertres-Vertres*11/12-Vertres/(800/25))/2	;
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/25);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_LISTBOX1:
    {
      i1 = Horres*1/40;
      i2 = Vertres-Vertres*11/12;
      i3 = Horres*0.7;
      i4 = Vertres*0.7;
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_CHECKBOX1:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*10/12;//6
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_CHECKBOX6:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*5/12;
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }

  case ID_CHECKBOX2:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*9/12;
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_CHECKBOX3:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*8/12;
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_CHECKBOX4:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*7/12 ;//9
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_CHECKBOX5:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/250)-Horres/(1280/20);
      i2 = Vertres-Vertres*6/12;//10
      i3 = Horres/(1280/240);
      i4 = Vertres/(800/16);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_EDIT1:
    {
      i1 = Horres*1/40+Horres/(1280/100);
      i2 = (Vertres-Vertres*11/12-Vertres/(800/20))/2;
      i3 = Horres/(1280/300); 
      i4 = Vertres/(800/20);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_EDIT2:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/300);
      i2 = (Vertres-Vertres*11/12-Vertres/(800/20))/2;
      i3 =  Horres/(1280/300);
      i4 =  Vertres/(800/20);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_SETFONT1://!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    {//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      HFONT hFont = CreateFont(-11,0,0,0,0,TRUE,0,0,DEFAULT_CHARSET,0,0,0,0,"Tahoma");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);  //!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    }//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  case ID_GROUPBOX1:
    {
      i1 = Horres-(Horres*1/40)-(Horres/(1280/250))-Horres/(1280/40);
      i2 = Vertres-Vertres*11/12;
      i3 = Horres/(1280/250)+Horres/(1280/40);
      i4 = Vertres-Vertres/2.5;//2
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_GROUPBOX2:
    {
      i1 = Horres*1/40;
      i2 = Vertres-Vertres*2.5/12;
      i3 = Horres*0.7;
      i4 = Vertres/6;
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_STATUSBAR1:
    {
      i1 = 0;
      i2 = Vertres-Vertres/(800/25);
      i3 = Horres;
      i4 = Vertres/(800/20);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_STATIC1:
    {
      i1 = Horres*1/40;
      i2 = (Vertres-Vertres*11/12-Vertres/(800/20))/2;
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/20);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_STATIC2:
    {
      i1 = Horres-Horres*1/40-Horres/(1280/300)-Horres/(1280/100);
      i2 = (Vertres-Vertres*11/12-Vertres/(800/20))/2;
      i3 = Horres/(1280/100);
      i4 = Vertres/(800/20);
      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_STATIC3:
    {
      i1 = Horres*1/40+Horres/(1280/10);
      i2 = Vertres-Vertres*2.5/12+Vertres/(800/25);

      i3 = Horres*0.7-(Horres/(1280/10))*2;
      i4 = Vertres/(800/20);

      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }
  case ID_STATIC4:
    {
      i1 = Horres*1/40+Horres/(1280/10);
      i2 = Vertres-Vertres*2.5/12+Vertres/(800/50);

      i3 = Horres*0.7-(Horres/(1280/10))*2;
      i4 = Vertres/(800/20);

      HFONT hFont = CreateFont(-Vertres/40,Horres/120,0,0,0,FALSE,0,0,DEFAULT_CHARSET,0,0,0,0,"Arial");//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

      SendMessage(hwndChild,WM_SETFONT,(WPARAM)hFont,1);//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      break;
    }

  }

  MoveWindow(hwndChild,i1,i2,i3,i4, TRUE);
  ShowWindow(hwndChild, SW_SHOW);
  return TRUE;
}




DWORD WINAPI fun1(LPVOID v)
{	
  CriticalSection s(&sec);
  while(true)
  {
    if(p.inListF != NULL)
    {
      SetDlgItemText(*HWtest, ID_STATUSBAR1, p.inListF->PathP);
      Sleep(10);
    }
  }
  return 0;
}




bool ChooseFolder(HWND hwnd, LPSTR lpszTitle, LPSTR lpBuffer)//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
{
  BROWSEINFO bi;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  bool res = false;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  LPITEMIDLIST pidlBrowse;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  ZeroMemory(&bi, sizeof(BROWSEINFO));//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  bi.hwndOwner = hwnd;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  //bi.pszDisplayName = lpBuffer;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  bi.lpszTitle = lpszTitle;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  bi.ulFlags = BIF_RETURNONLYFSDIRS|BIF_DONTGOBELOWDOMAIN|BIF_BROWSEFORCOMPUTER|BIF_NEWDIALOGSTYLE|BIF_NONEWFOLDERBUTTON;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  pidlBrowse = SHBrowseForFolder(&bi); //!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  if (pidlBrowse != NULL) {//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
    if (SHGetPathFromIDList(pidlBrowse, lpBuffer))//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
      res = true;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  }//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
  return res;//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!
}//!!!!!!!!!!!!!!!!!!!!!ДОБАВИЛ!!!!!!!!!!!!!!!!!!!!!

void addwrite2(char* buf)
{
  strcpy(buf,"");

  for (int i = 0; i < 2; i++)
  {
    if (massbool2[i])
      strcat(buf,masschar2[i]);
  }

}



void addwrite(char* buf)
{
  int flagsPusto = 0, flags = 0;

  for (int i = 0; i < 4; i++)
    if (massbool[i])
      flagsPusto++;

  if (!flagsPusto)
    strcpy(buf,"");
  else
    strcpy(buf,"Выбранные методы сравнения файлов: ");


  for (int i = 0; i < 4; i++)
  {

    if (massbool[i])
    {
      flags ++;
      strcat(buf,masschar[i]);

      if(flags != flagsPusto)
        strcat(buf,", ");
      else 
        strcat(buf, ".");
    }
  }

}

BOOL SaveFile(LPSTR pszFileName)
{
  HANDLE hFile;
  BOOL bSuccess = FALSE;

  hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);


  if(hFile != INVALID_HANDLE_VALUE)
  {
    if (p.inListL)
    {

      //!!!!!!!!!!!!!!!!!!!!!!!!
      ListL *temp = NULL;
      temp = p.inListL;
      char tc[MAX_PATH + MAX_PATH];
      ListF *temp2 = NULL;

      DWORD dwWritten;

      while(temp)
      {
        strcpy(tc,"*************************************************************\r\n");
        if ( WriteFile(hFile,tc,strlen(tc),&dwWritten, NULL)) 
          bSuccess = TRUE;
        else
          return false;

        temp2 = temp->spisok;
        while(temp2)
        {
          strcpy(tc, temp2->PathP);
          strcat(tc, "     ");
          strcat(tc, temp2->WFD.cFileName);
          strcat(tc, "\r\n");

          if ( WriteFile(hFile,tc,strlen(tc),&dwWritten, NULL)) 
            bSuccess = TRUE;
          else
            return false;
          temp2 = temp2->next;
        };	
        /*
        strcpy(tc, "\r\n");

        if ( WriteFile(hFile,tc,strlen(tc),&dwWritten, NULL)) 
        bSuccess = TRUE;
        else
        return false;
        */

        temp = temp->next;
      };
    }
    CloseHandle(hFile);
  }
  return bSuccess;
}