#pragma once


// CImageSegmentDlg ��ȭ �����Դϴ�.

class CImageSegmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CImageSegmentDlg)

public:
	CImageSegmentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CImageSegmentDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int num1;
	int num2;
	int num3;
};
