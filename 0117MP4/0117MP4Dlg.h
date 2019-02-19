
// 0117MP4Dlg.h : 头文件
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
// CMy0117MP4Dlg 对话框
class CMy0117MP4Dlg : public CDialogEx
{
// 构造
public:
	CMy0117MP4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY0117MP4_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CBrush				m_brush;				//对话框,播发滑块,音量滑块画刷
	HBITMAP				m_playBit;				//播放图片
	HBITMAP				m_pauseBit;				//暂停图片
	bool				m_isPlayBit;			//播放暂停图片标志
	CStatic				m_PlayButton;			//
	CMyComDlg			m_listDlg;				//列表窗口
	CMyLoginDlg			m_loginDlg;				//登录窗口
	CMyRegisterDlg		m_registerDlg;			//注册窗口
	CMyPublicWordDlg	m_wordDlg;				//查看公告窗口
	//CMyStreaming m_streamDlg;					//直播窗口
	CMyCollectDlg		m_collectDlg;			//收藏窗口
	CSliderCtrl			m_sliderProcess;		//播放进度控制条
	CSliderCtrl			m_sliderVolume;			//声音控制条
	CStatic				m_PlayingName;			//显示正在播放的视频名称
	CStatic				m_PlayMaxTime;			//视频的总时间
	CStatic				m_PlayMinTime;			//视频播放当前时间
	bool				m_isSetMaxTime;			//在定时器中判断是否已经设置了maxtime
	CButton				m_buttonWord;			//公告按钮
	CButton				m_buttonLogin;			//登录按钮
	int					m_PlayNetVideoCount;	//播放在线视频第几段 默认为0表示本地视频
	CRect				m_rect;					//主窗口位置
	long				m_CurrentVolume;		//时刻记录每次音量的调整
	CRect				m_rectPic;				//播放picture控件大小
	bool				m_IsMaxPicture;			//是否最大化播放(当前状态)
	CBitmap				m_picBit1,m_picBit2;	//播放控件切换图片
	CBitmap				m_picBit3;
	CButton				m_CollectButn;
	CButton				m_DownloadButn;
	CButton				m_SreenShotButn;
	CButton				m_SwitchListButn;
	CStatic				m_LastPlay;
	CStatic				m_NextPlay;
	CStatic				m_StopPlay;
public:
	bool   HideAllCtrl();			//隐藏/恢复所有控件、为最大化使用
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
