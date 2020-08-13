// TestAppDoc.cpp : implementation of the TestAppDoc class


#include "stdafx.h"
#include "TestAppDoc.h"
#include "DataStore.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "TestApp.h"
#include "TestAppView.h"


// TestAppDoc

IMPLEMENT_DYNCREATE(TestAppDoc, CDoc)

BEGIN_MESSAGE_MAP(TestAppDoc, CDoc)
  ON_COMMAND(ID_FILE_OPEN,  &TestAppDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,  &TestAppDoc::OnFileSave)
  ON_COMMAND(ID_Test,       &TestAppDoc::OnTest)
  ON_COMMAND(ID_Options,    &TestAppDoc::OnOptions)
END_MESSAGE_MAP()


// TestAppDoc construction/destruction

TestAppDoc::TestAppDoc() noexcept {
  saveAsTitle = _T("Test App");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }

TestAppDoc::~TestAppDoc() { }


BOOL TestAppDoc::OnNewDocument() {return CDocument::OnNewDocument();}


// TestAppDoc commands


void TestAppDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void TestAppDoc::OnOptions() {options();  view()->setOrientation(options.orient);}


void TestAppDoc::OnFileOpen() {
String path;

  saveAsTitle = _T("Test App");   defExt = _T("txt");   defFilePat = _T("*.txt");

  if (!getPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);   view()->rightFooter= defFileName;  view()->date.getToday();

  notePad.clear();

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  dataStore.setName(defFileName);  invalidate();
  }


void TestAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// TestAppDoc serialization

void TestAppDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {dataStore.store(ar); return;}

  dataStore.load(ar);
  }


// TestAppDoc diagnostics

#ifdef _DEBUG
void TestAppDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void TestAppDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

