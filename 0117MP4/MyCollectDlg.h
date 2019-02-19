#pragma once
#include "afxwin.h"


// CMyCollectDlg �Ի���
#include <map>
using namespace std;
class CMyCollectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyCollectDlg)

public:
	CMyCollectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyCollectDlg();

// �Ի�������
	enum { IDD = IDD_COLLECT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
