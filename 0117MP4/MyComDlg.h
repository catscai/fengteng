#pragma once


// CMyComDlg �Ի���
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"
#include "0117MP4.h"
#include <map>
#include <string>
#include <vector>
#include "playlistbox.h"
#include "SerachDlg.h"
using namespace std;

class CMyComDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyComDlg)

public:
	CMyComDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyComDlg();

// �Ի�������
	enum { IDD = IDD_MYCOMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBrush			m_BrushBk;	//������ˢ
	CListBox		m_listReferVideo;	//�Ƽ��б�
	VideoManager*	m_videoManager;
	CString			m_videoPath;	//��ǰ����·��
	CString			m_playingName;	//���ڲ��ŵ���Ƶ����
	CEdit			m_editVideoName;
	map<CString,CString>		m_nameToPathMap;
	map<CString,vector<string>> m_movieNameToLinkMap;	//���ƶ�Ӧ����
	CSerachDlg		m_SerachDlg;		//��������
	PlayListBox		m_listName;
	unsigned		m_moviepos;		//���ܷ������Ƽ�����Ƶ��Ŀ
public:
	void PlayLocation(CString movieName);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnDblclkList2();
	afx_msg LRESULT OnMovieInfo(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSerachMovieRs(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSerachMovieInfoRs(WPARAM w, LPARAM l);
	/*afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);*/
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTttDownLoad();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedLoadmore();
	afx_msg void OnStnClickedCleanlist();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
