// DiologZoomR.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DiologZoomR.h"
#include "afxdialogex.h"


// CDiologZoomR ��ȭ �����Դϴ�.

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


// CDiologZoomR �޽��� ó�����Դϴ�.


void CDiologZoomR::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}
