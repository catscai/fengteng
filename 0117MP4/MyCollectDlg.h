#pragma once
#include "afxwin.h"


// CMyCollectDlg 对话框
#include <map>
using namespace std;
class CMyCollectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyCollectDlg)

public:
	CMyCollectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyCollectDlg();

// 对话框数据
	enum { IDD = IDD_COLLECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_collectLst;
	CBrush   m_brush;
	map<CString,CString> m_collectMap;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void GetCollections();
	afx_msg LRESULT GetCollections(WPARAM w, LPARAM l);
	afx_msg LRESULT DeleteCollections(WPARAM w, LPARAM l);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLbnDblclkList1();
};
