// MakeApp.h : main header file for the MakeApp application

#pragma once
#include "CApp.h"


class MakeAppDoc;
class MakeAppView;


// MakeApp:
// See MakeApp.cpp for the implementation of this class

class MakeApp : public CApp {

public:

               MakeApp() noexcept { }

  virtual BOOL InitInstance();

          MakeAppDoc*  doc()  {return (MakeAppDoc*)  CApp::getDoc();}
          MakeAppView* view() {return (MakeAppView*) CApp::getView();}

  afx_msg void OnAppAbout();
  afx_msg void OnSpecifyBaseDir();
  afx_msg void OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern MakeApp theApp;

inline void           invalidate() {theApp.invalidate();}
inline MakeAppDoc*  doc()  {return theApp.doc();}
inline MakeAppView* view() {return theApp.view();}

