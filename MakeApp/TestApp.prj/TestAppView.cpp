// TestAppView.cpp : implementation of the TestAppView class


#include "stdafx.h"
#include "TestAppView.h"
#include "TestAppDoc.h"


// TestAppView

IMPLEMENT_DYNCREATE(TestAppView, CScrView)

BEGIN_MESSAGE_MAP(TestAppView, CScrView)
END_MESSAGE_MAP()



// TestAppView diagnostics

#ifdef _DEBUG

void TestAppView::AssertValid() const {CScrollView::AssertValid();}

void TestAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
TestAppDoc* TestAppView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(TestAppDoc))); return (TestAppDoc*)m_pDocument;}

#endif //_DEBUG
