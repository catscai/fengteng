#pragma once
#include "afxwin.h"


// CMyStreaming �Ի���

class CMyStreaming : public CDialogEx
{
	DECLARE_DYNAMIC(CMyStreaming)

public:
	CMyStreaming(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyStreaming();

// �Ի�������
	enum { IDD = IDD_PLAYING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;				//������ˢ
	CListBox m_NameStreamList;
	CEdit m_SreachName;
	CString m_PlayStreamName;
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLbnDblclkListPlaying();
};
