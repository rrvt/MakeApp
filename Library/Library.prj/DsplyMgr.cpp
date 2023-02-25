// Display Manager -- needed to isolate variables from Print Management


#include "pch.h"
#include "DsplyMgr.h"
#include "CScrView.h"
#include "DevTabs.h"


void DsplyMgr::OnPrepareDC(CDC* dc) {

  displayOut.clear();

  displayOut.prepare(font, fontSize, dc);

  displayOut.setHorzMgns(leftMargin, rightMargin);   displayOut.setVertMgns(topMargin, botMargin);

  vw.onDisplayOutput();   displayOut.startDev();
  }


// CScrView drawing,  Override

void DsplyMgr::OnDraw(CDC* pDC) {
DevBase& dev = displayOut.getDev();

  dev.startContext();   vw.displayHeader(dev);   dev.endContext();

    dev.disableWrap();   displayOut();

  dev.setFooter();   vw.displayFooter(dev);  dev.clrFooter();

  setScrollSize();
  }


void DsplyMgr::setScrollSize() {
RECT  winSize;
int   height = displayOut.chHeight();
int   t      = 1;
CSize scrollViewSize;
CSize pageSize;
CSize scrollSize;

  vw.GetClientRect(&winSize);

  if (height) {t = (winSize.bottom - 1) / height; t *= height;}

  pageSize.cy = t; pageSize.cx = winSize.right;

  scrollSize.cx = displayOut.lgChWidth();   scrollSize.cy = height;

  displayOut.getMaxPos(scrollViewSize.cx, scrollViewSize.cy);

  vw.SetScrollSizes(MM_TEXT, scrollViewSize, pageSize, scrollSize);
  }

