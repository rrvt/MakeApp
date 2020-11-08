// AppT3mplateDoc.cpp : implementation of the AppT3mplateDoc class


#include "stdafx.h"
#include "AppT3mplateDoc.h"
#include "Store.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "AppT3mplate.h"
#include "AppT3mplateView.h"
#include "ToolBar.h"


// AppT3mplateDoc

IMPLEMENT_DYNCREATE(AppT3mplateDoc, CDoc)

BEGIN_MESSAGE_MAP(AppT3mplateDoc, CDoc)
  ON_COMMAND(ID_File_Open,     &OnFileOpen)
  ON_COMMAND(ID_File_Save,     &OnFileSave)
  ON_COMMAND(ID_Test,          &OnTest)
  ON_COMMAND(ID_Options,       &OnOptions)

  ON_COMMAND(ID_SelDataStr,    &displayDataStore)

  ON_COMMAND(ID_MyBtn,         &myButton)

  ON_CBN_SELCHANGE(ID_CB,      &OnComboBoxChng)
  ON_COMMAND(      ID_CB,      &OnComboBoxChng)

  ON_COMMAND(ID_EditBox,       &OnTBEditBox)
  ON_COMMAND(ID_MyBtn1,        &onOption1)
  ON_COMMAND(ID_Option1,       &onOption1)
  ON_COMMAND(ID_Option2,       &onOption2)
  ON_COMMAND(ID_Option3,       &onOption3)
  ON_COMMAND(ID_Btn2,          &onOption21)
  ON_COMMAND(ID_Option21,      &onOption21)
  ON_COMMAND(ID_Option22,      &onOption22)
  ON_COMMAND(ID_Option23,      &onOption23)

END_MESSAGE_MAP()


// AppT3mplateDoc construction/destruction

AppT3mplateDoc::AppT3mplateDoc() noexcept : dataSource(NoteSource) {
  pathDsc = {_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt")};
  }

AppT3mplateDoc::~AppT3mplateDoc() { }


BOOL AppT3mplateDoc::OnNewDocument() {return CDocument::OnNewDocument();}


static TCchar* cbText[] = {_T("Zeta"),
                           _T("Beta"),
                           _T("Alpha"),
                           _T("Omega"),
                           _T("Phi"),
                           _T("Mu"),
                           _T("Xi"),
                           _T("Omicron"),
                           _T("Pi"),
                           _T("Rho"),
                           _T("Sigma"),
                           _T("Nu"),
                           _T("Kappa"),
                           _T("Iota")
                           };


void AppT3mplateDoc::myButton() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int n = noElements(cbText);
int i;
int x;

  dataSource = NoteSource;

  notePad << _T("My Button") << nCrlf;

  if (!cb) {invalidate();  return;}

//  cb->SetText(_T("Greeks"));

  for (i = 0; i < n; i++) if (cb->findExact(cbText[i]) < 0) {

    x = cb->AddSortedItem(cbText[i], i);                           //AddSortedItem

    String s;  s.format(_T("%02i: "), i);

    notePad << s << _T("Pos = ") << x << _T(". Added ") << cbText[i] << nCrlf;
    }

  cb->SelectItem(-1);
  cb->SetText(_T("Greeks"));

#if 0
  cb->SetText(_T("Greeks"));
#endif

  notePad << _T("Greeks") << nCrlf;  display(NoteSource);
  }


void AppT3mplateDoc::OnComboBoxChng() {
TBComboBox* cb = TBComboBox::get(ID_CB);
int        i;
String     s;
int        x;
MainFrame* mf = theApp.mainFrm();

  if (!cb)   return;
  i  = cb->GetCurSel();    if (i < 0) return;
  s  = cb->GetItem(i);
  x  = cb->GetItemData(i);   mf->SetFocus();

  notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;

  display(NoteSource);
  }



void AppT3mplateDoc::OnTBEditBox() {
TBEditBox*  eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String      s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NoteSource);
  }


void AppT3mplateDoc::myButton1() {
TBEditBox* eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String     s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NoteSource);
  }


void AppT3mplateDoc::onOption1() {notePad << _T("Option 1") << nCrlf; display(NoteSource);}
void AppT3mplateDoc::onOption2() {notePad << _T("Option 2") << nCrlf; display(NoteSource);}
void AppT3mplateDoc::onOption3() {notePad << _T("Option 3") << nCrlf; display(NoteSource);}


void AppT3mplateDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display(NoteSource);}
void AppT3mplateDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display(NoteSource);}
void AppT3mplateDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display(NoteSource);}


void AppT3mplateDoc::OnTestEditBoxes() {display(NoteSource);}


// AppT3mplateDoc commands


void AppT3mplateDoc::OnTest() {

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << _T("Hello World") << nCrlf;

  display(NoteSource);
  }


void AppT3mplateDoc::OnOptions() {options();  view()->setOrientation(options.orient);}


void AppT3mplateDoc::OnFileOpen() {

  notePad.clear();   dataSource = StoreSource;

  pathDsc = {_T("Ugly Example"), pathDsc.name, _T("txt"), _T("*.txt")};

  if (!setPath(pathDsc)) return;

  pathDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

  store.setName(pathDsc.name);   display(StoreSource);
  }


void AppT3mplateDoc::display(DataSource ds) {dataSource = ds; invalidate();}


void AppT3mplateDoc::displayDataStore() {dataSource = StoreSource; invalidate();}



void AppT3mplateDoc::OnFileSave() {if (setSaveAsPath(pathDsc)) OnSaveDocument(path);}


// UglyDoc serialization

void AppT3mplateDoc::serialize(Archive& ar) {

  switch(ar.isStoring()) {
    case true:
      switch(dataSource) {
        case NoteSource : notePad.archive(ar); return;
        case StoreSource: store.store(ar); return;
        default         : return;
        }

    case false:
      switch(dataSource) {
        case StoreSource: store.load(ar); return;
        default         : return;
        }
    }
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

