// Printer Device


#include "pch.h"
#include "DevPrntr.h"


void DevPrntr::prepare(TCchar* face, double fontSize, CDC* pDC, CPrintInfo* pInfo) {

  if (!pInfo) return;

  pInfo->m_bContinuePrinting = printing = true;    initialize(face, fontSize, pDC);

  dvx.dcDim();   initPageSize();   setBeginPage();
  }


bool DevPrntr::doEndPageChk() {

  if (vert.isEndPage()) {vert.atEndPageCond();  return true;}

  return false;
  }




