#pragma once
#include "afxwin.h"


// CMyPublicWordDlg �Ի���

class CMyPublicWordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyPublicWordDlg)

public:
	CMyPublicWordDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyPublicWordDlg();

// �Ի�������
	enum { IDD = IDD_PUBLICWORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_publicBoard;	//�����
	CBrush m_brush;			//��ˢ
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
