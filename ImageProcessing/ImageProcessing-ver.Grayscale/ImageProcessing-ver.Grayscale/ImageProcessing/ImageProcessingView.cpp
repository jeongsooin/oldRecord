
// ImageProcessingView.cpp : CImageProcessingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include "ImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessingView

IMPLEMENT_DYNCREATE(CImageProcessingView, CView)

BEGIN_MESSAGE_MAP(CImageProcessingView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_COMMAND(ID_32771, &CImageProcessingView::OnBasicProcessing)
//ON_COMMAND(ID_BasicBinarization, &CImageProcessingView::OnBasicbinarization)
//ON_COMMAND(ID_BasicBinarization, &CImageProcessingView::OnBasicbinarization)
//ON_COMMAND(ID_BasicBinarization, &CImageProcessingView::OnBasicbinarization)
ON_COMMAND(ID_BasicBinarization, &CImageProcessingView::OnBasicProcessing)
ON_COMMAND(ID_ZoomIn, &CImageProcessingView::OnZoomin)
//ON_COMMAND(ID_ImageCopy, &CImageProcessingView::OnImagecopy)
ON_COMMAND(ID_IP1, &CImageProcessingView::OnImageMod)
ON_COMMAND(ID_IP1, &CImageProcessingView::OnImageMod)
ON_COMMAND(ID_HISTO_STRETCH, &CImageProcessingView::OnHistoStretch)
//ON_COMMAND(ID_END_IN_STRETCH, &CImageProcessingView::OnEndInStretch)
ON_COMMAND(ID_HISTO_EQUAL, &CImageProcessingView::OnHistoEqual)
//ON_COMMAND(ID_HISTOGRAM, &CImageProcessingView::OnHistogram)
//ON_UPDATE_COMMAND_UI(ID_HISTOGRAM, &CImageProcessingView::OnHistogram)
ON_COMMAND(ID_HISTOGRAM, &CImageProcessingView::OnHistogram)
ON_COMMAND(ID_HISTO_SPEC, &CImageProcessingView::OnHistoSpec)
ON_COMMAND(ID_PRACTICE1, &CImageProcessingView::OnPractice1)
ON_COMMAND(ID_EMBOSSING, &CImageProcessingView::OnEmbossing)
ON_COMMAND(ID_BLURR, &CImageProcessingView::OnBlurr)
ON_COMMAND(ID_GAUSSIAN_FILTER, &CImageProcessingView::OnGaussianFilter)
ON_COMMAND(ID_SHARPENING, &CImageProcessingView::OnSharpening)
ON_COMMAND(ID_HPF_SHARP, &CImageProcessingView::OnHpfSharp)
ON_COMMAND(ID_LPF_SHARP, &CImageProcessingView::OnLpfSharp)
ON_COMMAND(ID_IMAGE_COPY, &CImageProcessingView::OnImageCopy)
ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessingView::OnNegaTransform)
ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessingView::OnSumConstant)
ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessingView::OnSubConstant)
ON_COMMAND(ID_AND_OPERATE, &CImageProcessingView::OnAndOperate)
ON_COMMAND(ID_OR_OPERATE, &CImageProcessingView::OnOrOperate)
ON_COMMAND(ID_XOR_OPERATE, &CImageProcessingView::OnXorOperate)
ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessingView::OnGammaCorrection)
ON_COMMAND(ID_PRACTICE2, &CImageProcessingView::OnPractice2)
ON_COMMAND(ID_POSTERIZING, &CImageProcessingView::OnPosterizing)
ON_COMMAND(ID_BIT_SLICING, &CImageProcessingView::OnBitSlicing)
END_MESSAGE_MAP()

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessingView::~CImageProcessingView()
{
}

BOOL CImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView 그리기

void CImageProcessingView::OnDraw(CDC* pDC) //pDC 디바이스 컨트롤 포인터
{
	CImageProcessingDoc* pDoc = GetDocument(); //다큐먼트 클래스를 포인터로 참조해서 사용함
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, j; //영상의 가로,세로 축                                  // 1. 배열의 전체 크기  = m_InputImage[m_size] (1차원 배열)	
	unsigned char R, G, B;                                           // 2. 화면에는 2차원으로 나타내야 함.
	for (i = 0; i<pDoc->m_height; i++) {                             // 3. 따라서 i*pDoc->m_width + j는 일차원 배열의 인덱스를 i,j로 표현하겠다는 의미이다.
		for (j = 0; j<pDoc->m_width; j++) {                          // 4. i*pDoc->m_width = 가로줄 ( i가 0일때는 첫번째 줄, 1일때는 두번째 줄..)
			R = pDoc->m_InputImage[i*pDoc->m_width + j]        ; 	 // 5. 거기에 +j 하므로 n번째 줄의 n번째 인덱스를 의미하게 되는 것.  
			G = B = R;											     // => 1차원 배열을 2차원 배열처럼 사용하는 방법!
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));               // 근데 알고리즘이 이중 for 문으로 n2승 효율이라 느리고 안좋은 듯..
		}  
	}

	for (i = 0; i<pDoc->m_Re_height; i++) {                             
		for (j = 0; j<pDoc->m_Re_width; j++) {                         
			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j]; 	 
			G = B = R;											
			pDC->SetPixel(j + pDoc->m_width+10 , i + 5, RGB(R, G, B));
		}
	}

	for (i = 0; i < pDoc->m_Re_height2; i++) {
			for (j = 0; j < pDoc->m_Re_width2; j++) {
				R = pDoc->m_OutputImage2[i*pDoc->m_Re_width2 + j];
				G = B = R;
				pDC->SetPixel(j + 5, i + pDoc->m_height + 25, RGB(R, G, B));
			}
	}

	for (i = 0; i<pDoc->m_Re_height3; i++) {
		for (j = 0; j<pDoc->m_Re_width3; j++) {
			R = pDoc->m_OutputImage3[i*pDoc->m_Re_width3 + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + pDoc->m_height + 25, RGB(R, G, B));
		}
	}
}                                                                
                                                              
// CImageProcessingView 인쇄


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessingView 진단

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView 메시지 처리기



void CImageProcessingView::OnBasicProcessing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization(); // Doc 클래스의 함수 호출
	
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnZoomin()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn();

	Invalidate(TRUE); //화면 갱신
}



//void CImageProcessingView::OnImagecopy()
//{
//	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnImagecopy();
//
//	Invalidate(TRUE); //화면 갱신
//}



void CImageProcessingView::OnImageMod()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnImageMod();

	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnHistoStretch()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	// Document 클래스의 함수 호출
	pDoc->OnHistoStretch();

	Invalidate(TRUE); //화면 갱신
}



void CImageProcessingView::OnHistoEqual()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	// Document 클래스의 함수 호출
	pDoc->OnHistoEqual();

	Invalidate(TRUE); //화면 갱신
}

void CImageProcessingView::OnHistogram()
{
	CImageProcessingDoc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistogram();

	Invalidate(TRUE);
}


void CImageProcessingView::OnHistoSpec()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();
	Invalidate(TRUE);

}


void CImageProcessingView::OnPractice1()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnPractice1();
	Invalidate(TRUE);
}


void CImageProcessingView::OnEmbossing()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEmbossing();
	Invalidate(TRUE);
}


void CImageProcessingView::OnBlurr()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBlurr();
	Invalidate(TRUE);
}


void CImageProcessingView::OnGaussianFilter()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CImageProcessingView::OnSharpening()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnSharpening();
	Invalidate(TRUE);
}


void CImageProcessingView::OnHpfSharp()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingView::OnLpfSharp()
{
	CImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CImageProcessingView::OnImageCopy()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	
	pDoc->OnImagecopy();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnNegaTransform()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnSumConstant()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnSumConstant();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnSubConstant()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnAndOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnOrOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnXorOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnGammaCorrection()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnPractice2()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnPractice2();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnPosterizing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnPosterizing();
	Invalidate(TRUE); //화면 갱신
}


void CImageProcessingView::OnBitSlicing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnBitSlicing();
	Invalidate(TRUE); //화면 갱신
}
