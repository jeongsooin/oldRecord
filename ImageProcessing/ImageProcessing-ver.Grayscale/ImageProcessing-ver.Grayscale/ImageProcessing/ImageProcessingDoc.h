
// ImageProcessingDoc.h : CImageProcessingDoc Ŭ������ �������̽�
//


#pragma once


class CImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessingDoc();
	DECLARE_DYNCREATE(CImageProcessingDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	int m_height;
	int m_width;
	int m_size;
	int m_Re_size;
	int m_Re_height;
	int m_Re_width;
	int m_Re_size2;
	int m_Re_height2;
	int m_Re_width2;
	int m_Re_size3;
	int m_Re_height3;
	int m_Re_width3;
	unsigned char* m_OutputImage;
	unsigned char* m_OutputImage2;
	unsigned char* m_OutputImage3;
	unsigned char* m_InputImage;
	double** m_tempImage;
	double m_HIST[256];
	double m_Sum_of_HIST[256];
	unsigned char m_Scale_HIST[256];
// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	void OnBinarization();
	void OnZoomIn();
	void OnImagecopy();
	void OnImageMod();
	void OnHistoStretch();
	void OnHistoEqual();
	void OnHistogram();
	void OnHistoSpec();
	void OnPractice1();
	void OnEmbossing();
//	double** OnMaskProcess(unsigned char* Target);
	double** OnMaskProcess(unsigned char* Target, double  Mask[3][3]);
	double** Image2DMem(int height, int width);
	double** OnScale(double** Target, int height, int width);
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpening();
	void OnHpfSharp();
	void OnLpfSharp();
	void OnNegaTransform();
	void OnSumConstant();
	void OnSubConstant();
	void OnAndOperate();
	void OnOrOperate();
	void OnXorOperate();
	void OnGammaCorrection();
	void OnPractice2();
	void OnPosterizing();
	void OnBitSlicing();
};
