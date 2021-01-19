// Enum Fonts


#pragma once
#include "Expandable.h"
#include "IterT.h"


struct FontAtr {
String name;
uint   fType;


  FontAtr() : fType(0) { }
  FontAtr(FontAtr& f) {copy(f);}
 ~FontAtr() { }

  //  *s = *p
  //  *p == *q
  //  *p >  *q
  //  *p <= *q

  FontAtr& operator=  (FontAtr& f) {copy(f); return *this;}
  bool     operator== (FontAtr& f) {return name == f.name;}
  bool     operator>  (FontAtr& f) {return name >  f.name;}
  bool     operator<= (FontAtr& f) {return name <= f.name;}

private:

  void copy(FontAtr& f) {name = f.name; fType = f.fType;}
  };


class ListFonts;
typedef IterT<ListFonts, FontAtr> LFIter;


class ListFonts {

bool                   dspFonts;

Expandable<FontAtr, 2> fonts;

LOGFONT         lf;
NEWTEXTMETRICEX ntm;
TEXTMETRIC      tm;
ENUMTEXTMETRIC  etm;
DWORD           fontType;
int             fontCount[3];

public:

  ListFonts() : fontCount{0, 0, 0} { }

  bool operator() (CDC* dc);

  int   nData()      {return fonts.end();}                       // returns number of fonts items in array

private:

  // returns either a pointer to fonts (or datum) at index i in array or zero

  FontAtr* datum(int i) {return 0 <= i && i < nData() ? &fonts[i] : 0;}       // or fonts[i].p

  void  removeDatum(int i) {if (0 <= i && i < nData()) fonts.del(i);}

  friend typename LFIter;
  friend BOOL CALLBACK EnumFamCallBack(LOGFONT* lf, NEWTEXTMETRIC* ntm, DWORD FontType, VOID* aFontCount);
  };


extern ListFonts listFonts;
