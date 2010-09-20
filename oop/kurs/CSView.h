// ����: CSView.h
//������ ������ "������-���"
// �����: ������� �. ��. ��. 7304
// ����: 20.09.2010 ��������: 1.0


#ifndef CSVIEW_H_
#define CSVIEW_H_

#include "CView.h"
#include "CServer.h"
#include "CPoint.h"

class CServerView : public CView, public CServer {
public:
	CServerView(CPoint _P1,double _P1P2,CPoint _P3);
        CServerView(const CView& view);
	virtual ~CServerView();
	void ReciveMessage(CMessage* msg);
        void Print() const;
};

#endif