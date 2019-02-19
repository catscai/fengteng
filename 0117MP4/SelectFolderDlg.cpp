#include "stdafx.h"
#include "SelectFolderDlg.h"


CSelectFolderDlg::CSelectFolderDlg(void)
{
}


CSelectFolderDlg::~CSelectFolderDlg(void)
{
}

CString CSelectFolderDlg::SerachFolder(CString DlgTitle)
{
		TCHAR			szFolderPath[MAX_PATH] = {0};
		CString			strFolderPath = _T("");
		
		BROWSEINFO		sInfo;
		::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
		sInfo.pidlRoot   = 0;
		sInfo.lpszTitle   = DlgTitle;
		sInfo.ulFlags   = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
		sInfo.lpfn     = NULL;
 
		// ��ʾ�ļ���ѡ��Ի���
		LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo); 
		if (lpidlBrowse != NULL)
		{
			// ȡ���ļ�����
			if (::SHGetPathFromIDList(lpidlBrowse,szFolderPath))  
			{
				strFolderPath = szFolderPath;
			}
		}
		if(lpidlBrowse != NULL)
		{
			::CoTaskMemFree(lpidlBrowse);
		}
 
		return strFolderPath;

}
