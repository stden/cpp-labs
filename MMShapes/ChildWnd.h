#if !defined(AFX_CHILDWND_H__0406705F_A7EB_11D3_BAAA_00600864785A__INCLUDED_)
#define AFX_CHILDWND_H__0406705F_A7EB_11D3_BAAA_00600864785A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ChildWnd.h : header file
//

#include "Shapes.h"

/////////////////////////////////////////////////////////////////////////////
// CChildWnd window

class CChildWnd : public CWnd
{
// Construction
public:
	CChildWnd();

// Attributes
public:

	BOOL m_drawing;
	UINT m_nToolNum;
	UINT m_nSelected;
	CMenu m_menu;

	//CArray<CRect, CRect&>   arLine;
	//CArray<CPoint, CPoint&> arPoint;

	typedef std::vector< Shape* > Shapes;

	Shapes   m_shapes;
	Shapes   m_selected;
	Shape   *m_shCurrent;
	Figure	*m_shFigure;

protected:
	CRect m_rcSel;
	CRect m_rcCur;
	CPoint m_pnDot;


// Operations
private:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildWnd)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	Shape* ShapeGet(int) const;
	size_t ShapesCount() const;
	void ShapeRemove(Shape*);
	void ShapeAdd(Shape*);
	void ClearSelection();
	void CopySelectedShapesTo(Shapes&);
	void CopySelectedShapesTo(Shape *v[]);
	//Shapes *GetSelectedShapes() { return &m_selected; }

	LRESULT OnSelCanvas(WPARAM,LPARAM);

	virtual ~CChildWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnInvokeMM();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDWND_H__0406705F_A7EB_11D3_BAAA_00600864785A__INCLUDED_)
