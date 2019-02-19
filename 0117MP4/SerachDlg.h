#pragma once
#include "afxwin.h"


// CSerachDlg 对话框

class CSerachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerachDlg)

public:
	CSerachDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSerachDlg();

// 对话框数据
	enum { IDD = IDD_SERACH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_SerachLst;
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLbnKillfocusList1();
};
