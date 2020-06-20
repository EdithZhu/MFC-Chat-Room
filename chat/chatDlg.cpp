
// chatDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chat.h"
#include "chatDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CchatDlg �Ի���



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


// CchatDlg ��Ϣ�������

BOOL CchatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_IPADDRESS)->SetWindowText((LPCTSTR)"127.0.0.1"); 
	GetDlgItem(IDC_PORT)->SetWindowText((LPCTSTR)"5000");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CchatDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CchatDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchatDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_START)->EnableWindow(FALSE); //���˿ؼ�����Ϊ��ɫ������״̬
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE); //����Ӧ�ؼ�����Ϊ����
	CString temp1,temp2; //�����ַ�����
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(temp1); //	����IP��ַ��IDC_IPADDRESS�ؼ�
	CString m_IPAddress=temp1.GetBuffer(temp1.GetLength() ); //ΪCString�����Զ���������»�ȡ���ڲ��ַ���������ָ��
	GetDlgItem(IDC_PORT)->GetWindowText(temp2); //�������������
	int m_Port=atoi(temp2); //��������ַ���ת���ɳ�����������ֵ��m_Port
	m_client=new CMySocket;  //�����׽���
	if ((*m_client).Create()==0) 
	{ 
		CString errcode; 
		errcode.Format("%d",GetLastError()); //���ú�������Ĵ������ֵ��ת��Ϊ�ַ����ŵ�errcode��
		m_list.AddString(errcode); //���ô˳�Ա�������һ���ַ������б����
		UpdateData(FALSE); //�ѱ����е�����������ؼ�HISTORY
	} 
	m_client->Connect(m_IPAddress,m_Port);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE); 
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE); 
	GetDlgItem(IDC_NAME)->EnableWindow(FALSE); 
}



void CchatDlg::OnBnClickedDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	(*m_client).Close(); //�ر��׽���
	delete m_client;//ɾ��ָ�룬�ͷ��ڴ�ռ�
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE); 
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);				
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_NAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
	CString str; 
	m_tm=CTime::GetCurrentTime(); //��ȡ��ǰʱ��
	str=m_tm.Format("%X "); 
	str+="�ӷ������Ͽ�!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);

}



void CchatDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_input.GetWindowText(buff,200); //��ȡ��input�ؼ����������,�洢��buff��
	m_name.GetWindowText(name,200);////��ȡ��name�ؼ����������,�洢��name��
	CString temp1=(CString)name+"��"; 
	CString temp2=buff; 
	CString formatbuff="#c#s#"+(CString)buff;//char#<ID>#<toID>#<message>
	(*m_client).Send(formatbuff,200,0); 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X "); 
	temp1=str+temp1; //ʱ��+��
	temp1+=temp2; 
	m_list.AddString(temp1); 
	UpdateData(FALSE); 
	m_input.SetWindowText("");
}


void CchatDlg::OnBnClickedCancle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}


void CchatDlg::OnBnClickedReceive()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CSocket cliSock;//�����׽��ֶ˿�
	cliSock.Create();

	if(!cliSock.Connect((LPCTSTR)m_strip,1001))//���û������
	{
		AfxMessageBox("δ�����ļ�!");
		return;
	}
	
	SOCKET_STREAM_FILE_INFO StreamFileInfo;
	cliSock.Receive(&StreamFileInfo,sizeof(SOCKET_STREAM_FILE_INFO));

	CString	name=StreamFileInfo.szFileTitle;

    const 	char *ty=(LPCTSTR)name;//LPSTR��һ��ָ���ԡ�\0����β��ANSI�ַ������ָ�룬��char*���Ի���ʹ�ã���win32�н϶��ʹ��LPSTR����LPCSTR�����ӵġ�C���ĺ����ǡ�CONSTANT���������������������������͵�ʵ�����ܱ�ʹ������API�����ı䣬����֮�⣬����LPSTR�ǵ�ͬ�ġ�
		CFileDialog dlg( FALSE,ty,ty);
       
			
 
	if(IDOK!=dlg.DoModal())  return;//��ok����

	strcpy(StreamFileInfo.szFileTitle,dlg.GetPathName());
	CFile myFile(StreamFileInfo.szFileTitle, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);

	 AfxMessageBox(StreamFileInfo.szFileTitle);

	UINT nSize=0;
	UINT nData=0;
	
	while (nSize < StreamFileInfo.nFileSizeLow)//�ֶν���
	{
		byte * szBuf=new byte[1024];
		nData=cliSock.Receive(szBuf, 1024);
		myFile.Write(szBuf, nData);
		nSize+=nData;
	}
	SetFileTime((HANDLE)myFile.m_hFile/*ϵͳ�ļ����*/,&StreamFileInfo.ftCreationTime/*�ļ�����ʱ��*/,
                &StreamFileInfo.ftLastAccessTime/*�ļ���һ�η���ʱ��*/,&StreamFileInfo.ftLastWriteTime)/*�ļ���һ���޸�ʱ��*/;//�����ļ��Ĵ��������ʡ��ϴ��޸�ʱ�䣬
	myFile.Close();
	SetFileAttributes(StreamFileInfo.szFileTitle,StreamFileInfo.dwFileAttributes);//�����ļ�����
	cliSock.Close();
	AfxMessageBox("������ϣ�");
}


void CchatDlg::OnEnChangeName()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialog::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�


	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
