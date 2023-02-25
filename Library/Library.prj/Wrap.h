// Wrap --


#pragma once
#include "DevCtx.h"


class Wrap {
bool    enabled;
DevCtx& dvx;
int     extent;
int     maxExtent;
bool    isItalic;

String frag;

public:

  Wrap(DevCtx& devCtx) : enabled(false), dvx(devCtx), extent(0), maxExtent(0), isItalic(false) { }
  Wrap(bool enable, DevCtx& devCtx, int widthLeft, int maxWidth, bool italic) :
                enabled(enable), dvx(devCtx), extent(widthLeft), maxExtent(maxWidth), isItalic(italic) { }
 ~Wrap() { }

  void    set(bool enable, int widthLeft, int maxWidth)
             {enabled = enable; extent = widthLeft; maxExtent = maxWidth; isItalic = dvx.isFontItalic();}

  void    clear() {enabled = false; extent = maxExtent = 0; isItalic = false;}

  bool    operator() (double pos, String& s);

  String& stg() {return frag;}

private:

  String findFirst(String& s);
  int    findLast(Tchar ch, String& s);
  int    findLastChar(String& s);
//  int    width(String& s);

  int    findLastWh(String& s, int noChars);
  };




//  Wrap(Wrap& w) {copy(w);}
//  Wrap& operator= (Wrap& w) {copy(w); return *this;}
//  void initialize(bool enable, CDC* pDC, int widthLeft, int maxWidth, bool isItalic);
//  void   add(int i, TCchar* line, double pos);
//  void   copy(Wrap& w);
#if 0
struct WrapData {
bool   indent;
double pos;
String line;

  WrapData() : indent(false), pos(0) { }
  WrapData(WrapData& wd) {copy(wd);}
 ~WrapData() {line.clear();}

  WrapData& operator= (WrapData& wd) {copy(wd); return *this;}

private:

  void copy(WrapData& wd) {indent = wd.indent; pos = wd.pos; line = wd.line;}
  };
#endif
//CDC*    dc;

