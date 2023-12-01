// AppT3mplate.h : main header file for the AppT3mplate application

#pragma once
#include "CApp.h"
#include "MainFrame.h"


class AppT3mplateDoc;
class AppT3mplateView;


class AppT3mplate : public CApp {

String roamPath;
String appPath;

public:

               AppT3mplate() noexcept : CApp(this) { }

  virtual BOOL InitInstance();
  virtual int  ExitInstance();

          AppT3mplateDoc*  doc()         {return (AppT3mplateDoc*)  CApp::getDoc();}
          AppT3mplateView* view()        {return (AppT3mplateView*) CApp::getView();}
          MainFrame*       mainFrm()     {return (MainFrame*)       m_pMainWnd;}
          String&          roamingPath() {return roamPath;}
          String&          thisAppPath() {return appPath;}

  DECLARE_MESSAGE_MAP()

  afx_msg void onAppAbout();
  afx_msg void onHelp();
  };


extern AppT3mplate theApp;

inline void             invalidate() {theApp.invalidate();}
inline AppT3mplateDoc*  doc()        {return theApp.doc();}
inline AppT3mplateView* view()       {return theApp.view();}
inline MainFrame*       mainFrm()    {return theApp.mainFrm();}
inline ToolBar&         getToolBar() {return mainFrm()->getToolBar();}

