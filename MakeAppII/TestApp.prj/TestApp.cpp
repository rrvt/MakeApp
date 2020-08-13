// TestApp.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "TestApp.h"
#include "About.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "NotePad.h"
#include "Options.h"
#include "TestAppDoc.h"
#include "TestAppView.h"


TestApp theApp;                       // The one and only TestApp object
IniFile iniFile;


// TestApp

BEGIN_MESSAGE_MAP(TestApp, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &TestApp::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &TestApp::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &TestApp::OnHelp)
END_MESSAGE_MAP()


// TestApp initialization

BOOL TestApp::InitInstance() {

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
    RUNTIME_CLASS(TestAppDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(TestAppView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("Test App")); setTitle(_T("A Template for MFC Applications"));

  view()->setFont(_T("Arial"), 120);

  options.load();    view()->setOrientation(options.orient);

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void TestApp::OnFilePrintSetup() {view()->setPrntrOrient(getDevMode());   CWinApp::OnFilePrintSetup();}



void TestApp::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void TestApp::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

