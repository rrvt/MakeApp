// TestApp.h : main header file for the TestApp application

#pragma once
#include "resource.h"       // main symbols
#include "IniFile.h"
#include "MainFrame.h"


class TestAppDoc;
class TestAppView;


// TestApp:
// See TestApp.cpp for the implementation of this class

class TestApp : public CWinAppEx {
String       appID;

TestAppDoc*  doc;
TestAppView* view;

public:

String version;

               TestApp() noexcept;

  virtual BOOL InitInstance();

          void setAppName(TCchar* appName) {getMainFrame()->setAppName(appName);}   // Title left part
          void setTitle(TCchar* rightPart) {getMainFrame()->setTitle(rightPart);}    // title right part

          void invalidate();

  // Implementation

  afx_msg void OnAppAbout();
  afx_msg void OnHelp();

  DECLARE_MESSAGE_MAP()

private:

  MainFrame*   getMainFrame() {return (MainFrame*) m_pMainWnd;}
  TestAppDoc*  getDocument();
  TestAppView* getView();

public:
  friend TestAppDoc* doc();
  };


extern TestApp theApp;

inline void invalidate() {theApp.invalidate();}
inline  TestAppDoc*   doc() {return theApp.getDocument();}

