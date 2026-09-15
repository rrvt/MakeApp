// MakeApp.h : main header file for the MakeApp application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class MakeAppDoc;
class MakeAppView;


// MakeApp:
// See MakeApp.cpp for the implementation of this class

class MakeApp : public CApp {

String roamPath;
String appPath;

public:
               MakeApp() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

  MakeAppDoc*  doc()         {return (MakeAppDoc*)  CApp::getDoc();}
  MakeAppView* view()        {return (MakeAppView*) CApp::getView();}
  MainFrame*   mainFrm()     {return (MainFrame*) m_pMainWnd;}
  String&      roamingPath() {return roamPath;}
  String&      thisAppPath() {return appPath;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnAppAbout();
  afx_msg void OnSpecifyBaseDir();
  afx_msg void OnHelp();
  afx_msg void onExitApp();
  };


extern MakeApp theApp;

inline MakeAppDoc*  doc()        {return theApp.doc();}
inline MakeAppView* view()       {return theApp.view();}
inline MainFrame*   mainFrm()    {return theApp.mainFrm();}
inline MyToolBar&   getToolBar() {return mainFrm()->getToolBar();}

