// Store Report -- Template for such a report


#include "stdafx.h"
#include "StoreRpt.h"
#include "CScrView.h"
#include "Store.h"


void StoreRpt::print(CScrView& vw) {

  maxLines = vw.noLinesPrPg();

  vw.disableWrap();

  detNoPages(vw);

  create();
  }


void StoreRpt::create() {
DSIter iter(store);
Data*  datum;
int    i;

  np.clear();   noLines = BigNmbr;                      // Skip first header

  for (i = 0, datum = iter(); datum; i++, datum = iter++) {

    if (noLines + 1 > maxLines) {

      if (i) np << nEndPage;

      header();  np << nClrTabs << nSetTab(10);
      }

    np << datum->get() << nCrlf;   noLines += 1;
    }
  }


void StoreRpt::header() {
String s = store.date() + _T(" ") + store.time();

  np << store.name << nRight << s << nCrlf << nCrlf;   noLines =  2;
  }


void StoreRpt::footer(Display& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dRight << pageN << _T(" of ") << maxPages << dflushFtr;
  }





//void StoreRpt::display(CScrView& vw) {detWraps(vw);   vw.disableWrap();   create();}


#if 0
void StoreRpt::detWraps(CScrView& vw& vw) {
Display& dev = vw.getDev();
CDC*     dc  = dev.getDC();
DSIter   iter(store);
Data*    datum;

  for (datum = iter(); datum; datum = iter++) datum->wrap(dev, dc);
  }
#endif

