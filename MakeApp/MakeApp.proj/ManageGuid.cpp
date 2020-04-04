// Manage GUIDs


#include "stdafx.h"
#include "ManageGuid.h"
#include "Guid.h"
#include "match.h"


static RegExpr re(_T("^{[0-9A-Fa-f\\-][0-9A-Fa-f\\-]*}$"));


bool ManageGuid::findGuid(String& line, String& suffix) {
int    pos;
int    endPos;
String prefix;
String candidate;

  suffix.clear();

  pos = line.find(_T('{'));   if (pos < 0) return false;

  prefix = line.substr(0, pos);   candidate = line.substr(pos);

  endPos = candidate.find(_T('}'));  if (endPos < 0) return false;

  suffix = candidate.substr(endPos+1);   candidate = candidate.substr(0, endPos+1);

  if (re.match(candidate)) {line = prefix + replace(candidate); return true;}

  return false;
  }



String& ManageGuid::replace(String& id) {
int    i;
int    n = guids.end();
String s;

  for (i = 0; i < n; i++) if (guids[i].before == id) return guids[i].after;

  if (!getGuid(s)) return id;

  guids[n].before = id;   guids[n].after = _T('{') + s + _T('}');   return guids[n].after;
  }


