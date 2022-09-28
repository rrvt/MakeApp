// Manage GUIDs


#include "stdafx.h"
#include "ManageGuid.h"
#include "Guid.h"
#include "match.h"


static RegExpr UUIDExpr(_T("^[0-9A-Fa-f\\-][0-9A-Fa-f\\-]*$"));


void ManageGuid::fixBraceGuids(String& s) {
String prefix;
String suffix;

  for (prefix = s, s.clear(); findBraceGuid(prefix, suffix); prefix = suffix) s += prefix;

  s += prefix;
  }



bool ManageGuid::findBraceGuid(String& line, String& suffix) {
int    pos;
int    endPos;
String prefix;
String candidate;

  suffix.clear();

  pos = line.find(_T('{'));   if (pos < 0) return false;   pos++;

  prefix = line.substr(0, pos);   candidate = line.substr(pos);

  endPos = candidate.find(_T('}'));  if (endPos < 0) return false;

  suffix = candidate.substr(endPos);   candidate = candidate.substr(0, endPos);

  if (candidate.length() < 36 || !UUIDExpr.match(candidate)) return false;

  line = prefix + replace(candidate); return true;
  }


void ManageGuid::fixWxsGuid(String& s) {

  if (rplcWxsGuid(_T("UpgradeCode=\""), _T("\""),             s)) return;
  if (rplcWxsGuid(_T("Guid=\""),        _T("\""),             s)) return;
  if (rplcWxsGuid(_T("<ProjectGuid>"),  _T("</ProjectGuid>"), s)) return;
  }


void ManageGuid::fixWxdGuid(String& s) {
  if (rplcWxdGuid(_T("UpgradeCode="), s)) return;
  if (rplcWxdGuid(_T("UpgradeGUID="), s)) return;
  if (rplcWxdGuid(_T("Guid="),        s)) return;
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

  suffix = candidate.substr(endPos);   candidate = candidate.substr(0, endPos);

  if (candidate.length() < 36 || !UUIDExpr.match(candidate)) return false;

  s = prefix + replace(candidate) + suffix; return true;
  }


bool ManageGuid::rplcWxdGuid(TCchar* label, String& s) {
int    lng;
String prefix;
String candidate;

  if (s.find(label) < 0) return false;

  lng = _tcslen(label);

  prefix = s.substr(0, lng);  candidate = s.substr(lng);

  if (candidate.length() < 36 || !UUIDExpr.match(candidate)) return false;

  s = prefix + replace(candidate);  return true;
  }



String& ManageGuid::replace(String& id) {
MGIter     iter(*this);
GuidDatum* gd;
String     s;

  for (gd = iter(); gd; gd = iter++) if (gd->before == id) return gd->after;

  if (!getGuid(s)) return id;

  GuidDatum& dtm = data.nextData();

  dtm.before = id;   dtm.after = s;   return dtm.after;
  }


