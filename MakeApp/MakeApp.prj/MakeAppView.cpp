// MakeAppView.cpp : implementation of the MakeAppView class


#include "stdafx.h"
#include "MakeAppView.h"
#include "MakeAppDoc.h"


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrView)

// ThAddrView message handlers
BEGIN_MESSAGE_MAP(MakeAppView, CScrView)
END_MESSAGE_MAP()


// MakeAppView diagnostics

#ifdef _DEBUG

void MakeAppView::AssertValid() const {CScrollView::AssertValid();}

void MakeAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}

MakeAppDoc* MakeAppView::GetDocument() const // non-debug version is inline
          {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc)));   return (MakeAppDoc*)m_pDocument;}

#endif //_DEBUG
