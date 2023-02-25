// Store Report -- Template for such a report


#include "pch.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


void StoreRpt::onBeginPrinting(CScrView& vw) {printing = true;   vw.disablePrtWrap();   getPageAttr(vw);}


void StoreRpt::getData(CScrView& vw) {
DSIter iter(store);
Datum* datum;
int    i;

  np.clear();   dateModified = store.lastModified;

  np << nClrTabs << nFSize(12) << nSetRTab(3) << nSetTab(5);

  for (i = 0, datum = iter(); datum; i++, datum = iter++) np << (*datum)() << nCrlf;
  }


void StoreRpt::prtHeader(DevBase& dev, int pageNo) {
String s = store.date() + _T(" ") + store.time();

  dev << dFSize(12);
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


