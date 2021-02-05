
// ChildFrm.cpp : CChildFrame Ŭ������ ����
//

#include "stdafx.h"
#include "ImageProcessing_Team4.h"
#include "ImageProcessing_Team4Doc.h"
#include "ImageProcessing_Team4View.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
END_MESSAGE_MAP()

// CChildFrame ����/�Ҹ�

CChildFrame::CChildFrame()
{
	// TODO: ���⿡ ��� �ʱ�ȭ �ڵ带 �߰��մϴ�.
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ����

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame �޽��� ó����


void CChildFrame::ActivateFrame(int nCmdShow)
{
	CRect rect, rectC;
	GetWindowRect(&rect); 
	GetClientRect(&rectC);
	CSize sizeImg;
	sizeImg.cx = ((CImageProcessing_Team4Doc*) GetActiveDocument())->width;
	sizeImg.cy = ((CImageProcessing_Team4Doc*)GetActiveDocument())->height;
	int cx = sizeImg.cx + rect.Width() - rectC.Width() + 4;
	int cy = sizeImg.cy + rect.Height() - rectC.Height() + 4;
	SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_SHOWWINDOW);

	CMDIChildWndEx::ActivateFrame(nCmdShow);
}
