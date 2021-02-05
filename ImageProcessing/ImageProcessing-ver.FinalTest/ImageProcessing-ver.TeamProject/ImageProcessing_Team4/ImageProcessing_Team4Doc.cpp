
// ImageProcessing_Team4Doc.cpp : CImageProcessing_Team4Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_Team4.h"
#endif

#include "ImageProcessing_Team4Doc.h"

#include <propkey.h>
#include "ImageSegmentDlg.h"
#include "ImageClearDlg.h"
#include "ConstantDlg.h"
#include "RateDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessing_Team4Doc

IMPLEMENT_DYNCREATE(CImageProcessing_Team4Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessing_Team4Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcessing_Team4Doc 생성/소멸

CImageProcessing_Team4Doc::CImageProcessing_Team4Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessing_Team4Doc::~CImageProcessing_Team4Doc()
{
}

BOOL CImageProcessing_Team4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	::OpenClipboard(NULL);

	if (!IsClipboardFormatAvailable(CF_DIB))
		return FALSE;
	HGLOBAL m_hImage = ::GetClipboardData(CF_DIB);
	::CloseClipboard();

	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	memcpy(&dibHi, pDIB, sizeof(BITMAPINFOHEADER));
	height = dibHi.biHeight;
	width = dibHi.biWidth;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	DWORD dwBitsSize =
		sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 + rwsize*height * sizeof(char); //

	m_InImg = new unsigned char[dibHi.biSizeImage];
	m_OutImg = new unsigned char[dibHi.biSizeImage];

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

	dibHf.bfOffBits = dibHf.bfSize - rwsize*height * sizeof(char);
	dibHf.bfReserved1 = dibHf.bfReserved2 = 0;

	return TRUE;
}




// CImageProcessing_Team4Doc serialization

void CImageProcessing_Team4Doc::Serialize(CArchive& ar)
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
void CImageProcessing_Team4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessing_Team4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessing_Team4Doc::SetSearchContent(const CString& value)
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

// CImageProcessing_Team4Doc 진단

#ifdef _DEBUG
void CImageProcessing_Team4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessing_Team4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessing_Team4Doc 명령


BOOL CImageProcessing_Team4Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile hFile;

	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER)); // 파일 헤드를 읽음
	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");
		return FALSE;
	}
	//이 파일이 BMP파일인지 검사. 0x4d42=='BM'

	hFile.Read(&dibHi, sizeof(BITMAPINFOHEADER)); //"영상정보의 Header"를 읽는다.
	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}

	if (dibHi.biBitCount == 8)
		hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

	// 메모리 할당 (바뀐 부분)
	int ImgSize;

	if (dibHi.biBitCount == 8)
		ImgSize = (int)(hFile.GetLength() - sizeof(BITMAPFILEHEADER) -
			sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD));

	else if (dibHi.biBitCount == 24)
		ImgSize = (int)(hFile.GetLength() - sizeof(BITMAPFILEHEADER) -
			sizeof(BITMAPINFOHEADER));

	m_InImg = new unsigned char[ImgSize]; //dibHi.biSizeImage
	m_OutImg = new unsigned char[ImgSize];
	m_COrigin = new unsigned char[ImgSize];

	hFile.Read(m_InImg, ImgSize);
	hFile.Close();
	height = dibHi.biHeight;
	width = dibHi.biWidth;

	if (dibHi.biBitCount == 24)
		return TRUE;

	// 영상데이터 대입
	int i, j, index;
	int rwsize = WIDTHBYTES(dibHi.biBitCount*width);
	for (i = 0; i<height; i++) {
		index = i*rwsize;
		for (j = 0; j<width; j++)
			m_InImg[index + j] = (unsigned char)palRGB[(int)m_InImg[index + j]].rgbBlue;
	}

	ImgType = 0;
	if (dibHi.biBitCount == 8) ImgType = 1;

	return TRUE;
}


void CImageProcessing_Team4Doc::CopyClipboard(BYTE *m_CpyImg, int height, int width, int biBitCount)
{
	// 클립보드에 복사하기 위한 파일의 길이를 구함
	int rwsize = WIDTHBYTES(biBitCount*width);

	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 +
		rwsize*height * sizeof(char); //

									  // 메모리 할당(파일헤드만 제외시킨 길이)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
		dwBitsSize);

	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	// 데이타복사
	BITMAPINFOHEADER dibCpyHi;
	memcpy(&dibCpyHi, &dibHi, sizeof(BITMAPINFOHEADER));
	dibCpyHi.biBitCount = biBitCount;
	dibCpyHi.biHeight = height;
	dibCpyHi.biWidth = width;
	dibCpyHi.biSizeImage = height*rwsize;

	if (biBitCount == 8)
		dibCpyHi.biClrUsed = dibCpyHi.biClrImportant = 256;
	memcpy(pDIB, &dibCpyHi, sizeof(BITMAPINFOHEADER));

	if (biBitCount == 8)
	{
		memcpy(pDIB + sizeof(BITMAPINFOHEADER), palRGB, sizeof(RGBQUAD) * 256);
		memcpy(pDIB + dwBitsSize - dibCpyHi.biSizeImage, m_CpyImg, dibCpyHi.biSizeImage);
	}
	else memcpy(pDIB + sizeof(BITMAPINFOHEADER), m_CpyImg, dibCpyHi.biSizeImage);

	// 클립보드 복사
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();
	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);
}

//OnMaskProcess함수
double** CImageProcessing_Team4Doc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
{
	// 회선 처리가 일어나는 함수
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	// 입력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);
	// 출력 값을 위한 메모리 할당

	// 1차원 입력 영상 M_InputImage[]의 값을 2차원 배열 tempInputImage[][]에 할당 
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	// 회선연산
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			for (n = 0; n<3; n++) {
				for (m = 0; m<3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			} // 회선 마스크의 크기 만큼 이동하면서 값을 누적

			tempOutputImage[i][j] = S; // 누적된 값을 출력 메모리에 저장
			S = 0.0; // 다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	return tempOutputImage; // 결과 버퍼 반환 
}

//Image2DMem함수
double** CImageProcessing_Team4Doc::Image2DMem(int height, int width)
{
	// 2차원 메모리 할당을 위한 함수 
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
	} // 할당된 2차원 메모리를 초기화
	return temp;
}


//영상 분할
void CImageProcessing_Team4Doc::OnImageSegmentation()
{
	CImageSegmentDlg dlg;

	int i, j; int num_C = 3;

	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	if (dlg.DoModal() == IDOK) {
		if (dlg.num1 <= dlg.num2) {
			for (i = 0; i < m_Re_height; i++) {
				for (j = 0; j < m_Re_width; j++) {
					// B구간
					if (m_InImg[i*m_Re_width * 3 + j*num_C] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C] = m_InImg[i*m_Re_width * 3 + j*num_C];

					// G구간
					if (m_InImg[i*m_Re_width * 3 + j*num_C + 1] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C + 1] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];

					// R구간
					if (m_InImg[i*m_Re_width * 3 + j*num_C + 2] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C + 2] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = m_InImg[i*m_Re_width * 3 + j*num_C + 2];
				}
			}
		}
		else AfxMessageBox(L"앞에 입력되는 변수의 값이 더 작아야 합니다.(오류)");
	}
}


//영상 선명화
void  CImageProcessing_Team4Doc::OnImageclear()
{
	CImageClearDlg dlg;

	int i, j; int num_C = 3; int MAX = 255;

	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_size = m_height*m_width;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				//B구간
				if (m_InImg[i*m_Re_width * 3 + j*num_C] < dlg.bnum1) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C] = m_InImg[i*m_Re_width * 3 + j*num_C] / 2;
				}
				else if (m_InImg[i*m_Re_width * 3 + j*num_C] > dlg.bnum2) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C] = m_InImg[i*m_Re_width * 3 + j*num_C] / 2 + MAX / 2;
				}
				else {
					m_OutputImage[i*m_Re_width * 3 + j*num_C] = dlg.bnum1 / 2 + (m_InImg[i*m_Re_width * 3 + j*num_C] - dlg.bnum1) *
						(dlg.bnum2 - dlg.bnum1 + MAX) / (2 * (dlg.bnum2 - dlg.bnum1));
				}

				//G구간
				if (m_InImg[i*m_Re_width * 3 + j*num_C + 1] < dlg.gnum1) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = m_InImg[i*m_Re_width * 3 + j*num_C + 1] / 2;
				}
				else if (m_InImg[i*m_Re_width * 3 + j*num_C + 1] > dlg.gnum2) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = m_InImg[i*m_Re_width * 3 + j*num_C + 1] / 2 + MAX / 2;
				}
				else {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = dlg.gnum1 / 2 + (m_InImg[i*m_Re_width * 3 + j*num_C + 1] - dlg.gnum1) *
						(dlg.gnum2 - dlg.gnum1 + MAX) / (2 * (dlg.gnum2 - dlg.gnum1));
				}

				//R구간
				if (m_InImg[i*m_Re_width * 3 + j*num_C + 2] < dlg.rnum1) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = m_InImg[i*m_Re_width * 3 + j*num_C + 2] / 2;
				}
				else if (m_InImg[i*m_Re_width * 3 + j*num_C + 2] > dlg.rnum2) {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = m_InImg[i*m_Re_width * 3 + j*num_C + 2] / 2 + MAX / 2;
				}
				else {
					m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = dlg.rnum1 / 2 + (m_InImg[i*m_Re_width * 3 + j*num_C + 2] - dlg.rnum1) *
						(dlg.rnum2 - dlg.rnum1 + MAX) / (2 * (dlg.rnum2 - dlg.rnum1));
				}
			}
		}
	}
}



//영상 블러링(3x3마스크)
void CImageProcessing_Team4Doc::ColorBlurring()
{
	int i, j, num_C;
	double BlurrMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//영상 블러링(가우시안)
void CImageProcessing_Team4Doc::OnBlurrgaussian()
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//영상 샤프닝마스크
void CImageProcessing_Team4Doc::OnSharpMask()
{
	int i, j, num_C;
	double SharpeningMask[3][3] = { { 0., -1., 0. },{ -1., 5., -1. },{ 0., -1., 0. } };
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//영상 고주파 필터 샤프닝
void CImageProcessing_Team4Doc::OnHpfFilterSharp()
{
	int i, j, num_C;
	double HpfSharpMask[3][3] = { { -1. / 9., -1. / 9., -1. / 9. },{ -1. / 9., 8. / 9., -1. / 9. },{ -1. / 9., -1. / 9., -1. / 9. } };
	double BlurrMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
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

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempOutputImageB[i][j]= (unsigned char)tempOutputImageB[i][j] + tempInputImageB[i*m_Re_width + j];
			tempOutputImageG[i][j] = (unsigned char)tempOutputImageG[i][j] + tempInputImageG[i*m_Re_width + j];
			tempOutputImageR[i][j] = (unsigned char)tempOutputImageR[i][j] + tempInputImageR[i*m_Re_width + j];
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


//영상 저주파 필터 샤프닝
void CImageProcessing_Team4Doc::OnLpfFilterSharp()
{
	ConstantDlg dlg;
	int i, j, num_C, alpha;
	double LpfSharpMask[3][3] = { { 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. },{ 1. / 9., 1. / 9., 1. / 9. } };
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//영상 에지검출(수평필터)
void CImageProcessing_Team4Doc::OnEdge()
{
	int i, j, num_C;
	double DiffHorMask[3][3] = { { 0., -1., 0. },{ 0., 1., 0. },{ 0., 0., 0. } }; // 수평 필터 선택
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//영상 에지검출(라플라시안)
void CImageProcessing_Team4Doc::OnLaplacian()
{
	//BYTE	R, G, B, GRAY;
	int i, j, num_C;
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
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}



//고주파 대역 필터링
void CImageProcessing_Team4Doc::OnHpfSharp()
{
	int i, j, num_C;
	double HpfSharpMask[3][3] = { { -1.,-1.,-1. },
	{ -1.,9.,-1. },{ -1.,-1.,-1. } };
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
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2];
		}
	}
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	tempOutputImageR = OnMaskProcess(tempInputImageR, HpfSharpMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, HpfSharpMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, HpfSharpMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;
}


//저주파 대역 필터링
void CImageProcessing_Team4Doc::OnLpfSharp()
{
	int i, j, num_C;
	double LpfSharpMask[3][3] = { { -1., -1., -1. },
	{ -1., 9., -1. },{ -1., -1., -1. } };
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
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2];
		}
	}
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	tempOutputImageR = OnMaskProcess(tempInputImageR, LpfSharpMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, LpfSharpMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, LpfSharpMask);

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)tempOutputImageR[i][j];
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR;
	delete tempOutputImageG, tempOutputImageB, tempOutputImageR;

}




//영상 축소
void CImageProcessing_Team4Doc::OnScalingDown()
{
	int i, j, num_C;

	int n, m, index = 0;
	int M = 1;// M = 서브 샘플링 비율 
	double SumR = 0.0;
	double SumG = 0.0;
	double SumB = 0.0;

	double ValueR, ValueG, ValueB;

	CString msg;
	CRateDialog dlg;

	if (dlg.DoModal() == IDOK) {
		M = (int)dlg.m_RateIn;
	}

	if (dibHi.biBitCount == 24) {
		num_C = 3;
	}
	else if (dibHi.biBitCount == 8) {
		num_C = 1;
	}

	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_size = m_height*m_width;

	m_Re_height = (int)((m_height) / M);
	if (M % 2 == 0) {
		m_Re_width = (int)((m_width) / M);
	}
	else if (M == 1) {
		m_Re_width = m_width;
		m_Re_height = m_height;
	}
	else m_Re_width = (int)((m_width - 2 * M) / M);
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	m_tempImageR = Image2DMem(m_height + 1, m_width + 1);
	m_tempImageG = Image2DMem(m_height + 1, m_width + 1);
	m_tempImageB = Image2DMem(m_height + 1, m_width + 1);

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			m_tempImageR[i][j] = m_InImg[i*m_width * 3 + j*num_C + 2];
			m_tempImageG[i][j] = m_InImg[i*m_width * 3 + j*num_C + 1];
			m_tempImageB[i][j] = m_InImg[i*m_width * 3 + j*num_C];
		}
	}

	for (i = 0; i<m_Re_height; i++)
	{
		for (j = 0; j<m_Re_width; j++)
		{
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					SumR += m_tempImageR[(int)((i * M) + n)][(int)((j * M) + m)];
					SumG += m_tempImageG[(int)((i * M) + n)][(int)((j * M) + m)];
					SumB += m_tempImageB[(int)((i * M) + n)][(int)((j * M) + m)];
				}
			}
			ValueR = (SumR / (M*M)); //평균을 계산
			ValueG = (SumG / (M*M));
			ValueB = (SumB / (M*M));
			m_OutputImage[i*m_Re_width * 3 + j * num_C + 2] = (unsigned char)ValueR;
			m_OutputImage[i*m_Re_width * 3 + j * num_C + 1] = (unsigned char)ValueG;
			m_OutputImage[i*m_Re_width * 3 + j * num_C] = (unsigned char)ValueB;
			SumR = 0.0; SumG = 0.0; SumB = 0.0;
		}
	}
}

void CImageProcessing_Team4Doc::OnBubleSort(double * A, int MAX)
{
	// 데이터의 정렬을 처리하는 함수 
	int i, j;

	for (i = 0; i<MAX; i++) {
		for (j = 0; j<MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}

// 데이터 교환 함수 
void CImageProcessing_Team4Doc::OnSwap(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//영상 확대 - 인접한 이웃 화소 보간법
void CImageProcessing_Team4Doc::OnNearScaleUp()
{
	int i, j, num_C;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;

	double ZoomRate = 1; // 영상 확대 배율 

	CString msg;
	CRateDialog dlg;

	if (dlg.DoModal() == IDOK) {
		ZoomRate = dlg.m_RateIn;
	}

	if (dibHi.biBitCount == 24) {
		num_C = 3;
	}
	else if (dibHi.biBitCount == 8) {
		num_C = 1;
	}

	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_size = m_height*m_width;

	m_Re_height = int(ZoomRate*m_height); // 확대된 영상의 높이 
	m_Re_width = int(ZoomRate*m_width); // 확대된 영상의 너비 
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	tempOutputImageR = Image2DMem(m_Re_height, m_Re_width);
	tempOutputImageG = Image2DMem(m_Re_height, m_Re_width);
	tempOutputImageB = Image2DMem(m_Re_height, m_Re_width);
	m_tempImageR = Image2DMem(m_height, m_width);
	m_tempImageG = Image2DMem(m_height, m_width);
	m_tempImageB = Image2DMem(m_height, m_width);

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++) {
		m_OutputImage[i] = 255;
	}

	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			m_tempImageR[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C + 2];
			m_tempImageG[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C + 1];
			m_tempImageB[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C];
		}
	}

	for (i = 0; i< m_Re_height; i++) {
		for (j = 0; j< m_Re_width; j++) {
			tempOutputImageR[i][j] = m_tempImageR[int(i / ZoomRate)][int(j / ZoomRate)];
			tempOutputImageG[i][j] = m_tempImageG[int(i / ZoomRate)][int(j / ZoomRate)];
			tempOutputImageB[i][j] = m_tempImageB[int(i / ZoomRate)][int(j / ZoomRate)];
			// 이웃한 화소를 이용한 보간
		}
	}

	//--처리 결과를 1차원 출력 버퍼:m_OutputImage로 데이터 복사 --//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] =
				(unsigned char)tempOutputImageB[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] =
				(unsigned char)tempOutputImageG[i][j];
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] =
				(unsigned char)tempOutputImageR[i][j];
		}
	}
}


//영상 확대 - 양선형 보간법 이용
void CImageProcessing_Team4Doc::OnBilinearScaleUp()
{
	int i, j, num_C;

	int point, i_H, i_W;
	unsigned char newValueR, newValueG, newValueB;
	double r_H, r_W, s_H, s_W;
	double C1R, C2R, C3R, C4R, C1G, C2G, C3G, C4G, C1B, C2B, C3B, C4B;

	double ZoomRate = 1.0;

	CString msg;
	CRateDialog dlg;

	if (dlg.DoModal() == IDOK) {
		ZoomRate = dlg.m_RateIn;
	}

	if (dibHi.biBitCount == 24) {
		num_C = 3;
	}
	else if (dibHi.biBitCount == 8) {
		num_C = 1;
	}

	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_size = m_height*m_width;

	m_Re_height = int(ZoomRate*m_height); // 확대된 영상의 높이 
	m_Re_width = int(ZoomRate*m_width); // 확대된 영상의 너비 
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	m_tempImageR = Image2DMem(m_height, m_width);
	m_tempImageG = Image2DMem(m_Re_height, m_width);
	m_tempImageB = Image2DMem(m_height, m_width);

	//--- 출력 버퍼 초기화 --//
	for (i = 0; i<m_Re_size * 3; i++) {
		m_OutputImage[i] = 255;
	}

	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			m_tempImageR[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C + 2];
			m_tempImageG[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C + 1];
			m_tempImageB[i][j] = (double)m_InImg[i*m_width * 3 + j*num_C];
		}
	}

	for (i = 0; i< m_Re_height; i++) {
		for (j = 0; j< m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;

			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;  // 수평방향 거리 계산 
			s_W = r_W - i_W;  // 수직방향 거리 계산

			if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0 || i_W >= (m_width - 1)) {
				point = i* m_Re_width + j;
				m_OutputImage[point*num_C + 2] = 255;
				m_OutputImage[point*num_C + 1] = 255;
				m_OutputImage[point*num_C] = 255;
			}
			else {
				C1R = (double)m_tempImageR[i_H][i_W];
				C2R = (double)m_tempImageR[i_H][i_W + 1];
				C3R = (double)m_tempImageR[i_H + 1][i_W + 1];
				C4R = (double)m_tempImageR[i_H + 1][i_W];
				C1G = (double)m_tempImageG[i_H][i_W];
				C2G = (double)m_tempImageG[i_H][i_W + 1];
				C3G = (double)m_tempImageG[i_H + 1][i_W + 1];
				C4G = (double)m_tempImageG[i_H + 1][i_W];
				C1B = (double)m_tempImageB[i_H][i_W];
				C2B = (double)m_tempImageB[i_H][i_W + 1];
				C3B = (double)m_tempImageB[i_H + 1][i_W + 1];
				C4B = (double)m_tempImageB[i_H + 1][i_W];

				newValueR = (unsigned char)(C1R*(1 - s_H)*(1 - s_W)
					+ C2R*s_W*(1 - s_H) + C3R*s_W*s_H + C4R*(1 - s_W)*s_H);
				newValueG = (unsigned char)(C1G*(1 - s_H)*(1 - s_W)
					+ C2G*s_W*(1 - s_H) + C3G*s_W*s_H + C4G*(1 - s_W)*s_H);
				newValueB = (unsigned char)(C1B*(1 - s_H)*(1 - s_W)
					+ C2B*s_W*(1 - s_H) + C3B*s_W*s_H + C4B*(1 - s_W)*s_H);
				point = i* m_Re_width + j;
				m_OutputImage[point*num_C + 2] = newValueR;
				m_OutputImage[point*num_C + 1] = newValueG;
				m_OutputImage[point*num_C] = newValueB;
			}
		}
	}
}


void CImageProcessing_Team4Doc::OnFft2d()
{

	unsigned char *tempInputImageR, *tempInputImageG, *tempInputImageB, *tempInputImageY;
	double** tempOutputImageY;
	int i, j, row, col, Log2N, Num,num_C;
	Complex *Data;
	unsigned char **temp;
	double Value, Absol;
	Num = m_width;
	Log2N = 0;
	while (Num >= 2) // 영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

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
	tempInputImageY = new unsigned char[m_Re_size];
	tempOutputImageY = Image2DMem(m_height, m_width);
	//--- 1차원 원본 영상데이터 임시 버퍼로 복사 ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2];
		}
	}
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageY[i*m_Re_width + j] = (0.29900*tempInputImageR[i*m_Re_width + j]) + (0.58700*tempInputImageG[i*m_Re_width + j]) + (0.11400*tempInputImageB[i*m_Re_width + j]);
		}
	}

	Data = new Complex[m_width];
	m_FFT = new Complex *[m_height];

	// 주파수 영역 변환 영상을 저장하기 위한 배열
	temp = new unsigned char *[m_height];
	for (i = 0; i<m_height; i++) {
		m_FFT[i] = new Complex[m_width];
		temp[i] = new unsigned char[m_width];
	}
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			Data[j].Re = (double)tempInputImageY[i*m_width + j];
			// 입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; // 복소 성분 값은 0
		}
		OnFft1d(Data, m_width, Log2N); // 1차원 FFT
		for (j = 0; j<m_width; j++) { // 결과 저장
			m_FFT[i][j].Re = Data[j].Re;
			m_FFT[i][j].Im = Data[j].Im;
		}
	}
	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}
	Data = new Complex[m_height];
	for (i = 0; i<m_width; i++) {
		for (j = 0; j<m_height; j++) {
			Data[j].Re = m_FFT[j][i].Re; // 영상의 한 열을 복사
			Data[j].Im = m_FFT[j][i].Im;
		}
		OnFft1d(Data, m_height, Log2N); // 1차원 FFT
		for (j = 0; j<m_height; j++) { // 결과 저장
			m_FFT[j][i].Re = Data[j].Re;
			m_FFT[j][i].Im = Data[j].Im;
		}
	}

	// FFT 실행 결과를 영상으로 출력하기 위한 연산
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			Value = sqrt((m_FFT[i][j].Re * m_FFT[i][j].Re) +
				(m_FFT[i][j].Im * m_FFT[i][j].Im));
			Absol = 20 * log(Value);
			if (Absol > 255.0)
				Absol = 255.0;
			if (Absol < 0.0)
				Absol = 0.0;
			tempOutputImageY[i][j] = Absol;
		}
	}
	// 셔플링 과정 : 영상을 4등분하고 분할된 영상을 상하 대칭 및 좌우 대칭
	for (i = 0; i<m_height; i += m_height / 2) {
		for (int j = 0; j<m_width; j += m_width / 2) {
			for (row = 0; row<m_height / 2; row++) {
				for (col = 0; col<m_width / 2; col++) {
					temp[(m_height / 2 - 1) - row + i][(m_width / 2 - 1) - col + j]
						= (unsigned char)tempOutputImageY[i + row][j + col];
				}
			}
		}
	}
	delete tempInputImageG, tempInputImageB, tempInputImageR, tempInputImageY;
	delete[] Data, **temp;

}


void CImageProcessing_Team4Doc::OnFft1d(Complex* X, int N, int Log2N)
{
	OnShuffle(X, N, Log2N); // 함수 호출
	OnButterfly(X, N, Log2N, 1); // 함수 호출

}


void CImageProcessing_Team4Doc::OnShuffle(Complex* X, int N, int Log2N)
{
	// 입력 데이터의 순서를 바구기 위한 함수
	int i;
	Complex *temp;
	temp = new Complex[N];
	for (i = 0; i<N; i++) {
		temp[i].Re = X[OnReverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[OnReverseBitOrder(i, Log2N)].Im;
	}
	for (i = 0; i<N; i++) {
		X[i].Re = temp[i].Re;
		X[i].Im = temp[i].Im;
	}
	delete[] temp;

}


void CImageProcessing_Team4Doc::OnButterfly(Complex* X, int N, int Log2N, int mode)
{
	// 나비(Butterfly) 구조를 위한 함수
	int i, j, k, m;
	int start;
	double Value;
	double PI = 3.14159265358979;
	Complex *Y, temp;
	Y = new Complex[N / 2];
	for (i = 0; i<Log2N; i++) {
		Value = pow(2, i + 1);
		if (mode == 1) {
			for (j = 0; j<(int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = -sin(j*2.0*PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j<(int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}
		start = 0;
		for (k = 0; k<N / (int)Value; k++) {
			for (j = start; j<start + (int)(Value / 2); j++) {
				m = j + (int)(Value / 2);
				temp.Re = Y[j - start].Re * X[m].Re
					- Y[j - start].Im * X[m].Im;
				temp.Im = Y[j - start].Im * X[m].Re
					+ Y[j - start].Re * X[m].Im;
				X[m].Re = X[j].Re - temp.Re;
				X[m].Im = X[j].Im - temp.Im;
				X[j].Re = X[j].Re + temp.Re;
				X[j].Im = X[j].Im + temp.Im;
			}
			start = start + (int)Value;
		}
	}
	if (mode == 2) {
		for (i = 0; i<N; i++) {
			X[i].Re = X[i].Re / N;
			X[i].Im = X[i].Im / N;
		}
	}
	delete[] Y;
}


int CImageProcessing_Team4Doc::OnReverseBitOrder(int index, int Log2N)
{
	int i, X, Y;
	Y = 0;
	for (i = 0; i<Log2N; i++) {
		X = (index & (1 << i)) >> i;
		Y = (Y << 1) | X;
	}
	return Y;
}


void CImageProcessing_Team4Doc::OnIfft2d()
{
	int i, j, Num, Log2N, num_C;
	m_OutputImage = new unsigned char[m_Re_size * 3];
	Complex *Data;
	Num = m_width;
	Log2N = 0;
	while (Num >= 2) // 주파수변환된영상의너비계산
	{
		Num >>= 1;
		Log2N++;
	}

	if (dibHi.biBitCount == 24)
		num_C = 3;
	else if (dibHi.biBitCount == 8)
		num_C = 1;
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	Data = new Complex[m_height];
	m_IFFT = new Complex *[m_height]; // 역변환된영상을위한배열
	for (i = 0; i<m_height; i++) {
		m_IFFT[i] = new Complex[m_width];
	}
	for (i = 0; i< m_height; i++) {
		for (j = 0; j<m_width; j++) { // 한행을복사
			Data[j].Re = m_FFT[i][j].Re;
			Data[j].Im = m_FFT[i][j].Im;
		}
		OnIfft1d(Data, m_width, Log2N); // 1차원IFFT
		for (j = 0; j<m_width; j++) {
			m_IFFT[i][j].Re = Data[j].Re; // 결과저장
			m_IFFT[i][j].Im = Data[j].Im;
		}
	}
	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // 주파수변환된영상의높이계산
	{
		Num >>= 1;
		Log2N++;
	}
	Data = new Complex[m_height];
	for (i = 0; i<m_width; i++) {
		for (j = 0; j<m_height; j++) {
			Data[j].Re = m_IFFT[j][i].Re; // 한열을복사
			Data[j].Im = m_IFFT[j][i].Im;
		}
		OnIfft1d(Data, m_height, Log2N); // 1차원IFFT
		for (j = 0; j<m_height; j++) {
			m_IFFT[j][i].Re = Data[j].Re; // 결과저장
			m_IFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width * 3 + j*num_C] = (unsigned char)m_IFFT[i][j].Re;
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = (unsigned char)m_IFFT[i][j].Re;
			m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = (unsigned char)m_IFFT[i][j].Re;
		}
	}

	delete[] Data;
}


void CImageProcessing_Team4Doc::OnIfft1d(Complex* X, int N, int Log2N)
{
	OnShuffle(X, N, Log2N);
	OnButterfly(X, N, Log2N, 2);
}


void CImageProcessing_Team4Doc::OnLpfFrequency()
{
	int i, j, x, y;
	double temp, D, N;
	D = 32.0;
	N = 4.0;
	OnFft2d(); // 주파수변환
			   // 주파수변환된값에서고주파성분제거
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			x = i;
			y = j;
			if (x > m_height / 2)
				x = x - m_height;
			if (y > m_width / 2)
				y = y - m_width;
			temp = 1.0 / (1.0 + pow(sqrt((double)
				(x * x + y * y)) / D, 2 * N));
			m_FFT[i][j].Re = m_FFT[i][j].Re * temp;
			m_FFT[i][j].Im = m_FFT[i][j].Im * temp;
		}
	}
	OnIfft2d(); // 주파수역변환
}
