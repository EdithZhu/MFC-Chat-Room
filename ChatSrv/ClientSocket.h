#pragma once

// CClientSocket ÃüÁîÄ¿±ê

class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
};


