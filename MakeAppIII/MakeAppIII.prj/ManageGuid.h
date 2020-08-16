// Manage GUIDs


#pragma once
#include "Expandable.h"


struct Subst {
String before;
String after;
};


class ManageGuid {
Expandable<Subst, 16> guids;

public:

  ManageGuid() {}
 ~ManageGuid() {guids.clr();}

  bool    findGuid(String& line, String& suffix);

  String& replace(String& id);
  };

