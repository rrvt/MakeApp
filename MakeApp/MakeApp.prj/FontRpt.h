// Font Report -- List all Fonts in CDC


#pragma once
//#include "ReportBase.h"

class NotePad;


class FontRpt {

public:

  FontRpt(NotePad& notePad) { }
 ~FontRpt() { }

#if 0
  void display(CScrView& vw);

  void dspHeader(DevStream& dev, int pageNo = 1) { }
  void dspFooter(DevStream& dev, int pageNo = 1) { }

  void onBeginPrinting(CScrView& vw);

  void prtHeader(DevStream& dev, int pageNo) { }
  void prtFooter(DevStream& dev, int pageNo) { }
#endif
private:

  void getData();
  bool filter(TCchar* name);

//  FontRpt() : ReportBase(*(NotePad*)0, ReportID) { }
  };
