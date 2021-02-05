
// ImageProcessing_Team4View.h : CImageProcessing_Team4View Ŭ������ �������̽�
//

#pragma once


class CImageProcessing_Team4View : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageProcessing_Team4View();
	DECLARE_DYNCREATE(CImageProcessing_Team4View)

// Ư���Դϴ�.
public:
	CImageProcessing_Team4Doc* GetDocument() const;

// �۾��Դϴ�.
public:
	int rwsize;
	int height;
	int width;

	BITMAPINFO *BmInfo;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CImageProcessing_Team4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnImageSegmentation();
	afx_msg void OnImageclear();
	afx_msg void OnBlurring();
	afx_msg void OnBlurrGaussian();
	afx_msg void OnSharpMask();
	afx_msg void OnHpfFilterSharp();
	afx_msg void OnLpfFilterSharp();
	afx_msg void OnEdge();
	afx_msg void OnLaplacian();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnScaleDown();
	afx_msg void OnNearScaleUp();
	afx_msg void OnBilinearScaleUp();
	afx_msg void OnFft2d();
	afx_msg void OnIfft2d();
	afx_msg void OnLpfFrequency();
};

#ifndef _DEBUG  // ImageProcessing_Team4View.cpp�� ����� ����
inline CImageProcessing_Team4Doc* CImageProcessing_Team4View::GetDocument() const
   { return reinterpret_cast<CImageProcessing_Team4Doc*>(m_pDocument); }
#endif

