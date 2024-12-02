
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include<cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, m_picture_1);
	DDX_Control(pDX, IDC_PIC2, m_picture_2);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	SetWindowText(_T("Image processing using MFC"));
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		m_picture_1.GetWindowRect(all_rect);

		SetDlgItemInt(IDC_POINT_BOX1, all_rect.Width());
		SetDlgItemInt(IDC_POINT_BOX2, all_rect.Height());

		m_picture_2.GetWindowRect(all_rect);

		SetDlgItemInt(IDC_POINT_BOX3, all_rect.Width());
		SetDlgItemInt(IDC_POINT_BOX4, all_rect.Height());
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!image.IsNull()) //사진추가 할 때, picture control이 NULL인지 체크
		image.Destroy(); //이전에 추가한 사진이 있으면 삭제
	//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_picture_1.GetWindowRect(all_rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	//CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_picture_1.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.
	//CImage image;//불러오고 싶은 이미지를 로드할 CImage 

	static TCHAR BASED_CODE szFilter[] = 
		_T("이미지 파일(*.BMP, *.GIF, *.JPG, *.PNG) | *.PNG; *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

	CFileDialog dlg(TRUE, _T("*.jpg"), _T("image"), OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		CString pathName = dlg.GetPathName();
		//MessageBox(pathName);
		image.Load(pathName);//이미지 로드

		//이미지를 픽쳐 컨트롤 크기로 조정
		image.StretchBlt(dc->m_hDC, 0, 0, all_rect.Width(), all_rect.Height(), SRCCOPY);
		ReleaseDC(dc);//DC 해제
	}
}




void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_picture_2.GetWindowRect(all_rect);
	dc = m_picture_2.GetDC();

	int histR[256] = { 0 }, histG[256] = { 0 }, histB[256] = { 0 };
	int lutR[256], lutG[256], lutB[256];
	int minR = 255, minG = 255, minB = 255;

	int w = image.GetWidth(), h = image.GetHeight();

	HBITMAP hBitmap = (HBITMAP)CopyImage(image, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	CImage result_his;
	result_his.Attach(hBitmap);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			histR[r]++;
			histG[g]++;
			histB[b]++;

			if (r < minR) minR = r;
			if (g < minG) minG = g;
			if (b < minB) minB = b;
		}
	}

	int sumR = 0, sumG = 0, sumB = 0;
	int totalPixels = w * h;
	// 누적 히스토그램을 통한 LUT 계산
	for (int i = 0; i < 256; i++)
	{
		sumR += histR[i];
		sumG += histG[i];
		sumB += histB[i];
		lutR[i] = (int)((float)(sumR - minR) / (totalPixels - minR) * 255);
		lutG[i] = (int)((float)(sumG - minG)/ (totalPixels - minG) * 255);
		lutB[i] = (int)((float)(sumB - minB) / (totalPixels - minB) * 255);
	}

	// 평활화 적용
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int newR = lutR[r];
			int newG = lutG[g];
			int newB = lutB[b];
			// 좌표 (x, y)에 평활화 적용된 색상 설정
			result_his.SetPixel(j, i, RGB(newR, newG, newB));
		}
	}

	// 결과 이미지를 Picture Control에 다시 표시
	result_his.StretchBlt(dc->m_hDC, 0, 0, all_rect.Width(), all_rect.Height(), SRCCOPY);
	result_his.Detach();
	ReleaseDC(dc);
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_picture_2.GetWindowRect(all_rect);
	dc = m_picture_2.GetDC();

	int w = image.GetWidth(), h = image.GetHeight();

	HBITMAP hBitmap = (HBITMAP)CopyImage(image, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	CImage result_con;
	result_con.Attach(hBitmap);

	int minR = 255, minG = 255, minB = 255;
	int maxR = 0, maxG = 0, maxB = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			COLORREF color = image.GetPixel(j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			
			if (r < minR) minR = r;
			if (r > maxR) maxR = r;
			if (g < minG) minG = g;
			if (g > maxG) maxG = g;
			if (b < minB) minB = b;
			if (b > maxB) maxB = b;
		}

	}

	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// 콘트라스트 조정 계산식 수정
			int newR = (float)(r - minR) / (maxR - minR) * 255;
			int newG = (float)(g - minG) / (maxG - minG) * 255;
			int newB = (float)(b - minB) / (maxB - minB) * 255;

			// 픽셀 값을 0-255 범위로 클램프
			newR = min(max(newR, 0), 255);
			newG = min(max(newG, 0), 255);
			newB = min(max(newB, 0), 255);

			// 새로운 픽셀 값 설정
			result_con.SetPixel(j, i, RGB(newR, newG, newB));
		}
	}
	result_con.StretchBlt(dc->m_hDC, 0, 0, all_rect.Width(), all_rect.Height(), SRCCOPY);
	result_con.Detach();
	ReleaseDC(dc);
}

void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_picture_1.GetWindowRect(all_rect);
	dc = m_picture_1.GetDC();

	int histR[256] = { 0 }, histG[256] = { 0 }, histB[256] = { 0 };
	int lutR[256], lutG[256], lutB[256];

	int w = image.GetWidth(), h = image.GetHeight();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			histR[r]++;
			histG[g]++;
			histB[b]++;
		}
	}

	int sumR = 0, sumG = 0, sumB = 0;
	int totalPixels = w * h;
	// 누적 히스토그램을 통한 LUT 계산
	for (int i = 0; i < 256; i++)
	{
		sumR += histR[i];
		sumG += histG[i];
		sumB += histB[i];
		lutR[i] = (int)((float)sumR / totalPixels * 255);
		lutG[i] = (int)((float)sumG / totalPixels * 255);
		lutB[i] = (int)((float)sumB / totalPixels * 255);
	}

	// 평활화 적용
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int newR = lutR[r];
			int newG = lutG[g];
			int newB = lutB[b];
			// 좌표 (x, y)에 평활화 적용된 색상 설정
			image.SetPixel(j, i, RGB(newR, newG, newB));
		}
	}

	// 결과 이미지를 Picture Control에 다시 표시
	image.StretchBlt(dc->m_hDC, 0, 0, all_rect.Width(), all_rect.Height(), SRCCOPY);
	ReleaseDC(dc);

	/*===============================================================================*/
	m_picture_2.GetWindowRect(all_rect);
	dc = m_picture_2.GetDC();

	int minR = 255, minG = 255, minB = 255;
	int maxR = 0, maxG = 0, maxB = 0;

	w = image.GetWidth(), h = image.GetHeight();
	
	CImage con_result;

	HBITMAP hBitmap = (HBITMAP)CopyImage(image, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	con_result.Attach(hBitmap);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{

			COLORREF color = image.GetPixel(j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r < minR) minR = r;
			if (r > maxR) maxR = r;
			if (g < minG) minG = g;
			if (g > maxG) maxG = g;
			if (b < minB) minB = b;
			if (b > maxB) maxB = b;
		}

	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			COLORREF color = image.GetPixel(j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			int newR = (int)((float)(r - minR) / (maxR - minR) * 255);
			int newG = (int)((float)(g - minG) / (maxG - minG) * 255);
			int newB = (int)((float)(b - minB) / (maxB - minB) * 255);

			// 새로운 픽셀 값 설정
			con_result.SetPixel(j, i, RGB(newR, newG, newB));
		}
	}

	con_result.StretchBlt(dc->m_hDC, 0, 0, all_rect.Width(), all_rect.Height(), SRCCOPY);
	con_result.Detach();
	image.Detach();
	ReleaseDC(dc);
}

