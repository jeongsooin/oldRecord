// DiaolgHIST.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DiaolgHIST.h"
#include "afxdialogex.h"


// CDiaolgHIST ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDiaolgHIST, CDialogEx)

CDiaolgHIST::CDiaolgHIST(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_x1(0)
	, m_x2(0)
{

}

CDiaolgHIST::~CDiaolgHIST()
{
}

void CDiaolgHIST::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X1, m_x1);
	DDV_MinMaxInt(pDX, m_x1, 0, 255);
	DDX_Text(pDX, IDC_X2, m_x2);
	DDV_MinMaxInt(pDX, m_x2, 0, 255);
}


BEGIN_MESSAGE_MAP(CDiaolgHIST, CDialogEx)
END_MESSAGE_MAP()


// CDiaolgHIST �޽��� ó�����Դϴ�.
