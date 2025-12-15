#pragma once
#include<vector>
#include<WinSock2.h>

using namespace std;

#pragma comment (lib, "ws2_32.lib")
#pragma comment (lib, "user32.lib")

#define UM_MESSAGE (WM_USER + 100)
#define UM_IP_MESSAGE (WM_USER + 101)

#define PORT 52345

// CSocketProc 명령 대상

struct CLIENT_XTC { //클라이언트의 소켓과 클래스의 포인터를 담고있는 구조체
	class CSocketProc* pServer;
	SOCKET sock;
};

struct CLIENT_INFO
{
	SOCKET sock;
	CString ip;
};

class CSocketProc : public CObject
{
public:
	CSocketProc();
	virtual ~CSocketProc();
	void Server_Run();
	void Server_Stop();
	void Log(const CString& msg);
	void SetOwnerWnd(HWND hWnd) { m_hWnd = hWnd; }
	DWORD GetLocalIPv4Addr();

protected:
	HWND m_hWnd;
	SOCKET m_listenSock;
	WSADATA wsa;
	vector<CLIENT_INFO> clients;
	static DWORD WINAPI listenSock(LPVOID lpParam);
	static DWORD WINAPI ClientThread(LPVOID arg);
	void ClientDisconnected(SOCKET sock);
	void BroadcastToClients(SOCKET sock, const char* str, int len);
	bool m_bRunning = false; // 서버가 실행 중이라는 플래그
	bool m_bState = true; // 서버 종료에 대한 플래그. 종료 버튼을 누르면 true로 변환.
	CCriticalSection m_criClient; // 임계영역을 사용하기 위한 변수
};