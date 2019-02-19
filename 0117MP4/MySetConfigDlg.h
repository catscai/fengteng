#pragma once
#include "afxwin.h"


// CMySetConfigDlg 对话框

class CMySetConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySetConfigDlg)

public:
	CMySetConfigDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMySetConfigDlg();

// 对话框数据
	enum { IDD = IDD_SETCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_VideoDownloadPathEdit;
	CEdit m_VideoHistPathEdit;
	CEdit m_ScreenShotPathEdit;
public:

	afx_msg void OnBnClickedVideodownpath();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedScreenshotpath();
	afx_msg void OnBnClickedSaveallset();
	afx_msg void OnBnClickedCancelset();
	virtual BOOL OnInitDialog();
};
