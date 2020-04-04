// File Data


#pragma once
#include "Expandable.h"


//  *p == *q
//  *p >  *q
//  *p <= *q
//  *s = *p

class Datum {
public:

String line;

  Datum() { }
 ~Datum() { }

  Datum& operator=  (Datum& d) {line = d.line; return *this;}
  bool   operator== (Datum& d) {return _tcsicmp(line, d.line) == 0;};
  bool   operator>  (Datum& d) {return _tcsicmp(line, d.line)  > 0;};
  bool   operator<= (Datum& d) {return _tcsicmp(line, d.line) <= 0;};
  };


extern Expandable<Datum, 1024> fData;

