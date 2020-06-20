// ClientSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatSrv.h"
#include "ClientSocket.h"
#include "ChatSrvDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数
#pragma once

// CServerSocket 命令目标


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
CChatSrvDlg* dlg=(CChatSrvDlg*)AfxGetApp()->GetMainWnd(); 
	//获取时间 
	dlg->m_tm=CTime::GetCurrentTime(); 
	CString str; 
	str=dlg->m_tm.Format("%X "); 
	//接收数据 
	Receive(dlg->buff,200,0); 
	CString temp1=dlg->buff; 
	//解码，收到的数据 
	int index=0; 
	for (int i=0;i<3;i++) 
	{ 
		index=temp1.Find('#',index); 
		index++; 
	} 
	int sum=temp1.GetLength(); 
	int count=sum-index; 
	CString message=temp1.Mid(index,count); 
	CString temp2=" 客户端 : "; 
	temp2=str+temp2; 
	temp2+=message; 
	dlg->m_list.AddString(temp2); 
	
	

	if(dlg->m_judge==1)
	{    
		
		(*dlg->m_chat).Send("离开片刻，马上回来~",sizeof("离开片刻，马上回来~"));

	}


	CAsyncSocket::OnReceive(nErrorCode);
}
