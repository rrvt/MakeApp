// MakeAppIIDoc.cpp : implementation of the MakeAppIIDoc class


#include "stdafx.h"
#include "MakeAppIIDoc.h"
#include "FileStore.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "Guid.h"
#include "IniFile.h"
#include "MakeAppII.h"
#include "MakeAppIIView.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "OptionsDlg.h"
#include "Project.h"
#include "ProjectNameDlg.h"
#include "qsort.h"
#include "Resource.h"
#include "SlickEdit.h"


static TCchar* TestApp     = _T("TestApp");
static TCchar* TestSolDir  = _T("TestApp\\");
static TCchar* TestPrjDir  = _T("TestApp.prj\\");
static TCchar* TestHlpDir  = _T("Help\\");

static TCchar* PrjSection  = _T("Project");
static TCchar* PrjNameKey  = _T("Name");
static TCchar* PrjVisKey   = _T("VisibleName");
static TCchar* PrjDesc     = _T("Description");

static TCchar* Msg         = _T("The build order should be set in Vs2017.  This is done after loading ")
                             _T("Solution into vs2017 then using menu item ")
                             _T("Project/Project Dependencies... and filling in the dialog box with ")
                             _T("the appropriate data.");


// MakeAppIIDoc

IMPLEMENT_DYNCREATE(MakeAppIIDoc, CDoc)

BEGIN_MESSAGE_MAP(MakeAppIIDoc, CDoc)
  ON_COMMAND(ID_NameProject,  &MakeAppIIDoc::OnNameProject)
  ON_COMMAND(ID_FixSlickEdit, &MakeAppIIDoc::OnFixSlickEdit)
  ON_COMMAND(ID_FILE_SAVE,    &MakeAppIIDoc::OnFileSave)
  ON_COMMAND(ID_Test,         &MakeAppIIDoc::OnTest)
  ON_COMMAND(ID_Options,      &MakeAppIIDoc::OnOptions)
END_MESSAGE_MAP()


// MakeAppIIDoc construction/destruction

MakeAppIIDoc::MakeAppIIDoc() noexcept {
  saveAsTitle = _T("Make App");   defExt = _T("txt");   defFilePat = _T("*.txt");
  }

MakeAppIIDoc::~MakeAppIIDoc() { }


BOOL MakeAppIIDoc::OnNewDocument() {return CDocument::OnNewDocument();}


//void determineBasePath(TCchar* helpPath) {project.determineBasePath(helpPath);}



void MakeAppIIDoc::OnNameProject() {
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


void MakeAppIIDoc::OnFixSlickEdit() {
String    path;
String    mainName;
SlickEdit se;
String    saveAsTitle;
String    defExt;
String    defFilePat;

  saveAsTitle = _T("Slickedit Project File");   defExt = _T("vpj");   defFilePat = _T("*.vpj");

  if (!getPathDlg(saveAsTitle, 0, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  if (!OnOpenDocument(path)) return;

  se.fix();

  fileStore.display(getMainName(path));

  invalidate();
  }



// MakeAppIIDoc commands


void MakeAppIIDoc::OnTest() {

  theApp.setTitle(_T("My Test"));

  notePad.clear();  notePad << _T("Hello World") << nCrlf;

  invalidate();
  }


void MakeAppIIDoc::OnOptions() {
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



void MakeAppIIDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// MakeAppIIDoc serialization

void MakeAppIIDoc::serialize(Archive& ar) {
  if (ar.isStoring()) {fileStore.store(ar); return;}

  fileStore.load(ar);

  }


// MakeAppIIDoc diagnostics

#ifdef _DEBUG
void MakeAppIIDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void MakeAppIIDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

