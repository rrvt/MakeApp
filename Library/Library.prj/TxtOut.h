// Text Out to a device


#pragma once
#include "ClipLine.h"
#include "Horiz.h"
#include "NewAllocator.h"
#include "NoteNmbr.h"
#include "TxtOps.h"
#include "UndrLn.h"
#include "Wrap.h"

class  DevCtx;
class  DevBase;
class  VertMgmt;


class TxtOut {

DevBase&  dev;
DevCtx&   dvx;                      // Device Context and all details related to DCD
VertMgmt& vert;

DevTabs   devTabs;

UndrLn    undrLn;

NoteNmbr  nmbr;

TxtOps*   ops;

public:

String    sum;
Horiz     horz;
bool      wrapEnabled;
bool      center;                            // center string horizonally in window when true;
bool      right;                             // right align in window when true;
bool      nonBlankLine;                  // true when first non blank line is encountered during printing

DevCtxBkp bkp;

  TxtOut(DevBase& d);
 ~TxtOut() { }

  void     initialize();

  void     clear();

  void     stg(TCchar* tc) {if (*tc) nonBlankLine = true;   sum += tc;}
  void     append(int   v) {String s;   s.format(_T("%li"),  v);    sum += s;}
  void     append(ulong v) {String s;   s.format(_T("%uli"), v);    sum += s;}
  void     cr()            {horz.cr();}
  void     crlf();
  void     flush()         {(*this)(NilAftr);}

  void     clearTabs()      {devTabs.clear();}
  void     setTab( int pos) {devTabs.setTab(horz, pos);}            // Insert an character position for
                                                                    // the next tab position
  void     setRTab(int pos) {devTabs.setRTab(horz, pos);}           // Insert an character position for
                                                                    // the next right
  void     tab()         {clipLine.setHzPos(horz.currentPos()); clipLine.close(dvx);}
  void     findNextTab() {devTabs.findNextTab(horz);  horz.position = devTabs.cur->pos;}

  DevTabs& getTabs()         {return devTabs;}
  void     restoreTabs(DevTabs& tm) {devTabs = tm;}

  void     doBeginULine(int yPos) {(*this)(BegULAfter, yPos);}
  void     doEndULine(  int yPos) {(*this)(EndULAftr,  yPos);}

  void     setBegin(long x, long y) {undrLn.setBegin(x, y);}
  void     setEnd(  long x, long y) {undrLn.setEnd(  x, y);}

  int      maxX()      {return horz.maxX();}

  void     set(NoteNmbr& nn) {nmbr = nn;}

  bool     operator() (AfterTxt after, double val = 0, TCchar* fontFace = 0);

private:

//  void setMetric();

  void allocOps(AfterTxt aftr, double aftrVal, TCchar* face);
  void freeOps();

  TxtOut() : dvx(*(DevCtx*)0), dev(*(DevBase*)0), vert(*(VertMgmt*)0), horz(*(Horiz*)0) { }

  friend class  TxtOutStk;
  friend struct TxtOps;
  };


struct TxtOutP {
TxtOut* p;

  TxtOutP() : p(0) { }
 ~TxtOutP() {p = 0;}

  void create(DevBase& d);
  void del();
  };


class TxtOutStk {

int     i;
TxtOutP txtOut[3];                     // Stack of text output contexts

public:

  TxtOutStk(DevBase& d);
 ~TxtOutStk();

  TxtOut* push();
  TxtOut* pop();
  };



//  TxtOut(TxtOut& txo) : dev(txo.dev) {dc = txo.dc; font = txo.font; sum = txo.sum;}

//  void copy(TxtOut& txo);

//  TxtOut& operator= (TxtOut& txo) {copy(txo); return *this;}
//  double   getFontScale()      {return font.scale;}
//  void     setFontScale(double scale) {font.scale = scale;}
//  void     doCrlf() {(*this)(DoCrlfAftr);}

//  void evalNmbr(NoteNmbr& nmbr);
//  void fragmentOut(String& s);

//  void clipTabInvert();
//  int  txtWidth(String& s);                       // returns CString and width in current units

//  void dcOut(int hzPos, String& s);
//  void outError(TCchar* stg);
// {NewAlloc(TxtOps);  if (!ops) ops = AllocNode;  if (p) {new(p) T(init);}}
//  void     setPosition();
//CDC*      dc;
//#include "FontMgr.h"
//  void     setWidth(int width);
//  void     setMargins();

//  void     clrFont()       {font.clear();}
//  int      lgChWidth() {return horz.lgChWidth();}
#if 0
  void     initContext();
  void     restoreContext();
#endif

