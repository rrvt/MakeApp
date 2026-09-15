// Font Report Option -- Choose Leading letter of Font to display


#pragma once
#include "NotePad.h"


enum FontSel {ABFSel = 0x001, CDFSel = 0x002, EFFSel = 0x004, GHFSel = 0x008, IJFSel = 0x010,
              KLFSel = 0x020, MNFSel = 0x040, OPFSel = 0x080, QRFSel = 0x100, STFSel = 0x200,
              UVFSel = 0x400, WXFSel = 0x800, YZFSel = 0x1000
              };


class FontCmd {

int     fontSel{0};
int     lastFontSel{0};

NotePad np;

public:

  FontCmd() { }
 ~FontCmd() { }

  void operator() ();

  NotePad& getData(CDC* cdc);

private:

  bool filter(TCchar* name);
  bool getFontSel(FontSel fSel)         {return fontSel & fSel ? true : false;}
  void setFontSel(bool v, FontSel fSel) {if (v) fontSel |= fSel;}
  };

extern FontCmd fontCmd;




////////---------------
#if 0
//bool ab;
//bool cd;
bool ef;
bool gh;
bool ij;
bool kl;
bool mn;
bool op;
bool qr;
bool st;
bool uv;
bool wx;
bool yz;
#endif

