// NotePad Report -- the data is stored in the global notePad


#pragma once
#include "ReportBase.h"


class Note;


class NotePadRpt : public ReportBase {

public:
               NotePadRpt(NotePad& notePad) : ReportBase(notePad) { }
              ~NotePadRpt() { }

  virtual void onBeginPrinting(CScrView& vw);

  virtual void dspHeader(DevBase& dev, int pageNo = 1) { }
  virtual void dspFooter(DevBase& dev, int pageNo = 1) { }

  virtual void prtHeader(DevBase& dev, int pageNo);
  virtual void prtFooter(DevBase& dev, int pageNo);

protected:

  virtual void getData(CScrView& vw);

private:

  NotePadRpt() : ReportBase(*(NotePad*)0) { }
  };



//  void detWraps(  CScrView& vw);                  // Wrap each entity in the report body

//  void detNoPages(CScrView& vw);                  // Performs a dummy printer output to determine the
//  void display(CScrView& vw);
#if 0
  virtual void saveTab(Note& note);
  virtual void restoreTabs();
#endif
//  virtual int  header(NotePad& np, bool printing);


