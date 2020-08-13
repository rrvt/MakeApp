// TestApp.h : main header file for the TestApp application

#pragma once
#include "CApp.h"


class TestAppDoc;
class TestAppView;


// TestApp:
// See TestApp.cpp for the implementation of this class

class TestApp : public CApp {

public:

               TestApp() noexcept { }

  virtual BOOL InitInstance();

          TestAppDoc*  doc()  {return (TestAppDoc*)  CApp::getDoc();}
          TestAppView* view() {return (TestAppView*) CApp::getView();}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
};


extern TestApp theApp;

inline void         invalidate() {theApp.invalidate();}
inline TestAppDoc*  doc()  {return theApp.doc();}
inline TestAppView* view() {return theApp.view();}

