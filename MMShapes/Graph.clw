; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChildWnd
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Graph.h"
LastPage=0

ClassCount=5
Class1=CMainFrame
Class2=CGraphApp

ResourceCount=4
Class3=CChildWnd
Resource1=IDR_COLORBAR
Class4=CAboutDlg
Resource2=IDD_ABOUTBOX
Resource3=IDR_PANEBAR
Class5=CColorMenu
Resource4=IDR_MAINFRAME (English (U.S.))

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CGraphApp]
Type=0
BaseClass=CWinApp
HeaderFile=Graph.h
ImplementationFile=Graph.cpp
Filter=N
VirtualFilter=AC
LastObject=ID_APP_ABOUT

[CLS:CChildWnd]
Type=0
HeaderFile=ChildWnd.h
ImplementationFile=ChildWnd.cpp
BaseClass=CWnd
Filter=C
VirtualFilter=WC
LastObject=ID_INVOKE

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_VIEW_PANEBAR
Command5=ID_CLEARSELECTION
Command6=ID_APP_ABOUT
CommandCount=6

[CLS:CAboutDlg]
Type=0
HeaderFile=Graph.cpp
ImplementationFile=Graph.cpp
BaseClass=CDialog
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=3
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_EDIT_CUT
Command3=ID_EDIT_COPY
Command4=ID_EDIT_PASTE
Command5=ID_FILE_PRINT
Command6=ID_APP_ABOUT
CommandCount=6

[TB:IDR_PANEBAR]
Type=1
Class=?
Command1=ID_PANEERASE
Command2=ID_PANEPEN
Command3=ID_PANESELECT
Command4=ID_PANELINE
CommandCount=4

[TB:IDR_COLORBAR]
Type=1
Class=?
Command1=ID_CLR0
Command2=ID_CLR1
Command3=ID_CLR2
CommandCount=3

