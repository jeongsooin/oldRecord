// RateDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing_Team4.h"
#include "RateDialog.h"
#include "afxdialogex.h"


// CRateDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CRateDialog, CDialogEx)

CRateDialog::CRateDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_RateIn(0)
{

}

CRateDialog::~CRateDialog()
{
}

void CRateDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_RateIn);
}


BEGIN_MESSAGE_MAP(CRateDialog, CDialogEx)
//	ON_EN_CHANGE(IDC_EDIT1, &CRateDialog::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CRateDialog 메시지 처리기입니다.

