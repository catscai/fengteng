#pragma once
#include "afxwin.h"


// CSerachDlg �Ի���

class CSerachDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSerachDlg)

public:
	CSerachDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerachDlg();

// �Ի�������
	enum { IDD = IDD_SERACH_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_SerachLst;
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLbnKillfocusList1();
};
