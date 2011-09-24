// ReplayViewDlg.h : 头文件
//

#pragma once

#include "../DES_GOBSTG/DES_GOBSTG/Header/DataPrinter.h"
#include "Resource.h"
#include "afxwin.h"

// CReplayViewDlg 对话框
class CReplayViewDlg : public CDialog
{
// 构造
public:
	CReplayViewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_REPLAYVIEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	DECLARE_MESSAGE_MAP()
public:
	BOOL isChecked;
	CButton checkButton;
	CEdit filenameText;
	CEdit mainText;

	TCHAR cFilename[M_PATHMAX];
	TCHAR cOutputFilename[M_PATHMAX];
	afx_msg void OnBnClickedOpen();

	void Release();
	bool DisplayInfo();
	bool InitFile();
	afx_msg void OnBnClickedCancel();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
