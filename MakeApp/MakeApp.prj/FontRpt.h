// Font Report -- List all Fonts in CDC


#pragma once
#include "ReportBase.h"

class NotePad;


class FontRpt : public ReportBase {

public:

  FontRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~FontRpt() { }

 void display(CScrView& vw);
 void print(CScrView& vw);

 void footer(Device& dev, int pageNo);          // Output page Footer to NotePad

private:

  void create();
  bool filter(TCchar* name);
  int  header(NotePad& np, bool printing);

  FontRpt() : ReportBase(*(NotePad*)0) { }

  };
