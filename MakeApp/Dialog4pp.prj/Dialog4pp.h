// Dialog4pp.h -- Template for a Dialog Box Application


#pragma once
#include "CDialogApp.h"


class Dialog4pp : public CDialogApp {
public:

UINT  m_nAppLook;

  Dialog4pp() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern Dialog4pp theApp;
