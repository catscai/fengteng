#pragma once
#include "afxwin.h"


// CMyDownFinishedDlg 对话框
#include <map>
using namespace std;
class CMyDownFinishedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownFinishedDlg)

public:
	CMyDownFinishedDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDownFinishedDlg();

// 对话框数据
	enum { IDD = IDD_DOWNLOAD_FINISHED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_FinishedDownloadLst;
	map<CString,CString> m_finishedToPathMap;
	afx_msg void OnLbnDblclkList1();
	virtual BOOL OnInitDialog();
};
