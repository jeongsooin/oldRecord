
// ImageProcessing_Team4.h : ImageProcessing_Team4 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CImageProcessing_Team4App:
// �� Ŭ������ ������ ���ؼ��� ImageProcessing_Team4.cpp�� �����Ͻʽÿ�.
//

class CImageProcessing_Team4App : public CWinAppEx
{
public:
	CImageProcessing_Team4App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageProcessing_Team4App theApp;
