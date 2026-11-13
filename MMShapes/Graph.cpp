// Graph.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Graph.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphApp

BEGIN_MESSAGE_MAP(CGraphApp, CWinApp)
  //{{AFX_MSG_MAP(CGraphApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphApp construction

CGraphApp::CGraphApp() {
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraphApp object

CGraphApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraphApp initialization

BOOL CGraphApp::InitInstance() {

  // Standard initialization

#ifdef _AFXDLL
  Enable3dControls();     // Call this when using MFC in a shared DLL
#else
  Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif

  CMainFrame* pFrame = new CMainFrame;
  m_pMainWnd = pFrame;

  pFrame->LoadFrame(IDR_MAINFRAME,
                    WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
                    NULL,
                    NULL);

  m_pMainWnd->CenterWindow();
  m_pMainWnd->ShowWindow(SW_SHOW);
  m_pMainWnd->UpdateWindow();

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphApp commands
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog {
  // Construction
 public:
  CAboutDlg(CWnd* pParent = NULL);   // standard constructor

  // Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  // NOTE: the ClassWizard will add data members here
  //}}AFX_DATA


  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAboutDlg)
 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

  // Implementation
 protected:

  // Generated message map functions
  //{{AFX_MSG(CAboutDlg)
  // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CAboutDlg::IDD, pParent) {
  //{{AFX_DATA_INIT(CAboutDlg)
  // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  // NOTE: the ClassWizard will add DDX and DDV calls here
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
  // NOTE: the ClassWizard will add message map macros here
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers

void CGraphApp::OnAppAbout() {
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}
