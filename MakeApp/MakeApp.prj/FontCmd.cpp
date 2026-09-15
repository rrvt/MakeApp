// Font Report Option -- Choose Leading letter of Font to display


#include "pch.h"
#include "FontCmd.h"
#include "FontRptDlg.h"
#include "FontList.h"


static TCchar* Arial = _T("Arial");


FontCmd fontCmd;


void FontCmd::operator() () {
FontRptDlg dlg;

  dlg.abFonts = getFontSel(ABFSel);
  dlg.cdFonts = getFontSel(CDFSel);
  dlg.efFonts = getFontSel(EFFSel);
  dlg.ghFonts = getFontSel(GHFSel);
  dlg.ijFonts = getFontSel(IJFSel);
  dlg.klFonts = getFontSel(KLFSel);
  dlg.mnFonts = getFontSel(MNFSel);
  dlg.opFonts = getFontSel(OPFSel);
  dlg.qrFonts = getFontSel(QRFSel);
  dlg.stFonts = getFontSel(STFSel);
  dlg.uvFonts = getFontSel(UVFSel);
  dlg.wxFonts = getFontSel(WXFSel);
  dlg.yzFonts = getFontSel(YZFSel);

  if (dlg.DoModal() == IDOK) {
    setFontSel(dlg.abFonts, ABFSel);
    setFontSel(dlg.cdFonts, CDFSel);
    setFontSel(dlg.efFonts, EFFSel);
    setFontSel(dlg.ghFonts, GHFSel);
    setFontSel(dlg.ijFonts, IJFSel);
    setFontSel(dlg.klFonts, KLFSel);
    setFontSel(dlg.mnFonts, MNFSel);
    setFontSel(dlg.opFonts, OPFSel);
    setFontSel(dlg.qrFonts, QRFSel);
    setFontSel(dlg.stFonts, STFSel);
    setFontSel(dlg.uvFonts, UVFSel);
    setFontSel(dlg.wxFonts, WXFSel);
    setFontSel(dlg.yzFonts, YZFSel);
    }
  }




static TCchar* fontTypeName[] = {_T(" "),
                                 _T("RASTER"),
                                 _T("DEVICE"),
                                 _T(" "),
                                 _T("TRUETYPE")
                                 };


NotePad& FontCmd::getData(CDC* cdc) {
LFIter   iter(fontList);
FontAtr* fa;
int      n;

  if (!np.isEmpty() && fontSel == lastFontSel) return np;

  lastFontSel = fontSel;

  np.clear();    fontList(cdc);

  np << nFFace(Arial) << nFSize(12.0);

  for (n = 0, fa = iter(); fa; fa = iter++) {

    if (filter(fa->name)) continue;

    np << nClrTabs << nSetTab(40) << nSetTab(60);

    np << fa->name << nTab << fontTypeName[fa->fType] << nTab;

    np << nFFace(fa->name);
    np << _T("ABCDEFGHIJKLMNOPQRSTUVXYZ") << nTab;
    np << _T("abcdefghijklmnopqrstuvxyz");
    np << nFont << nCrlf;    n++;
    }

  np << nCrlf << _T("Number of Fonts:  ") << n << nFont << nFont << nCrlf;

  return np;
  }


bool FontCmd::filter(TCchar* name) {
Tchar ch = *name;   if (_T('a') <= ch && ch <= _T('z')) ch = _T('A') - _T('a');

  switch (ch) {
    case _T('A'):
    case _T('B'): return !getFontSel(ABFSel);
    case _T('C'):
    case _T('D'): return !getFontSel(CDFSel);
    case _T('E'):
    case _T('F'): return !getFontSel(EFFSel);
    case _T('G'):
    case _T('H'): return !getFontSel(GHFSel);
    case _T('I'):
    case _T('J'): return !getFontSel(IJFSel);
    case _T('K'):
    case _T('L'): return !getFontSel(KLFSel);
    case _T('M'):
    case _T('N'): return !getFontSel(MNFSel);
    case _T('O'):
    case _T('P'): return !getFontSel(OPFSel);
    case _T('Q'):
    case _T('R'): return !getFontSel(QRFSel);
    case _T('S'):
    case _T('T'): return !getFontSel(STFSel);
    case _T('U'):
    case _T('V'): return !getFontSel(UVFSel);
    case _T('W'):
    case _T('X'): return !getFontSel(WXFSel);
    case _T('Y'):
    case _T('Z'): return !getFontSel(YZFSel);
    }
  return true;
  }






////////////=--------------
#if 0
  np << nFFace(_T("Courier New")) << nClrTabs << nSetTab(1) << nSetTab(5);
  np << _T("01234567890123456789") << nCrlf;
  np << nTab << _T("X") << nTab << _T("Y") << nTab << _T("Z") << nCrlf << nCrlf;
#endif

