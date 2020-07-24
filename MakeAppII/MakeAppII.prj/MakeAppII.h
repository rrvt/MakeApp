// MakeAppII.h : main header file for the MakeAppII application

#pragma once
#include "CApp.h"


class MakeAppIIDoc;
class MakeAppIIView;


// MakeAppII:
// See MakeAppII.cpp for the implementation of this class

class MakeAppII : public CApp {

public:

               MakeAppII() noexcept { }

  virtual BOOL InitInstance();

          MakeAppIIDoc*  doc()  {return (MakeAppIIDoc*)  CApp::getDoc();}
          MakeAppIIView* view() {return (MakeAppIIView*) CApp::getView();}

  afx_msg void OnAppAbout();
  afx_msg void OnSpecifyBaseDir();
  afx_msg void OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern MakeAppII theApp;

inline void           invalidate() {theApp.invalidate();}
inline MakeAppIIDoc*  doc()  {return theApp.doc();}
inline MakeAppIIView* view() {return theApp.view();}

