#pragma once
#include "mytabctrl.h"


// CMyDownTaskDlg 对话框

class CMyDownTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownTaskDlg)

public:
	CMyDownTaskDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDownTaskDlg();

// 对话框数据
	enum { IDD = IDD_DOWNLOAD_TASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyTabCtrl m_tabCtrl;
public:
	virtual BOOL OnInitDialog();
};
