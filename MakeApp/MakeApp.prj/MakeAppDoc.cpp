// MakeAppDoc.cpp : implementation of the MakeAppDoc class


#include "pch.h"
#include "MakeAppDoc.h"
#include "MakeApp.h"
#include "MakeAppView.h"
#include "CalibDspPrt.h"
#include "CopyFile.h"
#include "ResourceExtra.h"
#include "FileStore.h"
#include "filename.h"
#include "FontCmd.h"
//#include "GetPathDlg.h"
#include "Guid.h"
#include "IniFileEx.h"
#include "Invalidate.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Printer.h"
#include "Project.h"
#include "ProjectNameDlg.h"
#include "qsort.h"
#include "Resource.h"
#include "SlickEdit.h"


static TCchar* AppT3mplate = _T("AppT3mplate");
static TCchar* TestSolDir  = _T("AppT3mplate\\");
static TCchar* TestPrjDir  = _T("AppT3mplate.prj\\");
static TCchar* TestHlpDir  = _T("Help\\");

static TCchar* PrjSection  = _T("Project");
static TCchar* PrjInclType = _T("InclType");
static TCchar* PrjAppType  = _T("AppType");
static TCchar* PrjNameKey  = _T("Name");
static TCchar* PrjVisKey   = _T("VisibleName");
static TCchar* PrjDesc     = _T("Description");


// MakeAppDoc

IMPLEMENT_DYNCREATE(MakeAppDoc, CDoc)

BEGIN_MESSAGE_MAP(MakeAppDoc, CDoc)
  ON_COMMAND(ID_NameProject,  &OnNameProject)
  ON_COMMAND(ID_FixSlickEdit, &OnFixSlickEdit)
  ON_COMMAND(ID_ListFonts,    &OnFontRptOpt)
  ON_COMMAND(ID_FileSave,     &OnFileSave)
  ON_COMMAND(ID_Test,         &onTest)
END_MESSAGE_MAP()


// MakeAppDoc construction/destruction

MakeAppDoc::MakeAppDoc() noexcept : dataSource(NotePadSrc) { }


MakeAppDoc::~MakeAppDoc() { }


BOOL MakeAppDoc::OnNewDocument() {return CDocument::OnNewDocument();}



void MakeAppDoc::OnNameProject() {
ProjectNameDlg dlg;
String         path;

  dlg.inclExmpls = iniFile.readInt(PrjSection, PrjInclType, 1);
  dlg.appType    = iniFile.readInt(PrjSection, PrjAppType,  0);
  iniFile.read(PrjSection, PrjNameKey, dlg.name);
  iniFile.read(PrjSection, PrjVisKey,  dlg.visibleName);
  iniFile.read(PrjSection, PrjDesc,    dlg.description);

  if (dlg.DoModal() == IDOK) {

    iniFile.write(PrjSection, PrjInclType, dlg.inclExmpls);
    iniFile.write(PrjSection, PrjAppType,  dlg.appType);
    iniFile.write(PrjSection, PrjNameKey,  dlg.name);
    iniFile.write(PrjSection, PrjVisKey,   dlg.visibleName);
    iniFile.write(PrjSection, PrjDesc,     dlg.description);

    project(dlg);   display();
    }
  }


void MakeAppDoc::OnFixSlickEdit() {
String    mainName;
SlickEdit se;

  notePad.clear();

  dlg(_T("Slickedit Project File"), path, _T("vpj"), _T("Project File"), _T("*.vpj"));

  if (!setOpenPath(dlg)) return;

  if (!OnOpenDocument(path)) return;

  se.fix();

  fileStore.display(getMainName(path));    dlg.iPath = path;

  display();
  }


void MakeAppDoc::OnFontRptOpt() {fontCmd();   notePad.clear();   display(FontsSrc);}



NotePad& MakeAppDoc::getData() {

  switch (dataSource) {
    case NotePadSrc : break;
    case FontsSrc   : return fontCmd.getData(displayDC());
    case TestSrc    : break;
    }
  return notePad;
  }

void MakeAppDoc::getHeader(NotePad& np, int pageNo, int noPages) {
    switch (dataSource) {
    case TestSrc: np << _T("Test") << nRight << pageNo;   break;
    default     : break;
    }
  }

void MakeAppDoc::getFooter(NotePad& np, int pageNo, int noPages) {
  switch (dataSource) {
    case TestSrc: np << nCenter << pageNo << _T(" of ") << noPages; break;
    default     : break;
    }
  }





void MakeAppDoc::onTest() {
int n = 0;

  theApp.setTitle(_T("A Template for MFC Applications"));

  notePad.clear();

  notePad << nFFace(_T("Arial")) << nFSize(12.0);
  notePad << nSetTab(30) << nSetTab(50);

  notePad << _T("01234567810123456782012345678301234567840123456785012345678601234567870") << nCrlf;

  notePad << nTab << _T('|') << nTab << _T('|') << nCrlf;

  notePad << _T("Courier New") << nFFace(_T("Courier New"));
  notePad << nTab << nBeginLine << _T("ABCEF") << nEndLine << nTab << _T("abcdef") << nCrlf;   n++;

  notePad << _T("01234567810123456782012345678301234567840123456785012345678601234567870") << nCrlf;
  notePad << nTab << _T('|') << nTab << _T('|') << nCrlf;

  notePad  << nFont;

  notePad << _T("Adobe Arabic") << nFFace(_T("Adobe Arabic"));
  notePad << nTab << nBeginLine << _T("ABCEF") << nCrlf;
  notePad << nTab << _T("abcdef") << nEndLine << nCrlf;   n++;

  notePad << _T("01234567810123456782012345678301234567840123456785012345678601234567870") << nCrlf;
  notePad << nTab << _T('|') << nTab << _T('|') << nCrlf;

  notePad  << nFont;

  notePad << nCrlf;

  notePad << _T("no Tries: ") << n << nFont << nFont << nCrlf;

  display(TestSrc);
  }




void MakeAppDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


//void MakeAppDoc::OnFontRptOpt() {fontCmd();  notePad.clear();  display(FontSrc);}


void MakeAppDoc::display(DataSource ds) {dataSource = ds; invalidate();}



void MakeAppDoc::OnFileSave() {

  if (!setSaveAsPath(dlg)) return;

  backupFile(5);   OnSaveDocument(path);
  }


// MakeAppDoc serialization

void MakeAppDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {fileStore.store(ar); return;}

  fileStore.load(ar);
  }


// MakeAppDoc diagnostics

#ifdef _DEBUG
void MakeAppDoc::AssertValid() const          {CDocument::AssertValid();}
void MakeAppDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG





///////////-------------------
#if 0
void MakeAppDoc::OnCalibDspPrt() {
CalibDspPrt calib;
int         n;

  calib();

  notePad.clear();  theApp.setTitle(_T("Calibrate Font Size"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = prtrDevAttr.orient == LandOrnt ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }
#endif

