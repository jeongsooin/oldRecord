#pragma once


// CDiaolgHIST 대화 상자입니다.

class CDiaolgHIST : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaolgHIST)

public:
	CDiaolgHIST(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDiaolgHIST();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_x1;
	int m_x2;
};
