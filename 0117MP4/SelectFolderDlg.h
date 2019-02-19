#pragma once
class CSelectFolderDlg
{
public:
	CSelectFolderDlg(void);
	~CSelectFolderDlg(void);
public:
	static CString SerachFolder(CString DlgTitle=_T("请选择一个文件夹："));
};

