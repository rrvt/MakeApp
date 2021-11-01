// MakeApp.h : main header file for the MakeApp application

#pragma once
#include "CApp.h"


class MakeAppDoc;
class MakeAppView;
class MainFrame;


// MakeApp:
// See MakeApp.cpp for the implementation of this class

class MakeApp : public CApp {

public:

               MakeApp() noexcept : CApp(this) { }

  virtual BOOL InitInstance();

          MakeAppDoc*  doc()     {return (MakeAppDoc*)  CApp::getDoc();}
          MakeAppView* view()    {return (MakeAppView*) CApp::getView();}
          MainFrame*   mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnSpecifyBaseDir();
  afx_msg void OnHelp();
  };


extern MakeApp theApp;

inline void         invalidate() {theApp.invalidate();}
inline MakeAppDoc*  doc()        {return theApp.doc();}
inline MakeAppView* view()       {return theApp.view();}

