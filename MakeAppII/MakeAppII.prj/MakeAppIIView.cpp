// MakeAppIIView.cpp : implementation of the MakeAppIIView class


#include "stdafx.h"
#include "MakeAppIIView.h"
#include "MakeAppIIDoc.h"
#include "Options.h"


// MakeAppIIView

IMPLEMENT_DYNCREATE(MakeAppIIView, CScrView)

BEGIN_MESSAGE_MAP(MakeAppIIView, CScrView)
END_MESSAGE_MAP()




void MakeAppIIView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if (pDC->IsPrinting()) {setHorzMgns(leftMgn,  rightMgn);  setVertMgns(topMgn,  botMgn);}
  else                   {setHorzMgns(0.33, 0.33); setVertMgns(0.33, 0.33);}

  CScrView::OnPrepareDC(pDC, pInfo);
  }




// MakeAppIIView diagnostics

#ifdef _DEBUG

void MakeAppIIView::AssertValid() const {CScrollView::AssertValid();}

void MakeAppIIView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
MakeAppIIDoc* MakeAppIIView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppIIDoc))); return (MakeAppIIDoc*)m_pDocument;}

#endif //_DEBUG
