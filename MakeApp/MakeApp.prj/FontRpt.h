// Font Report -- List all Fonts in CDC


#pragma once
#include "ReportBase.h"

class NotePad;


class FontRpt : public ReportBase {

public:

  FontRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~FontRpt() { }

 void display(CScrView& vw);

 virtual void dspHeader(DevBase& dev, int pageNo = 1) { }
 virtual void dspFooter(DevBase& dev, int pageNo = 1) { }

 void onBeginPrinting(CScrView& vw);

 virtual void prtHeader(DevBase& dev, int pageNo) { }
 virtual void prtFooter(DevBase& dev, int pageNo) { }

private:

  void getData(CScrView& vw);
  bool filter(TCchar* name);

  FontRpt() : ReportBase(*(NotePad*)0) { }
  };
