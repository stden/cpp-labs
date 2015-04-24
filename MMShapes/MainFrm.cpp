// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Graph.h"

#include "MainFrm.h"
#include "ChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
  //{{AFX_MSG_MAP(CMainFrame)
  ON_WM_CREATE()
  ON_COMMAND(ID_VIEW_PANEBAR, OnViewPaneBar)
  ON_UPDATE_COMMAND_UI(ID_VIEW_PANEBAR, OnUpdateViewPaneBar)
  ON_CBN_SELCHANGE(IDC_PANE, OnSelChangePane)
  ON_WM_DESTROY()
  ON_WM_TIMER()
  ON_COMMAND(ID_CLEARSELECTION, OnClearSelection)
  ON_MESSAGE( WM_USER + 1, OnMultimethod )
  //}}AFX_MSG_MAP
  ON_COMMAND_RANGE(ID_PANEERASE, ID_PANELINE, OnPane)
  //ON_UPDATE_COMMAND_UI_RANGE(ID_PANEERASE, ID_PANEOVAL, OnUpdatePane)
  //  ON_COMMAND_RANGE(ID_CLR0, ID_CLR15, OnColor)
END_MESSAGE_MAP()

static UINT indicators[] = {
  ID_SEPARATOR,           // индикаторы строки состояния
  ID_INDICATOR_NUM,
};

static UINT BASED_CODE cursors[] = {
  IDC_CUR_ERASE,
  IDC_CUR_PEN,
  IDC_CUR_SELECT,
  IDC_CUR_LINE,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() {
  m_nPaneCol = 2;
}

CMainFrame::~CMainFrame() {
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) {
  if( !CFrameWnd::PreCreateWindow(cs) )
    return FALSE;

  cs.x  = 0;
  cs.y  = 0;
  cs.cx = 560;
  cs.cy = 400;
  cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
  cs.lpszName  = "Graph Application";

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  // создаем дочернее окно и помещаем его в клиентскую область фрейма
  if (!m_wndChild.Create(NULL,
                         NULL,
                         AFX_WS_DEFAULT_VIEW,
                         CRect(0, 0, 0, 0),
                         this,
                         AFX_IDW_PANE_FIRST,
                         NULL)) {
    TRACE0("Ошибка при создании дочернего окна\n");
    return -1;
  }

  if (!m_wndStatusBar.Create(this) ||
      !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT))) {
    TRACE0("Ошибка при создании строки состояния\n");
    return -1;      // fail to create
  }

  if (!m_wndToolBar.Create(this) ||
      !m_wndToolBar.LoadToolBar(IDR_MAINFRAME)) {
    TRACE0("Ошибка при создании панели инструментов\n");
    return -1;      // fail to create
  }

  m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
                           CBRS_TOOLTIPS              |
                           CBRS_FLYBY                 |
                           CBRS_SIZE_DYNAMIC);


  m_nIndex = 1;
  m_wndChild.m_nToolNum = ID_PANEERASE + m_nIndex;
  ::SetClassLong(m_wndChild.GetSafeHwnd(), GCL_HCURSOR,
                 (LONG)AfxGetApp()->LoadCursor(cursors[m_nIndex]));

  if (!m_wndPaneBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_SIZE_FIXED |
                           CBRS_TOP | CBRS_TOOLTIPS) ||
      !m_wndPaneBar.LoadToolBar(IDR_PANEBAR)) {
    TRACE0("Ошибка при создании панели инструментов рисования\n");
    return -1;      // fail to create
  }

  m_wndPaneBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
                           CBRS_TOOLTIPS              |
                           CBRS_FLYBY                 |
                           CBRS_SIZE_DYNAMIC);

  (m_wndPaneBar.GetToolBarCtrl()).CheckButton(m_wndPaneBar.GetItemID(1));


  //
  // добавляем к изображениям на кнопках текстовые строки
  //

  // узнаем и запоминаем размер изображений
  CRect imageRect;
  m_wndPaneBar.GetItemRect(0, &imageRect);

  // добавляем по строке на каждую кнопку,
  // если строк будет меньше - все оставшиеся кнопки
  // будут осчастливлены ПЕРВОЙ ЗАДАННОЙ СТРОКОЙ !!!
  for (int index = ID_PANEERASE; index <= ID_PANELINE; index++) {
    CString szPane;
    szPane.LoadString(index);

    // строки хранятся в следующем виде:
    //   - сообщение для строки состояния о возможном выборе,
    //   - символ '\n',
    //   - краткое наименование для всплывающих подсказок.
    // именно последнее мы и используем
    m_wndPaneBar.SetButtonText(index - ID_PANEERASE,
                               szPane.Mid(szPane.Find('\n') + 1));
  }

  // после каждой вставки текста автоматически происходило изменение размеров,
  // но об этом знает Windows, объект класса CToolBar об этом знать не знает -
  // сообщим ему об этом, помятуя, что размер изображений остался без изменений
  // константы 7 - требования Microsoft
  CRect buttonRect;
  m_wndPaneBar.GetItemRect(0, &buttonRect);
  m_wndPaneBar.SetSizes(CSize(buttonRect.Width(), buttonRect.Height()),
                        CSize(imageRect.Width() - 7, imageRect.Height() - 7));

  // заголовок для будущего окна, если панель будет в плавающем режиме
  // (будет-будет)
  m_wndPaneBar.SetWindowText(_T("Инструменты"));


  EnableDocking(CBRS_ALIGN_ANY);

  // сразу настраиваем кол-во столбцов
  //SetColumns(m_nPaneCol);

  m_wndPaneBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndPaneBar, AFX_IDW_DOCKBAR_BOTTOM);

  // размещаем панель инструментов в задаваемом месте экрана
  /*  CPoint pt(::GetSystemMetrics(SM_CXSCREEN) - 300,
      ::GetSystemMetrics(SM_CYSCREEN) / 3);

    FloatControlBar(&m_wndPaneBar, pt);
  */

  m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
  DockControlBar(&m_wndToolBar, AFX_IDW_DOCKBAR_LEFT);

  return 0;
}

// разбивка панели на столбцы - находим
// конечные кнопки каждой строки
/*void CMainFrame::SetColumns(UINT nColumns)
{
  int nCount = m_wndPaneBar.GetToolBarCtrl().GetButtonCount();

  for (int i = 0; i < nCount; i++)
  {
    UINT nStyle = m_wndPaneBar.GetButtonStyle(i);
    BOOL bWrap = (((i + 1) % nColumns) == 0);
    if (bWrap)
      nStyle |= TBBS_WRAPPED;
    else
      nStyle &= ~TBBS_WRAPPED;
    m_wndPaneBar.SetButtonStyle(i, nStyle);
  }

  m_wndPaneBar.Invalidate();
  m_wndPaneBar.GetParentFrame()->RecalcLayout();
} */

void CMainFrame::OnSelChangePane() {
  CString strText;
  CString strItem;

  int nIndex = 0;
  AfxFormatString1(strText, IDS_SELECTED_PROMPT, (LPCTSTR)strItem);
  SetMessageText(strText);

  (m_wndPaneBar.GetToolBarCtrl()).CheckButton(m_wndPaneBar.GetItemID(nIndex));
  m_wndChild.m_nToolNum = nIndex + ID_PANEERASE;
  m_nIndex = nIndex;
  ::SetClassLong(m_wndChild.GetSafeHwnd(), GCL_HCURSOR,
                 (LONG)AfxGetApp()->LoadCursor(cursors[m_nIndex]));

}

void CMainFrame::OnViewPaneBar() {
  BOOL bVisible = ((m_wndPaneBar.GetStyle() & WS_VISIBLE) != 0);

  ShowControlBar(&m_wndPaneBar, !bVisible, FALSE);
  RecalcLayout();

  if(!bVisible)
    ::SetClassLong(m_wndChild.GetSafeHwnd(), GCL_HCURSOR,
                   (LONG)AfxGetApp()->LoadCursor(cursors[m_nIndex]));
  else
    ::SetClassLong(m_wndChild.GetSafeHwnd(), GCL_HCURSOR,
                   (LONG)AfxGetApp()->LoadStandardCursor(IDC_ARROW));

}

void CMainFrame::OnUpdateViewPaneBar(CCmdUI* pCmdUI) {
  BOOL bVisible = ((m_wndPaneBar.GetStyle() & WS_VISIBLE) != 0);
  pCmdUI->SetCheck(bVisible);
}

void CMainFrame::OnPane(UINT nID) {
  m_nIndex = nID - ID_PANEERASE;
  m_wndChild.m_nToolNum = nID;

  for(int i = ID_PANEERASE; i <= ID_PANELINE; i++)
    m_wndPaneBar.GetToolBarCtrl().CheckButton(i, FALSE);

  BOOL bCheck = m_wndPaneBar.GetToolBarCtrl().IsButtonChecked(nID);
  m_wndPaneBar.GetToolBarCtrl().CheckButton(nID, !bCheck);
  ::SetClassLong(m_wndChild.GetSafeHwnd(), GCL_HCURSOR,
                 (LONG)AfxGetApp()->LoadCursor(cursors[m_nIndex]));
}

void CMainFrame::OnDestroy() {
  CFrameWnd::OnDestroy();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
  if (m_wndChild.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
    return TRUE;

  return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::OnClearSelection() {
  m_wndChild.ClearSelection();
  m_vMMParamShapes.clear();
}

LRESULT CMainFrame::OnMultimethod(WPARAM, LPARAM) {
  Shape* v[100];
  m_wndChild.CopySelectedShapesTo(m_vMMParamShapes);

  for ( UINT i = 0; i < m_vMMParamShapes.size(); i++ )
    v[i] = m_vMMParamShapes[i];

  _mvt.args_set( v, m_vMMParamShapes.size() );
  _mvt.figure.pts.clear();

  for (  i = 0; i < _mvt.method_count(); i++ ) {
    MyMVT::Method* mm = _mvt.method_get( i );
    _mvt.invoke( mm );
  }

  m_wndChild.m_shFigure = &_mvt.figure;

  if ( m_wndChild.m_hWnd )
    m_wndChild.Invalidate();

  return 0;
}