#pragma once
#include "afxwin.h"


// CMyPublicWordDlg 对话框

class CMyPublicWordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPublicWordDlg)

public:
	CMyPublicWordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyPublicWordDlg();

// 对话框数据
	enum { IDD = IDD_PUBLICWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_publicBoard;	//公告板
	CBrush m_brush;			//画刷
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
