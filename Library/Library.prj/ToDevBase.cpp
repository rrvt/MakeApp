// Display DevBase Data


#include "pch.h"
#include "ToDevBase.h"


//#define DebugDD

#ifdef DebugDD
static String dbgLastLine[10];
static void   saveDbgLine(String& line);
static void   saveDbgWrap(Wrap& w);
static void   rippleDbgLine();
#endif


//void ToDevBase::startDev() {note = npIter(); lastPageNo = 0; endDoc = debugging = false;}
//void ToDevBase::incDev()   {note = npIter++;}

// Output to DevBase (Display or Printer)

void ToDevBase::operator() () {

dev.chkFontData();

  for ( ; note; incDev()) {

dev.chkFontData();

    if (!note->fFace.isEmpty()) {dev << dFFace(note->fFace);       if (isEndPage()) break;}
    if (note->fSize)            {dev << dFSize(note->fSize);       if (isEndPage()) break;}
    if (note->bold)             {dev << dBold;                     if (isEndPage()) break;}
    if (note->italic)           {dev << dItalic;                   if (isEndPage()) break;}
    if (note->underline)        {dev << dUnderLine;                if (isEndPage()) break;}
    if (note->strikeOut)        {dev << dStrikeOut;                if (isEndPage()) break;}

    if (note->prevFont)         {dev << dFont;                     if (isEndPage()) break;}

    if (note->leftMargin >= 0)   dev << dSetLMargin(note->leftMargin);

    if (note->clrTabs)           dev << dClrTabs;
    if (note->tabValue)         {if (!note->rightTab) dev << dSetTab( note->tabValue);
                                 else                 dev << dSetRTab(note->tabValue);
                                 }

    if (note->tab == true)      {dev << dTab;                      if (isEndPage()) break;}
    if (note->center)           {dev << dCenter;                   if (isEndPage()) break;}
    if (note->right)            {dev << dRight;                    if (isEndPage()) break;}

    if (note->beginLine)        {dev << dBeginLine;                if (isEndPage()) break;}

                                 dev << note->line;                if (isEndPage()) break;

    if (note->nmbr.typ)         {dev << note->nmbr;                if (isEndPage()) break;}

    if (note->endLine)          {dev << dEndLine;                  if (isEndPage()) break;}

    if (note->crlf)             {dev << dCrlf;                     if (isEndPage()) break;}

    if (note->endPage)          {dev << dEndPage;                  dev.atEndPageCond(); incDev(); break;}

    if (note->debug)             debugging = true;
    }

  endDoc = note == 0;
  }




#ifdef DebugDD
void saveDbgWrap(Wrap& w) {
String* s;

  if (w.isEmpty()) return;

  for (s = w.startLoop(); s; s = w.nextLine()) saveDbgLine(*s);
  }


void saveDbgLine(String& line) {

  if (line.isEmpty()) return;

  rippleDbgLine();

  dbgLastLine[noElements(dbgLastLine)-1] = line;
  }



void rippleDbgLine() {
int n = noElements(dbgLastLine);
int i;

  for (i = 1; i < n; i++) dbgLastLine[i-1] = dbgLastLine[i];
  }
#endif




//                                 dev << note->wrap;                if (isEndPage()) break;

//    if (note->startHdr)         {dev << dStartHdr;                 if (isEndPage()) break;}
//    if (note->endHdr)           {dev << dEndHdr;                   if (isEndPage()) break;}
//    if (note->editBoxX >= 0)    {dev << dEditBox(note->editBoxX);  if (isEndPage()) break;}

