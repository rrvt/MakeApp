// Printer Device

#pragma once

#include "DevBase.h"


class DevPrntr : public DevBase {

public:

  DevPrntr() : DevBase() { }         //TCchar* src  src
 ~DevPrntr() { }

  void     prepare(TCchar* face, double fontSize, CDC* pDC, CPrintInfo* pInfo);

  bool     doEndPageChk();
  void     atEndPageCond()   {vert.atEndPageCond();}

private:

          void     initializeFrame(CPrintInfo* pInfo);
  };



//  int      maxLines() {return vert.getMaxLines();}
//  virtual DevBase& append(Wrap& w);
//          void     setEndPage() {vert.setEndPage();}
//  void     clrLines()        {vert.clrLines();}
//  int      getMaxLines() {return vert.getMaxLines();}

