#pragma once


// CImageClearDlg ��ȭ �����Դϴ�.

class CImageClearDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageClearDlg)

public:
	CImageClearDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageClearDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int rnum1;
	int rnum2;
	int gnum1;
	int gnum2;
	int bnum1;
	int bnum2;
};
