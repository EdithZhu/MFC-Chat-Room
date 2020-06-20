#pragma once

// CSrvSocket ÃüÁîÄ¿±ê

class CSrvSocket : public CAsyncSocket
{
public:
	CSrvSocket();
	virtual ~CSrvSocket();
	virtual void OnAccept(int nErrorCode);
};

