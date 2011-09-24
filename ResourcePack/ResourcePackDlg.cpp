// ResourcePackDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "ResourcePack.h"
#include "ResourcePackDlg.h"
#include ".\resourcepackdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define STR_MSG_SUCCEED	"Succeeded!"
#define STR_MSG_FAILED	"Failed!"

HGE * hge = hgeCreate(HGE_VERSION);

// CResourcePackDlg 对话框

CResourcePackDlg::CResourcePackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResourcePackDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResourcePackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDPACK, packButton);
	DDX_Control(pDX, IDC_FOLDERNAME, foldernameText);
	DDX_Control(pDX, IDC_FOLDERNAME2, filteredit);
}

BEGIN_MESSAGE_MAP(CResourcePackDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, OnBnClickedOpen)
	ON_BN_CLICKED(IDPACK, OnBnClickedPack)
	ON_EN_CHANGE(IDC_FOLDERNAME, OnEnChangeFoldername)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// CResourcePackDlg 消息处理程序

BOOL CResourcePackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	Export::SetIni(true);
	Export::GetPassword();
	packButton.EnableWindow(FALSE);

	strcpy(szPath, "");

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CResourcePackDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CResourcePackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CResourcePackDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	BROWSEINFO m_bi;

	m_bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	m_bi.hwndOwner = m_hWnd;
	m_bi.pidlRoot = NULL;
	m_bi.lpszTitle = NULL;
	m_bi.lpfn = NULL;
	m_bi.lParam = NULL;
	m_bi.pszDisplayName = szPath;
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);

	if (pidl)
	{
		if (!::SHGetPathFromIDList(pidl, szPath))
			szPath[0]=0; 

		IMalloc * pMalloc = NULL;
		if (SUCCEEDED(::SHGetMalloc(&pMalloc)))
		{
			pMalloc-> Free(pidl);
			pMalloc-> Release();
		}
	}

	foldernameText.SetWindowText(szPath);
}

void CResourcePackDlg::OnBnClickedPack()
{
	// TODO: 在此添加控件通知处理程序代码

	foldernameText.GetWindowText(szPath, M_PATHMAX);

	int i = strlen(szPath) - 1;
	if (szPath[i] == '/' || szPath[i] == '\\')
	{
		szPath[i] = 0;
		i--;
	}
	while (i > 0 && szPath[i] != '/' && szPath[i] != '\\')
	{
		i--;
	}
	if (i == 0)
	{
		return;
	}
	i++;

	TCHAR upperfolder[M_PATHMAX];
	strncpy(upperfolder, szPath, i);
	upperfolder[i] = 0;
	hge->Resource_SetPath(upperfolder);
	hge->Resource_SetCurrentDirectory(upperfolder);
	strcpy(foldername, &szPath[i]);
	strcpy(packname, &szPath[i]);
	strcat(packname, M_PACKEXTENSION);

	filteredit.GetWindowText(filterstr, M_PATHMAX);

	if (Export::packFolder(packname, foldername, filterstr))
	{
		MessageBox(STR_MSG_SUCCEED);
		OnOK();
	}
	else
	{
		MessageBox(STR_MSG_FAILED);
	}
}

void CResourcePackDlg::OnEnChangeFoldername()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	foldernameText.GetWindowText(szPath, M_PATHMAX);
	if (strlen(szPath) == 0)
	{
		packButton.EnableWindow(FALSE);
	}
	else if (hge->Resource_AccessFile(hge->Resource_MakePath(szPath)))
	{
		packButton.EnableWindow(TRUE);
	}
	else
	{
		packButton.EnableWindow(FALSE);
	}
}

BOOL CResourcePackDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}
