// Manage GUIDs


#pragma once
#include "Expandable.h"
#include "IterT.h"


struct GuidDatum {
String before;
String after;

  GuidDatum() { }
 ~GuidDatum() { }

  GuidDatum& operator= (GuidDatum& gd) {before = gd.before; after = gd.after; return *this;}
  };


class ManageGuid;
typedef IterT<ManageGuid, GuidDatum> MGIter;


class ManageGuid {
Expandable<GuidDatum, 16> data;

public:

  ManageGuid() {}
 ~ManageGuid() {}

  void clear() {data.clear();}

  void fixBraceGuids(String& s);
  void fixWxsGuid(String& s);
  void fixWxdGuid(String& s);

private:

  bool    findBraceGuid(String& line, String& suffix);
  bool    rplcWxsGuid(TCchar* label, TCchar* end, String& s);
  bool    rplcWxdGuid(TCchar* label, String& s);

  String& replace(String& id);

  // returns either a pointer to datum at index i in array or zero

  GuidDatum* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int   nData()      {return data.end();}                       // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MGIter;
  };

