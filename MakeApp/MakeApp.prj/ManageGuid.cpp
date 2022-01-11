// Manage GUIDs


#include "stdafx.h"
#include "ManageGuid.h"
#include "Guid.h"
#include "match.h"


static RegExpr re(_T("^{[0-9A-Fa-f\\-][0-9A-Fa-f\\-]*}$"));


void ManageGuid::fixBraceGuids(String& s) {
String prefix;
String suffix;

//  if (!findBraceGuid(s, suffix)) return;

  for (prefix = s, s.clear(); findBraceGuid(prefix, suffix); prefix = suffix) s += prefix;

  s += prefix;
  }



bool ManageGuid::findBraceGuid(String& line, String& suffix) {
int    pos;
int    endPos;
String prefix;
String candidate;

  suffix.clear();

  pos = line.find(_T('{'));   if (pos < 0) return false;

  prefix = line.substr(0, pos + 1);   candidate = line.substr(pos);

  endPos = candidate.find(_T('}'));  if (endPos < 0) return false;

  suffix = candidate.substr(endPos);   candidate = candidate.substr(0, endPos+1);

  if (re.match(candidate)) {line = prefix + replace(candidate); return true;}

  return false;
  }
                                 // <ProjectGuid>

void ManageGuid::fixWxsGuid(String& s) {

  if (rplcWxsGuid(_T("UpgradeCode=\""), _T("\""),             s)) return;
  if (rplcWxsGuid(_T("Guid=\""),        _T("\""),             s)) return;
  if (rplcWxsGuid(_T("<ProjectGuid>"),  _T("</ProjectGuid>"), s)) return;
  }


bool ManageGuid::rplcWxsGuid(TCchar* label, TCchar* end, String& s) {
int    lng = _tcslen(label);
int    pos;
int    endPos;
String prefix;
String candidate;
String suffix;

  pos = s.find(label);                 if (pos < 0) return false;

  prefix = s.substr(0, pos + lng);     candidate = s.substr(pos+lng);

  endPos = candidate.find(end);        if (endPos < 0) return false;

  suffix = candidate.substr(endPos);   candidate = _T('{') + candidate.substr(0, endPos) + _T('}');

  if (re.match(candidate)) {s = prefix + replace(candidate) + suffix; return true;}

  return false;
  }




String& ManageGuid::replace(String& id) {
MGIter     iter(*this);
GuidDatum* gd;
String s;

  for (gd = iter(); gd; gd = iter++) if (gd->before == id) return gd->after;

  if (!getGuid(s)) return id;

  GuidDatum& dtm = data.nextData();

  dtm.before = id;   dtm.after = s;   return dtm.after;
  }


