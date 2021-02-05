
// ImageProcessing_Team4View.cpp : CImageProcessing_Team4View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CImageProcessing_Team4View ����/�Ҹ�

CImageProcessing_Team4View::CImageProcessing_Team4View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessing_Team4View �׸���

void CImageProcessing_Team4View::OnDraw(CDC* pDC)
{
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// OnDraw 2) : ȭ�鿡 ����� ����ϴ� �Լ�
	if (pDoc->m_InImg == NULL)
		return;

	height = pDoc->dibHi.biHeight;
	width = pDoc->dibHi.biWidth;
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

	BmInfo->bmiHeader = pDoc->dibHi;

	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);

}


// CImageProcessing_Team4View �μ�


void CImageProcessing_Team4View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessing_Team4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessing_Team4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessing_Team4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CImageProcessing_Team4View ����

#ifdef _DEBUG
void CImageProcessing_Team4View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessing_Team4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessing_Team4Doc* CImageProcessing_Team4View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessing_Team4Doc)));
	return (CImageProcessing_Team4Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessing_Team4View �޽��� ó����


//���� ����
void CImageProcessing_Team4View::OnImageSegmentation()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnImageSegmentation(); // �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ����ȭ
void CImageProcessing_Team4View::OnImageclear()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnImageclear(); // �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//���� ����(3x3 ����ũ)
void CImageProcessing_Team4View::OnBlurring()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->ColorBlurring();  // �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ����(����þ�)
void CImageProcessing_Team4View::OnBlurrGaussian()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnBlurrgaussian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� �����׸���ũ
void CImageProcessing_Team4View::OnSharpMask()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnSharpMask();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ������ ���� ������
void CImageProcessing_Team4View::OnHpfFilterSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnHpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ������ ���� ������
void CImageProcessing_Team4View::OnLpfFilterSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ��������(��������)
void CImageProcessing_Team4View::OnEdge()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnEdge();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� ��������(���ö�þ�)
void CImageProcessing_Team4View::OnLaplacian()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//������ �뿪 ���͸�
void CImageProcessing_Team4View::OnHpfSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHpfSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//������ �뿪 ���͸�
void CImageProcessing_Team4View::OnLpfSharp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnLpfSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


//���� ���
void CImageProcessing_Team4View::OnScaleDown()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnScalingDown();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� Ȯ�� - ������ �̿� ȭ�� ������
void CImageProcessing_Team4View::OnNearScaleUp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnNearScaleUp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

//���� Ȯ�� - �缱�� ������ �̿�
void CImageProcessing_Team4View::OnBilinearScaleUp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnBilinearScaleUp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}



void CImageProcessing_Team4View::OnFft2d()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnFft2d();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessing_Team4View::OnIfft2d()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnIfft2d();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessing_Team4View::OnLpfFrequency()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CImageProcessing_Team4Doc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFrequency();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->m_Re_height, pDoc->m_Re_width, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}
