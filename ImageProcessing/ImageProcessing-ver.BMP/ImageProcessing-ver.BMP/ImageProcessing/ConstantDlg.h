#pragma once


// ConstantDlg ��ȭ �����Դϴ�.

class ConstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConstantDlg)

public:
	ConstantDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ConstantDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
