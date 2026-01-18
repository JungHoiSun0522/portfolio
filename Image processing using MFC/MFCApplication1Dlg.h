
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once
#include <string>


// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	const CImage* m_viewPic1 = nullptr;  // 현재 Pic1에 보여줄 이미지
	const CImage* m_viewPic2 = nullptr;  // 현재 Pic2에 보여줄 이미지

	CStatic m_pic1;
	CStatic m_pic2;
	CRect rect;
	CDC* dc;
	CImage m_srcFull;      // 버튼1로 로드한 "원본(풀 해상도)"
	CImage m_eqFull;       // 원본에 히스토그램 평활화(풀 해상도)
	CImage m_conFull;      // 원본에 콘트라스트(풀 해상도)
	CImage m_eqConFull;    // 평활화한 결과에 콘트라스트(풀 해상도)
	
	void DrawToPicture(int picID, const CImage* img);
	void ClearPicture(int picID);
	void UpdateViews(const CImage* pic1, const CImage* pic2);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
};
