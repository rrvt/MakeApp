// Print Manager -- needed to isolate variables from Display Management!


#include "pch.h"
#include "PrintMgr.h"
#include "CApp.h"
#include "CScrView.h"
#include "Printer.h"

/* Doc/View Framework Calls to implement printing
     CMyView::OnPreparePrinting    o Set length of doc if known
             |                     o Call DoPreparePrining to display Print dialog box which creates DC
             V
     CMyView::OnBeginPrinting      o Set length of document based on DC
             |                     o Allocate DGI resources
             V
         CDC::StartDoc
             |
             V
  |->CMyView::OnPrepareDC          o Change DC attributes
  |          |                     o Check for end of document
  |          V
  |      CDC::StartPage
  |          |
  |          V
  |  CMyView::OnPrint              o Print specified page, including Headers and Footers
  |          |
  |          V
  -------CDC::EndPage
             |
             V
         CDC::EndDoc
             |
             V
     CMyView::OnEndPrinting        o Deallocate GDI resources
*/

/* The following functions are called for printing a page in the order given with one exception:
BOOL OnPreparePrinting(        CPrintInfo* pInfo);  -- 1st                    // handled by CScrView
void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);  -- 2nd
     CDC::StartDoc()                                -- 3rd
void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo);  -- 4th
     CDC::StartPage()                               -- 5th
void OnPrint(        CDC* pDC, CPrintInfo* pInfo);  -- 6th
     CDC::EndPage()                                 -- 7th then loops for each page
     CDC::EndDoc()                                  -- after last page
void OnEndPrinting(  CDC* pDC, CPrintInfo* pInfo);  -- last
*/


PrintMgr::PrintMgr(CScrView& view) : ShowMgr(view, npd, pageOut), pageOut(npd), cdc(0), pinfo(0),
                                     endPrinting(false), pageNo(0) { }


void PrintMgr::clear() {
  npd.clear();   pageOut.clear();   cdc = 0;   pinfo = 0;   endPrinting = false;
  leftFooter.clear();   date.clear();   pageNo = 0;
  }



void PrintMgr::OnBeginPrinting(CDC* dc, CPrintInfo* info) {

  clear();   cdc = dc;   pinfo = info;

  init(dc, info);    preparePrinter(dc, info);

  vw.onBeginPrinting();   pageOut.startDev();
  }


void PrintMgr::OnPrepareDC(CDC* dc, CPrintInfo* info) {                       // Override

  preparePrinter(dc, info);

  if (info->m_bPreview) findNextPreviewPage(dc, info);
  }



void PrintMgr::init(CDC* dc, CPrintInfo* info) {
DEVMODE devMode;

  memset(&devMode, 0, sizeof(devMode));   dc->ResetDC(&devMode); // sets the Addtribut devmode parameter

  info->m_bContinuePrinting = true;     endPrinting = false;

  info->m_nNumPreviewPages = 1;

  info->SetMinPage(1);   info->SetMaxPage(9999);

  pageOut.clear();

  pageOut.prepare(font, fontSize, dc, info);

  pageOut.setVertMgns(printer.topMargin, printer.botMargin);
  }


// Initialize dc for printer and other initialization, called for each page

void PrintMgr::preparePrinter(CDC* dc, CPrintInfo* info) {
double  leftMgn;
double  rightMgn;

  pageNo = info->m_nCurPage;
  leftMgn  = pageNo & 1 ? printer.leftOdd  : printer.leftEven;
  rightMgn = pageNo & 1 ? printer.rightOdd : printer.rightEven;

  pageOut.setHorzMgns(leftMgn, rightMgn);
  }


// Find the next preview page by suppressing the output of preceding pages.
// The OnPrint function is used to output to the preview window.

void PrintMgr::findNextPreviewPage(CDC* dc, CPrintInfo* info) {
uint i;

  pageOut.suppressOutput();   pageOut.startDev();

  for (i = 1; i < info->m_nCurPage; i++) {

    onePageOut();
    }

  pageOut.negateSuppress();
  }


// Draw on Printer (i.e. Output to Printer) -- Called by Windows after OnPrepareDC (thru CScrView)

void PrintMgr::OnPrint(CDC* dC, CPrintInfo* info)
                                    {onePageOut();   if (isFinishedPrinting(info)) {endPrinting = true;}}


// To determine number of pages

int  PrintMgr::getNoPages() {
uint     i;

  pageOut.startDev();

  pageOut.suppressOutput();    //if (wrapEnabled) pageOut.enableWrap(); else pageOut.disableWrap();

  pageOut.prepare(font, fontSize, cdc, pinfo);

  for (i = 0; !pageOut.isEndDoc(); i++) onePageOut();

//  pageOut.clrFont();

  pageOut.negateSuppress(); return i;
  }


void PrintMgr::onePageOut() {
DevBase& dev = pageOut.getDev();

  dev.setBeginPage();   if (wrapEnabled) dev.enableWrap(); else dev.disableWrap();

  dev.startContext();   vw.printHeader(dev, pageNo);   dev.endContext();

    pageOut();

  dev.setFooter();      vw.printFooter(dev, pageNo);   dev.clrFooter();
  }


// The most secure way to cease printed output is to change the continuePrinting value in the printer
// info structure from true to false.  This function determinse that by examining the progress of the
// passage through the NotePad list of entities.

bool PrintMgr::isFinishedPrinting(CPrintInfo* info) {
bool fin = pageOut.isEndDoc();

  if (info) {info->m_bContinuePrinting = !fin;   if (fin) info->SetMaxPage(info->m_nCurPage);}

  return fin;
  }




#if 1
#else
    pageOut.setBeginPage();

    dev.startContext();   vw.printHeader(dev, pageNo);   dev.endContext();

      pageOut();

    dev.setFooter();    vw.printFooter(dev, pageNo);   dev.clrFooter();
#endif
#if 1
#else
  if (wrapEnabled) dev.enableWrap(); else dev.disableWrap();

  dev.startContext();   vw.printHeader(dev, info->m_nCurPage);    dev.endContext();

    pageOut.setBeginPage();   pageOut();

  dev.setFooter();   vw.printFooter(dev, info->m_nCurPage);   dev.clrFooter();
#endif
//DevBase& dev = pageOut.getDev();    pageOut.clrLines();
//DevBase& dev = pageOut.getDev();
#if 1
#else
    if (wrapEnabled) pageOut.enableWrap(); else pageOut.disableWrap();

    pageOut.setBeginPage();   pageOut();

//    if (!isFinishedPrinting(info)) pageOut.prepare(font, fontSize, dc, info);
#endif
  /*pageOut.setBeginPage();*/
#if 0
  info->m_bContinuePrinting = true;     endPrinting = false;

  info->m_nNumPreviewPages = 1;

  info->SetMinPage(1);   info->SetMaxPage(9999);
#endif

