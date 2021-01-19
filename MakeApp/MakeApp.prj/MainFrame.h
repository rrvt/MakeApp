// MainFrame.h : interface of the MainFrame class


#pragma once
#include "CMainFrm.h"
#include "ToolBar.h"


class MainFrame : public CMainFrm {

CMFCMenuBar   m_wndMenuBar;
CMFCStatusBar m_wndStatusBar;
ToolBar       toolBar;
CMenu         menu;

protected:                                          // create from serialization only

  MainFrame() noexcept;


  DECLARE_DYNCREATE(MainFrame)

public:                                             // Overrides

  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual ~MainFrame();

  void setupToolBar();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:                                          // Generated message map functions
  DECLARE_MESSAGE_MAP()

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  };


