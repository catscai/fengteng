#pragma once
#include "afxwin.h"
#include "atlcomtime.h"


// CMyRegisterDlg 对话框

class CMyRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyRegisterDlg)

public:
	CMyRegisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyRegisterDlg();

// 对话框数据
	enum { IDD = IDD_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brushReg;				//画刷
	CEdit m_userIdReg;				//申请账号
	CString m_userNameReg;			//昵称
	CString m_userPasswdFirstReg;	//密码第一次
	CString m_userPasswdSocendReg;	//密码第二次
	COleDateTime m_userBirthReg;	//出生日期
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnRegisterRqUserId(WPARAM w, LPARAM l);
	afx_msg LRESULT OnRegisterSuccess(WPARAM w, LPARAM l);
	afx_msg void OnDestroy();
};
