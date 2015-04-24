// lab4Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "lab4.h"
#include "lab4Dlg.h"
#include "Put.h"
#include "FTime.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
HANDLE hFile;
BOOL bl_create = FALSE;
char str[90], str2[90];
class CAboutDlg : public CDialog {
 public:
  CAboutDlg();

  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
 protected:
  //{{AFX_MSG(CAboutDlg)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
  // No message handlers
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLab4Dlg dialog

CLab4Dlg::CLab4Dlg(CWnd* pParent /*=NULL*/)
  : CDialog(CLab4Dlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CLab4Dlg)
  m_res = _T("");
  //}}AFX_DATA_INIT
  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLab4Dlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLab4Dlg)
  DDX_Text(pDX, IDC_Result, m_res);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLab4Dlg, CDialog)
  //{{AFX_MSG_MAP(CLab4Dlg)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_CreateFile, OnCreateFile)
  ON_BN_CLICKED(IDC_CLEAN, OnClean)
  ON_BN_CLICKED(IDC_GetFileInformationByHandle, OnGetFileInformationByHandle)
  ON_BN_CLICKED(IDC_FileTimeToSystemTime, OnFileTimeToSystemTime)
  ON_BN_CLICKED(IDC_GetFileType, OnGetFileType)
  ON_BN_CLICKED(IDC_SetFileAttributes, OnSetFileAttributes)
  ON_BN_CLICKED(IDC_GetSystemTime, OnGetSystemTime)
  ON_BN_CLICKED(IDC_SystemTimeFileTime, OnSystemTimeFileTime)
  ON_BN_CLICKED(IDC_FileTimeToDosDateTime, OnFileTimeToDosDateTime)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLab4Dlg message handlers

BOOL CLab4Dlg::OnInitDialog() {
  CDialog::OnInitDialog();

  // Add "About..." menu item to system menu.

  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);

  CMenu* pSysMenu = GetSystemMenu(FALSE);

  if (pSysMenu != NULL) {
    CString strAboutMenu;
    strAboutMenu.LoadString(IDS_ABOUTBOX);

    if (!strAboutMenu.IsEmpty()) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon

  // TODO: Add extra initialization here
  //RECT rect;
  /*   m_listctrl.DeleteAllItems();
  m_listctrl.GetClientRect(&rect);

  int width ;

        width= rect.right/10;

  m_listctrl.InsertColumn(0,_T("Name"),LVCFMT_LEFT,width);
  m_listctrl.InsertColumn(1,_T("Date of creation"),LVCFMT_LEFT,width);
    m_listctrl.InsertColumn(2,"Date of last acces",LVCFMT_LEFT,width);
    m_listctrl.InsertColumn(3,"Date of last modification",LVCFMT_LEFT,width);
    m_listctrl.InsertColumn(4,"Volume serial Number ",LVCFMT_LEFT,width);
  m_listctrl.InsertColumn(5,"File size Low",LVCFMT_LEFT,width);
  m_listctrl.InsertColumn(6,"File size High",LVCFMT_LEFT,width);
  m_listctrl.InsertColumn(7,"File Number of Link",LVCFMT_LEFT,width);
  m_listctrl.InsertColumn(8,"File Index High",LVCFMT_LEFT,width);
    m_listctrl.InsertColumn(9,"File Index Low",LVCFMT_LEFT,width);    */

  //OnAddFile();


  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLab4Dlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  } else
    CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLab4Dlg::OnPaint() {
  if (IsIconic()) {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  } else
    CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLab4Dlg::OnQueryDragIcon() {
  return (HCURSOR) m_hIcon;
}

void CLab4Dlg::OnCreateFile() {
  // TODO: Add your control notification handler code here
  HANDLE hFile;
  char str[90];
  bl_create = TRUE;
  CPut Input;
  m_res.Empty();
  m_res = "Create File \r\n";
  Input.m_static = _T("Put a name of File to be Create")     ;

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);
    hFile = CreateFile(str,  // file name
                       GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                       0,                              // do not share
                       NULL,                           // default security
                       CREATE_ALWAYS,                  // overwrite  always
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);                          // no template

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "Could not create file."; // process error
    else {
      m_res = "File  ";
      m_res += str;
      m_res += "   Have been created succesfully" ;
    }
  }

  CloseHandle(hFile);
  UpdateData(FALSE);

}

void CLab4Dlg::OnClean() {
  // TODO: Add your control notification handler code here
  m_res.Empty();
  UpdateData(FALSE);

}

void CLab4Dlg::OnGetFileInformationByHandle() {
  // TODO: Add your control notification handler code here
  HANDLE hFile;
  m_res.Empty();
  CPut Input;
  m_res = "Get Information by Handle of File \r\n";
  Input.m_static = _T("Put name of File ");

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);

    //hFile = CreateFileNS(str,  // file name("C:\MyProgram\datafile.txt", GENERIC_READ| GENERIC_WRITE, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, 0)
    hFile = CreateFile(str,  // file name
                       GENERIC_READ ,                   // open for reading and writing
                       FILE_SHARE_READ,                              // do not share
                       NULL,                           // default security
                       OPEN_EXISTING,                // overwrite  always
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);                          // no template

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "Could not GetInformation By handle of this file."; // process error
    else {

      LPBY_HANDLE_FILE_INFORMATION lpFileInformation = new _BY_HANDLE_FILE_INFORMATION ;
      BOOL result;
      result = GetFileInformationByHandle(  // ????????? ?????????? ? ????? ?? ??????
                 hFile,                                  // handle to file  - ????? ?????         [in]
                 lpFileInformation);  // buffer - ?????????? ? ?????   [out]

      if(lpFileInformation->dwFileAttributes == 32) { // &FILE_ATTRIBUTE_ARCHIVE)
        sprintf(str, "File attributes are FILE ATTRIBUTE ARCHIVE ", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes == 33) { //&FILE_ATTRIBUTE_ARCHIVE) &&lpFileInformation->dwFileAttributes ==FILE_ATTRIBUTE_READONLY)
        sprintf(str, "File attributes are FILE ATTRIBUTE ARCHIVE AND READONLY \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes == 34) { //FILE_ATTRIBUTE_ARCHIVE &&lpFileInformation->dwFileAttributes ==FILE_ATTRIBUTE_HIDDEN)
        sprintf(str, "lpFileInformation->dwFileAttributes FILE_ATTRIBUTE_HIDDEN AND ARCHIVE \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes == 3) { // &FILE_ATTRIBUTE_HIDDEN) && (lpFileInformation->dwFileAttributes &FILE_ATTRIBUTE_READONLY))
        sprintf(str, "A read-only file FILE_ATTRIBUTE_READONLY  AND HIDDEN \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes == 35 ) {
        sprintf(str, "file attributes READONLY ,HIDDDEN AND ARCHIVE \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes & FILE_ATTRIBUTE_READONLY ) {
        sprintf(str, "A file cannot be combined with other attributes. FILE_ATTRIBUTE_READONLY  \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      } else if(lpFileInformation->dwFileAttributes == 2) { //&FILE_ATTRIBUTE_HIDDEN)
        sprintf(str, "A hidden file, not normally visible to the user FILE_ATTRIBUTE_HIDDEN  \r\n", lpFileInformation->dwFileAttributes);
        m_res += str;
      }



      m_res += "\r\n";
      sprintf(str, "Date of creation is :");
      m_res += str;
      strcpy(str, CTime(lpFileInformation->ftCreationTime).Format("%d/%m/%Y %H:%M:%S"));
      m_res += str;
      m_res += "\r\n";
      sprintf(str, "Date of last access is : ");
      m_res += str;
      strcpy(str, CTime(lpFileInformation->ftLastAccessTime).Format("%d/%m/%Y %H:%M:%S"));
      m_res += str;
      m_res += "\r\n";
      sprintf(str, "Date of last Modification is : ");
      m_res += str;
      strcpy(str, CTime(lpFileInformation->ftLastWriteTime).Format("%d/%m/%Y/ %H:%M:%S"));
      m_res += str;
      m_res += "\r\n";
      sprintf(str, " The serial number of the disk which the file is stored onis: %u \r\n ", lpFileInformation->dwVolumeSerialNumber);
      m_res += str;
      sprintf(str, "File size High is : %u\r\n  ", lpFileInformation->nFileSizeHigh);
      m_res += str;
      sprintf(str, "File size low is : %u \r\n ", lpFileInformation->nFileSizeLow);
      m_res += str;
      sprintf(str, " The number of links to the file in the file system   :%u \r\n ", lpFileInformation->nNumberOfLinks);
      m_res += str;
      sprintf(str, "File Index High is :%u \r\n ", lpFileInformation->nFileIndexHigh);
      m_res += str;
      sprintf(str, "File Index Low is :%u \r\n ", lpFileInformation->nFileIndexLow);
      m_res += str;

    }

    CloseHandle(hFile);

  }

  UpdateData(FALSE);

}

void CLab4Dlg::OnGetFileType() {
  // TODO: Add your control notification handler code here

  // TODO: Add your control notification handler code here
  // HANDLE hFile;
  m_res.Empty();
  CPut Input;
  DWORD dwType;
  m_res = "Get Type of File \r\n";
  Input.m_static = _T("Put name of File ");

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);
    hFile = CreateFile(str,  // file name
                       GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                       0,                              // do not share
                       NULL,                           // default security
                       OPEN_EXISTING,                // overwrite  always
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);                          // no template */

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "Could not Get type of this file."; // process error
    else {


      dwType = GetFileType( hFile);
      sprintf(str, "Type of the File is : %u \r\n ", dwType)  ;

      switch(dwType) {
        case 1:
          m_res += "FILE_TYPE_CHAR The specified file is a character file, typically an LPT device or a console. ";
          break;

        case 2:
          m_res += "FILE_TYPE_DISK The specified file is a disk file. ";
          break;

        case 3:
          m_res += "FILE_TYPE_PIPE The specified file is a socket, a named pipe, or an anonymous pipe. ";
          break;

        case 4:
          m_res += "FILE_TYPE_REMOTE Unused. ";
          break;

        case 5:
          m_res += "FILE_TYPE_UNKNOWN Either the type of the specified file is unknown, or the function failed. ";
      }

      //m_res+=str;
    }
  }

  CloseHandle(hFile);
  UpdateData(FALSE);
}






void CLab4Dlg::OnFileTimeToSystemTime() {


  HANDLE hFile;

  FILETIME ftCreate, ftAccess, ftWrite;
  SYSTEMTIME systime, sys;
  m_res.Empty();
  CPut Input;

  m_res = " File Time to systeme time\r\n";
  Input.m_static = _T("Put name of File ");
  char lpszString[80];

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);
    hFile = CreateFile(str,  // file name
                       GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                       0,                              // do not share
                       NULL,                           // default security
                       OPEN_EXISTING,                // open existing
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "File doest not exist"; // pr
    else {


      // Retrieve the file times for the file.
      if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {

        // Convert the last-write time to local time.
        if( FileTimeToSystemTime(&ftWrite, &sys) != 0)

        {
          SystemTimeToTzSpecificLocalTime(NULL, &sys, &systime);

          // Build a string showing the date and time.
          wsprintf(lpszString, "%02d/%02d/%02d  %02d:%02d",
                   systime.wDay, systime.wMonth, systime.wYear,
                   systime.wHour, systime.wMinute);

          m_res += "After transformation\r\n";
          m_res += lpszString;
        } else
          MessageBox("Can not convert ", "Error", MB_ICONSTOP);

      } else MessageBox("Can't retrieves a time ");
    }

    CloseHandle(hFile);
    UpdateData(FALSE);

  }
}



void CLab4Dlg::OnSetFileAttributes() {
  // TODO: Add your control notification handler code here
  HANDLE hFiles;
  BOOL test = TRUE;
  m_res.Empty();
  CFTime Input;
  DWORD dwAttribute;
  m_res = "Get Attributes  of File \r\n";
  //Input.m_static=_T("Put name of File or directory");

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_name);
    hFiles = CreateFile(str,  // file name
                        GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                        0,                              // do not share
                        NULL,                           // default security
                        OPEN_EXISTING,                // overwrite  always
                        FILE_ATTRIBUTE_NORMAL,          // normal file
                        NULL);                          // no template */

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "Could not Get type of this file."; // process error
    else {
      do {
        if(Input.m_hidden == FALSE  && Input.m_readonly == FALSE

            && Input.m_archive == FALSE) {
          m_res = "You didn't select attribute";
          test = FALSE;
          Input.DoModal();
        }

      } while(test == FALSE);

      if(Input.m_archive == TRUE)
        dwAttribute = FILE_ATTRIBUTE_ARCHIVE ;

      if(Input.m_hidden == TRUE)
        dwAttribute = FILE_ATTRIBUTE_HIDDEN;

      if(Input.m_readonly == TRUE)
        dwAttribute = FILE_ATTRIBUTE_READONLY;

      if(Input.m_readonly == TRUE && Input.m_archive == TRUE)
        dwAttribute = FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_ARCHIVE ;

      if(Input.m_hidden == TRUE && Input.m_archive == TRUE)
        dwAttribute = FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE ;

      if(Input.m_readonly == TRUE && Input.m_hidden == TRUE)
        dwAttribute = FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN ;

      if(Input.m_archive == TRUE && Input.m_hidden == TRUE && Input.m_readonly == TRUE)
        dwAttribute = FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_ARCHIVE ;


      if( SetFileAttributes(    // ????????? ????????? ?????
            str,      // file name - ??? ?????             [in]
            dwAttribute   // attributes -
          ) == TRUE  )

        m_res = "attribute have been changed";
      else
        m_res = " set attribute failed";
    }


  }

  CloseHandle(hFiles);
  UpdateData(FALSE);

}

void CLab4Dlg::OnGetSystemTime() {
  // TODO: Add your control notification handler code here
  char lpszString[90];
  m_res.Empty();
  SYSTEMTIME systime;
  GetSystemTime(   // ????????? ??????? ??????? ? ??????? SystemTime
    &systime );  // ????????? ?????          [out]

  wsprintf(lpszString, "%02d/%02d/%02d  %02d:%02d:%02d:%02d",
           systime.wDay, systime.wMonth, systime.wYear,
           systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

  m_res += "system Time is \r\n";
  m_res += lpszString;
  UpdateData(FALSE);

}

void CLab4Dlg::OnSystemTimeFileTime() {
  // TODO: Add your control notification handler code here

  HANDLE hFile;

  FILETIME ftCreate;
  SYSTEMTIME sys;
  m_res.Empty();
  CPut Input;

  m_res = " System Time to File time\r\n";
  Input.m_static = _T("Put name of File ");

  //char lpszString[80];
  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);
    hFile = CreateFile(str,  // file name
                       GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                       0,                              // do not share
                       NULL,                           // default security
                       OPEN_EXISTING,                // open existing
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "File doest not exist"; // pr
    else {


      // Retrieve the file times for the file.
      GetSystemTime(&sys);


      // Convert the last-write time to local time.
      if( SystemTimeToFileTime(&sys, &ftCreate) != 0)

      {

        if(SetFileTime(hFile, &ftCreate, (LPFILETIME)NULL, (LPFILETIME)NULL))

          // Build a string showing the date and time.
        {
          sprintf(str, "Date of creation is : ");
          m_res += str;
          strcpy(str, CTime(ftCreate).Format("%d/%m/%Y"));

          m_res += "After transformation\r\n";
          m_res += str;
        }
      } else
        MessageBox("Can not convert ", "Error", MB_ICONSTOP);


    }

    CloseHandle(hFile);
    UpdateData(FALSE);

  }
}

void CLab4Dlg::OnFileTimeToDosDateTime() {
  // TODO: Add your control notification handler code here
  HANDLE hFile;

  FILETIME ftCreate, ftAccess, ftWrite;
  WORD  FatDate, FatTime;
  m_res.Empty();
  CPut Input;
  WORD day, month, year, minut, second, hour;
  m_res = "File Time to Dos Date  time\r\n";
  Input.m_static = _T("Put name of File ");
  char lpszString[80];

  if(Input.DoModal() == IDOK) {
    strcpy(str, Input.m_info);
    hFile = CreateFile(str,  // file name
                       GENERIC_READ | GENERIC_WRITE,                   // open for reading and writing
                       0,                              // do not share
                       NULL,                           // default security
                       OPEN_EXISTING,                // open existing
                       FILE_ATTRIBUTE_NORMAL,          // normal file
                       NULL);

    if (hFile == INVALID_HANDLE_VALUE)

      m_res += "File doest not exist"; // pr
    else {

      if (GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {


        if(FileTimeToDosDateTime(&ftCreate, &FatDate, &FatTime)) {

          day = (FatDate & 0x001F); //  0000000000011111);
          month = (FatDate & 1111); //0x03C0);//0000001111000000);
          year = (FatDate &  111111000000000); //0xFE00);//1111111000000000);
          hour = (FatTime  & 111111); //0xF800); //
          minut = (FatTime & 0000011111100000);
          second = (FatTime & 0000000000011111) / 2;
          wsprintf(lpszString, " %02d/%02d/%02d %02d:%02d:%02d ", day, month, year, hour, minut, second);
          m_res += lpszString;



        }





      }
    }
  }

  UpdateData(FALSE);
}
