// MakeAppView.cpp : implementation of the MakeAppView class


#include "pch.h"
#include "MakeAppView.h"
#include "ListFonts.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "Options.h"
#include "Resources.h"


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrView)

BEGIN_MESSAGE_MAP(MakeAppView, CScrView)
END_MESSAGE_MAP()


MakeAppView::MakeAppView() noexcept : dspFonts(dMgr.getNotePad()), prtFonts(pMgr.getNotePad()),
                                      dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


void MakeAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if(doc()->dataSrc() == FontSrc) listFonts(pDC);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }



// Perpare output (i.e. report) then start the output with the call to SCrView

void MakeAppView::onPrepareOutput(bool printing) {
DataSource ds = doc()->dataSrc();

  if (printing)
    switch(ds) {
      case NotePadSrc : prtNote.print(*this);  break;
      case FontSrc    : prtFonts.print(*this); break;
      }

    else
      switch(ds) {
        case NotePadSrc : dspNote.display(*this);  break;
        case FontSrc    : dspFonts.display(*this); break;
        }


  CScrView::onPrepareOutput(printing);
  }


void MakeAppView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : setOrientation(options.orient); break;    // Setup separate Orientation?
    case FontSrc    : setOrientation(options.orient); break;
    }
  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void MakeAppView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.footer(dev, pageNo);  break;
    case FontSrc    : prtFonts.footer(dev, pageNo); break;
    }
  }



void MakeAppView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case FontSrc    : break;
    }
  }


void MakeAppView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case FontSrc : break;
    }
  }



// MakeAppView diagnostics

#ifdef _DEBUG

void MakeAppView::AssertValid() const {CScrollView::AssertValid();}

void MakeAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
MakeAppDoc* MakeAppView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc))); return (MakeAppDoc*)m_pDocument;}

#endif //_DEBUG
