// Bounds in files to process further


#pragma once


struct Bounds {
int beg;
int end;

  Bounds() {clear();}

  void clear() {beg = end = -1;}

  void getFiles();

  void find(TCchar* tgt, String& s, int i) {if (s.find(tgt) >= 0) set(i);}

  bool isLegal() {return beg >= 0;}

private:

  void set(int i) {if (beg < 0) beg = i;   end = i;}
  };

