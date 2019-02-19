
// 0117MP4Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MyComDlg.h"
#include "MyLoginDlg.h"
#include "MyRegisterDlg.h"
#include "MyPublicWordDlg.h"
#include "MyStreaming.h"
#include "MyCollectDlg.h"
// CMy0117MP4Dlg �Ի���
class CMy0117MP4Dlg : public CDialogEx
{
// ����
public:
	CMy0117MP4Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY0117MP4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CBrush				m_brush;				//�Ի���,��������,�������黭ˢ
	HBITMAP				m_playBit;				//����ͼƬ
	HBITMAP				m_pauseBit;				//��ͣͼƬ
	bool				m_isPlayBit;			//������ͣͼƬ��־
	CStatic				m_PlayButton;			//
	CMyComDlg			m_listDlg;				//�б���
	CMyLoginDlg			m_loginDlg;				//��¼����
	CMyRegisterDlg		m_registerDlg;			//ע�ᴰ��
	CMyPublicWordDlg	m_wordDlg;				//�鿴���洰��
	//CMyStreaming m_streamDlg;					//ֱ������
	CMyCollectDlg		m_collectDlg;			//�ղش���
	CSliderCtrl			m_sliderProcess;		//���Ž��ȿ�����
	CSliderCtrl			m_sliderVolume;			//����������
	CStatic				m_PlayingName;			//��ʾ���ڲ��ŵ���Ƶ����
	CStatic				m_PlayMaxTime;			//��Ƶ����ʱ��
	CStatic				m_PlayMinTime;			//��Ƶ���ŵ�ǰʱ��
	bool				m_isSetMaxTime;			//�ڶ�ʱ�����ж��Ƿ��Ѿ�������maxtime
	CButton				m_buttonWord;			//���水ť
	CButton				m_buttonLogin;			//��¼��ť
	int					m_PlayNetVideoCount;	//����������Ƶ�ڼ��� Ĭ��Ϊ0��ʾ������Ƶ
	CRect				m_rect;					//������λ��
	long				m_CurrentVolume;		//ʱ�̼�¼ÿ�������ĵ���
	CRect				m_rectPic;				//����picture�ؼ���С
	bool				m_IsMaxPicture;			//�Ƿ���󻯲���(��ǰ״̬)
	CBitmap				m_picBit1,m_picBit2;	//���ſؼ��л�ͼƬ
	CBitmap				m_picBit3;
	CButton				m_CollectButn;
	CButton				m_DownloadButn;
	CButton				m_SreenShotButn;
	CButton				m_SwitchListButn;
	CStatic				m_LastPlay;
	CStatic				m_NextPlay;
	CStatic				m_StopPlay;
public:
	bool   HideAllCtrl();			//����/�ָ����пؼ���Ϊ���ʹ��
	bool   RecoverAllCtrl();
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnStnClickedPlayBu();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnStnClickedStopBu();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButton6();
public:
	afx_msg void OnStnClickedNextBu();
	afx_msg void OnStnClickedLastBu();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnBnClickedButtonLogin();
	afx_msg void OnBnClickedButton9();
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButton10();
	afx_msg LRESULT OnPublicWord(WPARAM w, LPARAM l);
	afx_msg LRESULT OnLogingSuccess(WPARAM w, LPARAM l);
	afx_msg LRESULT OnLogingFailture(WPARAM w, LPARAM l);

	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
