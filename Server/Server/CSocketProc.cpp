// CSocketProc.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "CSocketProc.h"
#include<string>

// CSocketProc

CSocketProc::CSocketProc()
{
}

CSocketProc::~CSocketProc()
{
}

void CSocketProc::Log(const CString& msg) // 리스트 박스에 출력할 내용을 보냄.
{
	if (m_hWnd == NULL) return;

	// 힙에 문자열 복사해서 포인터 전달
	CString* pStr = new CString(msg);
	SendMessage(m_hWnd, UM_MESSAGE, 0, (LPARAM)pStr);
}

DWORD CSocketProc::GetLocalIPv4Addr() // 서버가 실행 중인 IP주소를 IPAddrCtrl에 출력하도록 메세지를 보냄.
{
	char host[256];

	if (gethostname(host, sizeof(host)) == SOCKET_ERROR) // 서버 소켓이 초기화가 안 되어있으면 리턴.
		return 0;

	HOSTENT* ent = gethostbyname(host);
	if (!ent || ent->h_addrtype != AF_INET || !ent->h_addr_list[0]) // 주소 체계가 IPv4가 아니거나 ent가 초기화 되어있지 않으면 리턴
		return 0;

	IN_ADDR addr = {};
	memcpy(&addr, ent->h_addr_list[0], sizeof(IN_ADDR));

	return PostMessage(m_hWnd, UM_IP_MESSAGE, 0, addr.S_un.S_addr);
}

void CSocketProc::Server_Run()
{
	if (!m_bRunning)
	{
		Log(_T("서버를 실행합니다."));
		m_bRunning = true;
		m_bState = false;
		HANDLE hThread = CreateThread(NULL, 0, listenSock, this, 0, NULL); // 서버 실행을 위한 소켓 초기화와 
	}																	   // aceept()를 수행할 워커쓰레드 실행
}

void CSocketProc::Server_Stop()
{
	if (m_bRunning)
	{
		m_bRunning = false;
		m_bState = true;
		closesocket(m_listenSock);  // accept()로 대기 중인 소켓을 깨움
		m_listenSock = INVALID_SOCKET; // INVALID_SOCKET으로 유효하지 않은 소켓으로 만듦
	}
}

void CSocketProc::ClientDisconnected(SOCKET sock)
{
	CSingleLock lock(&m_criClient, TRUE); // 임계영역으로 락을 걸어 벡터로 저장한 클라이언트의 삭제 연산이 꼬이지 않도록 보호.
	CString ipAddr = _T("Unknown.");

	for (auto now = clients.begin(); now != clients.end(); now++)
	{
		if (now->sock == sock)
		{
			ipAddr = now->ip;
			clients.erase(now);
			break;
		}
	}
	Log(_T("[클라이언트 접속 종료] IP : ") + ipAddr);
}

void CSocketProc::BroadcastToClients(SOCKET sock, const char* str, int len) // 메세지를 전달받은 클라이언트를 제외하고 
{																			// 타 클라이언트에게 메세지를 뿌림.
	int recval;
	for (auto now : clients)
	{
		if (now.sock == sock)
			continue;

		recval = send(now.sock, str, len, 0);
		if (recval == SOCKET_ERROR && !m_bState) // 소켓 에러인데, 종료 버튼을 누르지 않은 상태일 때 수행
			Log(_T("[클라이언트 IP : ") + now.ip + _T("] send() Error"));
	}
}

DWORD WINAPI CSocketProc::ClientThread(LPVOID arg)
{
	CLIENT_XTC* pCtx = (CLIENT_XTC*)arg; // 쓰레드를 생성할 때 넘겨받은 객체를 워커쓰레드의 구조체 지역 변수로 넘겨줌
	CSocketProc* sockProc = pCtx->pServer; // 해당 구조체로 넘어온 변수에 저장된 CSocketProc의 포인터 객체를 넘겨줌
	SOCKET client = pCtx->sock; // 위와 마찬가지로 소켓 정보를 넘겨줌
	char msg[1024];

	while (sockProc->m_bRunning)
	{
		int recval = recv(client, msg, sizeof(msg) - 1, 0);
		//CString t; t.Format(_T("recv ret=%d WSA=%d"), recval, WSAGetLastError());  //=> 디버깅용
		//sockProc->Log(t);															 //=> 디버깅용
		//CString s;																 //=> 디버깅용
		//s.Format(_T("recval : %d"), recval);										 //=> 디버깅용
		if (sockProc->m_bState) // 종료 버튼이 눌러진 상태면 반복문 빠져나옴		 
			break;

		if (recval > 0) // 유효한 값을 받으면 실행.
		{
			msg[recval] = '\0';
			//sockProc->Log(s);
			sockProc->BroadcastToClients(client, msg, recval);
		}
		else if (recval == 0) // 클라이언트 종료로 인해 반복문 종료
		{
			//sockProc->Log(s);
			break;
		}
		else if (recval == SOCKET_ERROR && !sockProc->m_bState) // 종료 버튼을 누르지 않았지만, 소켓 에러가 나면 실행
		{
			//sockProc->Log(s);
			sockProc->Log(_T("recv() Error"));
			break;
		}
	}
	if (!sockProc->m_bState) // 종료 버튼을 누르지 않은 상태로,
	{						 // 클라이언트가 종료시 타 클라이언트에 종료에 대한 메세지를 뿌림
		CW2A conv(_T("상대가 떠났습니다."), CP_UTF8); // WPF에서 리스트 박스에 출력하는 메세지 타입이 utf-8이므로 유니코드->utf-8로 인코딩
		const char* s = conv; // 인코딩된 문자열을 저장.
		sockProc->BroadcastToClients(client, s, (int)strlen(s));
	}
	sockProc->ClientDisconnected(client);
	closesocket(client);
	delete pCtx;

	return 0;
}

// CSocketProc 멤버 함수
DWORD WINAPI CSocketProc::listenSock(LPVOID lpParam)
{
	CSocketProc* p = (CSocketProc*)lpParam;
	p->Log(_T("Thread 시작."));

	if (WSAStartup(MAKEWORD(2, 2), &(p->wsa)) != 0)
		p->Log(_T("WSAStartup ERROR"));

	p->m_listenSock = socket(AF_INET, SOCK_STREAM, 0); // IPv4, tcp 형태의 소켓으로 초기화
	if (p->m_listenSock == INVALID_SOCKET && !p->m_bState)
		p->Log(_T("socket() Error"));

	SOCKADDR_IN servAddr;
	ZeroMemory(&servAddr, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(PORT);
	servAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

	int recval =
		bind(p->m_listenSock, (SOCKADDR*)&servAddr, sizeof(servAddr)); //소켓의 IP주소을 현재 기기의 IP주소로 잡아줌

	if (recval == SOCKET_ERROR && !p->m_bState)
		p->Log(_T("bind() Error"));

	recval = listen(p->m_listenSock, SOMAXCONN); // 클라이언트의 접속 요청을 수신 가능한 상태로 전환
	p->GetLocalIPv4Addr();

	if (recval == SOCKET_ERROR && !p->m_bState)
		p->Log(_T("listen() Error"));

	SOCKET clientSock = NULL; // 빈 소켓으로 초기화
	SOCKADDR_IN addrClient;
	int length;
	HANDLE hThread = NULL;

	CW2A conv(_T("상대가 입장하였습니다."), CP_UTF8);
	const char* s = conv;

	while (p->m_bRunning)
	{
		length = sizeof(addrClient);
		//p->Log(_T("listen OK, accept 대기"));
		clientSock = accept(p->m_listenSock, (SOCKADDR*)&addrClient, &length); // 클라이언트의 접속 요청을 수신 대기

		//p->Log(_T("accept OK"));

		if (p->m_bState)
			break;

		if (clientSock == INVALID_SOCKET)
		{
			p->Log(_T("accept() Error"));
			continue;
		}

		CString addr = (CString)inet_ntoa(addrClient.sin_addr); // 클라이언트의 정보를 저장하기 위해 IP주소를 넘김
		p->clients.emplace_back(CLIENT_INFO{ clientSock, addr }); // 클라이언트의 정보를 벡터로 저장
		p->Log(CString(_T("[클라이언트 접속] IP : ")) + addr);
		p->BroadcastToClients(clientSock, s, (int)strlen(s)); // 접속된 클라이언트 이외에 타 클라이언트에 새 유저의 접속을 알림

		CLIENT_XTC* pCtx = new CLIENT_XTC({ p, clientSock }); // 접속한 클라이언트의 소켓과 CSocketProc의 포인터 객체를 담아둠.

		hThread = CreateThread(NULL, 0, ClientThread, (LPVOID)pCtx, 0, NULL); // 클라이언트 워커쓰레드 생성하며 
																			  // 접속한 클라이언트의 정보를 같이 넘김
		if (hThread == NULL)
			p->Log(_T("CreateThread() Error"));
		else
			CloseHandle(hThread);
	}

	if (p->m_listenSock != INVALID_SOCKET)
		closesocket(p->m_listenSock);

	WSACleanup();

	while (!p->clients.empty()) {
		p->Log(_T("클라이언트 정리 중. . ."));
	}

	if (clientSock != INVALID_SOCKET)
		closesocket(clientSock);

	p->Log(_T("서버를 종료합니다."));

	return 0;

}
