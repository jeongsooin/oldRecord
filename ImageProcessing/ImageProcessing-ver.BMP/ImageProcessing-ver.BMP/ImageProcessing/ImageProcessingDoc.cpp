
// ImageProcessingDoc.cpp : CImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
#include <afxwin.h>
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include <bitset>
#include <propkey.h>
#include "DiologZoomR.h" // 정의한 클래스 쓸 수 있게 헤더 추가
#include "DiaolgHIST.h"
#include "DialogIP.h"
#include "ConstantDlg.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessingDoc

IMPLEMENT_DYNCREATE(CImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessingDoc, CDocument)
END_MESSAGE_MAP()


// CImageProcessingDoc 생성/소멸

CImageProcessingDoc::CImageProcessingDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument()) 
		return FALSE; 
	
	// TODO: add reinitialization code here 
	// (SDI documents will reuse this document)
	::OpenClipboard(NULL); 
	if(!IsClipboardFormatAvailable(CF_DIB)) 
		return FALSE; 	
	HGLOBAL m_hImage = ::GetClipboardData(CF_DIB); 
	::CloseClipboard(); 

	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage); 

	memcpy(&dibHi,pDIB,sizeof(BITMAPINFOHEADER));
	height = dibHi.biHeight; width = dibHi.biWidth; 
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width); 
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256+rwsize*height*sizeof(char); //
	m_InImg = new unsigned char [dibHi.biSizeImage]; 
	m_OutImg = new unsigned char [dibHi.biSizeImage];

	if (dibHi.biBitCount == 8)
	{
		memcpy(palRGB, pDIB + sizeof(BITMAPINFOHEADER), sizeof(RGBQUAD) * 256);
		memcpy(m_InImg, pDIB + dwBitsSize - dibHi.biSizeImage, dibHi.biSizeImage);
	}
	else memcpy(m_InImg, pDIB + sizeof(BITMAPINFOHEADER), dibHi.biSizeImage);

	// BITMAP Filer Header파라메타의 설정
	dibHf.bfType = 0x4d42; // 'BM'
	dibHf.bfSize = dwBitsSize + sizeof(BITMAPFILEHEADER); // 전체파일 크기

	if (dibHi.biBitCount == 24) 
		dibHf.bfSize -= sizeof(RGBQUAD) * 256; // no pallette

	dibHf.bfOffBits = dibHf.bfSize - rwsize*height*sizeof(char);
	dibHf.bfReserved1 = dibHf.bfReserved2 = 0;

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcessingDoc 진단

#ifdef _DEBUG
void CImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessingDoc 명령


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) // IpszPathName = 파일 경로와 파일 이름, Ipsz 데이터형
{
	//----- Prof. Kim on 2011. 03. 17 ----------// 
	if (!CDocument::OnOpenDocument(lpszPathName)) 
		return FALSE; 
	// TODO: Add your specialized creation code here 
	CFile hFile; 
	hFile.Open(lpszPathName,CFile::modeRead | CFile::typeBinary); 
	hFile.Read(&dibHf,sizeof(BITMAPFILEHEADER)); // 파일 헤드를 읽음 
	if(dibHf.bfType!=0x4D42) 
	{
		AfxMessageBox((const char)"Not BMP file!!");
		return FALSE;
	} 
	//이 파일이 BMP파일인지 검사. 0x4d42=='BM' 
	hFile.Read(&dibHi,sizeof(BITMAPINFOHEADER)); 
	//"영상정보의 Header"를 읽는다. 
	if(dibHi.biBitCount!=8 && dibHi.biBitCount!=24) 
	{ 
		AfxMessageBox((const char)"Gray/True Color Possible!!"); 
		return FALSE; 
	} 
	if(dibHi.biBitCount==8) 
		hFile.Read(palRGB,sizeof(RGBQUAD)*256);
	// 메모리 할당 (바뀐 부분)

	int ImgSize;

	if (dibHi.biBitCount == 8) 
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);
	else if (dibHi.biBitCount == 24) 
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);

	m_InImg = new unsigned char[ImgSize]; //dibHi.biSizeImage
	m_OutImg = new unsigned char[ImgSize];
	m_COrigin = new unsigned char[ImgSize];

	hFile.Read(m_InImg, ImgSize);
	hFile.Close();

	height = dibHi.biHeight; width = dibHi.biWidth;
	if (dibHi.biBitCount == 24) return TRUE;

	// 영상데이터 대입
	int i, j, index;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);

	for (i = 0; i<height; i++) {
		index = i*rwsize;
		for (j = 0; j<width; j++)
			m_InImg[index + j] = (unsigned char)palRGB[(int)m_InImg[index + j]].rgbBlue;
	}

	ImgType = 0;

	if (dibHi.biBitCount == 8) 
		ImgType = 1;

	return TRUE;
}


void CImageProcessingDoc::OnBinarization()
{
	int i, value;
	m_size = m_height*m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_OutputImage = new unsigned char[m_size];
	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		if (value > 128)
			m_OutputImage[i] = (char)128;
		else
			m_OutputImage[i] = (char)50;
	}
}



void CImageProcessingDoc::OnZoomIn()
{
	CString msg;

	CDiologZoomR dlg;

	//m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	if (dlg.DoModal() == IDOK) // DoModal() -> 내장 API(윈도우를 띄워준다.) IDOK = 확인버튼
	{
		m_Re_height = m_height * dlg.m_ZoomIn;
		m_Re_width = m_Re_width * dlg.m_ZoomIn;
		m_Re_size = m_Re_height*m_Re_width;
		m_OutputImage = new unsigned char [m_Re_size];

		for (int i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0;

		for (int i = 0; i < m_height; i++)
		{
			for (int j = 0; j < m_width; j++)
			{
				m_OutputImage[i*dlg.m_ZoomIn*m_Re_width + dlg.m_ZoomIn*j] = m_InputImage[i*m_width + j];
				// 재배치 하여 영상 확대
			}
		}

	}
}


void CImageProcessingDoc::OnImagecopy()
{
	int i;
	m_size = m_width*m_height;

	m_OutputImage = new unsigned char[m_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = m_InputImage[i];
            
}



void CImageProcessingDoc::OnImageMod()
{
	CString msg;
	DialogIP dlg;
	if (dlg.DoModal() == IDOK) // DoModal() -> 내장 API(윈도우를 띄워준다.) IDOK = 확인버튼
	{
		msg.Format(L"입력한 변수 = %2d,%2d", dlg.T1,dlg.T2); // Format() => 마찬가지로 CString 클래스의 내장 API
		AfxMessageBox(msg);
	}

	int i, value;
	m_size = m_height*m_width;
	m_size = m_height*m_width;
	m_Re_size = m_size;
	m_Re_height = m_height;
	m_Re_width = m_width;

	m_OutputImage = new unsigned char[m_size];

	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		if (value > dlg.T2)
			m_OutputImage[i] = (char)200;
		else if (value < dlg.T1)
			m_OutputImage[i] = (char)50;
		else
			m_OutputImage[i] = m_InputImage[i];
	}

}


void CImageProcessingDoc::OnHistoStretch()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	//입력 영상 최소값 찾기

	for (i = 0 ;i <m_size ; i++)
	{
		if (m_InputImage[i] < MIN )
			MIN = m_InputImage[i];
	}
	
	// 입력 영상 최대값 찾기
	for (i = 0; i <m_size; i++)
	{
		if ( m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	//출력 영상 버퍼 할당
	m_OutputImage = new unsigned char[m_Re_size];

	// 히스토그램 스트레칭
	for (i = 0; i < m_size; i++)
	{
		m_OutputImage[i] = (unsigned char)(255 * (m_InputImage[i] - MIN) / (MAX - MIN));
	}
}



void CImageProcessingDoc::OnHistoEqual()
{
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	//빈도 수 조사 : 히스토그램 생성
	for (i = 0; i < m_size; i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//누적 히스토그램 생성
	for (i = 0; i < 256; i++)
	{
		SUM += m_HIST[i];
		m_Sum_of_HIST[i] = SUM;
	}
	//출력 영상 버퍼 할당
	m_OutputImage = new unsigned char[m_Re_size];

	//입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++)
	{
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}
}

void CImageProcessingDoc::OnHistogram()
{
	// 히스토그램의 값은 0~255 
	// 히스토그램의 크기 값을 MAX=255로 정규화하여 출력 
	// 히스트그램의 크기 : 256*256 지정 

	int i, j, value;    unsigned char LOW, HIGH;    double MAX, MIN, DIF;
	m_Re_height = 256;    
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// 초기화 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사: 히스토그램 생성 // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];
	
	for (i = 0; i < m_Re_size; i++)
		m_OutputImage[i] = 255;

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < m_Scale_HIST[i]; j++)
		{
			m_OutputImage[m_Re_width*(m_Re_height-j)+i] = 0;
		}
	}

	// 히스토그램을 출력하고 그 아래 부분에 히스토그램의 색을 표시
	for (i = m_Re_height; i<m_Re_height + 5; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage[m_Re_height * i + j] = 255;
		}
	}
	for (i = m_Re_height + 5; i<m_Re_height + 20; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage[m_Re_height * i + j] = j;
		}
	}

	m_Re_height = m_Re_height + 20;
	m_Re_size = m_Re_height*m_Re_width;
}


void CImageProcessingDoc::OnHistoSpec()
{
	int i, value, Dvalue, top, bottom, DADD;
	unsigned char *m_DTEMP, m_Sum_Of_ScHIST[256], m_TABLE[256];    
	unsigned char LOW, HIGH, Temp, *m_Org_Temp;
	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;    
	double DMAX, DMIN;
	top = 255;   
	bottom = top - 1;
	m_Re_height = m_height;    
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];    
	m_Org_Temp = new unsigned char[m_size];

	CFile File;
	CFileDialog OpenDlg(TRUE);

	CString msg;
	msg = "Image size not matched";
	// 원하는 히스토그램이 있는 영상을 입력받음 
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(msg);
			// 같은 크기의 영상을 대상으로 함 
			return;
		}
	}

	LOW = 0;
	HIGH = 255;

	// 초기화 
	for (i = 0; i<256; i++) {
		m_HIST[i] = LOW;       m_DHIST[i] = LOW;       m_TABLE[i] = LOW;
	}
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];       m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];       m_DHIST[Dvalue]++;
	}

	// 누적 히스토그램 조사 
	for (i = 0; i<256; i++) {
		SUM += m_HIST[i];       
		m_Sum_of_HIST[i] = SUM;       
		DSUM += m_DHIST[i];      
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// 원본 영상의 평활화 
	for (i = 0; i<m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}

	// 누적 히스토그램에서 최소값과 최대값 지정 
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];

	// 원하는 영상을 평활화 //    
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN)*HIGH / (DMAX - DMIN));
	}

    // 룩업테이블을 이용한 명세화 // 
	for (; ; ) {
		for (i = m_Sum_Of_ScHIST[bottom]; i <= m_Sum_Of_ScHIST[top]; i++) {
			m_TABLE[i] = top;}
	top = bottom;     	
	bottom = bottom - 1;

	if (bottom < -1)
		break;
	}
	
	for (i = 0; i<m_size; i++) {
		DADD = (int)m_Org_Temp[i];       m_OutputImage[i] = m_TABLE[DADD];} 
}

void CImageProcessingDoc::OnPractice1()
{
	CString msg;
	CDiaolgHIST dlg;

	int i;
	double y1, y2;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) // DoModal() -> 내장 API(윈도우를 띄워준다.) IDOK = 확인버튼
	{
		y1 = 0.5 * dlg.m_x1;
		y2 = (0.5 * dlg.m_x2)+(255/2);
	}
	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] >= 0 && m_InputImage[i] < dlg.m_x1)
			m_OutputImage[i] = (y1 / dlg.m_x1)*m_InputImage[i];
		else if (m_InputImage[i] >= dlg.m_x1 && m_InputImage[i] < dlg.m_x2)
			m_OutputImage[i] = ((y2 - y1) / (dlg.m_x2 - dlg.m_x1)) * (m_InputImage[i] - dlg.m_x1) + y1;
		else if (m_InputImage[i] >= dlg.m_x2 && m_InputImage[i] <= 255)
			m_OutputImage[i] = ((255 - y2) / (255 - dlg.m_x2))*(m_InputImage[i] - dlg.m_x2) + y2;

	}

}

void CImageProcessingDoc::OnEmbossing()
{
	int i, j, sum,avg ;
	double EmboMask[3][3] = { { -1., 0., 0. },{ 0., 0., 0. },{ 0., 0., 1. } };
	// 마스크선택 : 여러가지 종류의 마스크 중에 하나 선택
	// double EmboMask[3][3] = {{0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.}}; // 계수의 합이 1이므로 회선 처리해도 평균 밝기 값 그대로 유지
	// double EmboMask[3][3] = {{1., 1., 1.}, {1., -8.,1.}, {1., 1., 1.}}; // 계수의 합이 0 이므로 경계 부분만 검출 된다.
	/* 엠보싱 회선 마스크는 계수의 합이 0이고, 가운데 값도 0이다. */
	/* 엠보싱 마스크의 특징 : 가운데에 있는 계수가 다른 계수를 상쇄시키도록 구성한다. 경계선에서 양각의 효과를 얻을 수 있다. */
	/* 마스크에 음수가 있으므로 회선 처리로 생성된 영상의 화소 값은 음수다. 따라서 처리 후 일정한 상수 값을 더해주어야 한다. */
	/* 8비트 그레이 레벨에서 회선 처리 수행한다면 최대 밝기 화소값의 절반인 128을 더해주면 양의 값을 만들 수 있다. */

	/* 출력 이미지 버퍼 크기 설정*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* 출력 이미지 버퍼와 임시 이미지 버퍼 할당*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);//회선처리
    
	sum = 0;
	avg = 0;
	/* 원본 영상 평균값 계산 */
	for (i = 0; i<m_Re_size; i++)
		sum += (int)m_InputImage[i]; // 일단 누적합을 구한다.
	avg = (int)(sum / m_Re_size);    // 누적합을 전체 픽셀 수로 나눈다. 

	/* 회선 처리 결과가 0~ 255 사이 값이 되도록 한다. */
	/* 회선 처리는 이미 위에서 함수 호출로 되어있는 상태이다. */
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	} 

	  // 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// 회선 처리가 일어나는 함수이다. 
double** CImageProcessingDoc::OnMaskProcess(unsigned char* Target, double  Mask[3][3])
{
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	/* 입력값을 위한 메모리 할당 */
	tempInputImage = Image2DMem(m_height + 2, m_width + 2); // 마스크 처리 해야 하기 때문에 테두리에 한칸 씩 더 줌(패딩)

	/* 출력값을 위한 메모리 할당*/
	tempOutputImage = Image2DMem(m_height, m_width);

	// 1차원입력영상m_InputImage[]의값을2차원배열tempInputImage[][]에할당
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	// 회선연산 => 마스크 크기 바뀌면 3중&4중 루프의 변수 크기 달라짐
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			for (n = 0; n<3; n++) {
				for (m = 0; m<3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			} // 회선마스크의크기만큼이동하면서값을누적
			tempOutputImage[i][j] = S; // 누적된값을출력메모리에저장
			S = 0.0; // 다음블록으로이동하면누적값을초기화. 반드시 잊지 말 것!
		}
	}
	return tempOutputImage; // 결과버퍼반환
}

//2차원 배열을 할당하는 함수이다.
double** CImageProcessingDoc::Image2DMem(int height, int width)
{
	double** temp;
	int i, j;
	temp = new double *[height];
	for (i = 0; i<height; i++) {
		temp[i] = new double[width];
	}
	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			temp[i][j] = 0.0;
		}
	} // 할당된2차원메모리를초기화
	return temp;
}

// 정규화를 하는 함수이다.
double** CImageProcessingDoc::OnScale(double** Target, int height, int width)
{
	// 일반적인 정규화랑 같고 그걸 2차원 배열에서 하려고 함수로 만든 것. 
	int i, j;
	double min, max;
	min = max = Target[0][0];
	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			if (Target[i][j] <= min)
				min = Target[i][j];
		}
	}
	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			if (Target[i][j] >= max)
				max = Target[i][j];
		}
	}
	max = max - min;
	for (i = 0; i<height; i++) {
		for (j = 0; j<width; j++) {
			Target[i][j] = (Target[i][j] - min) * (255. / max);
		}
	}
	return Target;
}


void CImageProcessingDoc::OnBlurr()
{
	int i, j;
	double BlurrMask[3][3] = { { 1./9., 1./9., 1./9. },{ 1./9., 1./9., 1./9. },{ 1./9., 1./9., 1./9. } };
	// 만약 마스크 사이즈 바꾸면? -> 블러 마스크 재정의 / OnMaskProcess 매개변수& 회선연산 재정의
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* 출력 이미지 버퍼와 임시 이미지 버퍼 할당*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);//회선처리

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CImageProcessingDoc::OnGaussianFilter()
{
	int i, j;
	double GaussianMask[3][3] = { { 1. / 16., 1. / 8., 1. / 16. },{ 1. / 8., 1. / 4., 1. / 8. },{ 1. / 16., 1. / 8., 1. / 16. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* 출력 이미지 버퍼와 임시 이미지 버퍼 할당*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);//회선처리

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}

}

void CImageProcessingDoc::OnSharpening()
{
	int i, j;
	double SharpeningMask[3][3] = { { 0., -1., 0. },{ -1., 5., -1. },{ 0., -1., 0. } };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* 출력 이미지 버퍼와 임시 이미지 버퍼 할당*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);//회선처리

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}

}


void CImageProcessingDoc::OnHpfSharp()
{
	/* 고주파 필터의 마스크는 합이 0으로 샤프닝 회선 마스크하고는 다르지만, 나머지 동작 특성은 같음 */
	/* 고주파 성분은 통과시키고 저주파 성분은 차단*/
	/* 가운데 큰 양수 값과 주변의 작은 음수 값으로 마스크 되어 경계선을 더욱 두드러지게 함 */
	int i, j;
	double HpfSharpMask[3][3] = { { -1. / 9., -1. / 9., -1. / 9. },
	{ -1. / 9., 8. / 9., -1. / 9. },{ -1. / 9., -1. / 9., -1. / 9. } };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	// 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CImageProcessingDoc::OnLpfSharp()
{

	ConstantDlg dlg;
	int i, j,alpha;
	double LpfSharpMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. }, { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_Constant;
		// 대화상자를이용하여상수를입력받는다.
	}
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask); // 원영상에서 뺄셈할 저주파 통과 필터링 영상

	/* 고주파 지원 필터 처리 */
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			m_tempImage[i][j] = (alpha * m_InputImage[i*m_width + j]) - (unsigned char)m_tempImage[i][j];
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	// 2차원배열m_tempImage[][] 데이터를1차원배열m_OutputImage[]로복사
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CImageProcessingDoc::OnNegaTransform()
{
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
	{
		m_OutputImage[i] = 255 - m_InputImage[i];
	}
}


void CImageProcessingDoc::OnSumConstant()
{
	ConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = unsigned char (m_InputImage[i] + dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnSubConstant()
{
	ConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = unsigned char(m_InputImage[i] - dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnAndOperate()
{
	ConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i]&(unsigned char)dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnOrOperate()
{
	ConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ( (m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnXorOperate()
{
	ConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255)
				m_OutputImage[i] = 255;
			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0)
				m_OutputImage[i] = 0;
			else
				m_OutputImage[i] = (m_InputImage[i] ^ (unsigned char)dlg.m_Constant);
		}
	}
}


void CImageProcessingDoc::OnGammaCorrection()
{
	ConstantDlg dlg;

	int i;
	double temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK)
	{
		for (i = 0; i < m_size; i++)
		{
			temp = pow(m_InputImage[i], (1 / dlg.m_Constant));

			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
}


void CImageProcessingDoc::OnPractice2()
{
	int LOW, HIGH, MIN,MAX, i,j,value,DIF;
	double SUM = 0.0;
	unsigned char Temp;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_Re_height2 = 256;
	m_Re_width2 = 256;
	m_Re_size2 = m_Re_height2*m_Re_width2;

	m_Re_height3 = 256;
	m_Re_width3 = 256;
	m_Re_size3 = m_Re_height3*m_Re_width3;

	LOW = 0;
	HIGH = 255;

	//초기화
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	//빈도 수 조사 : 히스토그램 생성
	for (i = 0; i < m_size; i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//누적 히스토그램 생성
	for (i = 0; i < 256; i++)
	{
		SUM += m_HIST[i];
		m_Sum_of_HIST[i] = SUM;
	}
	//출력 영상 버퍼 할당
	m_OutputImage = new unsigned char[m_Re_size];

	//입력 영상을 평활화된 영상으로 출력
	for (i = 0; i < m_size; i++)
	{
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}

	// 초기화 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사: 히스토그램 생성 // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// 정규화 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	m_OutputImage2 = new unsigned char[m_Re_size2 + (256 * 25)];

	for (i = 0; i < m_Re_size2; i++)
		m_OutputImage2[i] = 255;

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < m_Scale_HIST[i]; j++)
		{
			m_OutputImage2[m_Re_width2*(m_Re_height2 - j) + i] = 0;
		}
	}
	for (i = m_Re_height2 ; i<m_Re_height2 + 5 ; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage2[m_Re_height2 * i + j] = 255;
		}
	}
	for (i = m_Re_height2 + 5; i<m_Re_height2 + 20 ; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage2[m_Re_height2 * i + j] = j;
		}
	}

	m_Re_height2 = m_Re_height2 + 20;
	m_Re_size2 = m_Re_height2*m_Re_width2;

	// 초기화 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// 빈도 수 조사: 히스토그램 생성 // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_OutputImage[i];
		m_HIST[value]++;
	}
	// 정규화 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// 정규화된 히스토그램
	for (i = 0; i < 256; i++)
		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

	m_OutputImage3 = new unsigned char[m_Re_size3 + (256 * 20)];

	for (i = 0; i < m_Re_size3; i++)
		m_OutputImage3[i] = 255;

	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < m_Scale_HIST[i]; j++)
		{
			m_OutputImage3[m_Re_width3*(m_Re_height3 - j) + i] = 0;
		}
	}

	for (i = m_Re_height3 ; i<m_Re_height3 + 5; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage3[(m_Re_height3 * i) + j] = 255;
		}
	}
	for (i = m_Re_height3+5 ; i<m_Re_height3 +20; i++) {
		for (j = 0; j<256; j++) {
			m_OutputImage3[(m_Re_height3 * i) + j] = j;
		}
	}

	m_Re_height3 = m_Re_height3 + 20;
	m_Re_size3 = m_Re_height3*m_Re_width3;
}


void CImageProcessingDoc::OnPosterizing()
{
	ConstantDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		int i, j, value, LEVEL;
		double HIGH,*TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height*m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		TEMP = new double[m_size]; // 입력 영상 크기와 동일한 메모리 할당

		LEVEL = 256; // 원본 영상의 양자화 단계
		HIGH = 256.;

		value = (int)pow(2, dlg.m_Constant); // 양자화 단계를 입력 받은 변수로 결정

		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < value; j++)
			{
				if ((m_InputImage[i] >= (LEVEL / value)*j) && (m_InputImage[i] < (LEVEL / value)*(j + i)))
				{
					TEMP[i] = (double)(HIGH / value)*j; // 양자화 값보다 작거나 크면 양자화 수행
				}
			}
		}
		for (i = 0; i < m_size; i++)
		{
			m_OutputImage[i] = (unsigned char)TEMP[i]; // 반드시 타입 캐스팅 잊지 말 것 
		}
	}
}


void CImageProcessingDoc::OnBitSlicing()
{
	ConstantDlg dlg;
	int i,binary = 0;
	int num, result = 0;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height*m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		num = (int)dlg.m_Constant;
		if (num == 6)
			result = 0x20;
		for (i = 1; num > 0; i * 10)
		{
			binary = num % 2;
			result += binary * i;
			num /= 2;
		}
	}
	for (int i = 0; i < m_size; i++)
	{
		//std::bitset<8> bit;
		//bit = std::bitset<8>(num);
		//bit.set(num,TRUE);
		//result = bit;
		m_OutputImage[i] = unsigned char (m_InputImage[i] & result) *255;
	}
}


void CImageProcessingDoc::CopyClipboard(BYTE *m_CpyImg, int height, int width, int biBitCount)
{
	// 클립보드에 복사하기 위한 파일의 길이를 구함 
	int rwsize = WIDTHBYTES(biBitCount*width); 
	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256+ rwsize*height*sizeof(char); // 

    // 메모리 할당(파일헤드만 제외시킨 길이) 
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dwBitsSize); 
	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage); 
	
	// 데이타복사 
	BITMAPINFOHEADER dibCpyHi; 
	memcpy(&dibCpyHi,&dibHi,sizeof(BITMAPINFOHEADER)); 
	dibCpyHi.biBitCount = biBitCount; 
	dibCpyHi.biHeight = height; 
	dibCpyHi.biWidth = width; 
	dibCpyHi.biSizeImage = height*rwsize; 
	
	if(biBitCount==8) 
		dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = 256;

	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER)); 
	if (biBitCount == 8) 
	{ 
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), palRGB, sizeof(RGBQUAD) * 256); 
		memcpy(pDIB + dwBitsSize - dibCpyHi.biSizeImage, m_CpyImg, dibCpyHi.biSizeImage); 
	}
	else 
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_CpyImg, dibCpyHi.biSizeImage); 
	
	// 클립보드 복사 
	::OpenClipboard(NULL); 
	::SetClipboardData(CF_DIB, m_hImage); 
	::CloseClipboard(); 

	::GlobalUnlock((HGLOBAL)m_hImage); 
	GlobalFree(m_hImage);
}


void CImageProcessingDoc::OnRedColor()
{
	int i, j; 
	int num_C = 3; 

	m_height = dibHi.biHeight; 
	m_width = dibHi.biWidth; 
	m_size = m_height*m_width; 
	
	m_OutputImage = new BYTE[m_size * 3]; 
	
	// 칼라 영상을 위한 메모리 할당 
	//for (int C=1 ; C<=num_C ; C++)
	//{ 
	//	for(i=0 ; i<m_size ; i++)
	//	{ 
	//		m_OutputImage[i*num_C] = 0; //B 성분 
	//		m_OutputImage[i*num_C+1] = 0; //G성분 
	//		m_OutputImage[i*num_C+2] = 255; //R성분 
	//	} 
	//}

	// 이미지를 RGB 성분으로 추출 
	for (int C = 1; C <= num_C; C++) {
		for (i = 0; i < m_size; i++)
		{
			int B = (int)m_InImg[i*num_C]; //B 성분 
			int G = (int)m_InImg[i*num_C + 1]; //G성분 
			int R = (int)m_InImg[i*num_C + 2]; //R성분 

			if (B > R && B > G)
			{
				m_OutputImage[i*num_C] = 255; //B 성분 
				m_OutputImage[i*num_C + 1] = 0; //G성분 
				m_OutputImage[i*num_C + 2] = 0; //R성분 
			}
			else if (G > R && B < G)
			{
				m_OutputImage[i*num_C] = 0; //B 성분 
				m_OutputImage[i*num_C + 1] = 255; //G성분 
				m_OutputImage[i*num_C + 2] = 0; //R성분 
			}
			else if (B < R && R > G)
			{
				m_OutputImage[i*num_C] = 0; //B 성분 
				m_OutputImage[i*num_C + 1] = 0; //G성분 
				m_OutputImage[i*num_C + 2] = 255; //R성분 
			}
			else
			{
				m_OutputImage[i*num_C] = m_InImg[i*num_C]; //B 성분 
				m_OutputImage[i*num_C + 1] = m_InImg[i*num_C + 1]; //G성분 
				m_OutputImage[i*num_C + 2] = m_InImg[i*num_C + 2]; //R성분 
			}
		}
	}

}


void CImageProcessingDoc::ColorBlurring()
{
	int i, j, k, l, num_C;
	double BlurrMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
	double result;
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;
	CString msg;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, BlurrMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, BlurrMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, BlurrMask);

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}

void CImageProcessingDoc::OnEdge()
{
	int i, j, k, l, num_C;
	double DiffHorMask[3][3]= { { 0., -1., 0. },{ 0., 1., 0. },{ 0., 0., 0. } }; // 수평 필터 선택
	double result;
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;
	CString msg;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 수평 에지 검출
	tempOutputImageR = OnMaskProcess(tempInputImageR, DiffHorMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, DiffHorMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, DiffHorMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageR[i][j] > 255.)
				tempOutputImageR[i][j] = 255.;
			if (tempOutputImageR[i][j] < 0.)
				tempOutputImageR[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageG[i][j] > 255.)
				tempOutputImageG[i][j] = 255.;
			if (tempOutputImageG[i][j] < 0.)
				tempOutputImageG[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageB[i][j] > 255.)
				tempOutputImageB[i][j] = 255.;
			if (tempOutputImageB[i][j] < 0.)
				tempOutputImageB[i][j] = 0.;
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}

void CImageProcessingDoc::OnLaplacian()
{
	BYTE	R, G, B, GRAY;
	int i, j, k, l, num_C;
	double LaplacianMask[3][3] = { { 0., 1., 0. },{ 1., -4., 1. },{ 0., 1., 0. } };
	//double LaplacianMask2[3][3] = { { 1., 1., 1. },{ 1., -8., 1. },{ 1., 1., 1. } };
	//double LaplacianMask3[3][3] = { { -1., -1., -1. },{ -1., 8., -1. },{ -1., -1., -1. } };
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, LaplacianMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, LaplacianMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, LaplacianMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageR[i][j] > 255.)
				tempOutputImageR[i][j] = 255.;
			if (tempOutputImageR[i][j] < 0.)
				tempOutputImageR[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageG[i][j] > 255.)
				tempOutputImageG[i][j] = 255.;
			if (tempOutputImageG[i][j] < 0.)
				tempOutputImageG[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageB[i][j] > 255.)
				tempOutputImageB[i][j] = 255.;
			if (tempOutputImageB[i][j] < 0.)
				tempOutputImageB[i][j] = 0.;
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


void CImageProcessingDoc::OnBlurrgaussian()
{
	int i, j, num_C;
	double GaussianMask[3][3] = { { 1. / 16., 1. / 8., 1. / 16. },{ 1. / 8., 1. / 4., 1. / 8. },{ 1. / 16., 1. / 8., 1. / 16. } };
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;
	
	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, GaussianMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, GaussianMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, GaussianMask);

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


void CImageProcessingDoc::OnSharpMask()
{
	int i, j, k, l, num_C;
	double SharpeningMask[3][3] = { { 0., -1., 0. },{ -1., 5., -1. },{ 0., -1., 0. } };
	double result;
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;
	CString msg;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, SharpeningMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, SharpeningMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, SharpeningMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageR[i][j] > 255.)
				tempOutputImageR[i][j] = 255.;
			if (tempOutputImageR[i][j] < 0.)
				tempOutputImageR[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageG[i][j] > 255.)
				tempOutputImageG[i][j] = 255.;
			if (tempOutputImageG[i][j] < 0.)
				tempOutputImageG[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageB[i][j] > 255.)
				tempOutputImageB[i][j] = 255.;
			if (tempOutputImageB[i][j] < 0.)
				tempOutputImageB[i][j] = 0.;
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


void CImageProcessingDoc::OnHpfFilterSharp()
{
	int i, j, num_C;
	double HpfSharpMask[3][3] = { { -1. / 9., -1. / 9., -1. / 9. },{ -1. / 9., 8. / 9., -1. / 9. },{ -1. / 9., -1. / 9., -1. / 9. } };
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, HpfSharpMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, HpfSharpMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, HpfSharpMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageR[i][j] > 255.)
				tempOutputImageR[i][j] = 255.;
			if (tempOutputImageR[i][j] < 0.)
				tempOutputImageR[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageG[i][j] > 255.)
				tempOutputImageG[i][j] = 255.;
			if (tempOutputImageG[i][j] < 0.)
				tempOutputImageG[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageB[i][j] > 255.)
				tempOutputImageB[i][j] = 255.;
			if (tempOutputImageB[i][j] < 0.)
				tempOutputImageB[i][j] = 0.;
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


void CImageProcessingDoc::OnLpfFilterSharp()
{
	ConstantDlg dlg;
	int i, j, k, l, num_C, alpha;
	double LpfSharpMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
	double result;
	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;

	m_height = dibHi.biHeight; m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];
	tempInputImageR = new unsigned char[m_Re_size];
	tempInputImageG = new unsigned char[m_Re_size];
	tempInputImageB = new unsigned char[m_Re_size];

	tempOutputImageR = Image2DMem(m_height, m_width);
	tempOutputImageG = Image2DMem(m_height, m_width);
	tempOutputImageB = Image2DMem(m_height, m_width);

	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 해야 3PIXEL씩(R,G,B 니까) 처리된다.
		}
	}

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_Constant;
		// 대화상자를이용하여상수를입력받는다.
	}
	// 각 컬러 밴드 별 블러링처리
	tempOutputImageR = OnMaskProcess(tempInputImageR, LpfSharpMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, LpfSharpMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, LpfSharpMask);


	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			tempOutputImageR[i][j] = (alpha *tempInputImageR[i*m_width + j]) - (unsigned char)tempOutputImageR[i][j];
			tempOutputImageG[i][j] = (alpha *tempInputImageG[i*m_width + j]) - (unsigned char)tempOutputImageG[i][j];
			tempOutputImageB[i][j] = (alpha *tempInputImageB[i*m_width + j]) - (unsigned char)tempOutputImageB[i][j];
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageR[i][j] > 255.)
				tempOutputImageR[i][j] = 255.;
			if (tempOutputImageR[i][j] < 0.)
				tempOutputImageR[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageG[i][j] > 255.)
				tempOutputImageG[i][j] = 255.;
			if (tempOutputImageG[i][j] < 0.)
				tempOutputImageG[i][j] = 0.;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (tempOutputImageB[i][j] > 255.)
				tempOutputImageB[i][j] = 255.;
			if (tempOutputImageB[i][j] < 0.)
				tempOutputImageB[i][j] = 0.;
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//  // 세 컬러 버퍼 복사 해야 하니까 resize*3 크기로 m_OutputImage 버퍼를 할당한 것임.
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}
