// Dialog4ppDlg.cpp : implementation file
//

#include "pch.h"
#include "Dialog4ppDlg.h"
#include "AboutDlg.h"
#include "History.h"
#include "PrintNtPd.h"
#include "PrinterAttr.h"
#include "StatusBar.h"



IMPLEMENT_DYNAMIC(Dialog4ppDlg, CDialogEx)


#ifdef Examples
static TCchar* CbxCaption =   _T("Greeks +");

static CbxItem CbxText[]  = {{_T("Zeta"),    1},
                             {_T("Beta"),    2},
                             {_T("Alpha"),   3},
                             {_T("Omega"),   4},
                             {_T("Phi"),     5},
                             {_T("Mu"),      6},
                             {_T("Xi"),      7},
                             {_T("Omicron"), 8},
                             {_T("Pi"),      9},
                             {_T("Rho"),    10},
                             {_T("Sigma"),  11},
                             {_T("Nu"),     12},
                             {_T("Kappa"),  13},
                             {_T("Iota"),   14}
                             };


static CbxItem PopupItems1[] = {{_T("Option11"), ID_Option11},
                                {_T("Option12"), ID_Option12}
                                };
#endif


BEGIN_MESSAGE_MAP(Dialog4ppDlg, CDialogEx)

#ifdef Examples

  ON_COMMAND(      ID_Button,             &onX)

  ON_COMMAND(      ID_ChangeReady,        &changeReady)

  ON_EN_KILLFOCUS( ID_EditBox,            &onTBEditBox)         // Process content of edit box

  ON_CBN_SELCHANGE(ID_Menu,               &onDispatch)          // Send Command Message with ID_...
  ON_COMMAND(      ID_Option01,           &onOption01)
  ON_COMMAND(      ID_Option02,           &onOption02)

  ON_CBN_SELCHANGE(ID_Menu1,              &onDispatch1)         // Send Command Message with ID_...
  ON_COMMAND(      ID_Option11,           &onOption11)
  ON_COMMAND(      ID_Option12,           &onOption12)

  ON_CBN_SELCHANGE(ID_CboBox,             &onCboBxChange)       // Process secelection from list
  ON_CBN_SELCHANGE(ID_CboBox1,            &onCboBx1Change)      // Process secelection from list

#endif

  ON_CBN_SELCHANGE(ID_Options,            &onDispatch2)         // Send Command Message with ID_...
  ON_COMMAND(      ID_SetupDisplayPage,   &onSetupDisplayPage)

  ON_COMMAND(      ID_PrintFile,          &onPrintFile)
  ON_COMMAND(      ID_FILE_PRINT_PREVIEW, &onFilePrintPreview)
  ON_COMMAND(      ID_PrintSetup,         &onSetupPrinter)

  ON_COMMAND(      ID_SaveHist,           &onSaveHist)
  ON_COMMAND(      ID_Help,               &onHelp)
  ON_COMMAND(      ID_AppAbout,           &onAppAbout)
  ON_COMMAND(      ID_ExitApp,            &OnOK)

  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(    TTN_NEEDTEXT, 0, &OnTtnNeedText)         // Do ToolTips
  ON_WM_MOVE()
#ifdef DialogSizable
  ON_WM_SIZE()
#endif
END_MESSAGE_MAP()


Dialog4ppDlg::Dialog4ppDlg(TCchar* helpPth, CWnd* pParent) : DialogEx(IDD_Dialog4pp, pParent),
                                             helpPath(helpPth), toolBar(), isInitialized(false) { }


Dialog4ppDlg::~Dialog4ppDlg() {winPos.~WinPos();}


int Dialog4ppDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (DialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }



BOOL Dialog4ppDlg::OnInitDialog() {
CRect winRect;

  DialogEx::OnInitDialog();

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  SetBackgroundColor(RGB(255,255,255));               // toolBar.move(winRect);

  statusBar.setReady();

  winPos.initialPos(this, winRect);   toolBar.move(winRect);   statusBar.move(winRect);

  isInitialized = true;   return true;
  }


void Dialog4ppDlg::DoDataExchange(CDataExchange* pDX) {
  DialogEx::DoDataExchange(pDX);
  }


// Called to update printer attributes, Return true when attributes changed

bool Dialog4ppDlg::onPreparePrinter(PrinterInfo& info) {
  info.width = 3.5;   info.length = 4.5;
  info.topMgn  = 0.125;   info.leftMgn = 0.125;   info.rightMgn = 0.125;   info.bottomMgn = 0.125;
  info.orient  = LandOrnt;   return true;
  }


#ifdef Examples

static TCchar* text[] = {
            _T("0123456789 0123456789 0123456789 "),
            _T("Now is the time for all good people to come to the aid of the party.  "),
            _T("The grey dog jumped over the sleeping bear and kissed the wiggling turtle.  "),
            _T("When you're on the go, multiuse products that streamline your routine are "),
            _T("helpful.  Think tinted moisturizers with SPF, cheek-and-lip sticks, a dense, "),
            _T("all-body nourishing cream and concealers that double as highlighters.")
            };


NotePad& Dialog4ppDlg::onPreparePrinting() {
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
        case 70: notePad << _T("n End Line") << nEndLine << _T(' ');                     break;
        default:                                                                         break;
        }

      notePad << ele.word;   j++;
      }
    }

  return notePad;
  }


bool Dialog4ppDlg::findNextBrk(String& line, ElementX& ele) {
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


bool Dialog4ppDlg::findWhite(String& line, ElementX& ele) {
int pos;
int lng;

  ele.typ = WhiteEle;

  for (pos = 0, lng = line.length(); pos < lng; pos++) if (line[pos] != _T(' ')) break;

  if (!pos) return false;

  ele.word = line.substr(0, pos);   line = line.substr(pos);   return true;
  }

#endif


void Dialog4ppDlg::setHeader(PrintNtPd& prntNp) {
  prntNp.setHeader(_T("Arial"), 80, &getHdr);
  }


void Dialog4ppDlg::getHdr(NotePad& np, int pageNo, int noPages) {

  np.clear();

  np << _T("Header") << nCenter << _T("Page No: ") << pageNo << _T(" of ") << noPages;
  np << nRight << _T("Recipe: ") << pageNo;
  }


void Dialog4ppDlg::setFooter(PrintNtPd& prntNp) {
  prntNp.setFooter(_T("Courier New"), 60, getFtr);
  }


void Dialog4ppDlg::getFtr(NotePad& np, int pageNo, int noPages) {
  np.clear();   np << nCenter << _T("Footer: ") << pageNo << _T(" of ") << noPages;
  }


void Dialog4ppDlg::OnMove(int x, int y)
      {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   DialogEx::OnMove(x, y);}


#ifdef DialogSizable

void Dialog4ppDlg::OnSize(UINT nType, int cx, int cy) {
CRect r;

  GetWindowRect(&r);

  if (!isInitialized) {winPos.setInvBdrs(r, cx, cy);   return;}

  winPos.set(cx, cy);   toolBar.move(r);   statusBar.move(r);    DialogEx::OnSize(nType, cx, cy);
  }

#endif


// MainFrame message handlers

LRESULT Dialog4ppDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void Dialog4ppDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.set(winRect);

  toolBar.setCboItems(  ID_Options, IDR_Options);
  toolBar.setCboCaption(ID_Options, _T("Options"));

#ifdef Examples
  toolBar.addButton(    ID_Button, _T(" My Button "));

  toolBar.addEditBox(   ID_EditBox, 20);
  toolBar.setCboItems(  ID_Menu,  IDR_Menu);
  toolBar.setCboCaption(ID_Menu, _T("My Caption"));

  toolBar.setCboItems(  ID_Menu1, PopupItems1, noElements(PopupItems1));
  toolBar.setCboCaption(ID_Menu1, _T("My Caption #1"));

  toolBar.setCboItems(  ID_CboBox,  IDR_CbxMenu);
  toolBar.setCboCaption(ID_CboBox, _T("A Combo Box"));

  toolBar.setCboItems(  ID_CboBox1,  CbxText, noElements(CbxText));
  toolBar.setCboCaption(ID_CboBox1, CbxCaption);
#endif
  }



#ifdef Examples
void Dialog4ppDlg::onTBChange(NMHDR* pNMHDR, LRESULT* pResult) {

  LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

  // TODO: Add your control notification handler code here

  *pResult = 0;
  }
#endif


#ifdef Examples


void Dialog4ppDlg::onCboBxChange() {
String s;
ulongP x;
String t;

  if (!toolBar.getCurSel(ID_CboBox, s, x)) return;

  t.format(_T("Item = %s, Data = %i"), s.str(), x);

  statusBar.setText(1, t);
  }


void Dialog4ppDlg::onCboBx1Change() {
String s;
ulongP x;
String t;

  if (!toolBar.getCurSel(ID_CboBox1, s, x)) return;

  t.format(_T("Item = %s, Data = %i"), s.str(), x);

  statusBar.setText(1, t);
  }


void Dialog4ppDlg::onDispatch()  {toolBar.dispatch(ID_Menu);}


void Dialog4ppDlg::onOption00() {SetFocus();   onOption01();}


void Dialog4ppDlg::onOption01() {
  statusBar.setText(1, _T("Option 0.1"));
  }


void Dialog4ppDlg::onOption02() {
  statusBar.setText(1, _T("Option 0.2"));
  }


void Dialog4ppDlg::onDispatch1() {toolBar.dispatch(ID_Menu1);}


void Dialog4ppDlg::onOption11() {
  statusBar.setText(1, _T("Option 1.1"));
  }


void Dialog4ppDlg::onOption12() {
  statusBar.setText(1, _T("Option 1.2"));
  }


void Dialog4ppDlg::onTBEditBox() {
CString s = toolBar.getText(ID_EditBox);   statusBar.setText(1, s);
}
#endif


// Do ToolTips

BOOL Dialog4ppDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                            {return toolBar.OnTtnNeedText(pNMHDR);}


void Dialog4ppDlg::onSaveHist() {
  history.saveData();
  }


#ifdef Examples

void Dialog4ppDlg::changeReady() {
bool status = statusBar.isReady();

  statusBar.setReady(!status);
  }


void Dialog4ppDlg::onX() {
  statusBar.setText(1, _T("My Button"));
  }
#endif


void Dialog4ppDlg::onHelp() {
String topic = helpPath; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }



void Dialog4ppDlg::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}


void Dialog4ppDlg::OnOK() {CDialogEx::OnOK();}

