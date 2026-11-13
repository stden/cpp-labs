// Lab4.cpp : implementation file
//

#include "stdafx.h"
#include "OS.h"
#include "Lab4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLab4 property page

IMPLEMENT_DYNCREATE(CLab4, CPropertyPage)

CLab4::CLab4() : CPropertyPage(CLab4::IDD) {
  //{{AFX_DATA_INIT(CLab4)
  m_CurDir = _T("");
  m_FileName = _T("");
  m_OpenFileName = _T("");
  m_FileAttribute = _T("");
  //}}AFX_DATA_INIT
}

CLab4::~CLab4() {
}

void CLab4::DoDataExchange(CDataExchange* pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLab4)
  DDX_Text(pDX, IDC_FILENAME, m_FileName);
  DDX_Text(pDX, IDC_OPENFILENAME, m_OpenFileName);
  DDX_Text(pDX, IDC_FILEATTRIBUTE, m_FileAttribute);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLab4, CPropertyPage)
  //{{AFX_MSG_MAP(CLab4)
  ON_BN_CLICKED(IDC_CHANGECURDIR, OnChangecurdir)
  ON_BN_CLICKED(IDC_CHANGECFILENAME, OnChangecfilename)
  ON_BN_CLICKED(IDC_CREATEDIR, OnCreatedir)
  ON_BN_CLICKED(IDC_CHANGEOPENFILENAME, OnChangeopenfilename)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLab4 message handlers

//////////////////Изменения текущей директории//////////////////////////////
void CLab4::OnChangecurdir() {
  CString strDummyFile = m_CurDir;
  strDummyFile += _T("\\*.*");
  CFileDialog dlg(TRUE, NULL, strDummyFile, OFN_PATHMUSTEXIST);

  if (dlg.DoModal() == IDOK) {
    SetCurrentDirectory(dlg.GetPathName()) ;

    char CurDir[200] ;
    GetCurrentDirectory(200, CurDir) ;
    m_CurDir = CurDir ;

    UpdateData(FALSE) ;
  }
}

//////////////////Изменения имени создаваемого файла//////////////////////////////
void CLab4::OnChangecfilename() {
  CString strDummyFile = m_CurDir;
  strDummyFile += _T("\\*.*");
  CFileDialog dlg(FALSE, NULL, strDummyFile, OFN_PATHMUSTEXIST);

  if (dlg.DoModal() == IDOK) {
    m_FileName = dlg.GetPathName() ;
    UpdateData(FALSE) ;
  }
}



struct {
  UINT ID;
  UINT MASK;
  char* Text;
} uMasks[8] = {
  { IDC_FILE_ATTRIBUTE_ARCHIVE, FILE_ATTRIBUTE_ARCHIVE, "ARCHIVE" },
  { IDC_FILE_ATTRIBUTE_OFFLINE, FILE_ATTRIBUTE_OFFLINE, "OFFLINE"},
  { IDC_FILE_ATTRIBUTE_HIDDEN,  FILE_ATTRIBUTE_HIDDEN, "HIDDEN" },
  { IDC_FILE_ATTRIBUTE_NORMAL,  FILE_ATTRIBUTE_NORMAL, "NORMAL" },
  { IDC_FILE_ATTRIBUTE_NOT_CONTENT_INDEXED, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED, "NOT_CONTENT_INDEXED" },
  { IDC_FILE_ATTRIBUTE_READONLY,  FILE_ATTRIBUTE_READONLY, "READONLY" },
  { IDC_FILE_ATTRIBUTE_SYSTEM,  FILE_ATTRIBUTE_SYSTEM, "SYSTEM" },
  { IDC_FILE_ATTRIBUTE_TEMPORARY, FILE_ATTRIBUTE_TEMPORARY, "TEMPORARY" }
};

//////////////////Создание файла//////////////////////////////
void CLab4::OnCreatedir() {
  /*
    HANDLE CreateFile(
    LPCTSTR lpFileName,                         // file name
    DWORD dwDesiredAccess,                      // access mode
    DWORD dwShareMode,                          // share mode
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, // SD
    DWORD dwCreationDisposition,                // how to create
    DWORD dwFlagsAndAttributes,                 // file attributes
    HANDLE hTemplateFile                        // handle to template file
  );
  */
  DWORD uFlags = 0;

  for ( int i = 0 ; i < 8; i++ ) {
    CButton* pCheck = (CButton*)GetDlgItem(uMasks[i].ID) ;

    if ( pCheck->GetCheck() == 1 )
      uFlags |= uMasks[i].MASK ;
  }

  HANDLE hFile = CreateFile(m_FileName, GENERIC_READ, 0, 0, CREATE_ALWAYS, 0, NULL) ;

  if (hFile == INVALID_HANDLE_VALUE)
    AfxMessageBox("Файл не создан") ;
  else
    ::CloseHandle(hFile);

  (m_FileNSetFileAttributesame, uFlags) ;
}

//////////////////Изменения имени открываемого файла//////////////////////////////
void CLab4::OnChangeopenfilename() {
  CString strDummyFile = m_CurDir;

  if (m_CurDir[m_CurDir.GetLength() - 1] != '\\')
    strDummyFile += _T("\\*.*");
  else
    strDummyFile += _T("*.*");

  CFileDialog dlg(TRUE, NULL, strDummyFile, OFN_PATHMUSTEXIST);

  if (dlg.DoModal() == IDOK) {
    m_OpenFileName = dlg.GetPathName() ;

    HANDLE hFile = CreateFile(m_OpenFileName, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, NULL) ;

    BY_HANDLE_FILE_INFORMATION FileInfo ;
    GetFileInformationByHandle(hFile, &FileInfo) ;

    CString strFileInfo ;

    for (int i = 0; i < 8; i++ ) {
      if (FileInfo.dwFileAttributes & uMasks[i].MASK) {
        strFileInfo += uMasks[i].Text ;
        strFileInfo += "\r\n" ;
      }
    }

    FILETIME CreationTime ;
    FILETIME LastAccessTime ;
    FILETIME LastWriteTime ;

    GetFileTime(hFile, &CreationTime, &LastAccessTime, &LastWriteTime) ;

    WORD Date = 0 ;
    WORD Time = 0 ;
    CString strDateTime ;

    FileTimeToDosDateTime(&CreationTime, &Date, &Time) ;
    strDateTime.Format("\r\nDos Creation Date = %x\r\nDos Creation Time = %x\r\n\r\n", Date, Time) ;
    strFileInfo += strDateTime ;

    FILETIME newCreationTime ;
    DosDateTimeToFileTime(Date, Time, &newCreationTime) ;

    //    FileTimeToDosDateTime(&newCreationTime, &Date, &Time) ;
    //    strDateTime.Format("\r\nDos Creation Date = %x\r\nDos Creation Time = %x\r\n\r\n", Date, Time) ;
    //    strFileInfo += strDateTime ;


    if ( CompareFileTime(&CreationTime, &newCreationTime) == 0 )
      strFileInfo += "Compare OK" ;
    else
      strFileInfo += "Compare NOT OK" ;



    ::CloseHandle(hFile);

    m_FileAttribute = strFileInfo ;


    UpdateData(FALSE) ;



  }
}



BOOL CLab4::OnSetActive() {
  char CurDir[200] ;
  GetCurrentDirectory(200, CurDir) ;
  m_CurDir = CurDir ;

  UpdateData(FALSE) ;
  return CPropertyPage::OnSetActive();
}
