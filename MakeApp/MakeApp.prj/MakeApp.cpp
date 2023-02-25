// MakeApp.cpp : Defines the class behaviors for the application.


#include "pch.h"
#include "MakeApp.h"
#include "AboutDlg.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "MakeAppDoc.h"
#include "MakeAppView.h"
#include "NotePad.h"
#include "OptionsDlg.h"
#include "Project.h"
#include "Resource.h"

MakeApp   theApp;                       // The one and only MakeApp object
IniFile   iniFile;


// MakeApp


BEGIN_MESSAGE_MAP(MakeApp, CWinAppEx)
  ON_COMMAND(ID_SpecifyBaseDir,   &OnSpecifyBaseDir)
  ON_COMMAND(ID_App_About,        &OnAppAbout)
  ON_COMMAND(ID_Help,             &OnHelp)
END_MESSAGE_MAP()


// MakeApp initialization

BOOL MakeApp::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);           // A convenient place to get the iniFile
                                                              // initialized
  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(MakeAppDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window                                N
    RUNTIME_CLASS(MakeAppView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  // App initialization may begin here.  All Windows stuff is available at this point but the window is
  // not visible until ShowWindow below

  notePad.clear();     view()->setFont(_T("Ariel"), 12.0);

  setAppName(_T("MakeApp")); setTitle(_T("Make An Application"));

  project.getBaseDir();

  project.determineBasePath(m_pszHelpFilePath);

//  options.load();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }



void MakeApp::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }



void MakeApp::OnSpecifyBaseDir() {project.getBaseDirUser();   invalidate();}


void MakeApp::OnAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}




#if 0

void MakeApp::OnFilePrintSetup() {
PrtrOrient orient;

  view()->setPrntrOrient(getDevMode());

    CWinApp::OnFilePrintSetup();

  orient = view()->getPrntrOrient(getDevMode());

  options.setOrient(orient);   view()->setOrientation(options.orient);
  }
#endif
