// AppT3mplateView.cpp : implementation of the AppT3mplateView class


#include "stdafx.h"
#include "AppT3mplateView.h"
#include "AppT3mplate.h"
#include "AppT3mplateDoc.h"
#include "ClipLine.h"
#include "Options.h"
#include "Resource.h"
#include "Resources.h"


// AppT3mplateView

IMPLEMENT_DYNCREATE(AppT3mplateView, CScrView)

BEGIN_MESSAGE_MAP(AppT3mplateView, CScrView)
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()
  ON_COMMAND(ID_Pup0, &onCopy)
  ON_COMMAND(ID_Pup1, &onPup1)
  ON_COMMAND(ID_Pup2, &onPup2)

END_MESSAGE_MAP()


AppT3mplateView::AppT3mplateView() noexcept :
                                    #ifdef Examples
                                      dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()),
                                    #endif
                                    dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);

  sub.LoadMenu(ID_PopupMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));        //

  sub.Detach();
  }


BOOL AppT3mplateView::PreCreateWindow(CREATESTRUCT& cs) {

  return CScrView::PreCreateWindow(cs);
  }


void AppT3mplateView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AppT3mplateView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc : prtNote.print(*this);  break;
#ifdef Examples
      case StoreSrc   : prtStore.print(*this); break;
#endif
      }

  else
    switch(ds) {
      case NotePadSrc : dspNote.display(*this);  break;
#ifdef Examples
      case StoreSrc   : dspStore.display(*this); break;
#endif
      }


  CScrView::onPrepareOutput(printing);
  }


void AppT3mplateView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case StoreSrc   : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AppT3mplateView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
#ifdef Examples
    case StoreSrc   : prtStore.footer(dev, pageNo); break;
#endif
    }
  }



void AppT3mplateView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

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


void AppT3mplateView::OnLButtonDblClk(UINT nFlags, CPoint point)
  {clipLine.set(point);   RedrawWindow();   clipLine.load();   CScrView::OnLButtonDblClk(nFlags, point);}


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

void AppT3mplateView::AssertValid() const {CScrollView::AssertValid();}

void AppT3mplateView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
AppT3mplateDoc* AppT3mplateView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AppT3mplateDoc))); return (AppT3mplateDoc*)m_pDocument;}

#endif //_DEBUG




#if 1
#else
  sub.CreatePopupMenu();

  sub.AppendMenu(MF_STRING, ID_Pup0, _T("Copy Selection\tCtrl+C"));
  sub.AppendMenu(MF_STRING, ID_Pup1, _T("Popup 1\tCtrl+A"));
  sub.AppendMenu(MF_STRING, ID_Pup2, _T("Popup 2\tCtrl+B"));
#endif

