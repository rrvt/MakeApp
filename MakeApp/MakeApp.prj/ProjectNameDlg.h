// ProjectNameDlg dialog


#pragma once


enum AppType {DocViewType, DialogType};


class ProjectNameDlg : public CDialogEx {

  DECLARE_DYNAMIC(ProjectNameDlg)

public:

int     appType;
Cstring name;
Cstring description;
Cstring visibleName;

           ProjectNameDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~ProjectNameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DIALOG1 };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  };
