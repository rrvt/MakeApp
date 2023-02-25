// DisplayDevice


#include "pch.h"
#include "DevDsply.h"


void DevDsply::prepare(TCchar* face, double fontSize, CDC* pDC) {
//RECT  winSz;

  printing = false;   initialize(face, fontSize, pDC);

//  pDC->GetWindow()->GetClientRect(&winSz);   initPageSize(winSz.right, winSz.bottom);

  dvx.wdwDim();  initPageSize();
  }






#if 1
#else
//#include "ClipLine.h"
  sum.clear(); noPoints = 0;

  center = right = rightTab.right = false;

  initializeFont(face, fontSize);
#endif
#if 1
#else
  vert.setAttributes(cy, topMargin,  botMargin);
  hz.setAttributes(  cx, leftMargin, rightMargin);    hz.clrTabs();
#endif
#if 1
#else
  //CWnd* win     = 0;
  //int   cx      = 0;
  //int   cy      = 0;
  win = pDC->GetWindow(); win->GetClientRect(&winSz);
  //  cy = winSz.bottom; cx = winSz.right;
#endif

