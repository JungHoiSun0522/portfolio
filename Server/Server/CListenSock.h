#pragma once

// CLsitenSock 명령 대상

class CListenSock : public CObject
{
public:
	CListenSock();
	virtual ~CListenSock();
protected:
	void SockListen();
};


