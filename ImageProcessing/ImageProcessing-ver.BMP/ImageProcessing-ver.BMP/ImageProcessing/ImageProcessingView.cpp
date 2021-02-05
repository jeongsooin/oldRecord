
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
ON_COMMAND(ID_RedColor, &CImageProcessingView::OnRedcolor)
ON_COMMAND(ID_BLURRING, &CImageProcessingView::OnBlurring)
ON_COMMAND(ID_EDGE, &CImageProcessingView::OnEdge)
ON_COMMAND(ID_LAPLACIAN, &CImageProcessingView::OnLaplacian)
ON_COMMAND(ID_BLURRGAUSSIAN, &CImageProcessingView::OnBlurrgaussian)
ON_COMMAND(ID_SHARP_MASK, &CImageProcessingView::OnSharpMask)
ON_COMMAND(ID_HPF_FILTER_SHARP, &CImageProcessingView::OnHpfFilterSharp)
ON_COMMAND(ID_LPF_FILTER_SHARP, &CImageProcessingView::OnLpfFilterSharp)
END_MESSAGE_MAP()

// CImageProcessingView 생성/소멸

CImageProcessingView::CImageProcessingView()
{
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	for (int i = 0; i<256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}

}

CImageProcessingView::~CImageProcessingView()
{
	if (BmInfo) delete BmInfo;
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
	//----- By Prof. Kim Byung-Gyu on 2011. 03 16 ----// 
	CImageProcessingDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	
	// OnDraw 2) : 화면에 출력을 담담하는 함수 
	if(pDoc->m_InImg==NULL) 
		return; 
	height = pDoc->dibHi.biHeight; 
	width = pDoc->dibHi.biWidth; 
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth); 
	BmInfo->bmiHeader = pDoc->dibHi; 
	// 화면에 그리는 API
	SetDIBitsToDevice(pDC->GetSafeHdc(),0,0,width,height, 0,0,0,height,pDoc->m_InImg,BmInfo, DIB_RGB_COLORS); 
	//  코드를 보면 항상 화면에 그리는 버퍼는 m_InImg밖에 없음
	// 따라서 처리하고 나면 항상 m_InImg 버퍼로 copy 해 줘야 함.
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

void CImageProcessingView::OnRedcolor()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);

	pDoc->OnRedColor(); // 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

void CImageProcessingView::OnBlurring()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->ColorBlurring(); // 확대 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);  // 여기서 출력되는 m_InImg 버퍼는 물리적으로 다른 버퍼 
	//AfxGetMainWnd 는 메인프레임 클래스 포인터를 반환한다. 간접 참조 연산자로 SendMessage 호출했으니 포인터겠지.  
}


void CImageProcessingView::OnEdge()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnEdge(); // 확대 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnLaplacian()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian(); 
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnBlurrgaussian()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBlurrgaussian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnSharpMask()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnSharpMask();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnHpfFilterSharp()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnLpfFilterSharp()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}
