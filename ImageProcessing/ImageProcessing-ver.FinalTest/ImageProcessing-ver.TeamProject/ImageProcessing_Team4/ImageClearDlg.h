#pragma once


// CImageClearDlg 대화 상자입니다.

class CImageClearDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageClearDlg)

public:
	CImageClearDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CImageClearDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int rnum1;
	int rnum2;
	int gnum1;
	int gnum2;
	int bnum1;
	int bnum2;
};
