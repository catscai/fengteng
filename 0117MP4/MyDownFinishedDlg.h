#pragma once
#include "afxwin.h"


// CMyDownFinishedDlg �Ի���
#include <map>
using namespace std;
class CMyDownFinishedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownFinishedDlg)

public:
	CMyDownFinishedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDownFinishedDlg();

// �Ի�������
	enum { IDD = IDD_DOWNLOAD_FINISHED };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_FinishedDownloadLst;
	map<CString,CString> m_finishedToPathMap;
	afx_msg void OnLbnDblclkList1();
	virtual BOOL OnInitDialog();
};
