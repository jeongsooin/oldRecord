#pragma once


// DialogIP ��ȭ �����Դϴ�.

class DialogIP : public CDialogEx
{
	DECLARE_DYNAMIC(DialogIP)

public:
	DialogIP(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~DialogIP();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int T1;
	int T2;
};
