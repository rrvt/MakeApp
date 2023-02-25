// Print Manager -- needed to isolate variables from Display Management!


#pragma once
#include "Printer.h"
#include "NtPdToPrtr.h"
#include "ShowMgr.h"

class CScrView;


class PrintMgr : public ShowMgr {

NotePad     npd;
NtPdToPrtr  pageOut;

CDC*        cdc;                      // Capture during initialization for convenience
CPrintInfo* pinfo;

bool        endPrinting;              // Flag to end printing

String      leftFooter;               // Data to print at right side of footer
Date        date;                     // Date to print at left edge of footer

int         pageNo;

public:

  PrintMgr(CScrView& view);
 ~PrintMgr() { }

  void clear();

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
  void       OnBeginPrinting(CDC* dc, CPrintInfo* info);
  void       OnPrepareDC(    CDC* dc, CPrintInfo* info);
  void       OnPrint(        CDC* dC, CPrintInfo* info);
  void       OnEndPrinting(  CDC* dc, CPrintInfo* info) {clear();}

  // Utilities
  void       startDev() {if (!endPrinting) pageOut.startDev();}
//  int        noLinesPrPg() {return pageOut.getMaxLines();}

  int        getNoPages();

private:

  void       init(               CDC* dc, CPrintInfo* info);
  void       preparePrinter(     CDC* dc, CPrintInfo* info);
  void       findNextPreviewPage(CDC* dc, CPrintInfo* info);
  void       onePageOut();
  bool       isFinishedPrinting(CPrintInfo* info);

  PrintMgr() : ShowMgr(*(CScrView*)0, *(NotePad*)0, *(NtPdToPrtr*)0), pageOut(*(NotePad*)0) { }
  };


