// AppT3mplateView.cpp : implementation of the AppT3mplateView class


#include "stdafx.h"
#include "AppT3mplateView.h"
#include "AppT3mplate.h"
#include "AppT3mplateDoc.h"
#include "Options.h"
#include "Resources.h"


// AppT3mplateView

IMPLEMENT_DYNCREATE(AppT3mplateView, CScrView)

BEGIN_MESSAGE_MAP(AppT3mplateView, CScrView)
END_MESSAGE_MAP()


AppT3mplateView::AppT3mplateView() noexcept : dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()),
                                              dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
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
      case StoreSrc   : prtStore.print(*this); break;
      }

  else
    switch(ds) {
      case NotePadSrc : dspNote.display(*this);  break;
      case StoreSrc   : dspStore.display(*this); break;
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
    case StoreSrc   : prtStore.footer(dev, pageNo); break;
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


// AppT3mplateView diagnostics

#ifdef _DEBUG

void AppT3mplateView::AssertValid() const {CScrollView::AssertValid();}

void AppT3mplateView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
AppT3mplateDoc* AppT3mplateView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AppT3mplateDoc))); return (AppT3mplateDoc*)m_pDocument;}

#endif //_DEBUG
