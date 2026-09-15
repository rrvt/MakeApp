 // AppT3mplateDoc.cpp : implementation of the AppT3mplateDoc class


#include "pch.h"
#include "AppT3mplateDoc.h"
#include "AppT3mplate.h"
#include "AppT3mplateView.h"
#include "ClipLine.h"
#include "FileName.h"
#include "Invalidate.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "PathDlg.h"
#include "Printer.h"
#include "Resource.h"
#ifdef Examples
#include "Store.h"
#endif

// AppT3mplateDoc

IMPLEMENT_DYNCREATE(AppT3mplateDoc, CDoc)

BEGIN_MESSAGE_MAP(AppT3mplateDoc, CDoc)
  ON_COMMAND(      ID_FileOpen,   &onFileOpen)

#ifdef Examples
  ON_COMMAND(      ID_Button,      &myButton)
  ON_CBN_KILLFOCUS(ID_EditBox,     &OnTBEditBox)
  ON_COMMAND(      ID_EditBox,     &OnTBEditBox)

  ON_COMMAND(      ID_Menu,        &onOption11)
  ON_COMMAND(      ID_Option11,    &onOption11)
  ON_COMMAND(      ID_Option12,    &onOption12)
  ON_COMMAND(      ID_Option13,    &onOption13)

  ON_COMMAND(      ID_Menu1,       &onOption21)
  ON_COMMAND(      ID_Option21,    &onOption21)
  ON_COMMAND(      ID_Option22,    &onOption22)
  ON_COMMAND(      ID_Option23,    &onOption23)

  ON_CBN_SELCHANGE(ID_CboBox,      &OnComboBoxChng)
  ON_COMMAND(      ID_CboBox,      &OnComboBoxChng)
  ON_CBN_SELCHANGE(ID_CboBox1,     &OnComboBox1Chng)
  ON_COMMAND(      ID_CboBox1,     &OnComboBox1Chng)
#endif

  ON_COMMAND(      ID_TBSaveMenu,  &onSaveFile)
  ON_COMMAND(      ID_SaveFile,    &onSaveFile)
  ON_COMMAND(      ID_SaveNotePad, &onSaveNotePad)

  ON_COMMAND(      ID_EDIT_COPY,   &onEditCopy)

#ifdef Examples
  ON_COMMAND(      ID_Test,        &OnTest)
  ON_COMMAND(      ID_DsplyStore,  &displayStore)
#endif

END_MESSAGE_MAP()


// AppT3mplateDoc construction/destruction

AppT3mplateDoc::AppT3mplateDoc() noexcept : dataSource(NotePadSrc) { }

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
                            {_T("Iota"),    14}//,
//                            {_T("This is a reallyt long Greek"), 15}
                            };
static TCchar* CbxCaption = _T("Greeks");

static CbxItem cbx1Txt[] = {{_T("One"),     1},
                            {_T("Two"),     2},
                            {_T("Three"),   3}
                            };
static TCchar* Cbx1Caption = _T("Numbers");

#if 0
void AppT3mplateDoc::myButton() {
MyToolBar& toolBar = getToolBar();
int        i;
int        n;

  for (i = 0, n = noElements(cbxText); i < n; i++) {
    CbxItem& item = cbxText[i];

    toolBar.addCboItemSrtd(ID_CboBox, item.txt, item.data);
    }
  toolBar.setCboCaption(ID_CboBox, CbxCaption);
  toolBar.setCboWthPrct(ID_CboBox, 100);
  toolBar.setCboHeight(ID_CboBox);

  for (i = 0, n = noElements(cbx1Txt); i < n; i++)
    {CbxItem& item = cbx1Txt[i];   toolBar.addCboItem(ID_CboBox1,item.txt, item.data);}

  toolBar.setCboCaption(ID_CboBox1, Cbx1Caption);   toolBar.setCboHeight(ID_CboBox1);

  notePad << _T("Loaded ") << CbxCaption << _T(" into ComboBx") << nCrlf;  display();
  }
#endif



static TCchar* text[] = {
            _T("0123456789 0123456789 0123456789 "),
            _T("Now is the time for all good people to come to the aid of the party.  "),
            _T("The grey dog jumped over the sleeping bear and kissed the wiggling turtle.  "),
            _T("When you're on the go, multiuse products that streamline your routine are "),
            _T("helpful.  Think tinted moisturizers with SPF, cheek-and-lip sticks, a dense, "),
            _T("all-body nourishing cream and concealers that double as highlighters.")
            };


void AppT3mplateDoc::myButton() {
int    i;
int    j;
int    n = noElements(text);
String line;
ElementX ele;

  notePad.clear();

  for (i = 0, j = 0; i < n; i++) {

    line = text[i];

    while (findNextBrk(line, ele)) {

      switch (j) {
        case  6: notePad << nTab;                                                        break;
        case 10: notePad << nFFace(_T("Times New Roman")) << _T("Times gyp ");           break;
        case 16: notePad << nFFace(_T("Courier New"));                                   break;
        case 32: notePad << nFont;                                                       break;
        case 34: notePad << nFFace(_T("Arial")) << _T("Arial ");                         break;
        case 40: notePad << nBeginLine;                                                  break;
        case 62: notePad << nFFace(_T("Comic Sans MS")) << _T("Comic Sans ");            break;
        case 70: notePad << _T("n End Line") << nEndLine << _T(' ');                               break;
        default:                                                                         break;
        }

      notePad << ele.word;   j++;
      }
    }

  display();
  }




bool AppT3mplateDoc::findNextBrk(String& line, ElementX& ele) {
int pos;
int lng = line.length();
int next;

  ele.clear();

  if (line.isEmpty()) return false;

  if (line[0] == _T(' ')) return findWhite(line, ele);

  ele.typ = WordEle;

  pos = line.find(_T(' '));

  if (pos == 0)
    for (pos = 1, lng = line.length(); pos < lng; pos++) if (line[pos] != _T(' ')) break;

  next = pos < 0 ? line.length() : pos;

  ele.word = line.substr(0, next);   line = line.substr(next);   return true;
  }


bool AppT3mplateDoc::findWhite(String& line, ElementX& ele) {
int pos;
int lng;

  ele.typ = WhiteEle;

  for (pos = 0, lng = line.length(); pos < lng; pos++) if (line[pos] != _T(' ')) break;

  if (!pos) return false;

  ele.word = line.substr(0, pos);   line = line.substr(pos);   return true;
  }



void AppT3mplateDoc::OnComboBoxChng() {
MyToolBar& toolBar = getToolBar();
String     s;
ulongP     x;
int64      y;

  if (toolBar.getCurSel(ID_CboBox, s, x)) {
    y = (int64) x;

    notePad << _T("On Change, Item = ") << s << _T(", Data = ");
    notePad << y << nCrlf;
    }
  display();
  }


void AppT3mplateDoc::OnComboBox1Chng() {
MyToolBar& toolBar = getToolBar();
String     s;
ulongP     x;
int64      y;

  if (toolBar.getCurSel(ID_CboBox1, s, x)) {
    y = (int64) x;

    notePad << _T("On Change, Item = ") << s << _T(", Data = ");
    notePad << y << nCrlf;
    }
  display();
  }



void AppT3mplateDoc::OnTBEditBox() {
MyToolBar& toolBar = getToolBar();
CString    cs      = toolBar.getText(ID_EditBox);
String     s       = cs;

  if (!s.isEmpty()) notePad << s << nCrlf;

  display();
  }


void AppT3mplateDoc::myButton1() {
MyToolBar& toolBar = getToolBar();
CString    cs      = toolBar.getText(ID_EditBox);
String     s       = cs;

  if (!s.isEmpty()) notePad << s << nCrlf;

  display();
  }


void AppT3mplateDoc::onOption11() {notePad << _T("Option 11") << nCrlf; display();}
void AppT3mplateDoc::onOption12() {notePad << _T("Option 12") << nCrlf; display();}
void AppT3mplateDoc::onOption13() {notePad << _T("Option 13") << nCrlf; wholePage(); display();}


void AppT3mplateDoc::onOption21() {notePad << _T("Option 21") << nCrlf; display();}
void AppT3mplateDoc::onOption22() {notePad << _T("Option 22") << nCrlf; display();}
void AppT3mplateDoc::onOption23() {notePad << _T("Option 23") << nCrlf; display();}


void AppT3mplateDoc::OnTestEditBoxes() {display();}


// AppT3mplateDoc commands


void AppT3mplateDoc::OnTest() {
int n;

  notePad.clear();  theApp.setTitle(_T("My Test"));

  notePad << nFFace(_T("Windsor BT")) << nFSize(14.5) << nBold;

  notePad << _T("Hello World") << nCrlf;

  notePad << nFont << nFont << nFont;

  n = prtrDevAttr.orient == LandOrnt ? 10 : 8;

  notePad << nFFace(_T("Courier New")) << nFSize(12.0);   testLine(n);   notePad << nFont << nFont;

  testLine(n);   display();
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

    for (j = i+1; j < i+68; j++)
                              {s.format(_T("%i"), j);   s = s.substr(s.length()-1);  notePad << s;}
    notePad << nCrlf;
    }
  }


void AppT3mplateDoc::displayStore() {display(StoreSrc);}

#endif


void AppT3mplateDoc::onEditCopy() {/*clipLine.load();*/}


void AppT3mplateDoc::onFileOpen() {
String name;

  notePad.clear();   dataSource = StoreSrc;

  PathDlg dlg(_T("Ugly Example"), path, _T("txt"), _T("Text"), _T("*.txt"));

  if (!setOpenPath(dlg)) return;

  if (!OnOpenDocument(path)) messageBox(_T(" Not Loaded!"));

#ifdef Examples

  name = getMainName(path);   store.setName(name);

#endif

  display(StoreSrc);
  }


void AppT3mplateDoc::onSaveFile()
          {dataSource = StoreSrc; saveFile(_T("Save File"), _T(""), _T("txt")); display(StoreSrc);}


void AppT3mplateDoc::onSaveNotePad() {
PathDlg dlg(_T("Ugly Example"), path, _T("txt"), _T("Text"), _T("*.txt"));

  dataSource = NotePadSrc;   if (setSaveAsPath(dlg)) OnSaveDocument(path);

  display(StoreSrc);
  }


void AppT3mplateDoc::display(DataSource ds)
                                       {currentSource = NilSrc;   dataSource = ds;   invalidate();}


void AppT3mplateDoc::getHeader(NotePad& np, int pageNo, int noPages) {

  switch (dataSource) {
    case NilSrc     :                                               break;
    case NotePadSrc : np << _T("Header") << nRight << theApp.name;  break;
    case StoreSrc   : store.header(np, pageNo, noPages);            break;
    default         :                                               break;
    }

  }


NotePad& AppT3mplateDoc::getData() {
  if (dataSource == currentSource) return notePad;

  switch (dataSource) {
    case NilSrc     :                                            break;
    case NotePadSrc : view()->enableWrap();   myButton();        break;
    case StoreSrc   : view()->disableWrap();  store.display();   break;
    default         :                                            break;
    }

  currentSource = dataSource;   return notePad;
  }


void AppT3mplateDoc::getFooter(NotePad& np, int pageNo, int noPages) {

    switch (dataSource) {
      case NilSrc     :                                                                    break;
      case NotePadSrc : np << nCenter << _T("Page ") << pageNo << _T(" of ") << noPages;   break;
      case StoreSrc   : store.footer(np, pageNo, noPages);                                 break;
      default         :                                                                    break;
      }
  }


void AppT3mplateDoc::saveFile(TCchar* title, TCchar* suffix, TCchar* fileType) {
String fileName = path;
int    pos      = fileName.findLastOf(_T('\\'));
String filter   = _T("*."); filter += fileType;
String ttl      = title;    ttl += _T(" Output");

  fileName = fileName.substr(pos+1);   pos = fileName.findFirstOf(_T('.'));
  fileName = fileName.substr(0, pos);  fileName += suffix;

  PathDlg dlg(ttl, fileName, fileType, _T("File Type"), filter);

  if (setSaveAsPath(dlg)) OnSaveDocument(path);
  }


// UglyDoc serialization

void AppT3mplateDoc::serialize(Archive& ar) {

  if (ar.isStoring())
    switch(dataSource) {
      case NotePadSrc : ar << notePad; return;
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
      default       : return;
      }
  }


// AppT3mplateDoc diagnostics

#ifdef _DEBUG
void AppT3mplateDoc::AssertValid() const {         CDocument::AssertValid();}
void AppT3mplateDoc::Dump(CDumpContext& dc) const {CDocument::Dump(dc);}
#endif //_DEBUG


