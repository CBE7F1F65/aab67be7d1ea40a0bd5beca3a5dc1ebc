// ResourceUnpackDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CResourceUnpackDlg 对话框
class CResourceUnpackDlg : public CDialog
{
// 构造
public:
	CResourceUnpackDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RESOURCEUNPACK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedUnpack();
public:
	TCHAR szIniFilename[M_PATHMAX];
	CEdit foldernameText;
	CButton unpackButton;
	afx_msg void OnEnChangeFoldername();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnBnClickedUnpack2();
};
