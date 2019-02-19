#pragma once
#include "processlist.h"


// CMyDownLoadListDlg 对话框
//#define SETNOSKINHWND(x) {\
//HWND w=(x).UnsubclassWindow();\
//skinppSetNoSkinHwnd(w);\
//(x).SubclassWindow(w);\
//} 
class CMyDownLoadListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownLoadListDlg)

public:
	CMyDownLoadListDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDownLoadListDlg();

// 对话框数据
	enum { IDD = IDD_DOWNLOADDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CProcessList m_processList;
	CBrush m_BrushBk;
	//CMyTabCtrl m_tabCtrl;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnDestroy();
};
