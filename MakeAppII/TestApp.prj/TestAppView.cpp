// TestAppView.cpp : implementation of the TestAppView class


#include "stdafx.h"
#include "TestAppView.h"
#include "Options.h"
#include "Report.h"
#include "TestApp.h"
#include "TestAppDoc.h"


// TestAppView

IMPLEMENT_DYNCREATE(TestAppView, CScrView)

BEGIN_MESSAGE_MAP(TestAppView, CScrView)
END_MESSAGE_MAP()




void TestAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
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

void TestAppView::onPrepareOutput() {report(isPrinting());   CScrView::onPrepareOutput();}




void TestAppView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  setPrntrOrient(theApp.getDevMode(), pDC);

  CScrView::OnBeginPrinting(pDC, pInfo);
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void TestAppView::printFooter(Display& dev, int pageNo) {report.footer(dev, pageNo); invalidate();}




// TestAppView diagnostics

#ifdef _DEBUG

void TestAppView::AssertValid() const {CScrollView::AssertValid();}

void TestAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
TestAppDoc* TestAppView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(TestAppDoc))); return (TestAppDoc*)m_pDocument;}

#endif //_DEBUG
