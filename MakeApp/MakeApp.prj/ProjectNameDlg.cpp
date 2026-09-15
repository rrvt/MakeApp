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


ProjectNameDlg::ProjectNameDlg(CWnd* pParent) :
                        CDialogEx(IDD_ProjectName, pParent), inclExmpls(FALSE), name(_T("")),
                        description(_T("")), visibleName(_T("")), appType(DocViewType) { }

ProjectNameDlg::~ProjectNameDlg() { }


BOOL ProjectNameDlg::OnInitDialog() {


  CDialogEx::OnInitDialog();

  return TRUE;
  }



void ProjectNameDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_InclExmpls,  inclExmpls);
  DDX_Radio(pDX, IDC_DocViewApp,  appType);
  DDX_Text( pDX, IDC_ProjectName, name);
  DDX_Text( pDX, IDC_WinDescription,       description);
  DDX_Text( pDX, IDC_VisibleName,       visibleName);
  }
