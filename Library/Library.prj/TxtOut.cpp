// Text Out to a device


#include "pch.h"
#include "TxtOut.h"
#include "DevBase.h"
#include "Horiz.h"
#include "VertMgmt.h"


TxtOut::TxtOut(DevBase& d) : dev(d), dvx(d.dvx), vert(d.vert), ops(0), horz(dvx),
                             wrapEnabled(false), center(false), right(false), nonBlankLine(false) { }


void TxtOut::initialize() {

  undrLn.clear();   nmbr.clear();   sum.clear();   wrapEnabled = center = right = nonBlankLine = false;
  }


void TxtOut::clear() {

  devTabs.clear();   undrLn.clear();   freeOps();

  sum.clear();   horz.clear();   wrapEnabled = center = right = false;

  nonBlankLine = true;
  }


void TxtOut::crlf() {dev.lf();   cr();   clipLine.setHzPos(horz.currentPos()); clipLine.close(dvx);}


bool TxtOut::operator() (AfterTxt after, double val, TCchar* tc) {

  allocOps(after, val, tc);

  if (!sum.empty()) {

    dev.incPageNo();

    ops->setPosition(sum);

    ops->start(wrapEnabled);

    if (!(*ops)(sum)) return false;
    }

  ops->afterTxtOut();   freeOps();   return true;
  }


void TxtOut::allocOps(AfterTxt aftr, double aftrVal, TCchar* face)
                        {NewAlloc(TxtOps);  if (!ops) ops = AllocNodeI4(*this, aftr, aftrVal, face);}


void TxtOut::freeOps()  {NewAlloc(TxtOps);  FreeNode(ops);   ops = 0;}


// Stack logic

TxtOutStk::TxtOutStk(DevBase& d) : i(-1)
                                      {for (int j = 0; j < noElements(txtOut); j++) txtOut[j].create(d);}


void TxtOutP::create(DevBase& d) {NewAlloc(TxtOut);  if (!p) p = AllocNodeI1(d);}


TxtOutStk::~TxtOutStk() {for (int i = 0; i < noElements(txtOut); i++) txtOut[i].del();}


void TxtOutP::del() {
//  messageBox(this, sizeof(*this));   if (p) messageBox(p, sizeof(TxtOut));

  NewAlloc(TxtOut);  if (p) FreeNode(p);
  }


TxtOut* TxtOutStk::push() {
TxtOut* cur = i >= 0 ? txtOut[i].p : 0;
TxtOut* p;
  i++; p = 0 <= i && i < noElements(txtOut) ? txtOut[i].p : 0;
  if (p) {
    p->devTabs.clear();
    p->undrLn.clear();
    p->nmbr.clear();
    p->freeOps();
    p->sum.clear();
    p->horz.initialize();
    p->wrapEnabled  = cur ? cur->wrapEnabled : false;
    p->center       = false;
    p->right        = false;
    p->nonBlankLine = cur ? cur->nonBlankLine : false;
    }

  return p;
  }

TxtOut* TxtOutStk::pop()  {i--;   return 0 <= i && i < noElements(txtOut) ? txtOut[i].p : 0;}






#if 0
void TxtOut::initContext()
  {clear();   dvx.setFont(dev.baseFont, dev.baseFontSize, dev.fontScale);   setMetric();}

void TxtOut::restoreContext() {dvx.restoreFontCtx();   dev.clearMaxHeight();   setMetric();}
#endif


//void TxtOut::setMetric() {vert.initBounds();}
