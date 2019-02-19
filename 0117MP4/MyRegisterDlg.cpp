// MyRegisterDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyRegisterDlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "MyTools.h"

// CMyRegisterDlg 对话框

IMPLEMENT_DYNAMIC(CMyRegisterDlg, CDialogEx)

CMyRegisterDlg::CMyRegisterDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyRegisterDlg::IDD, pParent)
	, m_userNameReg(_T(""))
	, m_userPasswdFirstReg(_T(""))
	, m_userPasswdSocendReg(_T(""))
	, m_userBirthReg(COleDateTime::GetCurrentTime())
{

}

CMyRegisterDlg::~CMyRegisterDlg()
{
}

void CMyRegisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_userIdReg);
	DDX_Text(pDX, IDC_EDIT3, m_userNameReg);
	DDX_Text(pDX, IDC_EDIT4, m_userPasswdFirstReg);
	DDX_Text(pDX, IDC_EDIT5, m_userPasswdSocendReg);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_userBirthReg);
}


BEGIN_MESSAGE_MAP(CMyRegisterDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON6, &CMyRegisterDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyRegisterDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyRegisterDlg::OnBnClickedButton1)
	ON_MESSAGE(REGISTER_RQUSERID,&CMyRegisterDlg::OnRegisterRqUserId)
	ON_MESSAGE(REGISTER_SUCCESS_MEG,&CMyRegisterDlg::OnRegisterSuccess)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyRegisterDlg 消息处理程序
//返回申请的账号
LRESULT CMyRegisterDlg::OnRegisterRqUserId(WPARAM w, LPARAM l)
{
	CString userId;
	userId.Format(_T("%ld"),l);
	m_userIdReg.SetWindowText(userId);
	UpdateData(FALSE);
	return 0;
}
//注册成功
LRESULT CMyRegisterDlg::OnRegisterSuccess(WPARAM w, LPARAM l)
{
	AfxMessageBox(_T("恭喜,注册成功"));
	//隐藏当前窗口
	this->ShowWindow(SW_HIDE);
	return 0;
}
BOOL CMyRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//定义画刷
	m_brushReg.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control
}


HBRUSH CMyRegisterDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return m_brushReg;
	}
	return hbr;
}


BOOL CMyRegisterDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN){

		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//注册
void CMyRegisterDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString userId;
	m_userIdReg.GetWindowText(userId);
	if(userId==_T("")){
		AfxMessageBox(_T("请先申请账号"));
		return;
	}
	if(m_userNameReg==_T(""))
	{
		AfxMessageBox(_T("您还没起名字呢"));
		return;
	}
	if(m_userNameReg.GetLength()>16)
	{
		AfxMessageBox(_T("昵称过长"));
		return;
	}
	if(m_userPasswdFirstReg==_T("")||m_userPasswdSocendReg==_T(""))
	{
		AfxMessageBox(_T("请输入密码不能大于16位"));
		return;
	}
	if(!CMyTools::CheckUserPasswd(m_userPasswdFirstReg)||!CMyTools::CheckUserPasswd(m_userPasswdSocendReg))
	{
		AfxMessageBox(_T("非法密码"));
		return;
	}
	if(m_userPasswdFirstReg!=m_userPasswdSocendReg)
	{
		AfxMessageBox(_T("两次密码不一致"));
		return;
	}
	//向服务器发送注册消息
	char*temp=CMyTools::EnCodeWCHARToUtf(userId.GetBuffer(0));
	char id[20];
	strcpy_s(id,temp);
	delete[] temp;
	//将字符串的id转化过来
	long uid=atoi(id);
	//转化昵称
	char* nameTemp=CMyTools::EnCodeWCHARToUtf(m_userNameReg.GetBuffer(0));
	char uname[MAX_LOGIN_PASSWD];
	strcpy_s(uname,nameTemp);
	delete[] nameTemp;
	//转化密码
	char* passwdTemp=CMyTools::EnCodeWCHARToUtf(m_userPasswdFirstReg.GetBuffer(0));
	char upass[MAX_LOGIN_PASSWD];
	strcpy_s(upass,passwdTemp);
	REGISTERINFO registerInfo;
	registerInfo.RqType=UDP_REGISTER_USER;
	registerInfo.userid=uid;				//账号
	strcpy_s(registerInfo.username,uname);	//昵称
	strcpy_s(registerInfo.passwd,upass);	//密码
	CString nBirth=m_userBirthReg.Format(_T("%Y-%m-%d"));
	char* tempTime=CMyTools::EnCodeWCHARToUtf(nBirth.GetBuffer(0));
	strcpy_s(registerInfo.birth,tempTime);	//出生日期
	delete[] tempTime;
	//发送
	theApp.getUDPMediator()->SendData((char*)&registerInfo,sizeof(registerInfo));
}

//取消
void CMyRegisterDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
}

//申请账号
void CMyRegisterDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//向服务器发送消息 申请账号
	REGISRTERRQ registerRq;
	registerRq.RqType=UDP_REGISTER_RQ;
	registerRq.userid=0;
	theApp.getUDPMediator()->SendData((char*)&registerRq,sizeof(registerRq));
}


void CMyRegisterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_brushReg.DeleteObject();
	
	// TODO: 在此处添加消息处理程序代码
}
