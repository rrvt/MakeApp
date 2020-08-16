// AppT3mplateView.cpp : implementation of the AppT3mplateView class


#include "stdafx.h"
#include "AppT3mplateView.h"
#include "Options.h"
#include "Report.h"
#include "AppT3mplate.h"
#include "AppT3mplateDoc.h"


// AppT3mplateView

IMPLEMENT_DYNCREATE(AppT3mplateView, CScrView)

BEGIN_MESSAGE_MAP(AppT3mplateView, CScrView)
END_MESSAGE_MAP()




void AppT3mplateView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if (pDC->IsPrinting()) {setHorzMgns(leftMgn,  rightMgn);  setVertMgns(topMgn,  botMgn);}
  else                   {setHorzMgns(0.33, 0.33); setVertMgns(0.33, 0.33);}

  CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void AppT3mplateView::onPrepareOutput() {report(isPrinting());   CScrView::onPrepareOutput();}




void AppT3mplateView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  setPrntrOrient(theApp.getDevMode(), pDC);

  CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void AppT3mplateView::printFooter(Display& dev, int pageNo) {report.footer(dev, pageNo); invalidate();}




// AppT3mplateView diagnostics

#ifdef _DEBUG

void AppT3mplateView::AssertValid() const {CScrollView::AssertValid();}

void AppT3mplateView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
AppT3mplateDoc* AppT3mplateView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AppT3mplateDoc))); return (AppT3mplateDoc*)m_pDocument;}

#endif //_DEBUG
