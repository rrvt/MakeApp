// Main Dialog Box


#pragma once
#include "Resource.h"
#include "StatusBar.h"
#include "TBBtnCtx.h"
#include "ToolBar.h"

class StatusBar;


// DialogDlg dialog

class DialogDlg : public CDialogEx {

DECLARE_DYNAMIC(DialogDlg)

String    helpPath;

ToolBar   toolBar;
StatusBar statusBar;

public:

           DialogDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual ~DialogDlg();

  virtual BOOL OnInitDialog();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_DialogApp };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnOK();

  DECLARE_MESSAGE_MAP()

private:

  void     setupToolBar();
  void     setComboBox();

  ToolBar* getToolBar() {return &toolBar;}

public:

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  afx_msg void    changeReady();
  afx_msg void    onAppAbout();
  afx_msg void    onHelp();

  afx_msg void    onDispatch();
  afx_msg void    onOption01();
  afx_msg void    onOption02();
  afx_msg void    onDispatch1();
  afx_msg void    onOption11();
  afx_msg void    onOption12();

  afx_msg void    onX();
  afx_msg void    onComboBoxChng();
  afx_msg void    onTBEditBox();

  afx_msg void    onSaveHist();
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
  };


