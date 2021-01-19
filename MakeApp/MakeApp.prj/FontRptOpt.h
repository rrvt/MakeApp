// Font Report Option -- Choose Leading letter of Font to display


#pragma once


class FontRptOpt {

bool ab;
bool cd;
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

public:

  FontRptOpt() { }
 ~FontRptOpt() { }

  void operator() ();

  friend class FontRpt;
  };

extern FontRptOpt fontRptOpt;
