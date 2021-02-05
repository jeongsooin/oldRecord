// DialogIP.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ImageProcessing.h"
#include "DialogIP.h"
#include "afxdialogex.h"


// DialogIP 대화 상자입니다.

IMPLEMENT_DYNAMIC(DialogIP, CDialogEx)

DialogIP::DialogIP(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, T1(0)
	, T2(0)
{

}

DialogIP::~DialogIP()
{
}

void DialogIP::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_T1, T1);
	//  DDX_Text(pDX, IDC_T2, T2);
	DDX_Text(pDX, IDC_T2, T2);
}


BEGIN_MESSAGE_MAP(DialogIP, CDialogEx)
END_MESSAGE_MAP()


// DialogIP 메시지 처리기입니다.
