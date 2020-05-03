// MakeApp.h : main header file for the MakeApp application

#pragma once
#include "resource.h"       // main symbols
#include "IniFile.h"


class        MakeAppDoc;
class        MakeAppView;


// MakeApp:
// See MakeApp.cpp for the implementation of this class

class MakeApp : public CWinAppEx {
String       appID;

CFrameWndEx* mainFrame;
MakeAppDoc*  doc;
MakeAppView* view;

public:

String version;
String basePath;

               MakeApp() noexcept;

  virtual BOOL InitInstance();

          void determineBasePath(TCchar* helpPath);
          void setTitle(TCchar* title) {mainFrame->SetWindowText(title);}

          bool getDocument();
          void invalidate();
          bool getView();

  // Implementation

  DECLARE_MESSAGE_MAP()

  afx_msg void OnAppAbout();
  afx_msg void OnSpecifyBaseDir();
  afx_msg void OnHelp();

  friend MakeAppDoc* doc();
  };


extern MakeApp theApp;

inline void invalidate() {theApp.invalidate();}
inline  MakeAppDoc*   doc() {return theApp.getDocument() ? theApp.doc : 0;}

