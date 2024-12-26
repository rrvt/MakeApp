// Store Report -- Template for such a report


#pragma once
#include "ReportBase.h"


class StoreRpt : public ReportBase {

public:

  StoreRpt(NotePad& notePad) : ReportBase(notePad, ReportID) { }
 ~StoreRpt() { }

  void dspHeader(DevStream& dev, int pageNo = 1) {prtHeader(dev, pageNo);}
  void dspFooter(DevStream& dev, int pageNo = 1) {prtFooter(dev, pageNo);}

  void display(CScrView& vw);

  void onPreparePrinting(CPrintInfo* info);
  void onBeginPrinting(CScrView& vw);

  void prtHeader(DevStream& dev, int pageNo = 1);
  void prtFooter(DevStream& dev, int pageNo);

private:

  void getData();

  StoreRpt() : ReportBase(*(NotePad*)0, ReportID) { }
  };

