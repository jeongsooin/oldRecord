// DiologZoomR.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DiologZoomR.h"
#include "afxdialogex.h"


// CDiologZoomR 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDiologZoomR, CDialogEx)

CDiologZoomR::CDiologZoomR(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_ZoomIn(0)
{

}

CDiologZoomR::~CDiologZoomR()
{
}

void CDiologZoomR::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_ZoomIn);
	DDX_Text(pDX, IDC_EDIT1, m_ZoomIn);
}


BEGIN_MESSAGE_MAP(CDiologZoomR, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CDiologZoomR::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDiologZoomR 메시지 처리기입니다.


void CDiologZoomR::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}
