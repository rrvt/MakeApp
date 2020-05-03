// ProjectName.cpp : implementation file
//

#include "stdafx.h"
#include "MakeApp.h"
#include "ProjectName.h"
#include "afxdialogex.h"


// ProjectName dialog

IMPLEMENT_DYNAMIC(ProjectName, CDialogEx)

ProjectName::ProjectName(CWnd* pParent /*=nullptr*/)
  : CDialogEx(IDD_DIALOG1, pParent)
  , name(_T(""))
  , description(_T(""))
	, visibleName(_T(""))
{

}

ProjectName::~ProjectName()
{
}

void ProjectName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, name);
	DDX_Text(pDX, IDC_EDIT2, description);
	DDX_Text(pDX, IDC_EDIT3, visibleName);
}


BEGIN_MESSAGE_MAP(ProjectName, CDialogEx)
END_MESSAGE_MAP()


// ProjectName message handlers
