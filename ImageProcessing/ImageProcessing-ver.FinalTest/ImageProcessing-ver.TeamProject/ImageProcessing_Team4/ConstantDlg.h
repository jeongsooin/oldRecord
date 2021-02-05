#pragma once


// ConstantDlg 대화 상자입니다.

class ConstantDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConstantDlg)

public:
	ConstantDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ConstantDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_Constant;
};
