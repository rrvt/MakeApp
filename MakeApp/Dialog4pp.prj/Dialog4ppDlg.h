// Main Dialog Box


#pragma once
#include "Resource.h"
#include "StatusBar.h"
#include "MyToolBar.h"
#include "WinPos.h"

class StatusBar;


// Dialog4ppDlg dialog

class Dialog4ppDlg : public CDialogEx {

DECLARE_DYNAMIC(Dialog4ppDlg)

String    helpPath;

MyToolBar toolBar;
StatusBar statusBar;

bool      isInitialized;

public:

           Dialog4ppDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual ~Dialog4ppDlg();

  virtual BOOL OnInitDialog();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Dialog4pp };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnOK();

  DECLARE_MESSAGE_MAP()

private:

  void            setupToolBar();

public:

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  afx_msg void    onAppAbout();
  afx_msg void    onHelp();

  afx_msg void    OnMove(int x, int y);
#ifdef DialogSizable
  afx_msg void    OnSize(UINT nType, int cx, int cy);
#endif
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);

#ifdef Examples
  afx_msg void    changeReady();

  afx_msg void    onTBChange(NMHDR* pNMHDR, LRESULT* pResult);

  afx_msg void    onDispatch();
  afx_msg void    onOption00();
  afx_msg void    onOption01();
  afx_msg void    onOption02();
  afx_msg void    onDispatch1();
  afx_msg void    onOption11();
  afx_msg void    onOption12();
  afx_msg void    onSaveHist();

  afx_msg void    onX();
  afx_msg void    onCboBxChange();
  afx_msg void    onCboBx1Change();

  afx_msg void    onTBEditBox();
#endif
  };


