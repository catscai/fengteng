#pragma once


// CMyTabCtrl
#include "MyDownLoadListDlg.h"
#include "MyDownFinishedDlg.h"
#include "MyDownLocalDlg.h"
class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CMyDownLoadListDlg m_downListDlg;
	CMyDownFinishedDlg m_finishedListDlg;
	CMyDownLocalDlg    m_localListDlg;
public:
	void InitTabCtrl(int nCount,CString strName[]);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
};


