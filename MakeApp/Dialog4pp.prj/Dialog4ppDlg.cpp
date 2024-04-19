// Dialog4ppDlg.cpp : implementation file
//

#include "pch.h"
#include "Dialog4ppDlg.h"
#include "AboutDlg.h"
#include "History.h"
#include "StatusBar.h"

#include "NotePad.h"


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

  ON_COMMAND(      ID_Button,       &onX)

  ON_COMMAND(      ID_ChangeReady,  &changeReady)

  ON_EN_KILLFOCUS( ID_EditBox,      &onTBEditBox)           // Process content of edit box


  ON_CBN_SELCHANGE(ID_PopupMenu,    &onDispatch)            // Send Command Message with ID_...
  ON_COMMAND(      ID_Option01,     &onOption01)
  ON_COMMAND(      ID_Option02,     &onOption02)

  ON_CBN_SELCHANGE(ID_PopupMenu1,   &onDispatch1)           // Send Command Message with ID_...
  ON_COMMAND(      ID_Option11,     &onOption11)
  ON_COMMAND(      ID_Option12,     &onOption12)

  ON_CBN_SELCHANGE(ID_CboBx,        &onCboBxChange)        // Process secelection from list
  ON_CBN_SELCHANGE(ID_CboBx1,       &onCboBx1Change)        // Process secelection from list

  ON_COMMAND(      ID_SaveHist,     &onSaveHist)
#endif

  ON_COMMAND(      ID_Help,         &onHelp)
  ON_COMMAND(      ID_App_About,    &onAppAbout)
  ON_COMMAND(      ID_App_Exit,     &OnOK)

  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(    TTN_NEEDTEXT, 0, &OnTtnNeedText)         // Do ToolTips
  ON_WM_MOVE()
#ifdef DialogSizable
  ON_WM_SIZE()
#endif
END_MESSAGE_MAP()


Dialog4ppDlg::Dialog4ppDlg(TCchar* helpPth, CWnd* pParent) : CDialogEx(IDD_Dialog4pp, pParent),
                                       helpPath(helpPth), toolBar(), statusBar(), isInitialized(false) { }


Dialog4ppDlg::~Dialog4ppDlg() {winPos.~WinPos();}


int Dialog4ppDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }


BOOL Dialog4ppDlg::OnInitDialog() {
CRect winRect;

  CDialogEx::OnInitDialog();

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  SetBackgroundColor(RGB(255,255,255));               // toolBar.move(winRect);

  if (!statusBar.create(this, IDC_StatusBar)) return false;

  statusBar.setReady();

  winPos.initialPos(this, winRect);   toolBar.move(winRect);   statusBar.move(winRect);

  isInitialized = true;   return true;
  }


void Dialog4ppDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  }


void Dialog4ppDlg::OnMove(int x, int y)
            {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}


#ifdef DialogSizable

void Dialog4ppDlg::OnSize(UINT nType, int cx, int cy) {
CRect r;

  GetWindowRect(&r);

  if (!isInitialized) {winPos.setInvBdrs(r, cx, cy);   return;}

  winPos.set(cx, cy);   toolBar.move(r);   statusBar.move(r);    CDialogEx::OnSize(nType, cx, cy);
  }

#endif


// MainFrame message handlers

LRESULT Dialog4ppDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void Dialog4ppDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.set(winRect);

  toolBar.addButton(ID_Button, _T(" My Button "));

  toolBar.addEditBox(ID_EditBox, 20);
  toolBar.addMenu(ID_PopupMenu,  IDR_PopupMenu, _T("My Caption"));
  toolBar.addMenu(ID_PopupMenu1, PopupItems1, noElements(PopupItems1), _T("My Caption #1"));
  toolBar.addCBx( ID_CboBx,      IDR_CbxMenu,   _T("A Combo Box"));
  toolBar.addCBx( ID_CboBx1,     CbxText, noElements(CbxText), CbxCaption);
  }




void Dialog4ppDlg::onTBChange(NMHDR* pNMHDR, LRESULT* pResult) {

  LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

  // TODO: Add your control notification handler code here

  *pResult = 0;
  }



#ifdef Examples


void Dialog4ppDlg::onCboBxChange() {
String s;
int    x;
String t;

  if (!toolBar.getCurSel(ID_CboBx, s, x)) return;

  t.format(_T("Item = %s, Data = %i"), s.str(), x);

  statusBar.setText(1, t);
  }


void Dialog4ppDlg::onCboBx1Change() {
String s;
int    x;
String t;

  if (!toolBar.getCurSel(ID_CboBx1, s, x)) return;

  t.format(_T("Item = %s, Data = %i"), s.str(), x);

  statusBar.setText(1, t);
  }


void Dialog4ppDlg::onDispatch()  {toolBar.dispatch(ID_PopupMenu);}


void Dialog4ppDlg::onOption00() {SetFocus();   onOption01();}


void Dialog4ppDlg::onOption01() {
  statusBar.setText(1, _T("Option 0.1"));
  }


void Dialog4ppDlg::onOption02() {
  statusBar.setText(1, _T("Option 0.2"));
  }


void Dialog4ppDlg::onDispatch1() {toolBar.dispatch(ID_PopupMenu1);}


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


#ifdef Examples
void Dialog4ppDlg::onSaveHist() {
  history.saveData();
  }


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

