#pragma once


// CDiologZoomR ��ȭ �����Դϴ�.

class CDiologZoomR : public CDialogEx
{
	DECLARE_DYNAMIC(CDiologZoomR)

public:
	CDiologZoomR(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDiologZoomR();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
//	int m_ZoomIn;
	int m_ZoomIn; // ���� �߰��� ����
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
