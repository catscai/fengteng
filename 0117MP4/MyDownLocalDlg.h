#pragma once
#include "afxwin.h"


// CMyDownLocalDlg �Ի���
#include <vector>
#include <map>
using namespace std;
class CMyDownLocalDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownLocalDlg)

public:
	CMyDownLocalDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDownLocalDlg();

// �Ի�������
	enum { IDD = IDD_DOWNLOAD_LOCAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_finishedLocalLst;
	map<CString,CString> m_nameTofilePathsMap;	//�洢·��
public:
	bool ShowVideos();
	void SerachLocalVideoes(CString filePath,vector<CString>& fileNames);
	afx_msg void OnLbnDblclkList1();
	virtual BOOL OnInitDialog();
};
