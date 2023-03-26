// Store Report -- Template for such a report


#include "pch.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


void StoreRpt::display(CScrView& vw) {printing = false;   vw.enableDplWrap();   getData(vw);}


void StoreRpt::onPreparePrinting(CPrintInfo* info) {printer.set(prtrOrietn);}


void StoreRpt::onBeginPrinting(CScrView& vw) {printing = true;   vw.enablePrtWrap();   getPageAttr(vw);}


void StoreRpt::getData(CScrView& vw) {
DSIter iter(store);
Datum* datum;
int    i;

  np.clear();   dateModified = store.lastModified;

  np << nClrTabs << nFSize(12) << nSetRTab(3) << nSetTab(5);

  for (i = 0, datum = iter(); datum; i++, datum = iter++) {
    np << nTab << i << nTab << (*datum)() << nCrlf;
    }
  }


void StoreRpt::prtHeader(DevBase& dev, int pageNo) {
String s = store.date() + _T(" ") + store.time();

  dev << dClrTabs << dSetRTab(3) << dSetTab(5);
  dev << dTab    << dBold      << _T("No")   << dFont;
  dev << dCenter << dItalic    << store.name << dFont;
  dev << dRight  << dUnderLine << s          << dFont;
  dev << dCrlf << dCrlf;
  }


void StoreRpt::prtFooter(DevBase& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dCenter << pageN << _T(" of ") << maxPages << dFlushFtr;
  }


