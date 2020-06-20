
// ChatSrvDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatSrv.h"
#include "ChatSrvDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatSrvDlg 对话框



CChatSrvDlg::CChatSrvDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatSrvDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//  button = 0;
	m_judge = 0;
	m_receive = 0;
}

void CChatSrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
	DDX_Control(pDX, IDC_FASONG, m_fasong);
}

BEGIN_MESSAGE_MAP(CChatSrvDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()


	ON_BN_CLICKED(IDC_START, &CChatSrvDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChatSrvDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CChatSrvDlg::OnBnClickedSend)

	
	ON_BN_CLICKED(IDC_FASONG, &CChatSrvDlg::OnBnClickedFasong)
	ON_BN_CLICKED(IDC_BUSY, &CChatSrvDlg::OnBnClickedBusy)
	
	ON_BN_CLICKED(IDC_BUTTON3, &CChatSrvDlg::OnBnClickedButton3)
END_MESSAGE_MAP()
// CChatSrvDlg 消息处理程序

BOOL CChatSrvDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT)->SetWindowText("5000"); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatSrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatSrvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatSrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CChatSrvDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START)->EnableWindow(FALSE);// 启动设为灰色
	CString temp; //设置字符串
	GetDlgItem(IDC_PORT)->GetWindowText(temp); //检测输入的字符串到端口控件
	UINT port=atoi(temp.GetBuffer() ); //把字符串转换为整数赋值给port
	//1st Create 创建套接字
	m_server=new CSrvSocket; 
	if ((*m_server).Create(port)==0) 
	{ 
		static int code=(*m_server).GetLastError(); //静态局部变量
		CString err; 
		err.Format("%d",code); //把code中的返回值变成字符串赋值给err
		CString error="Create Error Code= "; 
		error+=err;
		MessageBox(error); //弹出对话框，输出错误信息
		return; 
	} 
	
	//2nd Listen 监听过程
	if ((*m_server).Listen()==0) //如果监听失败
	{ 
		static int code=(*m_server).GetLastError(); 
		CString err; 
		err.Format("%d",code); 
		CString error="Create Error Code= "; 
		error+=err; 
		MessageBox(error); 
		return; 
	} 
	
	GetDlgItem(IDC_START)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE); 
	CString str; m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); str+="建立服务!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);
}


void CChatSrvDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码

	(*m_server).Close(); //关闭套接字
	delete m_server;//删除指针，释放内存
	delete m_chat; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	str+=" 服务中断!"; 
	m_list.AddString(str); 
	UpdateData(FALSE); 
	GetDlgItem(IDC_START)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
}


void CChatSrvDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff,200); 
	(*m_chat).Send(buff,200); 
	CString temp1=" 我："; 
	CString temp2=buff; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	temp1=str+temp1; 
	temp1+=temp2; 
	CChatSrvDlg* dlg=(CChatSrvDlg*)AfxGetApp()->GetMainWnd(); 
	m_list.AddString(temp1); 
	UpdateData(FALSE); 
	m_input.SetWindowText("");
}




void CChatSrvDlg::OnBnClickedFasong()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);//产生打开一个文件的对话框
	
	if(dlg.DoModal()!=IDOK)//DoModal代表这个窗口变成当前窗口，而且此函数一直阻塞知道你点OK或者Cancel退出，如果点的时候OK,该函数返回值为IDOK.
		return ;
	//提示接收文件
	(*m_chat).Send("please receive file",sizeof("please receive file"));
	   CFile myFile;
	CString szFilename;
	szFilename=dlg.GetPathName();//得到文件路径名字符串，赋值给szFilename;

	if(!myFile.Open(szFilename, CFile::modeRead | CFile::typeBinary))//打开文件失败
    {
		AfxMessageBox("文件不存在");
		return ;
	}
	 CSocket serSock, cliSock;
	serSock.Create(1001);//创建服务器套接字
	serSock.Listen();
	serSock.Accept(cliSock);
   
	SOCKET_STREAM_FILE_INFO StreamFileInfo;//创建结构体
	/*typedef struct _SOCKET_STREAM_FILE_INFO {

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

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;*/
	WIN32_FIND_DATA FindFileData;
	/*typedef struct _WIN32_FIND_DATA {
	DWORD dwFileAttributes; //文件属性
	FILETIME ftCreationTime; // 文件创建时间
	FILETIME ftLastAccessTime; // 文件最后一次访问时间
	FILETIME ftLastWriteTime; // 文件最后一次修改时间
	DWORD nFileSizeHigh; // 文件长度高32位
	DWORD nFileSizeLow; // 文件长度低32位
	DWORD dwReserved0; // 系统保留
	DWORD dwReserved1; // 系统保留
	TCHAR cFileName[ MAX_PATH ]; // 长文件名
	TCHAR cAlternateFileName[ 14 ]; // 8.3格式文件名
	} WIN32_FIND_DATA, *PWIN32_FIND_DATA;*/
	FindClose(FindFirstFile(szFilename, &FindFileData));//FindFirstFile函数是查找到目录下的第一个文件或目录,
    
	memset(&StreamFileInfo, 0, sizeof(SOCKET_STREAM_FILE_INFO));//　void *memset(void *s, int ch, unsigned n); 将s所指向的某一块内存中的每个字节的内容全部设置为ch指定的ASCII值, 块的大小由第三个参数指定,这个函数通常为新申请的内存做初始化工作, 其返回值为指向S的指针。
    strcpy(StreamFileInfo.szFileTitle, myFile.GetFileTitle());

	StreamFileInfo.dwFileAttributes     =       FindFileData.dwFileAttributes;
    StreamFileInfo.ftCreationTime       =       FindFileData.ftCreationTime;
    StreamFileInfo.ftLastAccessTime     =       FindFileData.ftLastAccessTime;
    StreamFileInfo.ftLastWriteTime      =       FindFileData.ftLastWriteTime;
    StreamFileInfo.nFileSizeHigh        =       FindFileData.nFileSizeHigh;
    StreamFileInfo.nFileSizeLow         =       FindFileData.nFileSizeLow;
	StreamFileInfo.cAlternateFileName   =       (TCHAR)FindFileData.cAlternateFileName;
	StreamFileInfo.cFileName           =        (TCHAR)FindFileData.cFileName;
     cliSock.Send(&StreamFileInfo, sizeof(SOCKET_STREAM_FILE_INFO));

	 UINT nSize=0;//无符号整形
	 UINT nSend=0;
	 
	 int len=StreamFileInfo.nFileSizeLow;
	 while(nSize < StreamFileInfo.nFileSizeLow)//分段传输文件
	 {
		 byte * szBuf=new byte[1024];//typedef unsigned char byte
		 nSend=myFile.Read(szBuf, 1024);//读取文件，赋值给szBuf
		 cliSock.Send(szBuf, nSend,0);
		 nSize+=nSend;
	 }

     serSock.Close();
	 myFile.Close();
	 AfxMessageBox("发送完成!");


}



void CChatSrvDlg::OnBnClickedBusy()
{
	// TODO: 在此添加控件通知处理程序代码
	m_judge=1;
	GetDlgItem(IDC_BUSY)->EnableWindow(FALSE);
}




void CChatSrvDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_judge=0;
	GetDlgItem(IDC_BUSY)->EnableWindow(TRUE);
}


