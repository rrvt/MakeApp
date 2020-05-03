// TestApp.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "TestApp.h"
#include "About.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "htmlhelp.h"
#include "IniFile.h"
#include "Resources.h"
#include "TestAppDoc.h"
#include "TestAppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


TestApp theApp;                       // The one and only TestApp object
IniFile iniFile;


// TestApp

BEGIN_MESSAGE_MAP(TestApp, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &TestApp::OnAppAbout)
  ON_COMMAND(ID_FILE_NEW,         &CWinAppEx::OnFileNew)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &TestApp::OnHelp)
END_MESSAGE_MAP()


// TestApp construction

TestApp::TestApp() noexcept : doc(0), view(0) {
ResourceData res;

  res.getVersion(version);

  if (res.getAppID(appID)) SetAppID(appID);   EnableHtmlHelp();
  }


// TestApp initialization

BOOL TestApp::InitInstance() {

  CWinAppEx::InitInstance();

//  helpFile = m_pszHelpFilePath;    //change_extension(helpFile, _T("chm"));

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.open();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

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

  if (getView()) {view->setAuthor(_T("Test App")); view->setFont(_T("Arial"));}

  setAppName(_T("Test App"));                           // Title left part
  setTitle(_T("A Template for MFC Applications"));      // Title right part

  // The one and only window has been initialized, so show and update it

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void TestApp::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void TestApp::invalidate() {if (getView()) view->Invalidate();}


TestAppView* TestApp::getView() {
POSITION   pos;

  if (view) return view;

  if (!getDocument()) return 0;

  pos  = doc->GetFirstViewPosition();   if (!pos)  return 0;

  return view = (TestAppView*) doc->GetNextView(pos);
  }



TestAppDoc* TestApp::getDocument() {

  if (doc) return doc;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return 0;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return 0;

  pos = t->GetFirstDocPosition();                    if (!pos) return 0;

  return doc = (TestAppDoc*) t->GetNextDoc(pos);
  }


void TestApp::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


