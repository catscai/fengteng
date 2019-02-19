#pragma once
#include "afxwin.h"


// CMySetConfigDlg �Ի���

class CMySetConfigDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMySetConfigDlg)

public:
	CMySetConfigDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMySetConfigDlg();

// �Ի�������
	enum { IDD = IDD_SETCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_VideoDownloadPathEdit;
	CEdit m_VideoHistPathEdit;
	CEdit m_ScreenShotPathEdit;
public:

	afx_msg void OnBnClickedVideodownpath();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedScreenshotpath();
	afx_msg void OnBnClickedSaveallset();
	afx_msg void OnBnClickedCancelset();
	virtual BOOL OnInitDialog();
};
