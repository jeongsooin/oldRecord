// ImageSegmentDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing_Team4.h"
#include "ImageSegmentDlg.h"
#include "afxdialogex.h"


// CImageSegmentDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageSegmentDlg, CDialogEx)

CImageSegmentDlg::CImageSegmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, num1(0)
	, num2(0)
	, num3(0)
{

}

CImageSegmentDlg::~CImageSegmentDlg()
{
}

void CImageSegmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, num1);
	DDX_Text(pDX, IDC_EDIT2, num2);
	DDX_Text(pDX, IDC_EDIT3, num3);
}


BEGIN_MESSAGE_MAP(CImageSegmentDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageSegmentDlg 메시지 처리기입니다.
