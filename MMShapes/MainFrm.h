// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__FCBE3148_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_)
#define AFX_MAINFRM_H__FCBE3148_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ChildWnd.h"
#include "MyMVT.h"

class CMainFrame : public CFrameWnd {
 public:
  CMainFrame();

  // Attributes
 public:

  // Operations
 public:
  void InvokeMM();

  // Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CMainFrame)
 public:
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
  //}}AFX_VIRTUAL

  // Implementation
 public:
  LRESULT OnMultimethod(WPARAM, LPARAM);

  virtual ~CMainFrame();

  //  void SetColor(int nID);

 protected:  // control bar embedded members
  CStatusBar  m_wndStatusBar;
  CToolBar    m_wndToolBar;
  CToolBar    m_wndPaneBar;    // панель инструментов рисования
  CChildWnd   m_wndChild;

  // дополнительные члены класса
  UINT m_nPaneCol;      // кол-во столбцов панели инструментов рисования
  std::vector< Shape* >  m_vMMParamShapes;
  MyMVT _mvt;

  // Generated message map functions
 protected:
  UINT m_nIndex;

  //{{AFX_MSG(CMainFrame)
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnViewPaneBar();
  afx_msg void OnUpdateViewPaneBar(CCmdUI* pCmdUI);
  afx_msg void OnSelChangePane();
  afx_msg void OnDestroy();
  afx_msg void OnPane(UINT nID);  // список инструментов рисования
  afx_msg void OnClearSelection();
  //}}AFX_MSG
  //afx_msg void OnUpdatePane(CCmdUI* pCmdUI);
  //  afx_msg void OnColor(UINT nID); // список цветов

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__FCBE3148_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_)
