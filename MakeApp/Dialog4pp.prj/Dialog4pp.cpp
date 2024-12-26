// Dialog4pp.h -- Template for a Dialog Box Application


#include "pch.h"
#include "Dialog4pp.h"
#include "Dialog4ppDlg.h"
#include "IniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Dialog4pp theApp;                         // The one and only Dialog4pp object
IniFile   iniFile;


// Dialog4pp construction

Dialog4pp::Dialog4pp() noexcept : CDialogApp(this) { }


// Dialog4pp initialization -- Start the MFC Dialog Box

BOOL Dialog4pp::InitInstance() {
Dialog4ppDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int Dialog4pp::ExitInstance() {return CWinApp::ExitInstance();}

