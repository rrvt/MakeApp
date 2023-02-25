// Print Device


#pragma once
#include "DevPrntr.h"
#include "ToDevBase.h"


class NtPdToPrtr : public ToDevBase {

DevPrntr dev;

public:
           NtPdToPrtr(NotePad& np) : ToDevBase(np, dev) { }    //src,  TCchar* src,
          ~NtPdToPrtr() { }

  void     prepare(TCchar* font, double fontSize, CDC* pDC, CPrintInfo* pInfo)
                                                                {dev.prepare(font, fontSize, pDC, pInfo);}
  bool     isEndDoc()   {return endDoc;}

  void     suppressOutput() {dev.suppressOutput();}
  void     negateSuppress() {dev.negateSuppress();}
  void     disableWrap()    {dev.disableWrap();}
  void     enableWrap()     {dev.enableWrap();}

//  void     clrLines()       {dev.clrLines();}
//  int      getMaxLines()    {return dev.getMaxLines();}

private:

  NtPdToPrtr() : ToDevBase(*(NotePad*)0, *(DevBase*)0) { }
  };

