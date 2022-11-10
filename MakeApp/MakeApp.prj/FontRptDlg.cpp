// FontRptDlg.cpp : implementation file
//

#include "pch.h"
#include "FontRptDlg.h"
#include "Resource.h"


// FontRptDlg dialog

IMPLEMENT_DYNAMIC(FontRptDlg, CDialogEx)

FontRptDlg::FontRptDlg(CWnd* pParent) : CDialogEx(IDD_FontRptDlg, pParent), abFonts(FALSE),
                                        cdFonts(FALSE), efFonts(FALSE), ghFonts(FALSE), ijFonts(FALSE),
                                        klFonts(FALSE), mnFonts(FALSE), opFonts(FALSE), qrFonts(FALSE),
                                        stFonts(FALSE), uvFonts(FALSE), wxFonts(FALSE), yzFonts(FALSE)
                                        { }


FontRptDlg::~FontRptDlg() { }


void FontRptDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_AB, abFonts);
  DDX_Check(pDX, IDC_CD, cdFonts);
  DDX_Check(pDX, IDC_EF, efFonts);
  DDX_Check(pDX, IDC_GH, ghFonts);
  DDX_Check(pDX, IDC_IJ, ijFonts);
  DDX_Check(pDX, IDC_KL, klFonts);
  DDX_Check(pDX, IDC_MN, mnFonts);
  DDX_Check(pDX, IDC_OP, opFonts);
  DDX_Check(pDX, IDC_QR, qrFonts);
  DDX_Check(pDX, IDC_ST, stFonts);
  DDX_Check(pDX, IDC_UV, uvFonts);
  DDX_Check(pDX, IDC_WX, wxFonts);
  DDX_Check(pDX, IDC_YZ, yzFonts);
  }



BEGIN_MESSAGE_MAP(FontRptDlg, CDialogEx)
END_MESSAGE_MAP()



