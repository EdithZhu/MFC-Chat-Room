
// chatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "chat.h"
#include "chatDlg.h"
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


// CchatDlg 对话框



CchatDlg::CchatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CchatDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CchatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
	DDX_Control(pDX, IDC_NAME, m_name);
}

BEGIN_MESSAGE_MAP(CchatDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CchatDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CchatDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CchatDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDCANCLE, &CchatDlg::OnBnClickedCancle)
	ON_BN_CLICKED(IDC_RECEIVE, &CchatDlg::OnBnClickedReceive)
	ON_EN_CHANGE(IDC_NAME, &CchatDlg::OnEnChangeName)
END_MESSAGE_MAP()


// CchatDlg 消息处理程序

BOOL CchatDlg::OnInitDialog()
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
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_IPADDRESS)->SetWindowText((LPCTSTR)"127.0.0.1"); 
	GetDlgItem(IDC_PORT)->SetWindowText((LPCTSTR)"5000");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CchatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CchatDlg::OnPaint()
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
HCURSOR CchatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchatDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_START)->EnableWindow(FALSE); //将此控件设置为灰色不可用状态
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE); //将相应控件设置为可用
	CString temp1,temp2; //定义字符串类
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(temp1); //	输入IP地址到IDC_IPADDRESS控件
	CString m_IPAddress=temp1.GetBuffer(temp1.GetLength() ); //为CString对象自定义变量重新获取其内部字符缓冲区的指针
	GetDlgItem(IDC_PORT)->GetWindowText(temp2); //赋予输入框内容
	int m_Port=atoi(temp2); //把输入的字符串转换成长整型数，赋值给m_Port
	m_client=new CMySocket;  //创建套接字
	if ((*m_client).Create()==0) 
	{ 
		CString errcode; 
		errcode.Format("%d",GetLastError()); //调用函数最近的错误代码值，转化为字符串放到errcode中
		m_list.AddString(errcode); //调用此成员函数添加一个字符串到列表框中
		UpdateData(FALSE); //把变量中的数据输出到控件HISTORY
	} 
	m_client->Connect(m_IPAddress,m_Port);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE); 
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_NAME)->EnableWindow(FALSE); 
}



void CchatDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	(*m_client).Close(); //关闭套接字
	delete m_client;//删除指针，释放内存空间
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE); 
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);				
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
	CString str; 
	m_tm=CTime::GetCurrentTime(); //获取当前时间
	str=m_tm.Format("%X "); 
	str+="从服务器断开!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);

}



void CchatDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff,200); //获取在input控件输入的内容,存储在buff中
	m_name.GetWindowText(name,200);////获取在name控件输入的内容,存储在name中
	CString temp1=(CString)name+"："; 
	CString temp2=buff; 
	CString formatbuff="#c#s#"+(CString)buff;//char#<ID>#<toID>#<message>
	(*m_client).Send(formatbuff,200,0); 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); 
	temp1=str+temp1; //时间+我
	temp1+=temp2; 
	m_list.AddString(temp1); 
	UpdateData(FALSE); 
	m_input.SetWindowText("");
}


void CchatDlg::OnBnClickedCancle()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CchatDlg::OnBnClickedReceive()
{
	// TODO: 在此添加控件通知处理程序代码
	CSocket cliSock;//创建套接字端口
	cliSock.Create();

	if(!cliSock.Connect((LPCTSTR)m_strip,1001))//如果没连接上
	{
		AfxMessageBox("未发送文件!");
		return;
	}
	
	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	cliSock.Receive(&StreamFileInfo,sizeof(SOCKET_STREAM_FILE_INFO));

	CString	name=StreamFileInfo.szFileTitle;

    const 	char *ty=(LPCTSTR)name;//LPSTR是一个指向以‘\0’结尾的ANSI字符数组的指针，与char*可以互换使用，在win32中较多地使用LPSTR。而LPCSTR中增加的‘C’的含义是“CONSTANT”（常量），表明这种数据类型的实例不能被使用它的API函数改变，除此之外，它与LPSTR是等同的。
		CFileDialog dlg( FALSE,ty,ty);
       
			
 
	if(IDOK!=dlg.DoModal())  return;//点ok返回

	strcpy(StreamFileInfo.szFileTitle,dlg.GetPathName());
	CFile myFile(StreamFileInfo.szFileTitle, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	 AfxMessageBox(StreamFileInfo.szFileTitle);

	UINT nSize=0;
	UINT nData=0;
	
	while (nSize < StreamFileInfo.nFileSizeLow)//分段接收
	{
		byte * szBuf=new byte[1024];
		nData=cliSock.Receive(szBuf, 1024);
		myFile.Write(szBuf, nData);
		nSize+=nData;
	}
	SetFileTime((HANDLE)myFile.m_hFile/*系统文件句柄*/,&StreamFileInfo.ftCreationTime/*文件创建时间*/,
                &StreamFileInfo.ftLastAccessTime/*文件上一次访问时间*/,&StreamFileInfo.ftLastWriteTime)/*文件上一次修改时间*/;//设置文件的创建、访问、上次修改时间，
	myFile.Close();
	SetFileAttributes(StreamFileInfo.szFileTitle,StreamFileInfo.dwFileAttributes);//设置文件属性
	cliSock.Close();
	AfxMessageBox("接收完毕！");
}


void CchatDlg::OnEnChangeName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}
