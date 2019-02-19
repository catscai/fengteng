// PlayListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "PlayListBox.h"
#include "MyComDlg.h"
#include "UDPMediator.h"
#include "Packdef.h"
// PlayListBox

IMPLEMENT_DYNAMIC(PlayListBox, CListBox)

PlayListBox::PlayListBox()
{
	m_menu.LoadMenu(IDR_MENU1);
	pool.CreateTestThread(1,4);
	m_downTaskDlg.Create(IDD_DOWNLOAD_TASK);
	m_SetConfigDlg.Create(IDD_SETCONFIG);
	m_downTaskDlg.SetWindowText(_T("��������"));
	m_SetConfigDlg.SetWindowText(_T("���ò�������"));
}

PlayListBox::~PlayListBox()
{
	m_menu.DestroyMenu();
	pool.DestoryTestThread();
}


BEGIN_MESSAGE_MAP(PlayListBox, CListBox)
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_TTT_32779, &PlayListBox::OnTttDownLoad)
	ON_COMMAND(ID_Menu32785, &PlayListBox::OnMenuDownListShow)
	ON_COMMAND(ID_TTT_32781, &PlayListBox::OnTtt32781)
	ON_COMMAND(ID_TTT_32780, &PlayListBox::OnTtt32780)
	ON_COMMAND(ID_TTT_32782, &PlayListBox::OnTtt32782)
	ON_COMMAND(ID_TTT_32786, &PlayListBox::OnTtt32786)
	//ON_COMMAND(ID_TTT_32787, &PlayListBox::OnTtt32787)
	ON_COMMAND(ID_TTT_32788, &PlayListBox::OnTttSetConfig)
END_MESSAGE_MAP()



// PlayListBox ��Ϣ�������




void PlayListBox::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	POINT CursorPos;
	::GetCursorPos(&CursorPos);
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, CursorPos.x, CursorPos.y, this);  
	CListBox::OnRButtonUp(nFlags, point);
}

//������Ƶ��ǰ
void PlayListBox::OnTttDownLoad()
{
	// TODO: �ڴ���������������
	CString vName;
	int curSel=this->m_comdlg->m_listName.GetCurSel();
	if(curSel==-1)
		return;
	this->m_comdlg->m_listName.GetText(curSel,vName);
	CString urlc=m_comdlg->m_nameToPathMap[vName];
	//�������غ���
	this->DownLoadVideoInUrl(urlc,vName);
}

////������Ƶ �ص�����
//void PlayListBox::DownLoadCallBack(int ContentSize, int CUR_LEN)
//{
//
//}

//���������б�
void PlayListBox::OnMenuDownListShow()
{
	// TODO: �ڴ���������������
	m_downTaskDlg.ShowWindow(SW_SHOW);
}

//������Ƶִ�к���
void PlayListBox::DownLoadVideoInUrl(CString urlc,CString vName)
{
	char* url=CMyTools::EnCodeWCHARToUtf(urlc.GetBuffer());
	if(strncmp(url,"rtmp",4)==0||strncmp(url,"https",5)==0||strncmp(url,"http",4)==0||strncmp(url,"rstp",4)==0||strncmp(url,"tcp",3)==0||strncmp(url,"udp",3)==0)
	{
		//��ȡ�����б�����
		int nRow=m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.GetItemCount();
		//���б��������
		m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.InsertItem(nRow,NULL);
		//��������Ϣ

		CString path(theApp.g_DownLoadVideoPath);
		CString sty=CMyTools::GetUrlName(urlc);
		if(vName.GetLength() > 50)
			vName = vName.Left(50);
		path += L"\\"+vName+sty;
		m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.SetItemText(nRow,0,vName+sty);
		m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.SetItemText(nRow,2,_T("0k"));
		m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.SetItemText(nRow,3,_T("�ȴ�����"));
		m_downTaskDlg.m_tabCtrl.m_downListDlg.m_processList.SetItemData(nRow,0);
		//����������
		DownLoadTask* newTask=new DownLoadTask;
		newTask->downListDlg=&(m_downTaskDlg.m_tabCtrl.m_downListDlg);
		newTask->finishedDlg=&(m_downTaskDlg.m_tabCtrl.m_finishedListDlg);
		newTask->nIteam=nRow;
		newTask->SetTaskParams(urlc.GetBuffer(),path.GetBuffer());
		//���̳߳����������
		pool.AddTask(newTask);
		m_downTaskDlg.m_tabCtrl.m_downListDlg.UpdateData(FALSE);
	}else{
		AfxMessageBox(_T("����ƵΪ������Ƶ�������أ�"));
	}
	//�ͷ�
	delete[] url;
}

//��������ר��
void PlayListBox::OnTtt32781()
{
	// TODO: �ڴ���������������
	CString vName;
	int curSel=this->m_comdlg->m_listName.GetCurSel();
	if(curSel==-1)
		return;
	this->m_comdlg->m_listName.GetText(curSel,vName);
	bool IsAlbumflag=false;
	int i=1;
	WCHAR NumStr[5]={0};
	CString Name=CMyTools::GetNamesAlbum(vName);
	_itot_s(i,NumStr,5,10);
	CString temp=NumStr;
	temp+=L"-"+Name;
	CString urlc;
	while(m_comdlg->m_nameToPathMap.find(temp)!=m_comdlg->m_nameToPathMap.end())
	{
		i++;
		IsAlbumflag=true;
		urlc=m_comdlg->m_nameToPathMap[temp];
		this->DownLoadVideoInUrl(urlc,temp);
		_itot_s(i,NumStr,5,10);
		temp=NumStr;
		temp+=L"-"+Name;
	}//���λ�ò�����ר���� �������ⵥ����Ƶ
	if(IsAlbumflag==false)
	{
		urlc=m_comdlg->m_nameToPathMap[vName];
		this->DownLoadVideoInUrl(urlc,vName);
	}
}

//�Ӳ����б���ɾ����Ƶ
void PlayListBox::OnTtt32780()
{
	// TODO: �ڴ���������������
	int index=this->m_comdlg->m_listName.GetCurSel();
	if(index==-1)
		return;
	CString vName;
	this->m_comdlg->m_listName.GetText(index,vName);
	if(vName==_T(""))
		return;
	this->m_comdlg->m_listName.DeleteString(index);
	this->m_comdlg->m_nameToPathMap.erase(vName);

}

//��ղ����б�
void PlayListBox::OnTtt32782()
{
	// TODO: �ڴ���������������
	int count=this->m_comdlg->m_listName.GetCount();
	for(int i=count-1;i>=0;i--)
	{
		this->m_comdlg->m_listName.DeleteString(i);
	}
	this->m_comdlg->m_nameToPathMap.clear();
}

//�ղص�����Ƶ
void PlayListBox::OnTtt32786()
{
	// TODO: �ڴ���������������
	UDPMediator*udpMediator=(UDPMediator*)theApp.getUDPMediator();
	if(udpMediator->m_isLoginFlag==false)
	{
		AfxMessageBox(_T("���ڵ�¼���ղظ���Ƶ"));
		return;
	}
	int index=this->m_comdlg->m_listName.GetCurSel();
	if(index==-1)
		return;
	CString vName;
	this->m_comdlg->m_listName.GetText(index,vName);

	CString urlc;
	urlc=this->m_comdlg->m_nameToPathMap[vName];
	if( wcsncmp(urlc.GetBuffer(),L"http",4)==0||wcsncmp(urlc.GetBuffer(),L"tcp",3)==0||
		wcsncmp(urlc.GetBuffer(),L"rstp",4)==0||wcsncmp(urlc.GetBuffer(),L"udp",4)==0)
	{
		//�����ղ���Ƶ��Ϣ
		COLLECTSINGLERQ collect;
		collect.RqType=COLLECT_SINGLE_RQ;
		char*temp=CMyTools::EnCodeWCHARToUtf(vName.GetBuffer());
		strcpy_s(collect.movieName,temp);
		delete[] temp;
		char*tempx=CMyTools::EnCodeWCHARToUtf(urlc.GetBuffer());
		strcpy_s(collect.link,tempx);
		delete[] tempx;
		collect.userid=udpMediator->m_userid;
		
		//����
		theApp.getUDPMediator()->SendData((char*)&collect,sizeof(collect));

	}else
	{
		AfxMessageBox(_T("����Ƶ��Ϊ������Ƶ,����Ҫ�ղ�"));
	}

}

////�ղ�����ר��
//void PlayListBox::OnTtt32787()
//{
//	// TODO: �ڴ���������������
//}


void PlayListBox::OnTttSetConfig()
{
	// TODO: �ڴ���������������
	m_SetConfigDlg.ShowWindow(SW_SHOW);
}
