// MakeAppDoc.cpp : implementation of the MakeAppDoc class


#include "stdafx.h"
#include "MakeAppDoc.h"
#include "CalibDspPrt.h"
#include "CopyFile.h"
#include "ExtraResource.h"
#include "FileStore.h"
#include "filename.h"
#include "FontRptOpt.h"
#include "GetPathDlg.h"
#include "Guid.h"
#include "IniFile.h"
#include "MakeApp.h"
#include "MakeAppView.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "OptionsDlg.h"
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
static TCchar* PrjAppType  = _T("AppType");
static TCchar* PrjNameKey  = _T("Name");
static TCchar* PrjVisKey   = _T("VisibleName");
static TCchar* PrjDesc     = _T("Description");

static TCchar* Msg         = _T("The build order should be set in Vs2017.  This is done after loading ")
                             _T("Solution into vs2017 then using menu item ")
                             _T("Project/Project Dependencies... and filling in the dialog box with ")
                             _T("the appropriate data.");


// MakeAppDoc

IMPLEMENT_DYNCREATE(MakeAppDoc, CDoc)

BEGIN_MESSAGE_MAP(MakeAppDoc, CDoc)
  ON_COMMAND(ID_NameProject,  &OnNameProject)
  ON_COMMAND(ID_FixSlickEdit, &OnFixSlickEdit)
  ON_COMMAND(ID_File_Save,    &OnFileSave)
  ON_COMMAND(ID_Test,         &OnTest)
  ON_COMMAND(ID_CalibDspPrt,  &OnCalibDspPrt)
  ON_COMMAND(ID_ListFonts,    &OnFontRptOpt)
  ON_COMMAND(ID_Options,      &OnOptions)
  ON_COMMAND(ID_File_Save,    &OnFileSave)
END_MESSAGE_MAP()


// MakeAppDoc construction/destruction

MakeAppDoc::MakeAppDoc() noexcept : dataSource(NotePadSrc) {
  saveAsTitle = _T("Make App");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }


MakeAppDoc::~MakeAppDoc() { }


BOOL MakeAppDoc::OnNewDocument() {return CDocument::OnNewDocument();}



void MakeAppDoc::OnNameProject() {
ProjectNameDlg dlg;
String         path;

  dlg.appType = iniFile.readInt(   PrjSection, PrjAppType, 0);
  iniFile.readString(PrjSection, PrjNameKey, dlg.name);
  iniFile.readString(PrjSection, PrjVisKey,  dlg.visibleName);
  iniFile.readString(PrjSection, PrjDesc,    dlg.description);

  if (dlg.DoModal() == IDOK) {

    notePad << _T("App Type: ") << dlg.appType << _T(" -- ");

    switch (dlg.appType) {
      case 0  : notePad << _T("DocView"); break;
      case 1  : notePad << _T("Dialog");  break;
      case 2  : notePad << _T("Radio2");      break;
      default : notePad << _T("Unknown");     break;
      }
    notePad << nCrlf;

    iniFile.writeInt(   PrjSection, PrjAppType, dlg.appType);
    iniFile.writeString(PrjSection, PrjNameKey, dlg.name);
    iniFile.writeString(PrjSection, PrjVisKey,  dlg.visibleName);
    iniFile.writeString(PrjSection, PrjDesc,    dlg.description);

    project(dlg);

    invalidate();

    messageBox(Msg);
    }
  }


void MakeAppDoc::OnFixSlickEdit() {
String    path;
String    mainName;
SlickEdit se;
String    saveAsTitle;

  notePad.clear();

  saveAsTitle = _T("Slickedit Project File");   defExt = _T("vpj");   defFilePat = _T("*.vpj");

  if (!getPathDlg(saveAsTitle, 0, defExt, defFilePat, path)) return;

  defFileName = path;

  if (!OnOpenDocument(path)) return;

  se.fix();

  fileStore.display(getMainName(path));

  invalidate();
  }


void MakeAppDoc::OnTest() {

  theApp.setTitle(_T("A Template for MFC Applications"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void MakeAppDoc::OnCalibDspPrt() {
CalibDspPrt calib;
int         n;

  calib();

  notePad.clear();  theApp.setTitle(_T("Calibrate Font Size"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = options.orient == Landscape ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }


void MakeAppDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void MakeAppDoc::OnFontRptOpt() {fontRptOpt();  notePad.clear();  display(FontSrc);}


void MakeAppDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void MakeAppDoc::display(DataSource ds) {dataSource = ds; invalidate();}



void MakeAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  backupFile(path, 5);

  OnSaveDocument(path);
  }


// MakeAppDoc serialization

void MakeAppDoc::serialize(Archive& ar) {
  if (ar.isStoring()) {fileStore.store(ar); return;}

  fileStore.load(ar);
  }


// MakeAppDoc diagnostics

#ifdef _DEBUG
void MakeAppDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void MakeAppDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

