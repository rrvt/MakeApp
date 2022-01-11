// DialogApp.h -- Template for a Dialog Box Application


#include "pch.h"
#include "DialogApp.h"
#include "DialogDlg.h"
#include "IniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DialogApp theApp;                         // The one and only DialogApp object
IniFile   iniFile;


// DialogApp construction

DialogApp::DialogApp() noexcept : CApp(this) { }


// DialogApp initialization -- Start the MFC Dialog Box

BOOL DialogApp::InitInstance() {
DialogDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);   dlg.DoModal();      m_pMainWnd = 0;   return 0;
  }


int DialogApp::ExitInstance() {return CWinApp::ExitInstance();}

