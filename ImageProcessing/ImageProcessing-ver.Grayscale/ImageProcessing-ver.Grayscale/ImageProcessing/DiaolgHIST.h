#pragma once


// CDiaolgHIST ��ȭ �����Դϴ�.

class CDiaolgHIST : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaolgHIST)

public:
	CDiaolgHIST(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDiaolgHIST();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_x1;
	int m_x2;
};
