// ImageClearDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing_Team4.h"
#include "ImageClearDlg.h"
#include "afxdialogex.h"


// CImageClearDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CImageClearDlg, CDialogEx)

CImageClearDlg::CImageClearDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, rnum1(0)
	, rnum2(0)
	, gnum1(0)
	, gnum2(0)
	, bnum1(0)
	, bnum2(0)
{

}

CImageClearDlg::~CImageClearDlg()
{
}

void CImageClearDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_CLEAR_EDIT1, rnum1);
	DDX_Text(pDX, ID_CLEAR_EDIT2, rnum2);
	DDX_Text(pDX, ID_CLEAR_EDIT3, gnum1);
	DDX_Text(pDX, ID_CLEAR_EDIT4, gnum2);
	DDX_Text(pDX, ID_CLEAR_EDIT5, bnum1);
	DDX_Text(pDX, ID_CLEAR_EDIT6, bnum2);
}


BEGIN_MESSAGE_MAP(CImageClearDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageClearDlg 메시지 처리기입니다.
