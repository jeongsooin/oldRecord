
// ImageProcessing_Team4Doc.h : CImageProcessing_Team4Doc Ŭ������ �������̽�
//


#pragma once


class CImageProcessing_Team4Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageProcessing_Team4Doc();
	DECLARE_DYNCREATE(CImageProcessing_Team4Doc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

	int m_Re_size;
	int m_Re_height;
	int m_Re_width;
	unsigned char* m_OutputImage;
	//void OnDownSampling();
	int m_width;
	int m_height;
	int m_size;
	unsigned char* m_InputImage;

	//ȭ�� ���� ó�� ���� �Լ� ����
	double** m_tempImage;
	int avg;

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
	//BMP���� ����
	int ImgType;
	int height, width;
	RGBQUAD palRGB[256];
	BITMAPINFOHEADER dibHi;
	BITMAPFILEHEADER dibHf;

	BYTE *m_InImg, *m_OutImg, *m_COrigin;
	BYTE *m_GrayImg1, *m_GrayImg2;
	BYTE *m_R, *m_G, *m_B;
	int *m_mRGB;

	//���� ���� ����
	double **m_tempImageR, **m_tempImageG, **m_tempImageB;

	struct Complex {
		double Re;
		double Im;
	};
	Complex **m_FFT;
	Complex **m_IFFT;
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
	virtual ~CImageProcessing_Team4Doc();
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
	virtual void CopyClipboard(BYTE *m_CpyImg, int height, int width, int biBitCount);

	double** OnMaskProcess(unsigned char *Target, double Mask[3][3]);
	double** Image2DMem(int height, int width);

	void OnImageSegmentation(); //���� ����
	void OnImageclear();//���� ����ȭ

	void ColorBlurring(); //����(3x3����ũ)
	void OnBlurrgaussian(); //����(����þ�)
	void OnSharpMask(); //�����׸���ũ
	void OnHpfFilterSharp(); //������ ���� ������
	void OnLpfFilterSharp(); //������ ���� ������
	void OnLaplacian(); //��������(���ö�þ�)
	void OnEdge(); //��������(��������)

	void OnHpfSharp(); //������ �뿪 ���͸�
	void OnLpfSharp(); //������ �뿪 ���͸�

	void OnScalingDown(); //���� ���
	void OnBubleSort(double * A, int MAX);
	void OnSwap(double *a, double *b);
	void OnNearScaleUp(); //���� Ȯ��-����ȭ�Һ���
	void OnBilinearScaleUp(); //���� Ȯ��-�缱������
	void OnFft2d();
	void OnFft1d(Complex* X, int N, int Log2N);
	void OnShuffle(Complex* X, int N, int Log2N);
	void OnButterfly(Complex* X, int N, int Log2N, int mode);
	int OnReverseBitOrder(int index, int Log2N);
	void OnIfft2d();
	void OnIfft1d(Complex* X, int N, int Log2N);
	void OnLpfFrequency();
};
