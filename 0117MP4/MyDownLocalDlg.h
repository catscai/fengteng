#pragma once
#include "afxwin.h"


// CMyDownLocalDlg 对话框
#include <vector>
#include <map>
using namespace std;
class CMyDownLocalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownLocalDlg)

public:
	CMyDownLocalDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDownLocalDlg();

// 对话框数据
	enum { IDD = IDD_DOWNLOAD_LOCAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_finishedLocalLst;
	map<CString,CString> m_nameTofilePathsMap;	//存储路径
public:
	bool ShowVideos();
	void SerachLocalVideoes(CString filePath,vector<CString>& fileNames);
	afx_msg void OnLbnDblclkList1();
	virtual BOOL OnInitDialog();
};
