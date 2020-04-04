// MakeAppView.cpp : implementation of the MakeAppView class


#include "stdafx.h"
#include "MakeAppView.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "DisplayView.h"
#include "Display.h"
#include "NotePad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrollView)

BEGIN_MESSAGE_MAP(MakeAppView, CScrollView)
  // Standard printing commands
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()


// MakeAppView construction/destruction

MakeAppView::MakeAppView() noexcept : font(_T("Arial")), author(_T("sde")) { }


MakeAppView::~MakeAppView() { }


BOOL MakeAppView::PreCreateWindow(CREATESTRUCT& cs) {return CScrollView::PreCreateWindow(cs);}


void MakeAppView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb)
                                                            {CScrollView::OnVScroll(nSBCode, nPos, sb);}


void MakeAppView::OnInitialUpdate() {CScrollView::OnInitialUpdate();}


void MakeAppView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
                                  {setScrollSize(dspView); CScrollView::OnUpdate(pSender, lHint, pHint);}


// MakeAppView printing
/* The following functions are called for printing a page in the order given with one exception:
BOOL OnPreparePrinting(        CPrintInfo* pInfo);  -- 1st
void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);  -- 2nd
     CDC::StartDoc()                                -- 3rd
void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo);  -- 4th                         <-
     CDC::StartPage()                               -- 5th                          ^
void OnPrint(        CDC* pDC, CPrintInfo* pInfo);  -- 6th                          ^
     CDC::EndPage()                                 -- 7th then loops for each page ^
     CDC::EndDoc()                                  -- after last page
void OnEndPrinting(  CDC* pDC, CPrintInfo* pInfo);  -- last
*/

BOOL MakeAppView::OnPreparePrinting(CPrintInfo* pInfo) {
BOOL rslt;

  pInfo->m_nNumPreviewPages = 0;

  prtView.OnPreparePrinting(pInfo);

  rslt = DoPreparePrinting(pInfo);                  // Get printer dialog box

  return rslt;
  }


void MakeAppView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
                       {Date d;   d.getToday();  prtView.OnBeginPrinting(pDC, pInfo, author, d);}


void MakeAppView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
DisplayView* dv = pInfo ? &prtView : &dspView;

  dv->OnPreparePrinting(pInfo);

  CScrollView::OnPrepareDC(pDC, pInfo);

  dv->OnPrepareDC(font, 120, pDC, pInfo);
  }


void MakeAppView::OnPrint(CDC* pDC, CPrintInfo* pInfo) {prtView.OnPrint(pInfo);}


void MakeAppView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {if (!pInfo->m_bPreview) invalidate();}


// MakeAppView drawing

void MakeAppView::OnDraw(CDC* pDC) {dspView.OnDraw(); setScrollSize(dspView);}


void MakeAppView::setScrollSize(DisplayView& dv) {
RECT  winSize;
CSize s;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize); dv.getScrollSize(winSize, s, pageSize, scrollSize);

  SetScrollSizes(MM_TEXT, s, pageSize, scrollSize);
  }


// MakeAppView diagnostics

#ifdef _DEBUG
void MakeAppView::AssertValid() const
{
  CScrollView::AssertValid();
}

void MakeAppView::Dump(CDumpContext& dc) const
{
  CScrollView::Dump(dc);
}

MakeAppDoc* MakeAppView::GetDocument() const // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc)));
  return (MakeAppDoc*)m_pDocument;
}
#endif //_DEBUG


// MakeAppView message handlers
