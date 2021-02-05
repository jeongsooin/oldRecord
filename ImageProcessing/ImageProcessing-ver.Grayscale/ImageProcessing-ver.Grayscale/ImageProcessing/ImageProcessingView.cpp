
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
END_MESSAGE_MAP()

// CImageProcessingView ����/�Ҹ�

CImageProcessingView::CImageProcessingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingView::~CImageProcessingView()
{
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
	CImageProcessingDoc* pDoc = GetDocument(); //��ť��Ʈ Ŭ������ �����ͷ� �����ؼ� �����
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, j; //������ ����,���� ��                                  // 1. �迭�� ��ü ũ��  = m_InputImage[m_size] (1���� �迭)	
	unsigned char R, G, B;                                           // 2. ȭ�鿡�� 2�������� ��Ÿ���� ��.
	for (i = 0; i<pDoc->m_height; i++) {                             // 3. ���� i*pDoc->m_width + j�� ������ �迭�� �ε����� i,j�� ǥ���ϰڴٴ� �ǹ��̴�.
		for (j = 0; j<pDoc->m_width; j++) {                          // 4. i*pDoc->m_width = ������ ( i�� 0�϶��� ù��° ��, 1�϶��� �ι�° ��..)
			R = pDoc->m_InputImage[i*pDoc->m_width + j]        ; 	 // 5. �ű⿡ +j �ϹǷ� n��° ���� n��° �ε����� �ǹ��ϰ� �Ǵ� ��.  
			G = B = R;											     // => 1���� �迭�� 2���� �迭ó�� ����ϴ� ���!
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));               // �ٵ� �˰����� ���� for ������ n2�� ȿ���̶� ������ ������ ��..
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



//void CImageProcessingView::OnImagecopy()
//{
//	CImageProcessingDoc* pDoc = GetDocument(); // Doc Ŭ���� ����
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnImagecopy();
//
//	Invalidate(TRUE); //ȭ�� ����
//}



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
