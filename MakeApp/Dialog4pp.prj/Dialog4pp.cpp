// Dialog4pp.h -- Template for a Dialog Box Application


#include "pch.h"
#include "Dialog4pp.h"
#include "Dialog4ppDlg.h"
#include "History.h"
#include "IniFileEx.h"
#include "Utilities.h"


Dialog4pp theApp;                         // The one and only Dialog4pp object
IniFileEx iniFile(theApp);                // One each of the classes
History   history;


// Dialog4pp construction

Dialog4pp::Dialog4pp() noexcept : CDialogApp(this) { }


// Dialog4pp initialization -- Start the MFC Dialog Box

BOOL Dialog4pp::InitInstance() {
Dialog4ppDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int Dialog4pp::ExitInstance() {

  clearLibUtilities();

  return CDialogApp::ExitInstance();
  }

