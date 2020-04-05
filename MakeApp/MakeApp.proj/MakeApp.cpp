
// MakeApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MakeApp.h"
#include "About.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MainFrm.h"
#include "Resources.h"
#include "MakeAppDoc.h"
#include "MakeAppView.h"
//#include "afxwinappex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


MakeApp theApp;                       // The one and only MakeApp object
IniFile iniFile;



static TCchar* MakeAppSect = _T("MakeApp");
static TCchar* BaseDirKey  = _T("BaseDir");


// MakeApp

BEGIN_MESSAGE_MAP(MakeApp, CWinAppEx)
  ON_COMMAND(ID_SpecifyBaseDir,   &MakeApp::OnSpecifyBaseDir)
  ON_COMMAND(ID_APP_ABOUT,        &MakeApp::OnAppAbout)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// MakeApp construction

MakeApp::MakeApp() noexcept : doc(0), view(0), basePath() {
ResourceData res;

  res.getVersion(version);

  if (res.getAppID(appID)) SetAppID(appID);
  }



// MakeApp initialization

BOOL MakeApp::InitInstance() {

  CWinAppEx::InitInstance();

  determineBasePath(m_pszHelpFilePath);

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.open();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(MakeAppDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(MakeAppView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  if (getView()) {view->setAuthor(_T("Make App")); view->setFont(_T("Courier New"));}

  mainFrame = (MainFrame*) m_pMainWnd;

  setTitle(_T("Make App -- Make a Template for an MFC Application"));
  iniFile.readString(MakeAppSect, BaseDirKey, doc->baseDir);

  notePad << _T("Base Directory: ") << doc->baseDir << nCrlf;

  invalidate();

  // The one and only window has been initialized, so show and update it

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void MakeApp::determineBasePath(TCchar* helpPath) {
String s = helpPath;
int    pos;

  pos = s.find(_T("MakeApp"));   if (pos < 0) return;

  basePath = s.substr(0, pos+8);
  }


                                                                      // OFN_PATHMUSTEXIST
void MakeApp::OnSpecifyBaseDir() {
String path;
int    lng;
Tchar  ch;

  if (!getDirPathDlg(_T("Make App"), path)) return;

  lng = path.length();  ch = path[lng-1];  if (ch != _T('\\')) path += _T('\\');

  doc->baseDir = path;

  iniFile.writeString(MakeAppSect, BaseDirKey, doc->baseDir);

  notePad.close();

  notePad << _T("Base Directory: ") << doc->baseDir << nCrlf;

  invalidate();
  }


void MakeApp::invalidate() {if (getView()) view->Invalidate();}


bool MakeApp::getView() {
POSITION   pos;

  if (view) return true;

  if (!getDocument()) return false;

  pos  = doc->GetFirstViewPosition();        if (!pos)  return false;
  view = (MakeAppView*) doc->GetNextView(pos);

  return view != 0;
  }



bool MakeApp::getDocument() {

  if (doc) return true;

  POSITION      pos = GetFirstDocTemplatePosition(); if (!pos) return false;
  CDocTemplate* t   = GetNextDocTemplate(pos);       if (!t)   return false;

  pos = t->GetFirstDocPosition();                    if (!pos) return false;
  doc = (MakeAppDoc*) t->GetNextDoc(pos);            if (!doc) return false;

  return true;
  }


void MakeApp::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}

