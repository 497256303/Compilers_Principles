#define _CRT_SECURE_NO_WARNINGS
// byDlg.cpp : implementation file
//

#include "stdafx.h"
#include "by.h"
#include "byDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

char  ch =' ';			// 存放读入当前的输入字符
int lineno;

struct reserve		 //关键字
{
	char lexptr[MAXBUF];
	int token;
};

struct reserve symtable[MAX];


class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CByDlg dialog

CByDlg::CByDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CByDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CByDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CByDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CByDlg)
	//DDX_Control(pDX, IDC_STATIC1, m_me);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CByDlg, CDialog)
	//{{AFX_MSG_MAP(CByDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_FENXI, OnFenxi)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CByDlg message handlers

BOOL CByDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_font.CreateFont(12, 0,0,0,FW_NORMAL, 0,0,0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Fixedsys");
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_font);

	m_me.SetToolTipText("访问我的网站: http://www.59hao.com/chx");

	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CByDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CByDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CByDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void pret(char buffer[])//注释预处理
{
	char c;
	int state = 0;
	for (int i = 0; buffer[i]; i++)
	{
		c = buffer[i];
		switch (state)
		{
		case 0:
			if (c == '/')
				state = 1;
			else
				state = 0;
			break;
		case 1:
			if (c == '*')
			{
				state = 2;
				buffer[i - 1] = ' ';
				buffer[i] = ' ';
			}
			else if (c == '/')
			{
				state = 4;
				buffer[i - 1] = ' ';
				buffer[i] = ' ';
			}
			else
				state = 0;
			break;
		case 2:
			if (c == '*')
			{
				state = 3;
				buffer[i] = ' ';
			}
			else
			{
				state = 2;
				buffer[i] = ' ';
				if (c == '\n')
					buffer[i] = '\n';
			}
			break;
		case 3:
			if (c == '/')
			{
				state = 0;
				buffer[i] = ' ';
			}
			else
			{
				state = 2;
				buffer[i] = ' ';
				if (c == '\n')
					buffer[i] = '\n';
			}
			break;
		case 4:
			if (c == '\n')
			{
				state = 0;
				buffer[i] = '\n';
			}
			else
			{
				state = 4;
				buffer[i] = ' ';
			}
		}
	}
}


void CByDlg::analyse(FILE *fpin, FILE *fpout)
{
	int i = 0;
	int j = 0;
	char prog[WORD_OF_PROGRAM*WORD_LENGTH], token[WORD_LENGTH];
	char ch;
	int syn, p=0, m = 0, n, row=0;
	double sum = 0;   //类型为整数或者小数的时候，用于保存源数据
	int syn_of_rwtab; //遍历关键字数组
	int locate_line; //单词在行中的位置
	char *rwtab[] = { "ifstream","const","short","int","char","bool","double","float","if","else","while","for","do","break","void","switch" }; //保存关键字

	while((ch = fgetc(fpin)) !=EOF)
	{
		prog[p++] = ch;
	} 

	pret(prog);//注释预处理

	int q = 0;
	while (prog[q])
	{
		for (n = 0; n < WORD_LENGTH; n++) 
			token[n] = NULL;
		ch = prog[q++];
		if (ch == ' ' || ch == ';' || ch == '{' || ch == '}' || ch == '(' || ch == ')')
		{
			if (ch == ' ')
				syn = 6;
			else if (ch == ';')
				syn = 7;
			else if (ch == '{')
				syn = 8;
			else if (ch == '}')
				syn = 9;
			else if (ch == '(')
				syn = 10;
			else if (ch == ')')
				syn = 11;
			token[0] = ch;
		}

		else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')  
		{
			m = 0;
			while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') 
			{
				token[m++] = ch;
				ch = prog[q++];
			}
			token[m++] = '\0';
			q--;
			syn = 2;
			for (n = 0; n < 16; n++) 
				if (strcmp(token, rwtab[n]) == 0) 
				{
					syn = 1;
					syn_of_rwtab = n;
					break;
				}
		}
		else if ((ch >= '0' && ch <= '9'))
		{

			bool flag = false; 
			sum = 0;

			while ((ch >= '0' && ch <= '9'))
			{
				sum = sum * 10 + ch - '0';
				ch = prog[q++];
			}
			if (ch == '.')
			{
				flag = true;
				ch = prog[q++];
				double tag = 0.1;
				while ((ch >= '0' && ch <= '9'))
				{
					sum += (ch - '0') * tag;
					tag = tag * 0.1;
					ch = prog[q++];
				}
			}
			int flag_err = 0;
			while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch == '_'))
			{
				flag_err = 1;
				ch = prog[q++];
			}
			if (flag_err)
				syn = -1;
			else
			{
				q--;
				if (flag)
					syn = 4;
				else
					syn = 3;
			}
		}
		else if (ch == '\"') 
		{
			syn = 5;
			m = 0;
			token[m++] = ch;
			while ((ch = prog[q++]) != '\"')
				token[m++] = ch;
			token[m] = ch;
			// q--;
		}
		else
			switch (ch) 
			{
			case '<':
				m = 0;
				token[m++] = ch;
				ch = prog[q++];
				if (ch == '=') 
				{
					syn = 12;
					token[m++] = ch;
				}
				else 
				{
					syn = 13;
					q--;
				}
				break;
			case '>':
				m = 0;
				token[m++] = ch;
				ch = prog[q++];
				if (ch == '=') 
				{
					syn = 14;
					token[m++] = ch;
				}
				else 
				{
					syn = 15;
					q--;
				}
				break;
			case ':':
				m = 0;
				token[m++] = ch;
				ch = prog[q++];
				if (ch == '=') 
				{
					syn = 16;
					token[m++] = ch;
				}
				else 
				{
					syn = 17;
					q--;
				}
				break;
			case '*':
				syn = 18;
				token[0] = ch;
				break;
			case '/':
				syn = 19;
				token[0] = ch;
				break;
			case '+':
				syn = 20;
				token[0] = ch;
				break;
			case '-':
				syn = 21;
				token[0] = ch;
				break;
			case '=':
				syn = 22;
				token[0] = ch;
				break;
			case '#':
				syn = 23;
				token[0] = ch;
				break;
			case ',':
				syn = 24;
				token[0] = ch;
				break;
			case '.':
				syn = 25;
				token[0] = ch;
				break;
			case '%':
				syn = 26;
				token[0] = ch;
				break;
			case '\n':
				syn = 27;
				locate_line = 0;//回行首
				break;
			case '\t'://等同于空格忽略掉
				syn = 6;
				break;
			default:
				syn = -1;
				break;
			}
			if (syn == -1)
				fprintf(fpout, "Error in row%d!\n", row+1);
			else if (syn==3||syn==4)
				fprintf(fpout, "%d %d (%d,%g)\n", row+1, locate_line, syn, sum);
			else if (syn == 6)
				continue;
			else if (syn == 27)
				row++;
			else
				fprintf(fpout, "%d %d (%d,%s)\n", row+1, locate_line,syn,token);
			locate_line++;
	}
}



void CByDlg::OnOpen() 
{
	CFileDialog fd(true);
	fd.m_ofn.lpstrTitle="请选择你要打开的文件";  //标题
	//fd.m_ofn.lpstrInitialDir="d:\\";            //初始目录
	if(fd.DoModal())
	{
		m_strFileName=fd.GetPathName();
		
		CStdioFile sf;
		CString str;
		if(sf.Open(m_strFileName.GetBuffer(0),CFile::modeRead))
		{
			CString  strTemp;
			while(sf.ReadString(strTemp))
			{
				str+=strTemp;
				str+="\r\n";
			}	
			SetDlgItemText(IDC_EDIT1,str);
			
			sf.Close();
		}
	}
}

void CByDlg::OnFenxi() 
{
	if(this->m_strFileName.IsEmpty())
	{
		MessageBox("请先选择一个源文件或者保存你编辑的代码后再进行词法分析","词法分析器",MB_ICONEXCLAMATION);
		return;
	}
	FILE* fpin=fopen(m_strFileName.GetBuffer(0),"r");
	FILE* fpout=fopen("output.txt","w");
	analyse(fpin,fpout);
	fclose(fpin);
	fclose(fpout);	

	CStdioFile sf;
	CString str;
	if(sf.Open("output.txt",CFile::modeRead))
	{
		CString  strTemp;
		while(sf.ReadString(strTemp))
		{
			str+=strTemp;
			str+="\r\n";
		}	
		SetDlgItemText(IDC_EDIT2,str);	
		sf.Close();
	}

}


BOOL CByDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg -> message == WM_KEYDOWN)
	{
        if(pMsg -> wParam == VK_ESCAPE)
		return TRUE;

	}return CDialog::PreTranslateMessage(pMsg);	

}

void CByDlg::OnSave() 
{
	if(this->m_strFileName.IsEmpty())
	{
		CFileDialog fd(false);
		fd.m_ofn.lpstrTitle="请选择你要打开的文件";  //标题
		fd.m_ofn.lpstrInitialDir="d:\\";            //初始目录
		if(fd.DoModal())
		{
			m_strFileName=fd.GetPathName();
		}
			
	}

	CFile sf;
	if(sf.Open(this->m_strFileName,CFile::modeWrite|CFile::modeCreate))
	{
		UpdateData();
		char buf[WORD_OF_PROGRAM]={0};
		GetDlgItem(IDC_EDIT1)->GetWindowText(buf, WORD_OF_PROGRAM);
		sf.Write(buf,strlen(buf));
		sf.Close();
		MessageBox("保存成功","词法分析器",MB_ICONINFORMATION);
	}	
}
