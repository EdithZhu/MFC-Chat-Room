// ClientSocket.cpp : ʵ���ļ�
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


// CClientSocket ��Ա����
#pragma once

// CServerSocket ����Ŀ��


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
CChatSrvDlg* dlg=(CChatSrvDlg*)AfxGetApp()->GetMainWnd(); 
	//��ȡʱ�� 
	dlg->m_tm=CTime::GetCurrentTime(); 
	CString str; 
	str=dlg->m_tm.Format("%X "); 
	//�������� 
	Receive(dlg->buff,200,0); 
	CString temp1=dlg->buff; 
	//���룬�յ������� 
	int index=0; 
	for (int i=0;i<3;i++) 
	{ 
		index=temp1.Find('#',index); 
		index++; 
	} 
	int sum=temp1.GetLength(); 
	int count=sum-index; 
	CString message=temp1.Mid(index,count); 
	CString temp2=" �ͻ��� : "; 
	temp2=str+temp2; 
	temp2+=message; 
	dlg->m_list.AddString(temp2); 
	
	

	if(dlg->m_judge==1)
	{    
		
		(*dlg->m_chat).Send("�뿪Ƭ�̣����ϻ���~",sizeof("�뿪Ƭ�̣����ϻ���~"));

	}


	CAsyncSocket::OnReceive(nErrorCode);
}
