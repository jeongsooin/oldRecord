// RateDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing_Team4.h"
#include "RateDialog.h"
#include "afxdialogex.h"


// CRateDialog ��ȭ �����Դϴ�.

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


// CRateDialog �޽��� ó�����Դϴ�.

