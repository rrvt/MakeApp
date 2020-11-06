// MakeAppDoc.cpp : implementation of the MakeAppDoc class


#include "stdafx.h"
#include "MakeAppDoc.h"
#include "FileStore.h"
#include "filename.h"
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


static TCchar* AppT3mplate     = _T("AppT3mplate");
static TCchar* TestSolDir  = _T("AppT3mplate\\");
static TCchar* TestPrjDir  = _T("AppT3mplate.prj\\");
static TCchar* TestHlpDir  = _T("Help\\");

static TCchar* PrjSection  = _T("Project");
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
  ON_COMMAND(ID_NameProject,  &MakeAppDoc::OnNameProject)
  ON_COMMAND(ID_FixSlickEdit, &MakeAppDoc::OnFixSlickEdit)
  ON_COMMAND(ID_File_Save,    &MakeAppDoc::OnFileSave)
  ON_COMMAND(ID_Test,         &MakeAppDoc::OnTest)
  ON_COMMAND(ID_Options,      &MakeAppDoc::OnOptions)
END_MESSAGE_MAP()


// MakeAppDoc construction/destruction

MakeAppDoc::MakeAppDoc() noexcept {
  saveAsTitle = _T("Make App");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }


MakeAppDoc::~MakeAppDoc() { }


BOOL MakeAppDoc::OnNewDocument() {return CDocument::OnNewDocument();}



void MakeAppDoc::OnNameProject() {
ProjectNameDlg dlg;
String         path;

  iniFile.readString(PrjSection, PrjNameKey, dlg.name);
  iniFile.readString(PrjSection, PrjVisKey,  dlg.visibleName);
  iniFile.readString(PrjSection, PrjDesc,    dlg.description);

  if (dlg.DoModal() == IDOK) {

    iniFile.writeString(PrjSection, PrjNameKey, dlg.name);
    iniFile.writeString(PrjSection, PrjVisKey,  dlg.visibleName);
    iniFile.writeString(PrjSection, PrjDesc,    dlg.description);

    project(dlg.name, dlg.visibleName, dlg.description);

    invalidate();

    messageBox(Msg);
    }
  }


void MakeAppDoc::OnFixSlickEdit() {
String    path;
String    mainName;
SlickEdit se;
String    saveAsTitle;

  saveAsTitle = _T("Slickedit Project File");   defExt = _T("vpj");   defFilePat = _T("*.vpj");

  if (!getPathDlg(saveAsTitle, 0, defExt, defFilePat, path)) return;

  defFileName = path;

  if (!OnOpenDocument(path)) return;

  se.fix();

  fileStore.display(getMainName(path));

  invalidate();
  }


void MakeAppDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void MakeAppDoc::OnOptions() {
OptionsDlg dlg;

  dlg.topMargin   = options.topMargin;
  dlg.leftMargin  = options.leftMargin;
  dlg.rightMargin = options.rightMargin;
  dlg.botMargin   = options.botMargin;

  if (dlg.DoModal() == IDOK) {
    options.topMargin    = dlg.topMargin;
    options.leftMargin   = dlg.leftMargin;
    options.rightMargin  = dlg.rightMargin;
    options.botMargin    = dlg.botMargin;

    options.store();
    }
  }



void MakeAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

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

