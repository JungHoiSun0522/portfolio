
// ServerDlg.h: 헤더 파일
//

#pragma once
#include "CSocketProc.h"

#define UM_MESSAGE (WM_USER + 100)
#define UM_IP_MESSAGE (WM_USER + 101)

using namespace std;

// CServerDlg 대화 상자
class CServerDlg : public CDialogEx
{
// 생성입니다.
public:
	CServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER_DIALOG };
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
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonStop();
	afx_msg LRESULT AddMessage(WPARAM wParam, LPARAM lParam);
protected:
	CListBox m_strLog;
	CSocketProc m_sockProc;
	CIPAddressCtrl m_cIPAddrCtrl;
	afx_msg LRESULT CallIPAddr(WPARAM wParam, LPARAM lParam);
	CEdit m_cPort;
};
