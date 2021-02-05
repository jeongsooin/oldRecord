#pragma once


// CRateDialog 대화 상자입니다.

class CRateDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CRateDialog)

public:
	CRateDialog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CRateDialog();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	double m_RateIn;
};
