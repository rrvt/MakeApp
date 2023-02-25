// Report Base


#pragma once
#include "Date.h"

class CScrView;
class DevBase;
class NotePad;



class ReportBase {
protected:

NotePad& np;

String   title;
int      maxPages;
Date     dateModified;

bool     printing;

public:
               ReportBase(NotePad& notePad) : np(notePad), maxPages(0), printing(false) { }
              ~ReportBase() { }

          void setTitle(TCchar* t) {title = t;}

  virtual void display(CScrView& vw);

  virtual void dspHeader(DevBase& dev, int pageNo = 1) { }
  virtual void dspFooter(DevBase& dev, int pageNo = 1) { }

  virtual void prtHeader(DevBase& dev, int pageNo);
  virtual void prtFooter(DevBase& dev, int pageNo);

protected:

          void getPageAttr(CScrView& vw);

  virtual void getData(CScrView& vw) = 0;

private:

  ReportBase() : np(*(NotePad*)0) { }
  };



//  virtual int  header(NotePad& np, bool printing) = 0;
/*noLines(0), maxLines(0),*/
//int      noLines;
//int      maxLines;


  //class ReportBase;
  //typedef IterT<ReportBase, RBtab> RbTbIter;
  // returns either a pointer to data (or datum) at index i in array or zero

//  RBtab* datum(int i) {return 0 <= i && i < nData() ? &tabs[i] : 0;}       // or data[i].p

//  int    nData()      {return tabs.end();}                       // returns number of data items in array

//  void   removeDatum(int i) {if (0 <= i && i < nData()) tabs.del(i);}

//  friend typename RbTbIter;

//Expandable<RBtab, 8> tabs;     tabs.clear();
#if 0
struct RBtab {
int  pos;
bool right;

public:

  RBtab() : pos(0), right(false) { }
  RBtab(RBtab& tb) {copy(tb);}
 ~RBtab() { }

  RBtab& operator= (RBtab& tb) {copy(tb); return *this;}

  bool  operator== (RBtab& tab) {return pos == tab.pos;}
  bool  operator>= (RBtab& tab) {return pos >= tab.pos;}

private:

  void copy(RBtab& tb) {pos = tb.pos; right = tb.right;}
  };
#endif
//#include "Expandable.h"
//#include "IterT.h"

