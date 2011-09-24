// ResourceUnpackDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ResourceUnpack.h"
#include "ResourceUnpackDlg.h"
#include ".\resourceunpackdlg.h"

#define STR_MSG_SUCCEED	"Succeeded!"
#define STR_MSG_FAILED	"Failed!"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


HGE * hge = hgeCreate(HGE_VERSION);

// CResourceUnpackDlg 对话框



CResourceUnpackDlg::CResourceUnpackDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResourceUnpackDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CResourceUnpackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FOLDERNAME, foldernameText);
	DDX_Control(pDX, IDC_UNPACK, unpackButton);
}

BEGIN_MESSAGE_MAP(CResourceUnpackDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, OnBnClickedOpen)
	ON_BN_CLICKED(IDC_UNPACK, OnBnClickedUnpack)
	ON_EN_CHANGE(IDC_FOLDERNAME, OnEnChangeFoldername)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_UNPACK2, OnBnClickedUnpack2)
END_MESSAGE_MAP()


// CResourceUnpackDlg 消息处理程序

BOOL CResourceUnpackDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	Export::SetIni(true);
	hge->System_SetState(HGE_LOGFILE, LOG_STR_FILENAME);
	Export::GetPassword();
	unpackButton.EnableWindow(FALSE);
	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CResourceUnpackDlg::OnPaint() 
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
HCURSOR CResourceUnpackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CResourceUnpackDlg::OnBnClickedOpen()
{
	CFileDialog fdlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Ini Files (*.ini)|*.ini||");
	CString filename;
	if (fdlg.DoModal() == IDOK)
	{
		filename = fdlg.GetPathName();
	}
	else
	{
		return;
	}
	strcpy(szIniFilename, filename);
	if (!(strlen(szIniFilename)))
	{
		return;
	}

	foldernameText.SetWindowText(szIniFilename);

}

void CResourceUnpackDlg::OnBnClickedUnpack()
{
	foldernameText.GetWindowText(szIniFilename, M_STRMAX);

	int i = strlen(szIniFilename) - 1;
	while (i > 0 && szIniFilename[i] != '/' && szIniFilename[i] != '\\')
	{
		i--;
	}
	if (i == 0)
	{
		return;
	}
	i++;

	TCHAR upperfolder[M_PATHMAX];
	strncpy(upperfolder, szIniFilename, i);
	upperfolder[i] = 0;
	hge->Resource_SetPath(upperfolder);
	hge->Resource_SetCurrentDirectory(upperfolder);

	if (Export::unpackFromIni(szIniFilename))
	{
		MessageBox(STR_MSG_SUCCEED);
		OnOK();
	}
	else
	{
		MessageBox(STR_MSG_FAILED);
	}
}

void CResourceUnpackDlg::OnEnChangeFoldername()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	foldernameText.GetWindowText(szIniFilename, M_PATHMAX);
	if (!strlen(szIniFilename))
	{
		unpackButton.EnableWindow(FALSE);
	}
	else if (hge->Resource_AccessFile(hge->Resource_MakePath(szIniFilename)))
	{
		unpackButton.EnableWindow(TRUE);
	}
	else
	{
		unpackButton.EnableWindow(FALSE);
	}
}

BOOL CResourceUnpackDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

void CResourceUnpackDlg::OnBnClickedUnpack2()
{
	OnCancel();
}
