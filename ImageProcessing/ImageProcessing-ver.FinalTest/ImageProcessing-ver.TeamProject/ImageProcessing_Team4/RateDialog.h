#pragma once


// CRateDialog ��ȭ �����Դϴ�.

class CRateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRateDialog)

public:
	CRateDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CRateDialog();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

	double m_RateIn;
};
