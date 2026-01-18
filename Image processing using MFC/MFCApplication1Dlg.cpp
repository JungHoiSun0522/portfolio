
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
	DDX_Control(pDX, IDC_PIC1, m_pic1);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButtonHist)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButtonCont)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButtonHistToCont)
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	//CWnd* pPicture1 = GetDlgItem(IDC_PIC1); // 기준 컨트롤 ID
	//CWnd* pPicture2 = GetDlgItem(IDC_PIC2); // 크기를 변경할 컨트롤 ID

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
		m_pic1.GetWindowRect(rect);

		SetDlgItemInt(IDC_POINT_BOX1, rect.Width());
		SetDlgItemInt(IDC_POINT_BOX2, rect.Height());

		m_pic2.GetWindowRect(rect);

		SetDlgItemInt(IDC_POINT_BOX3, rect.Width());
		SetDlgItemInt(IDC_POINT_BOX4, rect.Height());

		DrawToPicture(IDC_PIC1, m_viewPic1);
		DrawToPicture(IDC_PIC2, m_viewPic2);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication1Dlg::ClearPicture(int picID)
{
	CWnd* pPic = GetDlgItem(picID);
	if (!pPic) return;

	CClientDC dc(pPic);
	CRect rc;
	pPic->GetClientRect(&rc);
	dc.FillSolidRect(&rc, RGB(255, 255, 255));
}

void CMFCApplication1Dlg::UpdateViews(const CImage* pic1, const CImage* pic2)
{
	m_viewPic1 = pic1;
	m_viewPic2 = pic2;

	// 다이얼로그 OnPaint 트리거
	Invalidate(FALSE);

	// 그림이 빨리 갱신되도록 Pic 컨트롤도 같이 무효화(선택이지만 권장)
	if (GetDlgItem(IDC_PIC1)) GetDlgItem(IDC_PIC1)->Invalidate(FALSE);
	if (GetDlgItem(IDC_PIC2)) GetDlgItem(IDC_PIC2)->Invalidate(FALSE);
}

static inline BYTE ClampU8(int v)
{
	if (v < 0) return 0;
	if (v > 255) return 255;
	return (BYTE)v;
}

static void SetGrayPalette(CImage& img)                                              // 8bpp 그레이 팔레트 설정
{
	RGBQUAD table[256];                                                              // 팔레트 배열
	for (int i = 0; i < 256; ++i)                                                    // 0~255 반복
	{
		table[i].rgbRed = table[i].rgbGreen = table[i].rgbBlue = (BYTE)i;            // R, G, B 설정
		table[i].rgbReserved = 0;                                                    // 예약값 0
	}
	img.SetColorTable(0, 256, table);                                                // 팔레트 적용
}

static bool CloneImage(const CImage& src, CImage& dst)                               // CImage 안전 복사
{
	if (src.IsNull()) return false;                                                  // 소스 없으면 실패

	dst.Destroy();                                                                   // 기존 dst 제거
	dst.Create(src.GetWidth(), src.GetHeight(), src.GetBPP());                       // 동일 크기/비트 생성

	if (dst.IsNull()) return false;                                                  // 생성 실패 체크

	if (dst.GetBPP() == 8)                                                           // 8bpp면
		SetGrayPalette(dst);                                                         // 팔레트 세팅(안하면 깨질 수 있음)

	HDC hdcDst = dst.GetDC();                                                        // dst DC 획득
	HDC hdcSrc = ((CImage&)src).GetDC();                                             // src DC 획득(비 const라 캐스팅)
	BitBlt(hdcDst, 0, 0, dst.GetWidth(), dst.GetHeight(), hdcSrc, 0, 0, SRCCOPY);    // 전체 복사
	((CImage&)src).ReleaseDC();                                                      // src DC 해제
	dst.ReleaseDC();                                                                 // dst DC 해제

	return true;                                                                     // 성공
}

static void BuildEqualizeLUT(const int hist[256], int total, BYTE lut[256])
{
	int cdf[256] = { 0 };
	cdf[0] = hist[0];
	for (int i = 1; i < 256; ++i) cdf[i] = cdf[i - 1] + hist[i];

	int cdf_min = 0;
	for (int i = 0; i < 256; ++i)
	{
		if (cdf[i] != 0) { cdf_min = cdf[i]; break; }
	}

	const int den = total - cdf_min;
	for (int i = 0; i < 256; ++i)
	{
		int v = 0;
		if (den > 0) v = (cdf[i] - cdf_min) * 255 / den;
		lut[i] = ClampU8(v);
	}
}

bool EqualizePerChannel_InPlace(CImage& img)
{
	if (img.IsNull()) return false;

	const int w = img.GetWidth();
	const int h = img.GetHeight();
	const int bpp = img.GetBPP();
	if (w <= 0 || h <= 0) return false;

	// 8bpp (그레이)
	if (bpp == 8)
	{
		int hist[256] = { 0 };

		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);  // y번째 행 시작 주소
			if (!row) return false;

			for (int x = 0; x < w; ++x)
				hist[row[x]]++;
		}

		BYTE lut[256];
		BuildEqualizeLUT(hist, w * h, lut);

		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);
			if (!row) return false;

			for (int x = 0; x < w; ++x)
				row[x] = lut[row[x]];
		}
		return true;
	}

	// 24/32bpp (컬러) : B,G,R 각각 평활화
	if (bpp == 24 || bpp == 32)
	{
		const int bytesPerPixel = (bpp == 24) ? 3 : 4;

		int histB[256] = { 0 }, histG[256] = { 0 }, histR[256] = { 0 };

		// 히스토그램 계산
		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);
			if (!row) return false;

			for (int x = 0; x < w; ++x)
			{
				BYTE* p = row + x * bytesPerPixel; // [B][G][R][A]
				histB[p[0]]++;
				histG[p[1]]++;
				histR[p[2]]++;
			}
		}

		BYTE lutB[256], lutG[256], lutR[256];
		const int total = w * h;
		BuildEqualizeLUT(histB, total, lutB);
		BuildEqualizeLUT(histG, total, lutG);
		BuildEqualizeLUT(histR, total, lutR);

		// LUT 적용
		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);
			if (!row) return false;

			for (int x = 0; x < w; ++x)
			{
				BYTE* p = row + x * bytesPerPixel;
				p[0] = lutB[p[0]];
				p[1] = lutG[p[1]];
				p[2] = lutR[p[2]];
				// p[3] (알파) 유지
			}
		}
		return true;
	}

	// 그 외 bpp는 미지원
	return false;
}

bool ApplyContrast_InPlace(CImage& img, double alpha)
{
	if (img.IsNull()) return false;

	const int w = img.GetWidth();
	const int h = img.GetHeight();
	const int bpp = img.GetBPP();
	if (w <= 0 || h <= 0) return false;

	if (bpp == 8)
	{
		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);
			if (!row) return false;

			for (int x = 0; x < w; ++x)
			{
				int v = row[x];
				int out = (int)((v - 128) * alpha + 128);
				row[x] = ClampU8(out);
			}
		}
		return true;
	}

	if (bpp == 24 || bpp == 32)
	{
		const int bytesPerPixel = (bpp == 24) ? 3 : 4;

		for (int y = 0; y < h; ++y)
		{
			BYTE* row = (BYTE*)img.GetPixelAddress(0, y);
			if (!row) return false;

			for (int x = 0; x < w; ++x)
			{
				BYTE* p = row + x * bytesPerPixel;

				p[0] = ClampU8((int)((p[0] - 128) * alpha + 128)); // B
				p[1] = ClampU8((int)((p[1] - 128) * alpha + 128)); // G
				p[2] = ClampU8((int)((p[2] - 128) * alpha + 128)); // R
			}
		}
		return true;
	}

	return false;
}

void CMFCApplication1Dlg::DrawToPicture(int picID, const CImage* img)
{
	if (!img || img->IsNull())
	{
		ClearPicture(picID);
		return;
	}

	CWnd* pPic = GetDlgItem(picID);
	if (!pPic) return;

	CClientDC dc(pPic);
	CRect rc;
	pPic->GetClientRect(&rc);

	// 컨트롤 크기에 맞춰 Draw(= 내부적으로 StretchBlt)
	img->Draw(dc.GetSafeHdc(), rc);
}

void CMFCApplication1Dlg::OnBnClickedButtonLoad()                                                      // 버튼1: 로드
{
	CFileDialog dlg(TRUE, nullptr, nullptr,                                          // 파일 열기 대화상자
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,                                        // 옵션
		_T("Image Files (*.bmp;*.jpg;*.jpeg;*.png)|*.bmp;*.jpg;*.jpeg;*.png||"));    // 필터

	if (dlg.DoModal() != IDOK) return;                                               // 취소면 종료

	m_srcFull.Destroy();                                                             // 원본 제거
	m_eqFull.Destroy();                                                              // 캐시 제거
	m_conFull.Destroy();                                                             // 캐시 제거
	m_eqConFull.Destroy();                                                           // 캐시 제거

	if (FAILED(m_srcFull.Load(dlg.GetPathName()))) return;                           // 로드 실패 시 종료

	UpdateViews(&m_srcFull, nullptr);                                                // Pic1=원본, Pic2=비움
}

void CMFCApplication1Dlg::OnBnClickedButtonHist()                                                      // 버튼2: 원본은 유지, Pic2=평활화
{
	if (m_srcFull.IsNull()) return;                                                  // 원본 없으면 종료

	CloneImage(m_srcFull, m_eqFull);                                                 // 원본 복제 → m_eqFull
	EqualizePerChannel_InPlace(m_eqFull);                                            // 채널별 평활화

	UpdateViews(&m_srcFull, &m_eqFull);                                              // Pic1=원본 유지, Pic2=평활화
}

void CMFCApplication1Dlg::OnBnClickedButtonCont()                                                      // 버튼3: 원본은 유지, Pic2=콘트라스트
{
	if (m_srcFull.IsNull()) return;                                                  // 원본 없으면 종료

	CloneImage(m_srcFull, m_conFull);                                                // 원본 복제 → m_conFull
	ApplyContrast_InPlace(m_conFull, 1.3);                                           // 콘트라스트 적용

	UpdateViews(&m_srcFull, &m_conFull);                                             // Pic1=원본 유지, Pic2=콘트라스트
}

void CMFCApplication1Dlg::OnBnClickedButtonHistToCont()                                                      // 버튼4: Pic1=평활화, Pic2=평활화+콘트라스트
{
	if (m_srcFull.IsNull()) return;                                                  // 원본 없으면 종료

	CloneImage(m_srcFull, m_eqFull);                                                 // 원본 복제 → 평활화 베이스
	EqualizePerChannel_InPlace(m_eqFull);                                            // 채널별 평활화

	CloneImage(m_eqFull, m_eqConFull);                                               // 평활화 결과 복제
	ApplyContrast_InPlace(m_eqConFull, 1.3);                                         // 콘트라스트 적용

	UpdateViews(&m_eqFull, &m_eqConFull);                                            // Pic1=평활화, Pic2=평활화+콘트라스트
}