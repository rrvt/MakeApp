// AppT3mplateDoc.cpp : implementation of the AppT3mplateDoc class


#include "stdafx.h"
#include "AppT3mplateDoc.h"
#include "DataStore.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "AppT3mplate.h"
#include "AppT3mplateView.h"


// AppT3mplateDoc

IMPLEMENT_DYNCREATE(AppT3mplateDoc, CDoc)

BEGIN_MESSAGE_MAP(AppT3mplateDoc, CDoc)
  ON_COMMAND(ID_FILE_OPEN,  &AppT3mplateDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,  &AppT3mplateDoc::OnFileSave)
  ON_COMMAND(ID_Test,       &AppT3mplateDoc::OnTest)
  ON_COMMAND(ID_Options,    &AppT3mplateDoc::OnOptions)
END_MESSAGE_MAP()


// AppT3mplateDoc construction/destruction

AppT3mplateDoc::AppT3mplateDoc() noexcept {
  saveAsTitle = _T("App Template");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }

AppT3mplateDoc::~AppT3mplateDoc() { }


BOOL AppT3mplateDoc::OnNewDocument() {return CDocument::OnNewDocument();}


// AppT3mplateDoc commands


void AppT3mplateDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void AppT3mplateDoc::OnOptions() {options();  view()->setOrientation(options.orient);}


void AppT3mplateDoc::OnFileOpen() {
String path;

  saveAsTitle = _T("App Template");   defExt = _T("txt");   defFilePat = _T("*.txt");

  if (!getPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);   view()->rightFooter= defFileName;  view()->date.getToday();

  notePad.clear();

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  dataStore.setName(defFileName);  invalidate();
  }


void AppT3mplateDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// AppT3mplateDoc serialization

void AppT3mplateDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {dataStore.store(ar); return;}

  dataStore.load(ar);
  }


// AppT3mplateDoc diagnostics

#ifdef _DEBUG
void AppT3mplateDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void AppT3mplateDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

