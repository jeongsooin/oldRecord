
// ImageProcessing_Team4View.h : CImageProcessing_Team4View 클래스의 인터페이스
//

#pragma once


class CImageProcessing_Team4View : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageProcessing_Team4View();
	DECLARE_DYNCREATE(CImageProcessing_Team4View)

// 특성입니다.
public:
	CImageProcessing_Team4Doc* GetDocument() const;

// 작업입니다.
public:
	int rwsize;
	int height;
	int width;

	BITMAPINFO *BmInfo;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProcessing_Team4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ImageProcessing_Team4View.cpp의 디버그 버전
inline CImageProcessing_Team4Doc* CImageProcessing_Team4View::GetDocument() const
   { return reinterpret_cast<CImageProcessing_Team4Doc*>(m_pDocument); }
#endif

