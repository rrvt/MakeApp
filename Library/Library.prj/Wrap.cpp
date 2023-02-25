// Wrap --


#include "pch.h"
#include "Wrap.h"


bool Wrap::operator() (double pos, String& s) {
int    threshold = 5 * extent / 8;
int    posWh;
int    posComma;
int    brkPt;
String word;

  if (!enabled) {frag = s;   s.clear();   return false;}

  word = findFirst(s);

  if (extent <= dvx.width(word)) {frag = s;   s.clear();   return false;}

  brkPt    = 0;

  posWh    = findLast(_T(' '), s);
  posComma = findLast(_T(','), s);

  if (posWh    > brkPt) brkPt = posWh;
  if (posComma > brkPt) brkPt = posComma;
  if (brkPt > 0) frag = s.substr(0, brkPt);

  if (dvx.width(frag) < threshold) {brkPt = findLastChar(s); frag = s.substr(0, brkPt);}
  if (frag.isEmpty())          {brkPt = s.length() / 2;  frag = s.substr(0, brkPt);}

  if (extent < maxExtent / 3) extent = maxExtent;

  s = s.substr(brkPt);  s.trimLeft();   return !s.isEmpty();
  }


String Wrap::findFirst(String& s) {
int pos = s.find(_T(' '));   if (pos < 0) pos = s.find(_T(','));   if (pos < 0) pos = s.length();

  return pos <= 0 ? String(_T("WWWWW")) : s.substr(0, pos);
  }


int Wrap::findLast(Tchar ch, String& s) {
int     i;
int     lng = s.size();
String  part;
CString cs;
int     lastPos = -1;

  for (i = 0; i < lng; i++) {
    if (s[i] == ch) {
      part = s.substr(0, i);

      if (dvx.width(part) > extent) break;

      lastPos = i;
      }
    }

  return lastPos;
  }


int Wrap::findLastChar(String& s) {
int     i;
int     lng = s.size();
String  part;
CString cs;

  for (i = 1; i <= lng; i++) {part = s.substr(0, i);    if (dvx.width(part) > extent) break;}

  return i-1;
  }


int Wrap::findLastWh(String& s, int noChars) {
int   lastPos = 0;
int   n = s.length();
int   i;

  n = n < noChars ? n : noChars;

  for (i = 0; i < n; i++) if (s[i] <= _T(' ')) lastPos = i;

  return lastPos;
  }



#if 0
if (0 < posWh && posWh < 100) {
  String u;   u.format(_T("posWh = %i"), posWh);
  messageBox(u);
  }
#endif
#if 1

#else
  add(i, t, pos);
  WrapData wd; wd.line = t;   if (i && pos > 0) {wd.indent = true;   wd.pos = pos;}

  data += wd;
#endif
#if 0
void Wrap::initialize(bool enable, CDC* pDC, int widthLeft, int maxWidth, bool isItalic)
       {enabled = enable; dc = pDC; extent = widthLeft; maxExtent = maxWidth; this->isItalic = isItalic;}

void Wrap::copy(Wrap& w) {
  enabled  = w.enabled;
  dc       = w.dc;
  extent   = w.extent;
  maxExtent= w.maxExtent;
  isItalic = w.isItalic;
  frag     = w.frag;
//  data     = w.data;
  }
#endif
//String t;
//int    i;
#if 0
void Wrap::add(int i, TCchar* line, double pos)
   {WrapData wd;   wd.line = line;   if (i && pos > 0) {wd.indent = true;   wd.pos = pos;}    data += wd;}
#endif
#if 0
// returns CString and width in current units

int Wrap::width(String& s) {
CSize   sz;
Cstring cs = s;   sz = dc->GetOutputTextExtent(cs);

  if (isItalic) sz.cx += 2;   return sz.cx;
  }
#endif

