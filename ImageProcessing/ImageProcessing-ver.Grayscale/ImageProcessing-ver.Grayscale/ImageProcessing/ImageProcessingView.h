
// ImageProcessingView.h : CImageProcessingView Ŭ������ �������̽�
//

#pragma once


class CImageProcessingView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingView();
	DECLARE_DYNCREATE(CImageProcessingView)

// Ư���Դϴ�.
public:
	CImageProcessingDoc* GetDocument() const;

// �۾��Դϴ�.
public:

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
	virtual ~CImageProcessingView();
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
//	afx_msg void OnBasicProcessing();
//	afx_msg void OnBasicbinarization();
//	afx_msg void OnBasicbinarization();
//	afx_msg void OnBasicbinarization();
	afx_msg void OnBasicProcessing();
	afx_msg void OnZoomin();
	afx_msg void OnImageMod();
	afx_msg void OnHistoStretch();
	afx_msg void OnHistoEqual();
	afx_msg void OnHistogram();
	afx_msg void OnHistoSpec();
	afx_msg void OnPractice1();
	afx_msg void OnEmbossing();
	afx_msg void OnBlurr();
	afx_msg void OnGaussianFilter();
	afx_msg void OnSharpening();
	afx_msg void OnHpfSharp();
	afx_msg void OnLpfSharp();
	afx_msg void OnImageCopy();
	afx_msg void OnNegaTransform();
	afx_msg void OnSumConstant();
	afx_msg void OnSubConstant();
	afx_msg void OnAndOperate();
	afx_msg void OnOrOperate();
	afx_msg void OnXorOperate();
	afx_msg void OnGammaCorrection();
	afx_msg void OnPractice2();
	afx_msg void OnPosterizing();
	afx_msg void OnBitSlicing();
};

#ifndef _DEBUG  // ImageProcessingView.cpp�� ����� ����
inline CImageProcessingDoc* CImageProcessingView::GetDocument() const
   { return reinterpret_cast<CImageProcessingDoc*>(m_pDocument); }
#endif

