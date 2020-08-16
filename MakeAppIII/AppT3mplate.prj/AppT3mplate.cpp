// AppT3mplate.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "AppT3mplate.h"
#include "About.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "Options.h"
#include "AppT3mplateDoc.h"
#include "AppT3mplateView.h"


AppT3mplate theApp;                       // The one and only AppT3mplate object
IniFile iniFile;


// AppT3mplate

BEGIN_MESSAGE_MAP(AppT3mplate, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &AppT3mplate::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &AppT3mplate::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &AppT3mplate::OnHelp)
END_MESSAGE_MAP()


// AppT3mplate initialization

BOOL AppT3mplate::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

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

  setAppName(_T("App Template")); setTitle(_T("A Template for MFC Applications"));

  view()->setFont(_T("Arial"), 120);

  options.load();    view()->setOrientation(options.orient);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void AppT3mplate::OnFilePrintSetup() {view()->setPrntrOrient(getDevMode());   CWinApp::OnFilePrintSetup();}



void AppT3mplate::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void AppT3mplate::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

