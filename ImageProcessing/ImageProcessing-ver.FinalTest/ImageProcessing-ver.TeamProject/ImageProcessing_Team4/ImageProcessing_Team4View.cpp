
// ImageProcessing_Team4View.cpp : CImageProcessing_Team4View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_Team4.h"
#endif

#include "ImageProcessing_Team4Doc.h"
#include "ImageProcessing_Team4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessing_Team4View

IMPLEMENT_DYNCREATE(CImageProcessing_Team4View, CView)

BEGIN_MESSAGE_MAP(CImageProcessing_Team4View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageProcessing_Team4View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_IMAGE_SEGMENTATION, &CImageProcessing_Team4View::OnImageSegmentation)
	ON_COMMAND(ID_IMAGECLEAR, &CImageProcessing_Team4View::OnImageclear)
	ON_COMMAND(ID_BLURRING, &CImageProcessing_Team4View::OnBlurring)
	ON_COMMAND(ID_BLURR_GAUSSIAN, &CImageProcessing_Team4View::OnBlurrGaussian)
	ON_COMMAND(ID_SHARP_MASK, &CImageProcessing_Team4View::OnSharpMask)
	ON_COMMAND(ID_HPF_FILTER_SHARP, &CImageProcessing_Team4View::OnHpfFilterSharp)
	ON_COMMAND(ID_LPF_FILTER_SHARP, &CImageProcessing_Team4View::OnLpfFilterSharp)
	ON_COMMAND(ID_EDGE, &CImageProcessing_Team4View::OnEdge)
	ON_COMMAND(ID_LAPLACIAN, &CImageProcessing_Team4View::OnLaplacian)
	ON_COMMAND(ID_SCALE_DOWN, &CImageProcessing_Team4View::OnScaleDown)
	ON_COMMAND(ID_NEAR_SCALE_UP, &CImageProcessing_Team4View::OnNearScaleUp)
	ON_COMMAND(ID_BILINEAR_SCALE_UP, &CImageProcessing_Team4View::OnBilinearScaleUp)
	ON_COMMAND(ID_HPF_SHARP, &CImageProcessing_Team4View::OnHpfSharp)
	ON_COMMAND(ID_LPF_SHARP, &CImageProcessing_Team4View::OnLpfSharp)
	ON_COMMAND(ID_FFT2D, &CImageProcessing_Team4View::OnFft2d)
	ON_COMMAND(ID_IFFT_2D, &CImageProcessing_Team4View::OnIfft2d)
	ON_COMMAND(ID_LPF_FREQUENCY, &CImageProcessing_Team4View::OnLpfFrequency)
END_MESSAGE_MAP()

// CImageProcessing_Team4View 생성/소멸

CImageProcessing_Team4View::CImageProcessing_Team4View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
	for (int i = 0; i<256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
	//------------------------------------------------------//
}

CImageProcessing_Team4View::~CImageProcessing_Team4View()
{
	if (BmInfo) delete BmInfo;
	//------------------------------------------------------//
}

BOOL CImageProcessing_Team4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessing_Team4View 그리기

void CImageProcessing_Team4View::OnDraw(CDC* pDC)
{
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// OnDraw 2) : 화면에 출력을 담당하는 함수
	if (pDoc->m_InImg == NULL)
		return;

	height = pDoc->dibHi.biHeight;
	width = pDoc->dibHi.biWidth;
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

	BmInfo->bmiHeader = pDoc->dibHi;

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);

}


// CImageProcessing_Team4View 인쇄


void CImageProcessing_Team4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessing_Team4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessing_Team4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessing_Team4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageProcessing_Team4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageProcessing_Team4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageProcessing_Team4View 진단

#ifdef _DEBUG
void CImageProcessing_Team4View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessing_Team4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessing_Team4Doc* CImageProcessing_Team4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessing_Team4Doc)));
	return (CImageProcessing_Team4Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessing_Team4View 메시지 처리기


//영상 분할
void CImageProcessing_Team4View::OnImageSegmentation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnImageSegmentation(); // 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 선명화
void CImageProcessing_Team4View::OnImageclear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnImageclear(); // 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//영상 블러링(3x3 마스크)
void CImageProcessing_Team4View::OnBlurring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->ColorBlurring();  // 함수 호출
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 블러링(가우시안)
void CImageProcessing_Team4View::OnBlurrGaussian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBlurrgaussian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 샤프닝마스크
void CImageProcessing_Team4View::OnSharpMask()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnSharpMask();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 고주파 필터 샤프닝
void CImageProcessing_Team4View::OnHpfFilterSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnHpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 저주파 필터 샤프닝
void CImageProcessing_Team4View::OnLpfFilterSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 에지검출(수평필터)
void CImageProcessing_Team4View::OnEdge()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnEdge();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 에지검출(라플라시안)
void CImageProcessing_Team4View::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//고주파 대역 필터링
void CImageProcessing_Team4View::OnHpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//저주파 대역 필터링
void CImageProcessing_Team4View::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//영상 축소
void CImageProcessing_Team4View::OnScaleDown()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnScalingDown();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 확대 - 인접한 이웃 화소 보간법
void CImageProcessing_Team4View::OnNearScaleUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnNearScaleUp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//영상 확대 - 양선형 보간법 이용
void CImageProcessing_Team4View::OnBilinearScaleUp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnBilinearScaleUp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}



void CImageProcessing_Team4View::OnFft2d()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnFft2d();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessing_Team4View::OnIfft2d()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnIfft2d();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessing_Team4View::OnLpfFrequency()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc 클래스 참조
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFrequency();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== 독립된 Doc.(윈도우)를 열어서, Bit맵 정보와 데이터를 출력 버퍼에 복사함 //
	//<== 최종 Bit수는 입력 Buffer와 같게 해주어야 함 //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}
