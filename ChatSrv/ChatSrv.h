
// ChatSrv.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatSrvApp:
// �йش����ʵ�֣������ ChatSrv.cpp
//

class CChatSrvApp : public CWinApp
{
public:
	CChatSrvApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChatSrvApp theApp;