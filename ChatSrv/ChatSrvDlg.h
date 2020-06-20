
// ChatSrvDlg.h : ͷ�ļ�
//

#pragma once
#include "SrvSocket.h"
#include"ClientSocket.h"
#include "afxwin.h"

// CChatSrvDlg �Ի���
typedef struct _SOCKET_STREAM_FILE_INFO {

    TCHAR       szFileTitle[128];                   //�ļ��ı�����
    DWORD       dwFileAttributes;                   //�ļ�������
    FILETIME    ftCreationTime;                     //�ļ��Ĵ���ʱ��
    FILETIME    ftLastAccessTime;                   //�ļ���������ʱ��
    FILETIME    ftLastWriteTime;                    //�ļ�������޸�ʱ��
    DWORD       nFileSizeHigh;                      //�ļ���С�ĸ�λ˫��
    DWORD       nFileSizeLow;                       //�ļ���С�ĵ�λ˫��
    DWORD       dwReserved0;                        //������Ϊ0
    DWORD       dwReserved1;                        //������Ϊ0
	TCHAR       cAlternateFileName; 
	TCHAR       cFileName;                   

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;


class CChatSrvDlg : public CDialog
{
// ����
public:
	CChatSrvDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATSRV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL CChatSrvDlg::PreTranslateMessage(MSG* pMsg)//ֱ�������ص�PreTranslateMessage���������λس���ESC����Ϣ
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
		else
			return CDialog::PreTranslateMessage(pMsg);
	}
public:
	CListBox m_list;
	CEdit m_input;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedSend();

	CTime m_tm;
	char buff[200];
	CClientSocket * m_chat;
	CSrvSocket * m_server;
//	afx_msg void OnBnClickedRe();
//	bool button;
//	int button;
	CButton *re;
	afx_msg void OnBnClickedFasong();
	CButton m_fasong;
	int m_judge;
	int m_receive;
	afx_msg void OnBnClickedBusy();
	
	afx_msg void OnBnClickedButton3();
};
