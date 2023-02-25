// NotePad
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.

#include "pch.h"
#include "NotePad.h"
#include "TextPosition.h"


NotePad notePad;


static NtManipInt& setupManipInt(NtManipInt::Func func, int     val);
static NtManipDbl& setupManipDbl(NtManipDbl::Func func, double  val);
static NtManipStg& setupManipStg(NtManipStg::Func func, TCchar* val);

NoteManip nClrTabs;         // add to stream to clear tabs:                  dsp << dClrTabs;
NoteManip nCrlf;            // add to stream to terminate a line on display: dsp << "xyz" << dCrlf;
NoteManip nEndPage;         // add to stream to terminate page when printing otherwise ignore
NoteManip nTab;             // add to stream to tab to next tab position:    dsp << dTab << "xyz";
NoteManip nCenter;          // Set bit to center from here to crlf;
NoteManip nRight;           // Set bit to right align from here to crlf;
NoteManip nBeginLine;       // Begin and end line under text.
NoteManip nEndLine;
NoteManip nDebug;
NoteManip nFont;            // set previous font
NoteManip nBold;            // set font to bold
NoteManip nItalic;          // set font to italic
NoteManip nUnderLine;       // underline font
NoteManip nStrikeOut;       // strike out font

NtManipInt& nSetLMargin(int val) {return setupManipInt(NotePad::doSetLMargin, val);}
NtManipInt& nSetTab(    int val) {return setupManipInt(NotePad::doSetTab,     val);}
NtManipInt& nSetRTab(   int val) {return setupManipInt(NotePad::doSetRTab,    val);}

NtManipInt& nSetWidth(  int val) {return setupManipInt(NotePad::doSetWidth,   val);}
NtManipInt& nSetPrec(   int val) {return setupManipInt(NotePad::doSetPrec,    val);}
NtManipStg& nFFace( TCchar* face){return setupManipStg(NotePad::doFFace,      face);}
NtManipDbl& nFSize(  double val) {return setupManipDbl(NotePad::doFSize,      val);}

NtManipInt& setupManipInt(NtManipInt::Func func, int val)
          {NewAlloc(NtManipInt);   NtManipInt* m = AllocNode;  m->set(func, val); return *m;}

NtManipDbl& setupManipDbl(NtManipDbl::Func func, double val)
          {NewAlloc(NtManipDbl);   NtManipDbl* m = AllocNode;  m->set(func, val); return *m;}

NtManipStg& setupManipStg(NtManipStg::Func func, TCchar* val)
          {NewAlloc(NtManipStg);   NtManipStg* m = AllocNode;  m->set(func, val); return *m;}


NotePad::NotePad() : arWidth(106), tabFactor(1.0) {clear();}


// To clear notepad for new input.

void NotePad::clear() {noteList.removeAll(); note = 0; initialize();}


void NotePad::initialize() {

  nClrTabs.n   = this; nClrTabs.func   = NotePad::doClrTabs;
  nTab.n       = this; nTab.func       = NotePad::doTab;

  nCrlf.n      = this; nCrlf.func      = NotePad::doCrlf;
  nEndPage.n   = this; nEndPage.func   = NotePad::doEndPage;
  nCenter.n    = this; nCenter.func    = NotePad::doCenter;
  nRight.n     = this; nRight.func     = NotePad::doRight;
  nBeginLine.n = this; nBeginLine.func = NotePad::doBeginLine;
  nEndLine.n   = this; nEndLine.func   = NotePad::doEndLine;
  nDebug.n     = this; nDebug.func     = NotePad::doDebug;
  nFont.n      = this; nFont.func      = NotePad::doPrevFont;
  nBold.n      = this; nBold.func      = NotePad::doBoldFont;
  nItalic.n    = this; nItalic.func    = NotePad::doItalicFont;
  nUnderLine.n = this; nUnderLine.func = NotePad::doUnderLineFont;
  nStrikeOut.n = this; nStrikeOut.func = NotePad::doStrikeOutFont;

  noLines = 0;
  }


void NotePad::archive(Archive& ar) {
NtPdIter     iter(*this);
Note*        note;
TextPosition tPos;
Tab          tab;
bool         hasTab;
bool         rightTab;
int          cnt;

  for (note = iter(); note; note = iter++) {

    if (note->clrTabs)   tPos.clrTabs();
    if (note->tabValue)  tPos.setTab(applyTabFactor(note->tabValue), note->rightTab);

    hasTab = note->tab;

    if (hasTab) {
      tab = tPos.findNextTab();   rightTab = tab.right;

      if (!rightTab) movPos(tPos, tab.pos, ar);
      }

    if (note->right) {
      tab.pos = arWidth; tab.right = rightTab = hasTab = true;
      }

    cnt = note->line.length();

    if (note->center) movPos(tPos, (arWidth - cnt) / 2, ar);

    if (hasTab && rightTab) movPos(tPos, tab.pos - cnt, ar);

    if (cnt) {ar.write(note->line); tPos.move(cnt);}

    if (note->crlf) {ar.write(_T('\n'));   tPos.doCR();}
    }
  }


int NotePad::applyTabFactor(int tb) {
double val = tb * tabFactor;
double v2  = val + 0.5;
int    t   = int(v2);
  return t;
  }


void NotePad::movPos(TextPosition& from, int to, Archive& ar) {
int x = from.getCharPos();

  if (x >= to) to = x + 3;

  for ( ; x < to; x++) {ar << _T(" "); from.move(1);}
  }



NotePad& NotePad::append(const String& line) {getNote(EndLnNAttr).line += line;  return *this;}

NotePad& NotePad::append(Tchar   v)          {getNote(EndLnNAttr).line += v;     return *this;}
NotePad& NotePad::append(Cchar* cs)
                          {ToUniCode uni(cs); getNote(EndLnNAttr).line += uni(); return *this;}
NotePad& NotePad::append(Date    v)          {String s = v;                      return append(s);}


NotePad& NotePad::doSetWidth(  NotePad& n, int v) {n.getNote(NmbrNAttr).nmbr.width = v;   return n;}
NotePad& NotePad::doSetPrec(   NotePad& n, int v) {n.getNote(NmbrNAttr).nmbr.prec  = v;   return n;}


NotePad& NotePad::doNmbr(long   v)
                  {getNote(NmbrNAttr).nmbr.longVal  = v;   note->nmbr.typ = IntNmbrTyp;    return *this;}
NotePad& NotePad::doNmbr(ulong  v)
                  {getNote(NmbrNAttr).nmbr.uLongVal = v;   note->nmbr.typ = UIntNmbrTyp;   return *this;}
NotePad& NotePad::doNmbr(double v)
                  {getNote(NmbrNAttr).nmbr.dblVal   = v;   note->nmbr.typ = DblNmbTyp;     return *this;}







NotePad& NotePad::doSetLMargin(NotePad& n, int v) {n.getNote(LMgnNAttr).leftMargin = v;    return n;}
NotePad& NotePad::doClrTabs(   NotePad& n)        {n.getNote(StTbsNAttr).clrTabs   = true; return n;}
NotePad& NotePad::doSetTab(    NotePad& n, int v) {n.getNote(StTbsNAttr).tabValue  = v;    return n;}
NotePad& NotePad::doSetRTab(   NotePad& n, int v)
     {Note& note = n.getNote(StTbsNAttr);   note.rightTab = true;   note.tabValue  = v;    return n;}
NotePad& NotePad::doTab(       NotePad& n)        {n.getNote(TbNAttr).tab          = true; return n;}
NotePad& NotePad::doCenter(    NotePad& n)        {n.getNote(CtrNAttr).center      = true; return n;}
NotePad& NotePad::doRight(     NotePad& n)        {n.getNote(RghtNAttr).right      = true; return n;}
NotePad& NotePad::doBeginLine( NotePad& n)        {n.getNote(BgLnNAttr).beginLine  = true; return n;}
NotePad& NotePad::doEndLine(   NotePad& n)        {n.getNote(EndLnNAttr).endLine   = true; return n;}

NotePad& NotePad::crlf() {noLines++;   getNote(CrlfNAttr).crlf = true;                     return *this;}
NotePad& NotePad::endPage()
                        {if (noLines) {getNote(EndPgNAttr).endPage = true; noLines = 0;}   return *this;}


//Note& NotePad::getNote(NoteAttr attr) {return note && !note->isAfter(attr) ? *note : allocNote();}



//NoteManip nStartHdr;        // Start Header Output (saves pending output)
//NoteManip nEndHdr;          // End Header Output
//  nStartHdr.n  = this; nStartHdr.func  = doStartHdr;
//  nEndHdr.n    = this; nEndHdr.func    = doEndHdr;
#if 1
#else
Note& note = n.getNote();

  if (note.leftMargin != v) n.note = 0;   n.getNote().leftMargin = v;
#endif
#if 0
NotePad& NotePad::doEditBox(NotePad& n, int v) {

  if (n.getNote().editBoxX) n.note = 0;

  n.getNote().editBoxX = v; return n;
  }
#endif
#if 0
NotePad& NotePad::append(Wrap& w) {
Note& note = getNote();  if (!note.line.isEmpty()) this->note = 0;

  getNote().wrap = w; return *this;
  }
#endif
//NoteManip nTableName;       // Set bit to identify table name note:          dsp << dTableName << "xyz";

//NotePad& NotePad::append(TCchar* tc)         {getNote(EndLnNAttr).line += tc;    return *this;}
//NotePad& NotePad::append(CTimeSpan& v) {String s;     return append(s);}
#if 0
void NotePad::noFontReq(NotePad& n) {
Note& note = n.getNote();

  if (!note.fFace.isEmpty() || note.fSize     || note.prevFont  || note.bold || note.italic ||
                               note.underline || note.strikeOut || !note.line.empty()) n.note = 0;
  }
#endif
#if 0
NotePad& NotePad::doCrlf(NotePad& n) {
#if 1
#else
Note& note = n.getNote();

  if (note.leftMargin) n.note = 0;
#endif

  return n.crlf();
  }
#endif
#if 1
#else
Note& note = n.getNote();

  if (!note.line.empty() || note.right || note.tab) n.note = 0;

  n.getNote().beginLine = true;
#endif
#if 1
#else
Note& note = n.getNote();

  if (!note.line.empty() || note.right || note.tab || note.beginLine) n.note = 0;

  n.getNote().right  = true;
#endif
#if 1
#else
Note& note = n.getNote();

  if (!note.line.empty() || note.right || note.tab || note.beginLine) n.note = 0;

  n.getNote().right  = true;
#endif
//NtManipInt& nEditBox(   int val) {return setupManipInt(NotePad::doEditBox,    val);}
//  nTableName.n = this; nTableName.func = NotePad::setTableName;
#if 1

#else
Note& note = n.getNote();

  if (!note.line.empty() || note.clrTabs || note.right || note.tab ||
                                                             note.tabValue || note.rTabValue) n.note = 0;
  n.getNote().clrTabs   = true;
#endif
#if 1
#else
  if (n.getNote().tabValue) n.note = 0;

  n.getNote().tabValue = v;
#endif
#if 1
#else
  if (n.getNote().rTabValue) n.note = 0;

  n.getNote().rTabValue = v;
#endif
#if 1
#else
Note& note = n.getNote();

  if (!note.line.empty() || note.tab || note.beginLine || note.right) n.note = 0;

  n.getNote().tab = true;
#endif
#if 1

#else
Note& note = n.getNote();

  if (!note.line.empty()) n.note = 0;

  n.getNote().center = true;
#endif
#if 0
NotePad& NotePad::append(int v) {
#if 1
int  prec;
bool needTab = doNumAttr(prec);   append(intToString(v, 0));   if (needTab) doTab(*this);   return *this;

#else
Note&    note  = getNote(EndLnNAttr);
int      width = note.width;

  if (width < 0) doSetTab(*this, -width);   else if (width > 0) {doSetRTab(*this, width);  doTab(*this);}

  append(intToString(v, 0));   note.width = 0;

  if (width < 0) doTab(*this);
#endif
  }


bool NotePad::doNumAttr(int& prec) {
#if 0
Note&    note  = getNote(EndLnNAttr);
int      width = note.width;   note.width = 0;   prec = note.precision;   note.precision = 0;

  if (width < 0) {doSetTab(*this, 1-width);   return true;}

  if (width > 0) {doSetRTab(*this, width);   doTab(*this);}
#endif
  return false;
  }


NotePad& NotePad::append(long v) {
#if 1

int  prec;
bool needTab = doNumAttr(prec);   append(intToString(v, 0));   if (needTab) doTab(*this);   return *this;

#else
Note&    note    = getNote(EndLnNAttr);
NotePad& notePad = append(intToString(v, note.width));   note.width = 0; return notePad;
#endif
}


NotePad& NotePad::append(ulong v) {
#if 1

int  prec;
bool needTab = doNumAttr(prec);   append(uintToString(v, 0));   if (needTab) doTab(*this);   return *this;

#else
Note&    note    = getNote(EndLnNAttr);
NotePad& notePad = append(intToString(v, note.width));   note.width = 0; return notePad;
#endif
  }


NotePad& NotePad::append(double v) {
#if 1

int  prec;
bool needTab = doNumAttr(prec);    append(dblToString(v, 0, prec));   if (needTab) doTab(*this);

  return *this;

#else
Note&    note    = getNote(EndLnNAttr);
NotePad& notePad = append(dblToString(v, note.width, note.precision));

  note.width = 0; note.precision = 0; return notePad;
#endif
  }
#endif

