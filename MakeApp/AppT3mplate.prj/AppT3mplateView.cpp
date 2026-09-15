// AppT3mplateView.cpp : implementation of the AppT3mplateView class


#include "pch.h"
#include "AppT3mplateView.h"
#include "ClipLine.h"
#include "Invalidate.h"
#include "Resource.h"
#include "ResourceData.h"


static TCchar* StrOrietnKey = _T("Store");


IMPLEMENT_DYNCREATE(AppT3mplateView, ScrollView)

BEGIN_MESSAGE_MAP(AppT3mplateView, ScrollView)
  ON_COMMAND(ID_PrintFile,         &onFilePrint)
  ON_COMMAND(ID_PrintFilePreview,  &onFilePrintPreview)
  ON_COMMAND(ID_PrintSetup,        &onSetupPrinter)

  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONDBLCLK()

  ON_WM_CONTEXTMENU()                               // Right Mouse Popup Menu
  ON_COMMAND(ID_CopySel,           &onCopy)
  ON_COMMAND(ID_Pup1,              &onPup1)
  ON_COMMAND(ID_Pup2,              &onPup2)

END_MESSAGE_MAP()


AppT3mplateView::AppT3mplateView() noexcept : ScrollView(theApp.name) {
ResourceData res;
String       pn;

  sub.LoadMenu(IDR_RtMouseMenu);
  menu.CreatePopupMenu();
  menu.AppendMenu(MF_POPUP, (UINT_PTR) sub.GetSafeHmenu(), _T(""));

  sub.Detach();
  }


bool AppT3mplateView::onPreparePrinter(PrinterInfo& info)
                                                  {info.docName = _T("AppT3mplate");   return true;}


void AppT3mplateView::onFilePrint()        {printFile(true);}
void AppT3mplateView::onFilePrintPreview() {printFilePreview(true);}
void AppT3mplateView::onSetupPrinter()     {printerSetup();}


void AppT3mplateView::OnLButtonDown(UINT nFlags, CPoint point)
  {clipLine.set(point);   invalidate();   CScrollView::OnLButtonDown(nFlags, point);}


void AppT3mplateView::OnLButtonDblClk(UINT nFlags, CPoint point) {
  clipLine.set(point);   RedrawWindow();   clipLine.load();

  CScrollView::OnLButtonDblClk(nFlags, point);
  }


void AppT3mplateView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) {
CRect  rect;
CMenu* popup;
CWnd*  pWndPopupOwner = this;

  if (point.x == -1 && point.y == -1)
        {GetClientRect(rect);  ClientToScreen(rect);  point = rect.TopLeft();  point.Offset(5, 5);}

  popup = menu.GetSubMenu(0);   if (!popup) return;

  while (pWndPopupOwner->GetStyle() & WS_CHILD) pWndPopupOwner = pWndPopupOwner->GetParent();

  popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
  }


void AppT3mplateView::onCopy() {clipLine.load();  invalidate();}


void AppT3mplateView::onPup1() {  }


void AppT3mplateView::onPup2() {  }


// AppT3mplateView diagnostics

#ifdef _DEBUG
void AppT3mplateView::AssertValid() const          {CScrollView::AssertValid();}
void AppT3mplateView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
AppT3mplateDoc* AppT3mplateView::GetDocument() const {              // non-debug version is inline
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(AppT3mplateDoc)));
  return (AppT3mplateDoc*)m_pDocument;
  }
#endif //_DEBUG



