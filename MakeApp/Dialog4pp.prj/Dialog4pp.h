// Dialog4pp.h -- Template for a Dialog Box Application


#pragma once
#include "CApp.h"


class Dialog4pp : public CApp {
public:

UINT  m_nAppLook;

  Dialog4pp() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern Dialog4pp theApp;
