#pragma once


// CMyLoginDlg �Ի���

class CMyLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyLoginDlg)

public:
	CMyLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;	//���滭ˢ
	/*CString m_userName;*/
	CString m_userPasswd;
	DWORD m_userId;
public:
	//���˺�����ļ�����ڹ�������
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
