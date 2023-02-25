// Sample Data Store


#include "pch.h"
#include "FileStore.h"
#include "NotePad.h"
#include "qsort.h"


const int TabVal = 5;


FileStore fileStore;                                        // Global since all classes need access


#if 0
// The destructor needs to return the Data records to the heap.

FileStore::~FileStore() {
int i;

  for (i = 0; i < data.end(); i++) {
    DataP& dataP = data[i];

    delete dataP.p;  dataP.p = 0;
    }
  }
#endif


void FileStore::clear() {
#if 0
int i;

  for (i = 0; i < data.end(); i++) {
    DataP& dataP = data[i];

    delete dataP.p;  dataP.p = 0;
    }
#endif

  data.clear();   name.clear();   dt.clear();   mssnNo = 0;
  }



void FileStore::setName(String& s) {name = s; dt.getToday();}


int FileStore::missionNo() {
  if (!mssnNo) {Date d; d.getToday();   CTimeSpan t = d - dt;  mssnNo = t.GetSeconds() % 60;}

  return mssnNo;
  }


// Load is called from serialize in the Document class
// The basic idea is that the method reads some chunk from the file (Archive is a fileio surrogate)

void FileStore::load(Archive& ar) {
String s;

  clear();

  while (ar.read(s)) add(s);
  }


void FileStore::store(Archive& ar) {
FSIter iter(*this);
Datum* d;

  for (d = iter(); d; d = iter++) ar.write((*d)() + _T('\n'));
  }


static String nilStg = _T("");


String& FileStore::operator() (int i) {Datum* d = datum(i);  return d ? d->get() : nilStg;}


void FileStore::add(String& s) {data.nextData().add(s);}


// Parse the data into the record

void Datum::add(String& stg) {
int pos = stg.find('\n');

  s = pos >= 0 ? stg.substr(0, pos) : stg;
  }


void FileStore::sort() {qsort(&data[0], &data[data.end()-1]);}


void FileStore::sort(int beg, int end) {
  if (end <= beg || beg < 0 || data.end() <= end) return;

  qsort(&data[beg], &data[end]);
  }


void FileStore::display(TCchar* fileName) {
FSIter iter(fileStore);
Datum* d;
int    i;

  notePad << nClrTabs;   for (i = 0; i < 30; i++) notePad << nSetTab(i*2);

  notePad << nCrlf << fileName << nCrlf << nCrlf;

  for (d = iter(), i = 0; d; d = iter++, i++) {

    String& s = d->get();   if (!i && s[0] == 0xef) continue;

    dspLine(s);
    }

  notePad << _T("--------------") << nCrlf;
  }


void FileStore::dspLine(String s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(_T("\t")); pos >= 0; pos = s.find(_T("\t"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+1);

    if (!prefix.isEmpty()) notePad << prefix;   notePad << nTab;

    s = suffix;
    }

  if (!s.isEmpty()) notePad << s;

  notePad << nCrlf;
  }


#if 0
int Data::wrap(DevBase& dev, CDC* dc) {

  dev << dCR << dClrTabs << dSetTab(TabVal) << dTab;    // Return to left margin (dCR), clear Tabs and
                                                        // tab to position desired for wrap
    wrp.initialize(true, dc, dev.remaining(), dev.maxWidth(), false);

  dev<< dCR << dClrTabs;                                // return to left margin and clear tabs

  return wrp(dev.maxWidth() - dev.remaining(), s);                                        // wrap string
  }
#endif


int Datum::display() {notePad << s << nCrlf;   return 1;}




//int  chWidth = dev.flChWidth();
#if 1
#else
WrapIter  iter(wrp);
WrapData* wd;
int       i;

  notePad << nClrTabs << nSetTab(TabVal) << nTab;       // The tab is set to the same value as in wrap

  for (wd = iter(), i = 0; wd; wd = iter++, i++) {
    if (i) notePad << nTab;

    notePad << wd->line << nCrlf;
    }

  return i;
#endif

