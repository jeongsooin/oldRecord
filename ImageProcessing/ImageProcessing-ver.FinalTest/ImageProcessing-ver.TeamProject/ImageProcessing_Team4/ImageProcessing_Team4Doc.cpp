
// ImageProcessing_Team4Doc.cpp : CImageProcessing_Team4Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// CImageProcessing_Team4Doc ����/�Ҹ�

CImageProcessing_Team4Doc::CImageProcessing_Team4Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessing_Team4Doc::~CImageProcessing_Team4Doc()
{
}

BOOL CImageProcessing_Team4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
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

	// BITMAP Filer Header�Ķ��Ÿ�� ����
	dibHf.bfType = 0x4d42; // 'BM'
	dibHf.bfSize = dwBitsSize + sizeof(BITMAPFILEHEADER); // ��ü���� ũ��

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
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CImageProcessing_Team4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void CImageProcessing_Team4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessing_Team4Doc ����

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


// CImageProcessing_Team4Doc ���


BOOL CImageProcessing_Team4Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	CFile hFile;

	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER)); // ���� ��带 ����
	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");
		return FALSE;
	}
	//�� ������ BMP�������� �˻�. 0x4d42=='BM'

	hFile.Read(&dibHi, sizeof(BITMAPINFOHEADER)); //"���������� Header"�� �д´�.
	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}

	if (dibHi.biBitCount == 8)
		hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

	// �޸� �Ҵ� (�ٲ� �κ�)
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

	// �������� ����
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
	// Ŭ�����忡 �����ϱ� ���� ������ ���̸� ����
	int rwsize = WIDTHBYTES(biBitCount*width);

	DWORD dwBitsSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * 256 +
		rwsize*height * sizeof(char); //

									  // �޸� �Ҵ�(������常 ���ܽ�Ų ����)
	HGLOBAL m_hImage = (HGLOBAL)::GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT,
		dwBitsSize);

	LPSTR pDIB = (LPSTR) ::GlobalLock((HGLOBAL)m_hImage);

	// ����Ÿ����
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

	// Ŭ������ ����
	::OpenClipboard(NULL);
	::SetClipboardData(CF_DIB, m_hImage);
	::CloseClipboard();
	::GlobalUnlock((HGLOBAL)m_hImage);
	GlobalFree(m_hImage);
}

//OnMaskProcess�Լ�
double** CImageProcessing_Team4Doc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
{
	// ȸ�� ó���� �Ͼ�� �Լ�
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	// �Է� ���� ���� �޸� �Ҵ�
	tempOutputImage = Image2DMem(m_height, m_width);
	// ��� ���� ���� �޸� �Ҵ�

	// 1���� �Է� ���� M_InputImage[]�� ���� 2���� �迭 tempInputImage[][]�� �Ҵ� 
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	// ȸ������
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			for (n = 0; n<3; n++) {
				for (m = 0; m<3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			} // ȸ�� ����ũ�� ũ�� ��ŭ �̵��ϸ鼭 ���� ����

			tempOutputImage[i][j] = S; // ������ ���� ��� �޸𸮿� ����
			S = 0.0; // ���� ������� �̵��ϸ� ���� ���� �ʱ�ȭ
		}
	}
	return tempOutputImage; // ��� ���� ��ȯ 
}

//Image2DMem�Լ�
double** CImageProcessing_Team4Doc::Image2DMem(int height, int width)
{
	// 2���� �޸� �Ҵ��� ���� �Լ� 
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
	} // �Ҵ�� 2���� �޸𸮸� �ʱ�ȭ
	return temp;
}


//���� ����
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
					// B����
					if (m_InImg[i*m_Re_width * 3 + j*num_C] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C] = m_InImg[i*m_Re_width * 3 + j*num_C];

					// G����
					if (m_InImg[i*m_Re_width * 3 + j*num_C + 1] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C + 1] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C + 1] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];

					// R����
					if (m_InImg[i*m_Re_width * 3 + j*num_C + 2] >= 100 && m_InImg[i*m_Re_width * 3 + j*num_C + 2] <= 190) {
						m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = 190;
					}
					else m_OutputImage[i*m_Re_width * 3 + j*num_C + 2] = m_InImg[i*m_Re_width * 3 + j*num_C + 2];
				}
			}
		}
		else AfxMessageBox(L"�տ� �ԷµǴ� ������ ���� �� �۾ƾ� �մϴ�.(����)");
	}
}


//���� ����ȭ
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
				//B����
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

				//G����
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

				//R����
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



//���� ����(3x3����ũ)
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ����ó��
	tempOutputImageR = OnMaskProcess(tempInputImageR, BlurrMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, BlurrMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, BlurrMask);

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� ����(����þ�)
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ����ó��
	tempOutputImageR = OnMaskProcess(tempInputImageR, GaussianMask);
	tempOutputImageG = OnMaskProcess(tempInputImageG, GaussianMask);
	tempOutputImageB = OnMaskProcess(tempInputImageB, GaussianMask);

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� �����׸���ũ
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ����ó��
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

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� ������ ���� ������
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ����ó��
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

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� ������ ���� ������
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	if (dlg.DoModal() == IDOK) {
		alpha = (int)dlg.m_Constant;
		// ��ȭ���ڸ��̿��Ͽ�������Է¹޴´�.
	}

	// �� �÷� ��� �� ����ó��
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

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� ��������(��������)
void CImageProcessing_Team4Doc::OnEdge()
{
	int i, j, num_C;
	double DiffHorMask[3][3] = { { 0., -1., 0. },{ 0., 1., 0. },{ 0., 0., 0. } }; // ���� ���� ����
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ���� ���� ����
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

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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


//���� ��������(���ö�þ�)
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

	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			tempInputImageB[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C];
			tempInputImageG[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 1];
			tempInputImageR[i*m_Re_width + j] = m_InImg[i*m_Re_width * 3 + j*num_C + 2]; //*3 �ؾ� 3PIXEL��(R,G,B �ϱ�) ó���ȴ�.
		}
	}

	//--- ��� ���� �ʱ�ȭ --//
	for (i = 0; i<m_Re_size * 3; i++)
		m_OutputImage[i] = 255;

	// �� �÷� ��� �� ����ó��
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

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//  // �� �÷� ���� ���� �ؾ� �ϴϱ� resize*3 ũ��� m_OutputImage ���۸� �Ҵ��� ����.
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



//������ �뿪 ���͸�
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
	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
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


//������ �뿪 ���͸�
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
	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
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




//���� ���
void CImageProcessing_Team4Doc::OnScalingDown()
{
	int i, j, num_C;

	int n, m, index = 0;
	int M = 1;// M = ���� ���ø� ���� 
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

	//--- ��� ���� �ʱ�ȭ --//
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
			ValueR = (SumR / (M*M)); //����� ���
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
	// �������� ������ ó���ϴ� �Լ� 
	int i, j;

	for (i = 0; i<MAX; i++) {
		for (j = 0; j<MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}

// ������ ��ȯ �Լ� 
void CImageProcessing_Team4Doc::OnSwap(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//���� Ȯ�� - ������ �̿� ȭ�� ������
void CImageProcessing_Team4Doc::OnNearScaleUp()
{
	int i, j, num_C;
	double **tempOutputImageR, **tempOutputImageG, **tempOutputImageB;

	double ZoomRate = 1; // ���� Ȯ�� ���� 

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

	m_Re_height = int(ZoomRate*m_height); // Ȯ��� ������ ���� 
	m_Re_width = int(ZoomRate*m_width); // Ȯ��� ������ �ʺ� 
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	tempOutputImageR = Image2DMem(m_Re_height, m_Re_width);
	tempOutputImageG = Image2DMem(m_Re_height, m_Re_width);
	tempOutputImageB = Image2DMem(m_Re_height, m_Re_width);
	m_tempImageR = Image2DMem(m_height, m_width);
	m_tempImageG = Image2DMem(m_height, m_width);
	m_tempImageB = Image2DMem(m_height, m_width);

	//--- ��� ���� �ʱ�ȭ --//
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
			// �̿��� ȭ�Ҹ� �̿��� ����
		}
	}

	//--ó�� ����� 1���� ��� ����:m_OutputImage�� ������ ���� --//
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


//���� Ȯ�� - �缱�� ������ �̿�
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

	m_Re_height = int(ZoomRate*m_height); // Ȯ��� ������ ���� 
	m_Re_width = int(ZoomRate*m_width); // Ȯ��� ������ �ʺ� 
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size * 3];

	m_tempImageR = Image2DMem(m_height, m_width);
	m_tempImageG = Image2DMem(m_Re_height, m_width);
	m_tempImageB = Image2DMem(m_height, m_width);

	//--- ��� ���� �ʱ�ȭ --//
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

			s_H = r_H - i_H;  // ������� �Ÿ� ��� 
			s_W = r_W - i_W;  // �������� �Ÿ� ���

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
	while (Num >= 2) // ������ �ʺ� ���
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
	//--- 1���� ���� �������� �ӽ� ���۷� ���� ---//
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

	// ���ļ� ���� ��ȯ ������ �����ϱ� ���� �迭
	temp = new unsigned char *[m_height];
	for (i = 0; i<m_height; i++) {
		m_FFT[i] = new Complex[m_width];
		temp[i] = new unsigned char[m_width];
	}
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			Data[j].Re = (double)tempInputImageY[i*m_width + j];
			// �Է��� �� ���� ����, �Ǽ� ���� ���� ������ ��
			Data[j].Im = 0.0; // ���� ���� ���� 0
		}
		OnFft1d(Data, m_width, Log2N); // 1���� FFT
		for (j = 0; j<m_width; j++) { // ��� ����
			m_FFT[i][j].Re = Data[j].Re;
			m_FFT[i][j].Im = Data[j].Im;
		}
	}
	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // ������ ���� ���
	{
		Num >>= 1;
		Log2N++;
	}
	Data = new Complex[m_height];
	for (i = 0; i<m_width; i++) {
		for (j = 0; j<m_height; j++) {
			Data[j].Re = m_FFT[j][i].Re; // ������ �� ���� ����
			Data[j].Im = m_FFT[j][i].Im;
		}
		OnFft1d(Data, m_height, Log2N); // 1���� FFT
		for (j = 0; j<m_height; j++) { // ��� ����
			m_FFT[j][i].Re = Data[j].Re;
			m_FFT[j][i].Im = Data[j].Im;
		}
	}

	// FFT ���� ����� �������� ����ϱ� ���� ����
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
	// ���ø� ���� : ������ 4����ϰ� ���ҵ� ������ ���� ��Ī �� �¿� ��Ī
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
	OnShuffle(X, N, Log2N); // �Լ� ȣ��
	OnButterfly(X, N, Log2N, 1); // �Լ� ȣ��

}


void CImageProcessing_Team4Doc::OnShuffle(Complex* X, int N, int Log2N)
{
	// �Է� �������� ������ �ٱ��� ���� �Լ�
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
	// ����(Butterfly) ������ ���� �Լ�
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
	while (Num >= 2) // ���ļ���ȯ�ȿ����ǳʺ���
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
	m_IFFT = new Complex *[m_height]; // ����ȯ�ȿ��������ѹ迭
	for (i = 0; i<m_height; i++) {
		m_IFFT[i] = new Complex[m_width];
	}
	for (i = 0; i< m_height; i++) {
		for (j = 0; j<m_width; j++) { // ����������
			Data[j].Re = m_FFT[i][j].Re;
			Data[j].Im = m_FFT[i][j].Im;
		}
		OnIfft1d(Data, m_width, Log2N); // 1����IFFT
		for (j = 0; j<m_width; j++) {
			m_IFFT[i][j].Re = Data[j].Re; // �������
			m_IFFT[i][j].Im = Data[j].Im;
		}
	}
	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // ���ļ���ȯ�ȿ����ǳ��̰��
	{
		Num >>= 1;
		Log2N++;
	}
	Data = new Complex[m_height];
	for (i = 0; i<m_width; i++) {
		for (j = 0; j<m_height; j++) {
			Data[j].Re = m_IFFT[j][i].Re; // �ѿ�������
			Data[j].Im = m_IFFT[j][i].Im;
		}
		OnIfft1d(Data, m_height, Log2N); // 1����IFFT
		for (j = 0; j<m_height; j++) {
			m_IFFT[j][i].Re = Data[j].Re; // �������
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
	OnFft2d(); // ���ļ���ȯ
			   // ���ļ���ȯ�Ȱ����������ļ�������
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
	OnIfft2d(); // ���ļ�����ȯ
}
