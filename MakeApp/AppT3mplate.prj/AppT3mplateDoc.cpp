// AppT3mplateDoc.cpp : implementation of the AppT3mplateDoc class


#include "stdafx.h"
#include "AppT3mplateDoc.h"
#ifdef Examples
#include "Store.h"
#endif
#include "ExtraResource.h"
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
  ON_COMMAND(ID_Options,       &OnOptions)

#ifdef Examples
  ON_COMMAND(ID_Test,          &OnTest)
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
#endif
END_MESSAGE_MAP()


// AppT3mplateDoc construction/destruction

AppT3mplateDoc::AppT3mplateDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc = PathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

AppT3mplateDoc::~AppT3mplateDoc() { }


BOOL AppT3mplateDoc::OnNewDocument() {return CDocument::OnNewDocument();}

#ifdef Examples

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

  dataSource = NotePadSrc;

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

  notePad << _T("Greeks") << nCrlf;  display(NotePadSrc);
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

  display(NotePadSrc);
  }



void AppT3mplateDoc::OnTBEditBox() {
TBEditBox*  eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String      s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void AppT3mplateDoc::myButton1() {
TBEditBox* eb = TBEditBox::get(ID_EditBox);   if (!eb) return;
String     s  = eb->GetContentsAll(ID_EditBox);

  notePad << s << nCrlf;   display(NotePadSrc);
  }


void AppT3mplateDoc::onOption1() {notePad << _T("Option 1") << nCrlf; wholePage(); display(NotePadSrc);}
void AppT3mplateDoc::onOption2() {notePad << _T("Option 2") << nCrlf; display(NotePadSrc);}
void AppT3mplateDoc::onOption3() {notePad << _T("Option 3") << nCrlf; display(NotePadSrc);}


void AppT3mplateDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display(NotePadSrc);}
void AppT3mplateDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display(NotePadSrc);}
void AppT3mplateDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display(NotePadSrc);}


void AppT3mplateDoc::OnTestEditBoxes() {display(NotePadSrc);}


// AppT3mplateDoc commands


void AppT3mplateDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = options.orient == Landscape ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display(NotePadSrc);
  }


void AppT3mplateDoc::testLine(int n) {
int i;

  for (i = 0; i < n; i++) {

    if (!i) notePad << _T('|'); else notePad << i;

    notePad << _T("123456789");
    }

  notePad << _T('|') << nCrlf;
  }


void AppT3mplateDoc::wholePage() {
int    i;
int    j;
String s;

  notePad << nSetRTab(4) << nSetTab(6) << nSetTab(8) << nSetRTab(12) << nSetTab(14);

  for (i = 0; i < 100; i++) {
    s.format(_T("%3i:"), i);

    notePad << nTab << s << nTab << _T("X") << nTab << _T("Y") << nTab << i << nTab;

    for (j = i+1; j < i+68; j++) {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}

    notePad << nCrlf;
    }
  }


void AppT3mplateDoc::displayDataStore() {display(StoreSrc);}

#endif


void AppT3mplateDoc::OnOptions() {options(view());  view()->setOrientation(options.orient);}


void AppT3mplateDoc::OnFileOpen() {

  notePad.clear();   dataSource = StoreSrc;

  pathDlgDsc = PathDlgDsc(_T("Ugly Example"), pathDlgDsc.name, _T("txt"), _T("*.txt"));

  if (!setPath(pathDlgDsc)) return;

  pathDlgDsc.name = getMainName(path);

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

#ifdef Examples
  store.setName(pathDlgDsc.name);
#endif

  display(StoreSrc);
  }


void AppT3mplateDoc::display(DataSource ds) {dataSource = ds; invalidate();}





void AppT3mplateDoc::OnFileSave() {if (setSaveAsPath(pathDlgDsc)) OnSaveDocument(path);}


// UglyDoc serialization

void AppT3mplateDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : notePad.archive(ar); return;
#ifdef Examples
      case StoreSrc: store.store(ar); return;
#endif
      default         : return;
      }

  else
    switch(dataSource) {
#ifdef Examples
      case StoreSrc : store.load(ar); return;
#endif
      case FontSrc  :
      default       : return;
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

