
// ImageProcessingDoc.cpp : CImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ImageProcessing.h"
#endif

#include "ImageProcessingDoc.h"
#include <bitset>
#include <propkey.h>
#include "DiologZoomR.h" // ������ Ŭ���� �� �� �ְ� ��� �߰�
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


// CImageProcessingDoc ����/�Ҹ�

CImageProcessingDoc::CImageProcessingDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CImageProcessingDoc::~CImageProcessingDoc()
{
}

BOOL CImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CImageProcessingDoc serialization

void CImageProcessingDoc::Serialize(CArchive& ar)
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
void CImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CImageProcessingDoc ����

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


// CImageProcessingDoc ���


BOOL CImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName) // IpszPathName = ���� ��ο� ���� �̸�, Ipsz ��������
{
	if (!CDocument::OnOpenDocument(lpszPathName)) //������ ������ �Լ� ����
		return FALSE;

	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	if (File.GetLength() == 32 * 32) {
		m_height = 32;
		m_width = 32;
	}
	else if (File.GetLength() == 64 * 64) {
		m_height = 64;
		m_width = 64;
	}
	else if (File.GetLength() == 128 * 128) {
		m_height = 128;
		m_width = 128;
	}
	else if (File.GetLength() == 256 * 256) {
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { 
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) { 
		m_height = 480;
		m_width = 640;
	}
	else if (File.GetLength() == 176 * 144) {
		m_height = 144;
		m_width = 176;
	}
	else if (File.GetLength() == 176 * 216) {
		m_height = 216;
		m_width = 176;
	}
	else {
		AfxMessageBox(L"NotSupport Image Size", MB_OK | MB_ICONEXCLAMATION);
		return 0; 
	}
	m_size = m_width* m_height; // ���� ������ ũ�⸦ ���
	m_InputImage = new unsigned char[m_size]; // ���� ������ ũ�⸸ŭ �̹��� ���۸� �������� �Ҵ�
	for (int i = 0; i<m_size; i++)  // ���� �ʱ�ȭ(�������)
		m_InputImage[i] = 255;     
	File.Read(m_InputImage, m_size);  // �̹��� ���ۿ� m_size��ŭ ������ �о� ��.
	File.Close();

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
	if (dlg.DoModal() == IDOK) // DoModal() -> ���� API(�����츦 ����ش�.) IDOK = Ȯ�ι�ư
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
				// ���ġ �Ͽ� ���� Ȯ��
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
	if (dlg.DoModal() == IDOK) // DoModal() -> ���� API(�����츦 ����ش�.) IDOK = Ȯ�ι�ư
	{
		msg.Format(L"�Է��� ���� = %2d,%2d", dlg.T1,dlg.T2); // Format() => ���������� CString Ŭ������ ���� API
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

	//�Է� ���� �ּҰ� ã��

	for (i = 0 ;i <m_size ; i++)
	{
		if (m_InputImage[i] < MIN )
			MIN = m_InputImage[i];
	}
	
	// �Է� ���� �ִ밪 ã��
	for (i = 0; i <m_size; i++)
	{
		if ( m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	//��� ���� ���� �Ҵ�
	m_OutputImage = new unsigned char[m_Re_size];

	// ������׷� ��Ʈ��Ī
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

	//�ʱ�ȭ
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	//�� �� ���� : ������׷� ����
	for (i = 0; i < m_size; i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//���� ������׷� ����
	for (i = 0; i < 256; i++)
	{
		SUM += m_HIST[i];
		m_Sum_of_HIST[i] = SUM;
	}
	//��� ���� ���� �Ҵ�
	m_OutputImage = new unsigned char[m_Re_size];

	//�Է� ������ ��Ȱȭ�� �������� ���
	for (i = 0; i < m_size; i++)
	{
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}
}

void CImageProcessingDoc::OnHistogram()
{
	// ������׷��� ���� 0~255 
	// ������׷��� ũ�� ���� MAX=255�� ����ȭ�Ͽ� ��� 
	// ����Ʈ�׷��� ũ�� : 256*256 ���� 

	int i, j, value;    unsigned char LOW, HIGH;    double MAX, MIN, DIF;
	m_Re_height = 256;    
	m_Re_width = 256;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	// �ʱ�ȭ 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// �� �� ����: ������׷� ���� // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// ����ȭ 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// ����ȭ�� ������׷�
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

	// ������׷��� ����ϰ� �� �Ʒ� �κп� ������׷��� ���� ǥ��
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
	// ���ϴ� ������׷��� �ִ� ������ �Է¹��� 
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_size) {
			m_DTEMP = new unsigned char[m_size];
			File.Read(m_DTEMP, m_size);
			File.Close();
		}
		else {
			AfxMessageBox(msg);
			// ���� ũ���� ������ ������� �� 
			return;
		}
	}

	LOW = 0;
	HIGH = 255;

	// �ʱ�ȭ 
	for (i = 0; i<256; i++) {
		m_HIST[i] = LOW;       m_DHIST[i] = LOW;       m_TABLE[i] = LOW;
	}
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];       m_HIST[value]++;
		Dvalue = (int)m_DTEMP[i];       m_DHIST[Dvalue]++;
	}

	// ���� ������׷� ���� 
	for (i = 0; i<256; i++) {
		SUM += m_HIST[i];       
		m_Sum_of_HIST[i] = SUM;       
		DSUM += m_DHIST[i];      
		m_Sum_Of_DHIST[i] = DSUM;
	}
	// ���� ������ ��Ȱȭ 
	for (i = 0; i<m_size; i++) {
		Temp = m_InputImage[i];
		m_Org_Temp[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}

	// ���� ������׷����� �ּҰ��� �ִ밪 ���� 
	DMIN = m_Sum_Of_DHIST[0];
	DMAX = m_Sum_Of_DHIST[255];

	// ���ϴ� ������ ��Ȱȭ //    
	for (i = 0; i < 256; i++) {
		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i] - DMIN)*HIGH / (DMAX - DMIN));
	}

    // ������̺��� �̿��� ��ȭ // 
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

	if (dlg.DoModal() == IDOK) // DoModal() -> ���� API(�����츦 ����ش�.) IDOK = Ȯ�ι�ư
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

// 2���� �迭�� 1���� �迭��
/*
for (int i = 0; i < m_Re_Height; i++)
	for (int j = 0; j < m_Re_Width; j++)
		m_OutputImage[i*m_Re_Width+j] = m_InputImage[i][j];
*/

// i*m_Re_Width + j = i �� j��° ĭ

// 1���� �迭�� 2���� �迭��
/*
for(i=0 ; i<m_height ; i++){
	for(j=0 ; j<m_width ; j++){
	tempInputImage[i+1][j+1]= (double)Target[i * m_width + j];
	}
}
�� �� +1�� ����? 
*/

void CImageProcessingDoc::OnEmbossing()
{
	int i, j, sum,avg ;
	double EmboMask[3][3] = { { -1., 0., 0. },{ 0., 0., 0. },{ 0., 0., 1. } };
	// ����ũ���� : �������� ������ ����ũ �߿� �ϳ� ����
	// double EmboMask[3][3] = {{0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.}}; // ����� ���� 1�̹Ƿ� ȸ�� ó���ص� ��� ��� �� �״�� ����
	// double EmboMask[3][3] = {{1., 1., 1.}, {1., -8.,1.}, {1., 1., 1.}}; // ����� ���� 0 �̹Ƿ� ��� �κи� ���� �ȴ�.
	/* ������ ȸ�� ����ũ�� ����� ���� 0�̰�, ��� ���� 0�̴�. */
	/* ������ ����ũ�� Ư¡ : ����� �ִ� ����� �ٸ� ����� ����Ű���� �����Ѵ�. ��輱���� �簢�� ȿ���� ���� �� �ִ�. */
	/* ����ũ�� ������ �����Ƿ� ȸ�� ó���� ������ ������ ȭ�� ���� ������. ���� ó�� �� ������ ��� ���� �����־�� �Ѵ�. */
	/* 8��Ʈ �׷��� �������� ȸ�� ó�� �����Ѵٸ� �ִ� ��� ȭ�Ұ��� ������ 128�� �����ָ� ���� ���� ���� �� �ִ�. */

	/* ��� �̹��� ���� ũ�� ����*/
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* ��� �̹��� ���ۿ� �ӽ� �̹��� ���� �Ҵ�*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);//ȸ��ó��
    
	sum = 0;
	avg = 0;
	/* ���� ���� ��հ� ��� */
	for (i = 0; i<m_Re_size; i++)
		sum += (int)m_InputImage[i]; // �ϴ� �������� ���Ѵ�.
	avg = (int)(sum / m_Re_size);    // �������� ��ü �ȼ� ���� ������. 

	/* ȸ�� ó�� ����� 0~ 255 ���� ���� �ǵ��� �Ѵ�. */
	/* ȸ�� ó���� �̹� ������ �Լ� ȣ��� �Ǿ��ִ� �����̴�. */
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	} 

	  // 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


// ȸ�� ó���� �Ͼ�� �Լ��̴�. 
double** CImageProcessingDoc::OnMaskProcess(unsigned char* Target, double  Mask[3][3])
{
	int i, j, n, m;
	double **tempInputImage, **tempOutputImage, S = 0.0;

	/* �Է°��� ���� �޸� �Ҵ� */
	tempInputImage = Image2DMem(m_height + 2, m_width + 2); // ����ũ ó�� �ؾ� �ϱ� ������ �׵θ��� ��ĭ �� �� ��(�е�)

	/* ��°��� ���� �޸� �Ҵ�*/
	tempOutputImage = Image2DMem(m_height, m_width);

	// 1�����Է¿���m_InputImage[]�ǰ���2�����迭tempInputImage[][]���Ҵ�
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	// ȸ������ => ����ũ ũ�� �ٲ�� 3��&4�� ������ ���� ũ�� �޶���
	for (i = 0; i<m_height; i++) {
		for (j = 0; j<m_width; j++) {
			for (n = 0; n<3; n++) {
				for (m = 0; m<3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			} // ȸ������ũ��ũ�⸸ŭ�̵��ϸ鼭��������
			tempOutputImage[i][j] = S; // �����Ȱ�����¸޸𸮿�����
			S = 0.0; // ������������̵��ϸ鴩�������ʱ�ȭ. �ݵ�� ���� �� ��!
		}
	}
	return tempOutputImage; // ������۹�ȯ
}

//2���� �迭�� �Ҵ��ϴ� �Լ��̴�.
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
	} // �Ҵ��2�����޸𸮸��ʱ�ȭ
	return temp;
}

// ����ȭ�� �ϴ� �Լ��̴�.
double** CImageProcessingDoc::OnScale(double** Target, int height, int width)
{
	// �Ϲ����� ����ȭ�� ���� �װ� 2���� �迭���� �Ϸ��� �Լ��� ���� ��. 
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
	// ���� ����ũ ������ �ٲٸ�? -> �� ����ũ ������ / OnMaskProcess �Ű�����& ȸ������ ������
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	/* ��� �̹��� ���ۿ� �ӽ� �̹��� ���� �Ҵ�*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);//ȸ��ó��

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
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

	/* ��� �̹��� ���ۿ� �ӽ� �̹��� ���� �Ҵ�*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);//ȸ��ó��

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
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

	/* ��� �̹��� ���ۿ� �ӽ� �̹��� ���� �Ҵ�*/
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);//ȸ��ó��

	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}

	// 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
	for (i = 0; i<m_Re_height; i++) {
		for (j = 0; j<m_Re_width; j++) {
			m_OutputImage[i*m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}

}


void CImageProcessingDoc::OnHpfSharp()
{
	/* ������ ������ ����ũ�� ���� 0���� ������ ȸ�� ����ũ�ϰ�� �ٸ�����, ������ ���� Ư���� ���� */
	/* ������ ������ �����Ű�� ������ ������ ����*/
	/* ��� ū ��� ���� �ֺ��� ���� ���� ������ ����ũ �Ǿ� ��輱�� ���� �ε巯���� �� */
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
	// 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
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
		// ��ȭ���ڸ��̿��Ͽ�������Է¹޴´�.
	}
	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask); // �����󿡼� ������ ������ ��� ���͸� ����

	/* ������ ���� ���� ó�� */
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
	// 2�����迭m_tempImage[][] �����͸�1�����迭m_OutputImage[]�κ���
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

	//�ʱ�ȭ
	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	//�� �� ���� : ������׷� ����
	for (i = 0; i < m_size; i++)
	{
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}
	//���� ������׷� ����
	for (i = 0; i < 256; i++)
	{
		SUM += m_HIST[i];
		m_Sum_of_HIST[i] = SUM;
	}
	//��� ���� ���� �Ҵ�
	m_OutputImage = new unsigned char[m_Re_size];

	//�Է� ������ ��Ȱȭ�� �������� ���
	for (i = 0; i < m_size; i++)
	{
		Temp = m_InputImage[i];
		m_OutputImage[i] = (unsigned char)(m_Sum_of_HIST[Temp] * HIGH / m_size);
	}

	// �ʱ�ȭ 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// �� �� ����: ������׷� ���� // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	// ����ȭ 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// ����ȭ�� ������׷�
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

	// �ʱ�ȭ 
	for (i = 0; i<256; i++)
		m_HIST[i] = LOW;

	// �� �� ����: ������׷� ���� // 
	for (i = 0; i<m_size; i++) {
		value = (int)m_OutputImage[i];
		m_HIST[value]++;
	}
	// ����ȭ 
	MAX = m_HIST[0];
	MIN = m_HIST[0];

	for (i = 0; i<256; i++) {
		if (m_HIST[i] > MAX)          MAX = m_HIST[i];
	}
	for (i = 0; i<256; i++) {
		if (m_HIST[i] < MIN)          MIN = m_HIST[i];
	}

	DIF = MAX - MIN;

	// ����ȭ�� ������׷�
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

		TEMP = new double[m_size]; // �Է� ���� ũ��� ������ �޸� �Ҵ�

		LEVEL = 256; // ���� ������ ����ȭ �ܰ�
		HIGH = 256.;

		value = (int)pow(2, dlg.m_Constant); // ����ȭ �ܰ踦 �Է� ���� ������ ����

		for (i = 0; i < m_size; i++)
		{
			for (j = 0; j < value; j++)
			{
				if ((m_InputImage[i] >= (LEVEL / value)*j) && (m_InputImage[i] < (LEVEL / value)*(j + i)))
				{
					TEMP[i] = (double)(HIGH / value)*j; // ����ȭ ������ �۰ų� ũ�� ����ȭ ����
				}
			}
		}
		for (i = 0; i < m_size; i++)
		{
			m_OutputImage[i] = (unsigned char)TEMP[i]; // �ݵ�� Ÿ�� ĳ���� ���� �� �� 
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
