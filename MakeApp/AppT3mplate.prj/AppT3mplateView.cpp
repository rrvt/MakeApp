// AppT3mplateView.cpp : implementation of the AppT3mplateView class


#include "pch.h"
#include "AppT3mplateView.h"
#include "AppT3mplate.h"
#include "AppT3mplateDoc.h"
#include "ClipLine.h"
#include "IniFileEx.h"
#include "ReportNtpd.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "ResourceData.h"
#include "RptOrientDlgTwo.h"
#include "Store.h"


static TCchar* StrOrietnKey = _T("Store");


IMPLEMENT_DYNCREATE(AppT3mplateView, CScrView)

BEGIN_MESSAGE_MAP(AppT3mplateView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()                     // Right Mouse Popup Menu
  ON_COMMAND(ID_CopySel, &onCopy)
  ON_COMMAND(ID_Pup1,    &onPup1)
  ON_COMMAND(ID_Pup2,    &onPup2)

END_MESSAGE_MAP()


#ifdef Examples
AppT3mplateView::AppT3mplateView() noexcept : dspStore(dMgr.getNotePad()),
                                              prtStore(pMgr.getNotePad()) {
#else
AppT3mplateView::AppT3mplateView() noexcept {
#endif
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(IDR_RtMouseMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL AppT3mplateView::PreCreateWindow(CREATESTRUCT& cs) {return CScrView::PreCreateWindow(cs);}


void AppT3mplateView::OnInitialUpdate() {CScrView::OnInitialUpdate();}


void AppT3mplateView::initNoteOrietn() {
  dspNote.prtrOrietn = prtNote.prtrOrietn =
                           (PrtrOrient) iniFile.readInt(RptOrietnSect, NoteOrietnKey, PortOrient);
  }


void AppT3mplateView::saveNoteOrietn()
                                 {iniFile.write(RptOrietnSect, NoteOrietnKey, prtNote.prtrOrietn);}


void AppT3mplateView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


void AppT3mplateView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Store:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
#ifdef Examples
  dlg.rpt1 = printer.toStg(prtStore.prtrOrietn);
#endif

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
#ifdef Examples
    prtStore.prtrOrietn = printer.toOrient(dlg.rpt1);
#endif
    saveRptOrietn();
    }
  }


void AppT3mplateView::initRptOrietn()
#ifdef Examples
  {prtStore.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, StrOrietnKey, PortOrient);}
#else
  { }
#endif


void AppT3mplateView::saveRptOrietn() {
  saveNoteOrietn();

#ifdef Examples
  iniFile.write(RptOrietnSect, StrOrietnKey,  (int) prtStore.prtrOrietn);
#endif
  }


void AppT3mplateView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this); break;
#ifdef Examples
    case StoreSrc   : dspStore.display(*this); break;
#endif
    }
  }


void AppT3mplateView::displayHeader(DevStream& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
#ifdef Examples
    case StoreSrc     : dspStore.dspHeader(dev);  break;
#endif
    }
  }


void AppT3mplateView::displayFooter(DevStream& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
#ifdef Examples
    case StoreSrc     : dspStore.dspFooter(dev);  break;
#endif
    }
  }



void AppT3mplateView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
#ifdef Examples
    case StoreSrc   : prtStore.onPreparePrinting(info);    break;
#endif
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AppT3mplateView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
#ifdef Examples
    case StoreSrc   : prtStore.onBeginPrinting(*this); break;
#endif
    }
  }


void AppT3mplateView::printHeader(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc: prtNote.prtHeader(dev, pageNo);   break;
#ifdef Examples
    case StoreSrc  : dspStore.prtHeader(dev, pageNo);  break;
#endif
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void AppT3mplateView::printFooter(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
#ifdef Examples
    case StoreSrc   : prtStore.prtFooter(dev, pageNo); break;
#endif
    }
  }



void AppT3mplateView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void AppT3mplateView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case StoreSrc   : break;
    }
  }


void AppT3mplateView::OnLButtonDown(UINT nFlags, CPoint point)
                   {clipLine.set(point);   invalidate();   CScrView::OnLButtonDown(nFlags, point);}


void AppT3mplateView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  clipLine.set(point);   RedrawWindow();   clipLine.load();

  CScrView::OnLButtonDblClk(nFlags, point);
  }


void AppT3mplateView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
        {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void AppT3mplateView::onCopy() {clipLine.load();  invalidate();}


void AppT3mplateView::onPup1() {  }


void AppT3mplateView::onPup2() {  }


// AppT3mplateView diagnostics

#ifdef _DEBUG
void AppT3mplateView::AssertValid() const          {CScrollView::AssertValid();}
void AppT3mplateView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
AppT3mplateDoc* AppT3mplateView::GetDocument() const {              // non-debug version is inline
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AppT3mplateDoc)));
  return (AppT3mplateDoc*)m_pDocument;
  }
#endif //_DEBUG



