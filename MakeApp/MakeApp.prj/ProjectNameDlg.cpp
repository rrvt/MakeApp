// ProjectNameDlg.cpp : implementation file
//

#include "pch.h"
#include "ProjectNameDlg.h"
#include "MakeApp.h"
#include "Resource.h"


// ProjectNameDlg dialog

IMPLEMENT_DYNAMIC(ProjectNameDlg, CDialogEx)



BEGIN_MESSAGE_MAP(ProjectNameDlg, CDialogEx)
END_MESSAGE_MAP()


ProjectNameDlg::ProjectNameDlg(CWnd* pParent) : CDialogEx(IDD_DIALOG1, pParent),
                                                name(_T("")),
                                                description(_T("")),
                                                visibleName(_T("")),
                                                appType(DocViewType) { }

ProjectNameDlg::~ProjectNameDlg() { }


BOOL ProjectNameDlg::OnInitDialog() {


  CDialogEx::OnInitDialog();

  return TRUE;
  }



void ProjectNameDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Radio(pDX, IDC_DocViewApp, appType);
  DDX_Text( pDX, IDC_EDIT1,      name);
  DDX_Text( pDX, IDC_EDIT2,      description);
  DDX_Text( pDX, IDC_EDIT3,      visibleName);
  }
