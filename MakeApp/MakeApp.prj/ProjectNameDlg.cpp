// ProjectNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MakeApp.h"
#include "ProjectNameDlg.h"
#include "Resource.h"


// ProjectNameDlg dialog

IMPLEMENT_DYNAMIC(ProjectNameDlg, CDialogEx)

ProjectNameDlg::ProjectNameDlg(CWnd* pParent) : CDialogEx(IDD_DIALOG1, pParent), name(_T("")),
                                                             description(_T("")), visibleName(_T("")) { }

ProjectNameDlg::~ProjectNameDlg() { }

void ProjectNameDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_EDIT1, name);
  DDX_Text(pDX, IDC_EDIT2, description);
  DDX_Text(pDX, IDC_EDIT3, visibleName);
  }


BEGIN_MESSAGE_MAP(ProjectNameDlg, CDialogEx)
END_MESSAGE_MAP()

