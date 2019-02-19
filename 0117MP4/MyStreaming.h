#pragma once
#include "afxwin.h"


// CMyStreaming 对话框

class CMyStreaming : public CDialogEx
{
	DECLARE_DYNAMIC(CMyStreaming)

public:
	CMyStreaming(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyStreaming();

// 对话框数据
	enum { IDD = IDD_PLAYING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;				//背景画刷
	CListBox m_NameStreamList;
	CEdit m_SreachName;
	CString m_PlayStreamName;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnDblclkListPlaying();
};
