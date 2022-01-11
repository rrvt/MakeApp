// DialogApp.h -- Template for a Dialog Box Application


#pragma once
#include "CApp.h"


class DialogApp : public CApp {
public:

UINT  m_nAppLook;

  DialogApp() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern DialogApp theApp;
