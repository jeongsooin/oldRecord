// ConstantDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "ConstantDlg.h"
#include "afxdialogex.h"


// ConstantDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ConstantDlg, CDialogEx)

ConstantDlg::ConstantDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_Constant(0)
{

}

ConstantDlg::~ConstantDlg()
{
}

void ConstantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONSTANT, m_Constant);
}


BEGIN_MESSAGE_MAP(ConstantDlg, CDialogEx)
END_MESSAGE_MAP()


// ConstantDlg �޽��� ó�����Դϴ�.
