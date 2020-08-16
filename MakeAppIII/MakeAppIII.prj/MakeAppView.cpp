// MakeAppView.cpp : implementation of the MakeAppView class


#include "stdafx.h"
#include "MakeAppView.h"
#include "MakeAppDoc.h"
#include "Options.h"


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrView)

BEGIN_MESSAGE_MAP(MakeAppView, CScrView)
END_MESSAGE_MAP()




void MakeAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if (pDC->IsPrinting()) {setHorzMgns(leftMgn,  rightMgn);  setVertMgns(topMgn,  botMgn);}
  else                   {setHorzMgns(0.33, 0.33); setVertMgns(0.33, 0.33);}

  CScrView::OnPrepareDC(pDC, pInfo);
  }




// MakeAppView diagnostics

#ifdef _DEBUG

void MakeAppView::AssertValid() const {CScrollView::AssertValid();}

void MakeAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
MakeAppDoc* MakeAppView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc))); return (MakeAppDoc*)m_pDocument;}

#endif //_DEBUG
