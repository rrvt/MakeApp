// MakeAppView.cpp : implementation of the MakeAppView class


#include "pch.h"
#include "MakeAppView.h"
#include "ListFonts.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrView)

BEGIN_MESSAGE_MAP(MakeAppView, CScrView)
  ON_COMMAND(ID_Options, &onOptions)
END_MESSAGE_MAP()


MakeAppView::MakeAppView() noexcept : dspFonts(dMgr.getNotePad()), prtFonts(pMgr.getNotePad()),
                                      dspNote( dMgr.getNotePad()), prtNote( pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }



void MakeAppView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) pMgr.setFontScale(printer.scale);
  }


#if 1
void MakeAppView::OnPrepareDC(CDC* dc, CPrintInfo* info) {

  if(doc()->dataSrc() == FontSrc) listFonts(dc);

  CScrView::OnPrepareDC(dc, info);
  }
#endif

// Perpare output (i.e. report) then start the output with the call to SCrView

void MakeAppView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    case FontSrc    : prtFonts.onBeginPrinting(*this); break;
    }
  }


void MakeAppView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this);  break;
    case FontSrc    : dspFonts.display(*this); break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void MakeAppView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    case FontSrc    : prtFonts.prtFooter(dev, pageNo); break;
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
void MakeAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}  // non-debug version is inline
MakeAppDoc* MakeAppView::GetDocument() const
              {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc))); return (MakeAppDoc*)m_pDocument;}
#endif //_DEBUG


#if 0
void MakeAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if(doc()->dataSrc() == FontSrc) listFonts(pDC);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }
#endif
//pMgr.orient = printer.orient; pMgr.pagePlex = printer.pagePlex;

