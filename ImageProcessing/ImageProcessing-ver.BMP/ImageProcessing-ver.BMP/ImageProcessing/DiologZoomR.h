#pragma once


// CDiologZoomR 대화 상자입니다.

class CDiologZoomR : public CDialogEx
{
	DECLARE_DYNAMIC(CDiologZoomR)

public:
	CDiologZoomR(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDiologZoomR();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	int m_ZoomIn;
	int m_ZoomIn; // 내가 추가한 변수
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
};
