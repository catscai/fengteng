#pragma once
#include "afxwin.h"
#include "atlcomtime.h"


// CMyRegisterDlg �Ի���

class CMyRegisterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyRegisterDlg)

public:
	CMyRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyRegisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush m_brushReg;				//��ˢ
	CEdit m_userIdReg;				//�����˺�
	CString m_userNameReg;			//�ǳ�
	CString m_userPasswdFirstReg;	//�����һ��
	CString m_userPasswdSocendReg;	//����ڶ���
	COleDateTime m_userBirthReg;	//��������
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
