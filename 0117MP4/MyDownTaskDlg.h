#pragma once
#include "mytabctrl.h"


// CMyDownTaskDlg �Ի���

class CMyDownTaskDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownTaskDlg)

public:
	CMyDownTaskDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDownTaskDlg();

// �Ի�������
	enum { IDD = IDD_DOWNLOAD_TASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyTabCtrl m_tabCtrl;
public:
	virtual BOOL OnInitDialog();
};
