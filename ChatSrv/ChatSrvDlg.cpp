
// ChatSrvDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ChatSrv.h"
#include "ChatSrvDlg.h"
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


// CChatSrvDlg �Ի���



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
// CChatSrvDlg ��Ϣ�������

BOOL CChatSrvDlg::OnInitDialog()
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
	GetDlgItem(IDC_PORT)->SetWindowText("5000"); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE); 
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatSrvDlg::OnPaint()
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
HCURSOR CChatSrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CChatSrvDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_START)->EnableWindow(FALSE);// ������Ϊ��ɫ
	CString temp; //�����ַ���
	GetDlgItem(IDC_PORT)->GetWindowText(temp); //���������ַ������˿ڿؼ�
	UINT port=atoi(temp.GetBuffer() ); //���ַ���ת��Ϊ������ֵ��port
	//1st Create �����׽���
	m_server=new CSrvSocket; 
	if ((*m_server).Create(port)==0) 
	{ 
		static int code=(*m_server).GetLastError(); //��̬�ֲ�����
		CString err; 
		err.Format("%d",code); //��code�еķ���ֵ����ַ�����ֵ��err
		CString error="Create Error Code= "; 
		error+=err;
		MessageBox(error); //�����Ի������������Ϣ
		return; 
	} 
	
	//2nd Listen ��������
	if ((*m_server).Listen()==0) //�������ʧ��
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
	str=m_tm.Format("%X "); str+="��������!"; 
	m_list.AddString(str); 
	UpdateData(FALSE);
}


void CChatSrvDlg::OnBnClickedDisconnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	(*m_server).Close(); //�ر��׽���
	delete m_server;//ɾ��ָ�룬�ͷ��ڴ�
	delete m_chat; 
	CString str; 
	m_tm=CTime::GetCurrentTime(); 
	str=m_tm.Format("%X"); 
	str+=" �����ж�!"; 
	m_list.AddString(str); 
	UpdateData(FALSE); 
	GetDlgItem(IDC_START)->EnableWindow(TRUE); 
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE); 
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
}


void CChatSrvDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_input.GetWindowText(buff,200); 
	(*m_chat).Send(buff,200); 
	CString temp1=" �ң�"; 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);//������һ���ļ��ĶԻ���
	
	if(dlg.DoModal()!=IDOK)//DoModal����������ڱ�ɵ�ǰ���ڣ����Ҵ˺���һֱ����֪�����OK����Cancel�˳���������ʱ��OK,�ú�������ֵΪIDOK.
		return ;
	//��ʾ�����ļ�
	(*m_chat).Send("please receive file",sizeof("please receive file"));
	   CFile myFile;
	CString szFilename;
	szFilename=dlg.GetPathName();//�õ��ļ�·�����ַ�������ֵ��szFilename;

	if(!myFile.Open(szFilename, CFile::modeRead | CFile::typeBinary))//���ļ�ʧ��
    {
		AfxMessageBox("�ļ�������");
		return ;
	}
	 CSocket serSock, cliSock;
	serSock.Create(1001);//�����������׽���
	serSock.Listen();
	serSock.Accept(cliSock);
   
	SOCKET_STREAM_FILE_INFO StreamFileInfo;//�����ṹ��
	/*typedef struct _SOCKET_STREAM_FILE_INFO {

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

} SOCKET_STREAM_FILE_INFO, * PSOCKET_STREAM_FILE_INFO;*/
	WIN32_FIND_DATA FindFileData;
	/*typedef struct _WIN32_FIND_DATA {
	DWORD dwFileAttributes; //�ļ�����
	FILETIME ftCreationTime; // �ļ�����ʱ��
	FILETIME ftLastAccessTime; // �ļ����һ�η���ʱ��
	FILETIME ftLastWriteTime; // �ļ����һ���޸�ʱ��
	DWORD nFileSizeHigh; // �ļ����ȸ�32λ
	DWORD nFileSizeLow; // �ļ����ȵ�32λ
	DWORD dwReserved0; // ϵͳ����
	DWORD dwReserved1; // ϵͳ����
	TCHAR cFileName[ MAX_PATH ]; // ���ļ���
	TCHAR cAlternateFileName[ 14 ]; // 8.3��ʽ�ļ���
	} WIN32_FIND_DATA, *PWIN32_FIND_DATA;*/
	FindClose(FindFirstFile(szFilename, &FindFileData));//FindFirstFile�����ǲ��ҵ�Ŀ¼�µĵ�һ���ļ���Ŀ¼,
    
	memset(&StreamFileInfo, 0, sizeof(SOCKET_STREAM_FILE_INFO));//��void *memset(void *s, int ch, unsigned n); ��s��ָ���ĳһ���ڴ��е�ÿ���ֽڵ�����ȫ������Ϊchָ����ASCIIֵ, ��Ĵ�С�ɵ���������ָ��,�������ͨ��Ϊ��������ڴ�����ʼ������, �䷵��ֵΪָ��S��ָ�롣
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

	 UINT nSize=0;//�޷�������
	 UINT nSend=0;
	 
	 int len=StreamFileInfo.nFileSizeLow;
	 while(nSize < StreamFileInfo.nFileSizeLow)//�ֶδ����ļ�
	 {
		 byte * szBuf=new byte[1024];//typedef unsigned char byte
		 nSend=myFile.Read(szBuf, 1024);//��ȡ�ļ�����ֵ��szBuf
		 cliSock.Send(szBuf, nSend,0);
		 nSize+=nSend;
	 }

     serSock.Close();
	 myFile.Close();
	 AfxMessageBox("�������!");


}



void CChatSrvDlg::OnBnClickedBusy()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_judge=1;
	GetDlgItem(IDC_BUSY)->EnableWindow(FALSE);
}




void CChatSrvDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_judge=0;
	GetDlgItem(IDC_BUSY)->EnableWindow(TRUE);
}


