// ChildWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"
#include "ChildWnd.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildWnd

CChildWnd::CChildWnd() {
  m_menu.CreatePopupMenu();
  m_menu.AppendMenu(MF_STRING, ID_INVOKE, (LPCTSTR)"&Invoke multimethod");
  m_nSelected = 0;
  m_shFigure = NULL;
}

CChildWnd::~CChildWnd() {
}


BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
  //{{AFX_MSG_MAP(CChildWnd)
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_WM_DESTROY()
  ON_WM_PAINT()
  ON_WM_ERASEBKGND()
  ON_WM_CREATE()
  ON_WM_RBUTTONDOWN()
  ON_COMMAND(ID_INVOKE, OnInvokeMM)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildWnd message handlers

BOOL CChildWnd::PreCreateWindow(CREATESTRUCT& cs) {
  if (!CWnd::PreCreateWindow(cs))
    return FALSE;

  cs.dwExStyle |= WS_EX_CLIENTEDGE;
  cs.style &= ~WS_BORDER;
  /*  cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_HREDRAW | CS_DBLCLKS,
                                       AfxGetApp()->LoadCursor(IDR_MAINFRAME));
                                       (HBRUSH)COLOR_WINDOWFRAME,// + 1,
                                       AfxGetApp()->LoadIcon(IDR_MAINFRAME));*/

  return TRUE;
}

void CChildWnd::OnLButtonDown(UINT nFlags, CPoint point) {
  CClientDC dc(this);
  CRect lpRect(point.x, point.y, point.x + 12, point.y + 12);
  CBrush brNew(RGB(255, 255, 255)), *oldBrush;

  int oldMode = dc.SetROP2(R2_COPYPEN);
  CPen  newPen(PS_SOLID, 3, RGB(0, 100, 0)),
        *oldPen = dc.SelectObject(&newPen);
  oldBrush = dc.SelectObject(&brNew);

  dc.Rectangle(m_rcSel);

  // ¬ зависимости от выбранного инструмента
  // запоминаем место нажати€ кнопки мыши в соответствующей переменной
  switch(m_nToolNum) {
    case ID_PANEERASE:
      dc.FillSolidRect(&lpRect, dc.GetPixel(0, 0));
      break;

    case ID_PANESELECT:
      Shapes::iterator i;

      for ( i = m_shapes.begin(); i != m_shapes.end(); ++i ) {
        Shape* s = *i;

        if ( s->hitTest( point ) ) {
          s->select();
          s->draw( dc );
          //CopySelectedShapesTo( m_selected );
          //m_nSelected=(s->isSelected()) ? m_nSelected+1 : m_nSelected-1;
          /* if ( m_nSelected==2 ) {
            OnRButtonDown(nFlags, point);
          } else {
            //m_menu.DeleteMenu(ID_INVOKE, MF_STRING);
          } */
          return;
        }
      }

      break;

    case ID_PANELINE:
      m_rcSel = CRect(0, 0, 0, 0);
      m_rcCur.left = m_rcCur.right  = point.x;
      m_rcCur.top  = m_rcCur.bottom = point.y;
      break;

    case ID_PANEPEN: {
      //m_pnDot.x = point.x;
      //m_pnDot.y = point.y;
      //dc.Ellipse(point.x-4,point.y-4,point.x+4,point.y+4);
      Point* p = new Point(CPoint(point.x, point.y));
      p->draw(dc);
      ShapeAdd(p);
      break;
    }
  }

  // ¬осстанавливаем старые параметры в контексте устройства
  dc.SelectObject(oldPen);
  dc.SelectObject(oldBrush);
  dc.SetROP2(oldMode);

  // ќб€зательно (!) организуем "захват" мыши
  SetCapture();

  // ”станавливаем переключатель начала рисовани€
  m_drawing = TRUE;

  CWnd::OnLButtonDown(nFlags, point);
}

void CChildWnd::OnLButtonUp(UINT nFlags, CPoint point) {
  CClientDC dc(this);
  int oldMode = dc.SetROP2(R2_COPYPEN);
  CPen newPen(PS_SOLID, 1, RGB(0, 0, 100)), *oldPen = dc.SelectObject(&newPen); //DOT

  // ¬ыбираем в контекст устройства предопределенную кисть
  CBrush* oldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

  // ќпредел€ем выбранный инструмент рисовани€
  switch(m_nToolNum) {
    // Ќакапливаем каждую фигуру в своем массиве
    case ID_PANEPEN: {
      //dc.MoveTo(point.x, point.y);
      //dc.LineTo(point.x, point.y);
    }
    break;

    case ID_PANELINE: {
      m_rcCur.right  = point.x;
      m_rcCur.bottom = point.y;
      //dc.MoveTo(m_rcCur.left, m_rcCur.top);
      //dc.LineTo(m_rcCur.right, m_rcCur.bottom);
      Segment* s = new Segment(CPoint(m_rcCur.left, m_rcCur.top),
                               CPoint(m_rcCur.right, m_rcCur.bottom));
      s->draw(dc);
      ShapeAdd(s);
    }
    break;
  }

  dc.SelectObject(oldPen);
  dc.SelectObject(oldBrush);
  dc.SetROP2(oldMode);

  // —брасываем флаг рисовани€
  m_drawing = FALSE;

  // ќсвобождаем мышь
  ReleaseCapture();

  CWnd::OnLButtonUp(nFlags, point);
}

void CChildWnd::OnMouseMove(UINT nFlags, CPoint point) {
  // ѕровер€ем, что нажата лева€ кнопка мыши
  if(m_drawing == TRUE) {
    // ѕолучаем контекст устройства
    CClientDC dc(this);
    int oldMode = dc.SetROP2(R2_NOTXORPEN);
    CPen newPen(PS_SOLID, 1, RGB(25, 255, 255)), *oldPen = dc.SelectObject(&newPen); //DOT
    CPen pen(PS_DOT, 1, RGB(0, 0, 100));
    CRect lpRect(point.x, point.y, point.x + 12, point.y + 12);

    // ¬ыбираем в контекст устройства предопределенную кисть
    CBrush* oldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

    // ќпредел€ем выбранный инструмент рисовани€
    switch(m_nToolNum) {
      case ID_PANEERASE:
        dc.FillSolidRect(&lpRect, RGB(255, 255, 255));
        break;

      case ID_PANELINE:
        dc.MoveTo(m_rcCur.left, m_rcCur.top);
        dc.LineTo(m_rcCur.right, m_rcCur.bottom);
        m_rcCur.right  = point.x;
        m_rcCur.bottom = point.y;

        // –исуем линию
        dc.MoveTo(m_rcCur.left, m_rcCur.top);
        dc.LineTo(m_rcCur.right, m_rcCur.bottom);
        break;
        /*      case ID_PANEPEN:
                dc.SetROP2(R2_COPYPEN);
                dc.MoveTo(m_pnDot.x, m_pnDot.y);
                m_pnDot.x = point.x;
                m_pnDot.y = point.y;
                dc.LineTo(point.x, point.y);
                break; */
    }

    // ¬осстанавливаем карандаш, кисть и режим рисовани€
    dc.SelectObject(oldPen);
    dc.SelectObject(oldBrush);
    dc.SetROP2(oldMode);

  } else if (m_nToolNum == ID_PANESELECT) {

    CClientDC dc(this);

    Shapes::iterator i;

    for ( i = m_shapes.begin(); i != m_shapes.end(); ++i ) {
      Shape* s = *i;

      if ( s->hitTest( point ) ) {
        m_shCurrent = s;
        s->activate( true );
        s->draw( dc );
        return;
      }
    }

    if ( m_shCurrent ) {
      m_shCurrent->activate( false );
      m_shCurrent->draw( dc );
    }

    m_shCurrent = NULL;

    // ¬осстанавливаем карандаш, кисть и режим рисовани€
  }

  CWnd::OnMouseMove(nFlags, point);
}

void CChildWnd::OnDestroy() {
  CWnd::OnDestroy();
  m_shapes.clear();

}

int CChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) {
  if (CWnd::OnCreate(lpCreateStruct) == -1)
    return -1;

  return 0;
}

void CChildWnd::OnRButtonDown(UINT nFlags, CPoint point) {
  ClientToScreen(&point);
  m_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                        point.x, point.y, this);

  CWnd::OnRButtonDown(nFlags, point);
}


BOOL CChildWnd::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) {
  return CWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////

void CChildWnd::ShapeAdd(Shape* s) {
  if ( m_hWnd )
    Invalidate();

  m_shapes.push_back(s);
}

void CChildWnd::ShapeRemove(Shape* s) {
  if ( m_hWnd )
    Invalidate();

  m_shapes.erase( std::find( m_shapes.begin(), m_shapes.end(), s ) );
}

size_t CChildWnd::ShapesCount() const {
  return m_shapes.size();
}

Shape* CChildWnd::ShapeGet(int i) const {
  return m_shapes[i];
}

void CChildWnd::OnPaint() {
  CPaintDC dc(this);

  for ( Shapes::iterator i = m_shapes.begin(); i != m_shapes.end(); ++i )
    (*i)->draw( dc );

  if ( m_shFigure ) m_shFigure->draw(dc);

  // Do not call CStatic::OnPaint() for painting messages
}

BOOL CChildWnd::OnEraseBkgnd(CDC* pDC) {
  CRect R;
  GetClientRect( R );
  FillRect( pDC->GetSafeHdc(), R, CBrush(RGB(255, 255, 255)) );
  return TRUE;
}

void CChildWnd::ClearSelection() {
  for( Shapes::iterator i = m_shapes.begin(); i != m_shapes.end(); ++i)
    (*i)->state_ = Shape::ShapeNormal;

  m_nSelected = 0;
  m_shFigure = NULL;

  //m_menu.DeleteMenu(ID_INVOKE, MF_STRING);
  if ( m_hWnd )
    Invalidate();
}

void CChildWnd::OnInvokeMM() {
  GetParent()->SendMessage( WM_USER + 1, 0, 0 );
}

void CChildWnd::CopySelectedShapesTo(Shapes& v) {
  v.clear();

  for ( Shapes::iterator i = m_shapes.begin(); i != m_shapes.end(); ++i )
    if ((*i)->isSelected()) v.push_back(*i);
}

void CChildWnd::CopySelectedShapesTo(Shape* v[]) {
  UINT j = 0;

  for ( Shapes::iterator i = m_shapes.begin(); i != m_shapes.end(); ++i )
    if ((*i)->isSelected()) v[j++] = *i;
}