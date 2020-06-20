// SrvSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatSrv.h"
#include "SrvSocket.h"
#include "ChatSrvDlg.h"


// CSrvSocket

CSrvSocket::CSrvSocket()
{
}

CSrvSocket::~CSrvSocket()
{
}


// CSrvSocket 成员函数

void CSrvSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
CChatSrvDlg* dlg=(CChatSrvDlg*)AfxGetApp()->GetMainWnd(); 
dlg->m_chat=new CClientSocket; 
Accept(*(dlg->m_chat)); 
CString str; 
dlg->m_tm=CTime::GetCurrentTime(); 
str=dlg->m_tm.Format("%X "); 
str+="客户端连接成功!"; 
dlg->m_list.AddString(str); 
dlg->m_list.UpdateData(FALSE); 

	CAsyncSocket::OnAccept(nErrorCode);
}
