// MyRegisterDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyRegisterDlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "MyTools.h"

// CMyRegisterDlg �Ի���

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


// CMyRegisterDlg ��Ϣ�������
//����������˺�
LRESULT CMyRegisterDlg::OnRegisterRqUserId(WPARAM w, LPARAM l)
{
	CString userId;
	userId.Format(_T("%ld"),l);
	m_userIdReg.SetWindowText(userId);
	UpdateData(FALSE);
	return 0;
}
//ע��ɹ�
LRESULT CMyRegisterDlg::OnRegisterSuccess(WPARAM w, LPARAM l)
{
	AfxMessageBox(_T("��ϲ,ע��ɹ�"));
	//���ص�ǰ����
	this->ShowWindow(SW_HIDE);
	return 0;
}
BOOL CMyRegisterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//���廭ˢ
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
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN){

		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

//ע��
void CMyRegisterDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString userId;
	m_userIdReg.GetWindowText(userId);
	if(userId==_T("")){
		AfxMessageBox(_T("���������˺�"));
		return;
	}
	if(m_userNameReg==_T(""))
	{
		AfxMessageBox(_T("����û��������"));
		return;
	}
	if(m_userNameReg.GetLength()>16)
	{
		AfxMessageBox(_T("�ǳƹ���"));
		return;
	}
	if(m_userPasswdFirstReg==_T("")||m_userPasswdSocendReg==_T(""))
	{
		AfxMessageBox(_T("���������벻�ܴ���16λ"));
		return;
	}
	if(!CMyTools::CheckUserPasswd(m_userPasswdFirstReg)||!CMyTools::CheckUserPasswd(m_userPasswdSocendReg))
	{
		AfxMessageBox(_T("�Ƿ�����"));
		return;
	}
	if(m_userPasswdFirstReg!=m_userPasswdSocendReg)
	{
		AfxMessageBox(_T("�������벻һ��"));
		return;
	}
	//�����������ע����Ϣ
	char*temp=CMyTools::EnCodeWCHARToUtf(userId.GetBuffer(0));
	char id[20];
	strcpy_s(id,temp);
	delete[] temp;
	//���ַ�����idת������
	long uid=atoi(id);
	//ת���ǳ�
	char* nameTemp=CMyTools::EnCodeWCHARToUtf(m_userNameReg.GetBuffer(0));
	char uname[MAX_LOGIN_PASSWD];
	strcpy_s(uname,nameTemp);
	delete[] nameTemp;
	//ת������
	char* passwdTemp=CMyTools::EnCodeWCHARToUtf(m_userPasswdFirstReg.GetBuffer(0));
	char upass[MAX_LOGIN_PASSWD];
	strcpy_s(upass,passwdTemp);
	REGISTERINFO registerInfo;
	registerInfo.RqType=UDP_REGISTER_USER;
	registerInfo.userid=uid;				//�˺�
	strcpy_s(registerInfo.username,uname);	//�ǳ�
	strcpy_s(registerInfo.passwd,upass);	//����
	CString nBirth=m_userBirthReg.Format(_T("%Y-%m-%d"));
	char* tempTime=CMyTools::EnCodeWCHARToUtf(nBirth.GetBuffer(0));
	strcpy_s(registerInfo.birth,tempTime);	//��������
	delete[] tempTime;
	//����
	theApp.getUDPMediator()->SendData((char*)&registerInfo,sizeof(registerInfo));
}

//ȡ��
void CMyRegisterDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
}

//�����˺�
void CMyRegisterDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������������Ϣ �����˺�
	REGISRTERRQ registerRq;
	registerRq.RqType=UDP_REGISTER_RQ;
	registerRq.userid=0;
	theApp.getUDPMediator()->SendData((char*)&registerRq,sizeof(registerRq));
}


void CMyRegisterDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_brushReg.DeleteObject();
	
	// TODO: �ڴ˴������Ϣ����������
}
