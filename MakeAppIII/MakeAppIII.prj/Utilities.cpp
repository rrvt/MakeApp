// Utilities


#include "stdafx.h"
#include "Utilities.h"
#include "Date.h"
#include "NotePad.h"


static String blks = _T("          ");


String addTab(String& s, int max) {int n = max - s.length(); return s + blks.substr(0, n);}


String normalizeDate(TCchar* date) {
String s  = date ? date : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%D"));  return s;
  }

String normalizeTime(TCchar* time) {
String s  = time ? time : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%R"));  return s;
  }


String getDateNow() {Date dt;   dt.getToday();   return dt.format(_T("%D"));}

String getTimeNow() {Date dt;   dt.getToday();   return dt.format(_T("%R"));}



static int  findLastWh(String& s, int noChars);
static int wrap(int i, int noTabs);

