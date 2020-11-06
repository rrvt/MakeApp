// AppT3mplate.h : main header file for the AppT3mplate application

#pragma once
#include "CApp.h"


class AppT3mplateDoc;
class AppT3mplateView;
class MainFrame;


// AppT3mplate:
// See AppT3mplate.cpp for the implementation of this class

class AppT3mplate : public CApp {

public:

               AppT3mplate() noexcept { }

  virtual BOOL InitInstance();

          AppT3mplateDoc*  doc()  {return (AppT3mplateDoc*)  CApp::getDoc();}
          AppT3mplateView* view() {return (AppT3mplateView*) CApp::getView();}
          MainFrame*       mainFrm() {return (MainFrame*) m_pMainWnd;}

  DECLARE_MESSAGE_MAP()

  afx_msg void OnFilePrintSetup();
  afx_msg void OnAppAbout();
  afx_msg void OnHelp();
  };


extern AppT3mplate theApp;

inline void         invalidate() {theApp.invalidate();}
inline AppT3mplateDoc*  doc()  {return theApp.doc();}
inline AppT3mplateView* view() {return theApp.view();}

