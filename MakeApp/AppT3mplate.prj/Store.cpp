// Sample Data Store


#include "pch.h"
#include "Store.h"
#include "NotePad.h"
#include "qsort.h"


const int TabVal = 5;


Store store;                                        // Global since all classes need access


void Store::header(NotePad& np, int pageNo, int noPages) {
  np.clear();
  np << name << nCenter << missionNo() << nRight << dt;
  }


void Store::display() {
DSIter iter(*this);
Datum* dtm;

  notePad.clear();

  for (dtm = iter(); dtm; dtm = iter++) {
    notePad << dtm->get() << nCrlf;;
    }
  }


void Store::footer(NotePad& np, int pageNo, int noPages) {
  np.clear();

  np << nCenter << _T("Page ") << pageNo << _T(" of ") << noPages;
  }


void Store::setName(String& s) {name = s; dt.getToday();}


String& Store::missionNo() {
  if (mssnNo.isEmpty()) {Date d; d.getToday();  mssnNo = d.format(_T("Mission %y.%j"));}

  return mssnNo;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void Store::load(Archive& ar) {
String s;

  data.clear();

  while (ar.read(s)) add(s);
  }


void Store::store(Archive& ar) {
DSIter iter(*this);
Datum* datum;

  for (datum = iter(); datum; datum = iter++) ar << (*datum)() << aCrlf;
  }


void Store::add(String& s) {data.nextData().add(s);   lastModified.getToday();}


// Parse the data into the record

void Datum::add(String& stg) {
int pos = stg.find('\n');

  s = pos >= 0 ? stg.substr(0, pos) : stg;
  }


void Store::sort() {qsort(&data[0], &data[data.end()-1]);}


int Datum::display() {notePad << s << nCrlf;   return 1;}


