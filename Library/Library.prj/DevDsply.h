// Display Device


#pragma once

#include "DevBase.h"


class DevDsply : public DevBase {

public:

       DevDsply() : DevBase() { }
      ~DevDsply() { }

  void prepare(TCchar* face, double fontSize, CDC* pDC);

  void getMaxPos(long& maxX, long& maxY) {maxY = txt->maxX(); maxY = vert.maxY();}
  };


