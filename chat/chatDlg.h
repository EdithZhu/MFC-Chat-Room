
// chatDlg.h : 头文件
//

#pragma once

#include "MySocket.h" //使主界面程序能够访问Socket类的代码文件
#include "afxwin.h"
// CchatDlg 对话框
typedef struct _SOCKET_STREAM_FILE_INFO {

    TCHAR       szFileTitle[128];                   //文件的标题名
    DWORD       dwFileAttributes;                   //文件的属性
    FILETIME    ftCreationTime;                     //文件的创建时间
    FILETIME    ftLastAccessTime;                   //文件的最后访问时间
    FILETIME    ftLastWriteTime;                    //文件的最后修改时间
    DWORD       nFileSizeHigh;                      //文件大小的高位双字
    DWORD       nFileSizeLow;                       //文件大小的低位双字
    DWORD       dwReserved0;                        //保留，为0
    DWORD       dwReserved1;                        //保留，为0
	TCHAR       cAlternateFileName; 
	TCHAR       cFileName;                   

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;
class CchatDlg : public CDialog
{
// 构造
public:
	CchatDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CHAT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	BOOL CchatDlg::PreTranslateMessage(MSG* pMsg)//直接在重载的PreTranslateMessage函数中屏蔽回车和ESC的消息
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
	afx_msg void OnBnClickedCancle();

	CString m_strip;
	CMySocket* m_client;
	char buff[200];
	CTime m_tm;
//  afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedReceive();
	CEdit m_name;
	char name[200];
	afx_msg void OnEnChangeName();
};
