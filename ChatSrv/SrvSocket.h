#pragma once

// CSrvSocket ����Ŀ��

class CSrvSocket : public CAsyncSocket
{
public:
	CSrvSocket();
	virtual ~CSrvSocket();
	virtual void OnAccept(int nErrorCode);
};

