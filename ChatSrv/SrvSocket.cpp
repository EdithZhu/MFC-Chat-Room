// SrvSocket.cpp : ʵ���ļ�
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


// CSrvSocket ��Ա����

void CSrvSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
CChatSrvDlg* dlg=(CChatSrvDlg*)AfxGetApp()->GetMainWnd(); 
dlg->m_chat=new CClientSocket; 
Accept(*(dlg->m_chat)); 
CString str; 
dlg->m_tm=CTime::GetCurrentTime(); 
str=dlg->m_tm.Format("%X "); 
str+="�ͻ������ӳɹ�!"; 
dlg->m_list.AddString(str); 
dlg->m_list.UpdateData(FALSE); 

	CAsyncSocket::OnAccept(nErrorCode);
}
