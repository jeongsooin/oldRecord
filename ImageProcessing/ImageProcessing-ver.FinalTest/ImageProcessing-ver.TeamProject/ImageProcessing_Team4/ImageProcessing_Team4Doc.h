
// ImageProcessing_Team4Doc.h : CImageProcessing_Team4Doc 클래스의 인터페이스
//


#pragma once


class CImageProcessing_Team4Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessing_Team4Doc();
	DECLARE_DYNCREATE(CImageProcessing_Team4Doc)

// 특성입니다.
public:

// 작업입니다.
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

	//화소 영역 처리 관련 함수 선언
	double** m_tempImage;
	int avg;

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
	//BMP관련 변수
	int ImgType;
	int height, width;
	RGBQUAD palRGB[256];
	BITMAPINFOHEADER dibHi;
	BITMAPFILEHEADER dibHf;

	BYTE *m_InImg, *m_OutImg, *m_COrigin;
	BYTE *m_GrayImg1, *m_GrayImg2;
	BYTE *m_R, *m_G, *m_B;
	int *m_mRGB;

	//개인 지정 변수
	double **m_tempImageR, **m_tempImageG, **m_tempImageB;

	struct Complex {
		double Re;
		double Im;
	};
	Complex **m_FFT;
	Complex **m_IFFT;
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProcessing_Team4Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void CopyClipboard(BYTE *m_CpyImg, int height, int width, int biBitCount);

	double** OnMaskProcess(unsigned char *Target, double Mask[3][3]);
	double** Image2DMem(int height, int width);

	void OnImageSegmentation(); //영상 분할
	void OnImageclear();//영상 선명화

	void ColorBlurring(); //블러링(3x3마스크)
	void OnBlurrgaussian(); //블러링(가우시안)
	void OnSharpMask(); //샤프닝마스크
	void OnHpfFilterSharp(); //고주파 필터 샤프닝
	void OnLpfFilterSharp(); //저주파 필터 샤프닝
	void OnLaplacian(); //에지검출(라플라시안)
	void OnEdge(); //에지검출(수평필터)

	void OnHpfSharp(); //고주파 대역 필터링
	void OnLpfSharp(); //저주파 대역 필터링

	void OnScalingDown(); //영상 축소
	void OnBubleSort(double * A, int MAX);
	void OnSwap(double *a, double *b);
	void OnNearScaleUp(); //영상 확대-인접화소보간
	void OnBilinearScaleUp(); //영상 확대-양선형보간
	void OnFft2d();
	void OnFft1d(Complex* X, int N, int Log2N);
	void OnShuffle(Complex* X, int N, int Log2N);
	void OnButterfly(Complex* X, int N, int Log2N, int mode);
	int OnReverseBitOrder(int index, int Log2N);
	void OnIfft2d();
	void OnIfft1d(Complex* X, int N, int Log2N);
	void OnLpfFrequency();
};
