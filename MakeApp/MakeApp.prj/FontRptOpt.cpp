// Font Report Option -- Choose Leading letter of Font to display


#include "pch.h"
#include "FontRptOpt.h"
#include "FontRptDlg.h"


FontRptOpt fontRptOpt;


void FontRptOpt::operator() () {
FontRptDlg dlg;

  dlg.abFonts = ab;
  dlg.cdFonts = cd;
  dlg.efFonts = ef;
  dlg.ghFonts = gh;
  dlg.ijFonts = ij;
  dlg.klFonts = kl;
  dlg.mnFonts = mn;
  dlg.opFonts = op;
  dlg.qrFonts = qr;
  dlg.stFonts = st;
  dlg.uvFonts = uv;
  dlg.wxFonts = wx;
  dlg.yzFonts = yz;

  if (dlg.DoModal() == IDOK) {
    ab = dlg.abFonts;
    cd = dlg.cdFonts;
    ef = dlg.efFonts;
    gh = dlg.ghFonts;
    ij = dlg.ijFonts;
    kl = dlg.klFonts;
    mn = dlg.mnFonts;
    op = dlg.opFonts;
    qr = dlg.qrFonts;
    st = dlg.stFonts;
    uv = dlg.uvFonts;
    wx = dlg.wxFonts;
    yz = dlg.yzFonts;
    }
  }

