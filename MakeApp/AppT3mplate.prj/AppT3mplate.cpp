// AppT3mplate.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "AppT3mplate.h"
#include "AboutDlg.h"
#include "AppT3mplateDoc.h"
#include "AppT3mplateView.h"
#include "FileName.h"
#include "IniFileEx.h"
#include "NotePad.h"
#include "Resource.h"
#include "Store.h"

AppT3mplate theApp;                       // The one and only AppT3mplate object
IniFileEx   iniFile(theApp);


// AppT3mplate

BEGIN_MESSAGE_MAP(AppT3mplate, CWinAppEx)
  ON_COMMAND(ID_File_New,  &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_Help,      &onHelp)
  ON_COMMAND(ID_App_About, &onAppAbout)
END_MESSAGE_MAP()


// AppT3mplate initialization

BOOL AppT3mplate::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath);

  roamPath = getPath(iniFile.getAppDataPath(m_pszHelpFilePath));
  appPath  = getPath(m_pszHelpFilePath);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(AppT3mplateDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(AppT3mplateView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("< Title >")); setTitle(_T("< Description >"));

  view()->setFont(_T("Arial"), 12.0);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



int AppT3mplate::ExitInstance() {
  store.~Store();   return CApp::ExitInstance();
  }


void AppT3mplate::onHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void AppT3mplate::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}

