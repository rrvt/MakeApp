// Vertical Display Management


#include "pch.h"
#include "VertMgmt.h"
#include "MessageBox.h"


VertMgmt::VertMgmt(DevCtx& devCtx) : dvx(devCtx) {clear();}


void VertMgmt::clear() {y = yMax = topBnd = botBnd = 0;   beginPage = endPage = false;}


void VertMgmt::initBounds() {
double factor;

  factor = dvx.chHeight;   factor /= 2;

  topBnd = y = int(dvx.topMgn * factor);
  botBnd =     int(dvx.pgHeight - dvx.botMgn * factor);
  }


bool VertMgmt::lf(bool printing, bool footer) {

  if (printing && !footer && exceedsBnd()) {setEndPage(); return false;}

  y += maxHeight;   maxHeight = dvx.chHeight;   setMaxY(y);   return true;
  }



//  if (printing) maxLines = (botBnd - topBnd) / chHeight;   bool printing
//  if (printing && !footer && noLines > maxLines) maxLines = noLines;


//bool VertMgmt::exceedsBnd(int n)


//void VertMgmt::setEndPage() {setBottom(); endPage = true;}
#if 0
void VertMgmt::setHeight(CDC* dc) {
TEXTMETRIC metric;

  if (dc->GetTextMetrics(&metric)) {

    chHeight = metric.tmHeight + metric.tmExternalLeading + 2;

    if (chHeight > maxHeight) maxHeight = chHeight;

    uLineDelta = chHeight - metric.tmInternalLeading - metric.tmExternalLeading;
    }
  }
#endif


//void VertMgmt::setTopMargin(double v) {initY();}
//void VertMgmt::setBotMargin(double v) {initY();}

