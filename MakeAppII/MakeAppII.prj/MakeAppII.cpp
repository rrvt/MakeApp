// MakeAppII.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "MakeAppII.h"
#include "About.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrame.h"
#include "MakeAppIIDoc.h"
#include "MakeAppIIView.h"
#include "NotePad.h"
#include "Options.h"
#include "Project.h"


MakeAppII theApp;                       // The one and only MakeAppII object
IniFile   iniFile;


// MakeAppII


BEGIN_MESSAGE_MAP(MakeAppII, CWinAppEx)
  ON_COMMAND(ID_SpecifyBaseDir,   &MakeAppII::OnSpecifyBaseDir)
  ON_COMMAND(ID_APP_ABOUT,        &MakeAppII::OnAppAbout)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &MakeAppII::OnHelp)
END_MESSAGE_MAP()


// MakeAppII initialization

BOOL MakeAppII::InitInstance() {

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
    RUNTIME_CLASS(MakeAppIIDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(MakeAppIIView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  // App initialization may begin here.  All Windows stuff is available at this point but the window is
  // not visible until ShowWindow below

  notePad.clear();     view()->setFont(_T("Courier New"), 120);

  setAppName(_T("MakeAppII")); setTitle(_T("Make An Application"));

//  iniFile.readString(MakeAppSect, BaseDirKey, project.baseDir);

//  notePad << _T("Base Directory: ") << project.baseDir << nCrlf;

  project.getBaseDir();

  project.determineBasePath(m_pszHelpFilePath);

  options.load();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void MakeAppII::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }



void MakeAppII::OnSpecifyBaseDir() {project.getBaseDirUser();   invalidate();}


void MakeAppII::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

