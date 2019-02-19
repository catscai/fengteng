#pragma once


// CMyLoginDlg 对话框

class CMyLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyLoginDlg)

public:
	CMyLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGINDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brush;	//界面画刷
	/*CString m_userName;*/
	CString m_userPasswd;
	DWORD m_userId;
public:
	//对账号密码的检验放在工具类中
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton8();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
};
