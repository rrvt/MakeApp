// Dialog4ppDlg.cpp : implementation file
//

#include "pch.h"
#include "Dialog4ppDlg.h"
#include "AboutDlg.h"
#include "History.h"
#include "StatusBar.h"
#include "TBComboBox.h"


static TCchar* MenuCaption = _T("Popup Menu");

// Dialog4ppDlg dialog

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

static CbxItem CbxSingle    =  {_T("Single"), 3000};

static CbxItem PopupItems[] = {{_T("Option11"), ID_Option11},
                               {_T("Option12"), ID_Option12}
                               };
static const TCchar* ItemsCaption = _T("Items Menu");
#endif


BEGIN_MESSAGE_MAP(Dialog4ppDlg, CDialogEx)
  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(    TTN_NEEDTEXT, 0, &OnTtnNeedText)         // Do ToolTips
  ON_WM_MOVE()
#ifdef DialogSizable
  ON_WM_SIZE()
#endif

#ifdef Examples
  ON_COMMAND(      ID_ChangeReady,  &changeReady)

  ON_CBN_SELCHANGE(ID_CBox,         &onComboBoxChng)        // Process secelection from list

  ON_EN_KILLFOCUS( ID_EditBox,      &onTBEditBox)           // Process content of edit box

  ON_CBN_SELCHANGE(ID_PopupMenu,    &onDispatch)            // Send Command Message with ID_...
  ON_COMMAND(      ID_Option01,     &onOption01)
  ON_COMMAND(      ID_Option02,     &onOption02)

  ON_CBN_SELCHANGE(ID_PopupMenu1,   &onDispatch1)           // Send Command Message with ID_...
  ON_COMMAND(      ID_Option11,     &onOption11)
  ON_COMMAND(      ID_Option12,     &onOption12)

  ON_COMMAND(      ID_Button,       &onX)

  ON_COMMAND(      ID_SaveHist,     &onSaveHist)
#endif

  ON_COMMAND(      ID_Help,         &onHelp)
  ON_COMMAND(      ID_App_About,    &onAppAbout)
  ON_COMMAND(      ID_App_Exit,     &OnOK)
END_MESSAGE_MAP()


Dialog4ppDlg::Dialog4ppDlg(TCchar* helpPth, CWnd* pParent) :
                           helpPath(helpPth), CDialogEx(IDD_Dialog4pp, pParent), isInitialized(false) { }


Dialog4ppDlg::~Dialog4ppDlg() { }


int Dialog4ppDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }


BOOL Dialog4ppDlg::OnInitDialog() {
CRect winRect;

  CDialogEx::OnInitDialog();

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  GetWindowRect(&winRect);   toolBar.move(winRect);   SetBackgroundColor(RGB(255,255,255));

  if (!statusBar.create(this, IDC_StatusBar)) return false;

  statusBar.setReady();

  winPos.initialPos(this, winRect);   isInitialized = true;   return true;
  }


void Dialog4ppDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  }


// MainFrame message handlers

LRESULT Dialog4ppDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void Dialog4ppDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.initialize(winRect);

#ifdef Examples
  toolBar.installBtn(ID_Button, _T(" My Button "));

  if (toolBar.installComboBox(ID_CBox)) setComboBox();

  toolBar.installEditBox(ID_EditBox, 20);

  if (toolBar.installPopupMenu(ID_PopupMenu)) {
    toolBar.addPopupMenu(   ID_PopupMenu, IDR_PopupMenu);
    toolBar.setPopupCaption(ID_PopupMenu, MenuCaption);
    }

  if (toolBar.installPopupMenu(ID_PopupMenu1)) {
    toolBar.addPopupItems(  ID_PopupMenu1, PopupItems, noElements(PopupItems));
    toolBar.setPopupCaption(ID_PopupMenu1, ItemsCaption);
    }
#endif
  }


void Dialog4ppDlg::OnMove(int x, int y)
            {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}


#ifdef DialogSizable

void Dialog4ppDlg::OnSize(UINT nType, int cx, int cy) {
CRect winRect;

  CDialogEx::OnSize(nType, cx, cy);

  if (!isInitialized) return;

  GetWindowRect(&winRect);   winPos.set(winRect);   toolBar.move(winRect);   statusBar.move(winRect);
  }
#endif


#ifdef Examples
void Dialog4ppDlg::onDispatch()  {toolBar.dispatch(ID_PopupMenu,  MenuCaption);}
void Dialog4ppDlg::onDispatch1() {toolBar.dispatch(ID_PopupMenu1, ItemsCaption);}


void Dialog4ppDlg::setComboBox() {

  toolBar.addCbxItems(  ID_CBox, CbxText, noElements(CbxText));

  toolBar.addCbxItem(   ID_CBox, CbxSingle);

  toolBar.addResToCbx(  ID_CBox, IDR_CbxMenu);

  toolBar.setCbxCaption(ID_CBox, CbxCaption);
  }


void Dialog4ppDlg::onComboBoxChng() {
String s;
int    x;
String t;

  if (!toolBar.getCbxSel(ID_CBox, s, x)) return;

  t.format(_T("Item = %s, Data = %i"), s.str(), x);

  statusBar.setText(1, t);
  }


void Dialog4ppDlg::onTBEditBox() {String s;   toolBar.getEbxText(ID_EditBox, s);   statusBar.setText(1, s);}
#endif


// Do ToolTips

BOOL Dialog4ppDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                                  {return toolBar.OnTtnNeedText(pNMHDR);}


#ifdef Examples
void Dialog4ppDlg::onSaveHist() {
  history.saveData();
  }


void Dialog4ppDlg::changeReady() {
bool status = statusBar.isReady();

  statusBar.setReady(!status);
  }


void Dialog4ppDlg::onOption01() {
  statusBar.setText(1, _T("Option 0.1"));
  }


void Dialog4ppDlg::onOption02() {
  statusBar.setText(1, _T("Option 0.2"));
  }


void Dialog4ppDlg::onOption11() {
  statusBar.setText(1, _T("Option 1.1"));
  }


void Dialog4ppDlg::onOption12() {
  statusBar.setText(1, _T("Option 1.2"));
  }


void Dialog4ppDlg::onX() {
  statusBar.setText(1, _T("XYZabc"));
  toolBar.setEbxText(ID_EditBox, _T("XYZabc"));
  }
#endif


void Dialog4ppDlg::onHelp() {
String topic = helpPath; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }



void Dialog4ppDlg::onAppAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}


void Dialog4ppDlg::OnOK() {CDialogEx::OnOK();}




#if 0

  //bool  rslt;
  //CRect rect;
  //int   parts[2];
  rect = CRect(0, 0, 0, 0);

  rslt = statusBar.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, rect, this, IDC_StatusBar);

  if (!rslt) return false;

  statusBar.GetClientRect(&rect);   parts[0] = rect.right/2;  parts[1] =  -1;

  rslt = statusBar.SetParts(2, parts);
#endif

