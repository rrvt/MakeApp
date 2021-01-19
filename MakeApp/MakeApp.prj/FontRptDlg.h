// Font Report Dialog


#pragma once


// FontRptDlg dialog

class FontRptDlg : public CDialogEx {

  DECLARE_DYNAMIC(FontRptDlg)

public:
BOOL abFonts;
BOOL cdFonts;
BOOL efFonts;
BOOL ghFonts;
BOOL ijFonts;
BOOL klFonts;
BOOL mnFonts;
BOOL opFonts;
BOOL qrFonts;
BOOL stFonts;
BOOL uvFonts;
BOOL wxFonts;
BOOL yzFonts;

  FontRptDlg(CWnd* pParent = nullptr);   // standard constructor

  virtual ~FontRptDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_FontRptDlg };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
