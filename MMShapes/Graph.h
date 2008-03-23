// Graph.h : main header file for the GRAPH application
//

#if !defined(AFX_FIRST_H__FCBE3144_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_)
#define AFX_FIRST_H__FCBE3144_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGraphApp:
// See Graph.cpp for the implementation of this class
//

class CGraphApp : public CWinApp
{
public:
	CGraphApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGraphApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRST_H__FCBE3144_99F0_11D3_B578_A1440AA7DB6E__INCLUDED_)
