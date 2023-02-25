 // AppT3mplateDoc.cpp : implementation of the AppT3mplateDoc class


#include "pch.h"
#include "AppT3mplateDoc.h"
#include "AppT3mplate.h"
#include "ClipLine.h"
#include "filename.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Printer.h"
#include "Resource.h"
#ifdef Examples
#include "Store.h"
#endif

// AppT3mplateDoc

IMPLEMENT_DYNCREATE(AppT3mplateDoc, CDoc)

BEGIN_MESSAGE_MAP(AppT3mplateDoc, CDoc)
  ON_COMMAND(      ID_File_Open,  &OnFileOpen)
  ON_COMMAND(      ID_File_Save,  &OnFileSave)
  ON_COMMAND(      ID_EDIT_COPY,  &onEditCopy)

#ifdef Examples
  ON_COMMAND(      ID_Test,       &OnTest)
  ON_COMMAND(      ID_SelDataStr, &displayDataStore)

  ON_COMMAND(      ID_Btn1,       &myButton)

  ON_CBN_SELCHANGE(ID_CBox,       &OnComboBoxChng)
  ON_COMMAND(      ID_CBox,       &OnComboBoxChng)

  ON_CBN_KILLFOCUS(ID_EditBox,    &OnTBEditBox)
  ON_COMMAND(      ID_EditBox,    &OnTBEditBox)

  ON_COMMAND(      ID_Menu1,      &onOption11)
  ON_COMMAND(      ID_Option11,   &onOption11)
  ON_COMMAND(      ID_Option12,   &onOption12)
  ON_COMMAND(      ID_Option13,   &onOption13)

  ON_COMMAND(      ID_Menu2,      &onOption21)
  ON_COMMAND(      ID_Option21,   &onOption21)
  ON_COMMAND(      ID_Option22,   &onOption22)
  ON_COMMAND(      ID_Option23,   &onOption23)
#endif
END_MESSAGE_MAP()


// AppT3mplateDoc construction/destruction

AppT3mplateDoc::AppT3mplateDoc() noexcept : dataSource(NotePadSrc) {
  pathDlgDsc(_T("Ugly Example"), _T(""), _T("txt"), _T("*.txt"));
  }

AppT3mplateDoc::~AppT3mplateDoc() { }


BOOL AppT3mplateDoc::OnNewDocument() {return CDocument::OnNewDocument();}

#ifdef Examples

static CbxItem cbxText[] = {{_T("Zeta"),     1},
                            {_T("Beta"),     2},
                            {_T("Alpha"),    3},
                            {_T("Omega"),    4},
                            {_T("Phi"),      5},
                            {_T("Mu"),       6},
                            {_T("Xi"),       7},
                            {_T("Omicron"),  8},
                            {_T("Pi"),       9},
                            {_T("Rho"),     10},
                            {_T("Sigma"),   11},
                            {_T("Nu"),      12},
                            {_T("Kappa"),   13},
                            {_T("Iota"),    14}
                            };
static TCchar* CbxCaption = _T("Greeks");


void AppT3mplateDoc::myButton() {
ToolBar& toolBar = getToolBar();

  toolBar.addCbxItems(  ID_CBox, cbxText, noElements(cbxText));
  toolBar.setCbxCaption(ID_CBox, CbxCaption);

  notePad << _T("Loaded ") << CbxCaption << _T(" into ComboBx") << nCrlf;  display(NotePadSrc);
  }


void AppT3mplateDoc::OnComboBoxChng() {
ToolBar& toolBar = getToolBar();
String   s;
int      x;

  if (toolBar.getCbxSel(ID_CBox, s, x))
                               notePad << _T("On Change, Item = ") << s << _T(", Data = ") << x << nCrlf;
  display(NotePadSrc);
  }



void AppT3mplateDoc::OnTBEditBox() {
ToolBar& toolBar = getToolBar();
String   s;

  if (toolBar.getEbxText(ID_EditBox, s)) notePad << s << nCrlf;

  display(NotePadSrc);
  }


void AppT3mplateDoc::myButton1() {
ToolBar& toolBar = getToolBar();
String   s;

  if (toolBar.getEbxText(ID_EditBox, s)) notePad << s << nCrlf;

  display(NotePadSrc);
  }


void AppT3mplateDoc::onOption11() {notePad << _T("Option 11") << nCrlf; display(NotePadSrc);}
void AppT3mplateDoc::onOption12() {notePad << _T("Option 12") << nCrlf; display(NotePadSrc);}
void AppT3mplateDoc::onOption13() {notePad << _T("Option 13") << nCrlf; wholePage(); display(NotePadSrc);}


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

  n = printer.orient == LandOrient ? 10 : 8;

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


void AppT3mplateDoc::onEditCopy() {clipLine.load();}


void AppT3mplateDoc::OnFileOpen() {

  notePad.clear();   dataSource = StoreSrc;

  pathDlgDsc(_T("Ugly Example"), pathDlgDsc.name, _T("txt"), _T("*.txt"));

  if (!setOpenPath(pathDlgDsc)) return;

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
      case StoreSrc   : store.store(ar); return;
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






#if 0
#include "AppT3mplateView.h"
#include "ExtraResource.h"
#include "GetPathDlg.h"
#include "ToolBar.h"
#endif

