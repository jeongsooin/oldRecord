
// ImageProcessingView.cpp : CImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CImageProcessingView ����/�Ҹ�

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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageProcessingView �׸���

void CImageProcessingView::OnDraw(CDC* pDC) //pDC ����̽� ��Ʈ�� ������
{
	//----- By Prof. Kim Byung-Gyu on 2011. 03 16 ----// 
	CImageProcessingDoc* pDoc = GetDocument(); 
	ASSERT_VALID(pDoc); 
	
	// OnDraw 2) : ȭ�鿡 ����� ����ϴ� �Լ� 
	if(pDoc->m_InImg==NULL) 
		return; 
	height = pDoc->dibHi.biHeight; 
	width = pDoc->dibHi.biWidth; 
	rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth); 
	BmInfo->bmiHeader = pDoc->dibHi; 
	// ȭ�鿡 �׸��� API
	SetDIBitsToDevice(pDC->GetSafeHdc(),0,0,width,height, 0,0,0,height,pDoc->m_InImg,BmInfo, DIB_RGB_COLORS); 
	//  �ڵ带 ���� �׻� ȭ�鿡 �׸��� ���۴� m_InImg�ۿ� ����
	// ���� ó���ϰ� ���� �׻� m_InImg ���۷� copy �� ��� ��.
}                                                                
                                                              
// CImageProcessingView �μ�


void CImageProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CImageProcessingView ����

#ifdef _DEBUG
void CImageProcessingView::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessingDoc* CImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessingDoc)));
	return (CImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessingView �޽��� ó����



void CImageProcessingView::OnBasicProcessing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnBinarization(); // Doc Ŭ������ �Լ� ȣ��
	
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnZoomin()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnZoomIn();

	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnImageMod()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnImageMod();

	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnHistoStretch()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	// Document Ŭ������ �Լ� ȣ��
	pDoc->OnHistoStretch();

	Invalidate(TRUE); //ȭ�� ����
}



void CImageProcessingView::OnHistoEqual()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	// Document Ŭ������ �Լ� ȣ��
	pDoc->OnHistoEqual();

	Invalidate(TRUE); //ȭ�� ����
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
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	
	pDoc->OnImagecopy();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnNegaTransform()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnNegaTransform();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnSumConstant()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnSumConstant();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnSubConstant()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnAndOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnOrOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnXorOperate()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnXorOperate();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnGammaCorrection()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnGammaCorrection();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnPractice2()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnPractice2();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnPosterizing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnPosterizing();
	Invalidate(TRUE); //ȭ�� ����
}


void CImageProcessingView::OnBitSlicing()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnBitSlicing();
	Invalidate(TRUE); //ȭ�� ����
}

void CImageProcessingView::OnRedcolor()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);

	pDoc->OnRedColor(); // �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);
	//<== ������ Doc.(������)�� ���, Bit�� ������ �����͸� ��� ���ۿ� ������ //
	//<== ���� Bit���� �Է� Buffer�� ���� ���־�� �� //
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}

void CImageProcessingView::OnBlurring()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->ColorBlurring(); // Ȯ�� �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);  // ���⼭ ��µǴ� m_InImg ���۴� ���������� �ٸ� ���� 
	//AfxGetMainWnd �� ���������� Ŭ���� �����͸� ��ȯ�Ѵ�. ���� ���� �����ڷ� SendMessage ȣ�������� �����Ͱ���.  
}


void CImageProcessingView::OnEdge()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnEdge(); // Ȯ�� �Լ� ȣ��
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnLaplacian()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnLaplacian(); 
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnBlurrgaussian()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnBlurrgaussian();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnSharpMask()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnSharpMask();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnHpfFilterSharp()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnHpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}


void CImageProcessingView::OnLpfFilterSharp()
{
	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
	ASSERT_VALID(pDoc);
	pDoc->OnLpfFilterSharp();
	pDoc->CopyClipboard(pDoc->m_OutputImage, pDoc->dibHi.biHeight, pDoc->dibHi.biWidth, 24);

	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);
}
