// Font Report -- List all Fonts in CDC


#include "stdafx.h"
#include "FontRpt.h"
#include "FontRptOpt.h"
#include "ListFonts.h"
#include "NotePad.h"



void FontRpt::display(CScrView& vw) {create(vw);}


void FontRpt::print(CScrView& vw) {create(vw);}


void FontRpt::footer(Device& dev, int pageNo) { }



static TCchar* fontTypeName[] = {_T(""),
                                 _T("RASTER"),
                                 _T("DEVICE"),
                                 _T(""),
                                 _T("TRUETYPE")
                                 };


void FontRpt::create(CScrView& vw) {
LFIter   iter(listFonts);
FontAtr* fa;
int      n;

  np.clear();

  np << nSetTab(28) << nSetTab(40);

  for (n = 0, fa = iter(); fa; fa = iter++) {

    if (filter(fa->name)) continue;

    np << fa->name << nTab << fontTypeName[fa->fType] << nTab;

    np << nFFace(fa->name);
    np << _T("ABCDE ");
    np << _T("abcde");
    np << nFont << nCrlf;    n++;
    }

  np << nCrlf << _T("Number of Fonts:  ") << n << nCrlf;
  }


bool FontRpt::filter(TCchar* name) {
Tchar ch = *name;   if (_T('a') <= ch && ch <= _T('z')) ch = _T('A') - _T('a');

  switch (ch) {
    case _T('A'):
    case _T('B'): return !fontRptOpt.ab;
    case _T('C'):
    case _T('D'): return !fontRptOpt.cd;
    case _T('E'):
    case _T('F'): return !fontRptOpt.ef;
    case _T('G'):
    case _T('H'): return !fontRptOpt.gh;
    case _T('I'):
    case _T('J'): return !fontRptOpt.ij;
    case _T('K'):
    case _T('L'): return !fontRptOpt.kl;
    case _T('M'):
    case _T('N'): return !fontRptOpt.mn;
    case _T('O'):
    case _T('P'): return !fontRptOpt.op;
    case _T('Q'):
    case _T('R'): return !fontRptOpt.qr;
    case _T('S'):
    case _T('T'): return !fontRptOpt.st;
    case _T('U'):
    case _T('V'): return !fontRptOpt.uv;
    case _T('W'):
    case _T('X'): return !fontRptOpt.wx;
    case _T('Y'):
    case _T('Z'): return !fontRptOpt.yz;
    }
  return true;
  }


int FontRpt::header(NotePad& np, bool printing) {
  return 0;
  }

