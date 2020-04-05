// TestAppDoc.cpp : implementation of the TestAppDoc class


#include "stdafx.h"
#include "TestAppDoc.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "TestApp.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// TestAppDoc

IMPLEMENT_DYNCREATE(TestAppDoc, CDocument)

BEGIN_MESSAGE_MAP(TestAppDoc, CDocument)
  ON_COMMAND(ID_FILE_OPEN,  &TestAppDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,  &TestAppDoc::OnFileSave)
  ON_COMMAND(ID_Test,       &TestAppDoc::OnTest)
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

  notePad.close();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }




void TestAppDoc::OnFileOpen() {
String path;

  saveAsTitle = _T("Test App");   defExt = _T("txt");   defFilePat = _T("*.txt");

  if (!getPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  notePad.close();

  if (OnOpenDocument(path)) messageBox(_T("Loaded!"));
  }


void TestAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// TestAppDoc serialization

void TestAppDoc::serialize(Archive& ar) {
  if (ar.isStoring()) {notePad.archive(ar); return;}

  Tchar  ch;
  String s;

  while (ar.read(ch)) {
    if (ch == _T('\n'))
      {notePad << s << nCrlf;  s.clear(); continue;}
    if (ch == _T('\r'))
      continue;
    s += ch;
    }

  if (!s.isEmpty()) notePad << s << nCrlf;

  invalidate();
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

