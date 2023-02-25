// Sample Data Store


#pragma once
#include "Archive.h"
#include "Date.h"
#include "DevBase.h"
#include "ExpandableP.h"
#include "IterT.h"


// This is the Datum record.  It can be a complex as necessary.
// Set will accept any reasonable group of entities and then will divide up the input into fields in
// the data.
// Get will return any grouping of data desired from the record, or there might be multiple get methods
// that will retrieve invidual or groups of fields.
// Note, the copy constructor and operator often call a private function that will do all the copying.

class Datum {

String s;

public:

  Datum()        { }                                       // Copy constructor: Datum a = b;
  Datum(Datum& d) {s = d.s;}
 ~Datum()        { }

  void    set(String& s) {this->s = s;}
  String& get()         {return s;}
  String& operator() () {return s;}

  void    add(String& stg);                               // Parse the data into the record

  int     display();

  Datum&   operator=  (Datum& d) {s = d.s; return *this;}    // Copy operator: a = b;

  bool     operator== (Datum& d) {return s == d.s;}
  bool     operator!= (Datum& d) {return s != d.s;}
  bool     operator>  (Datum& d) {return s >  d.s;}
  bool     operator<  (Datum& d) {return s <  d.s;}
  bool     operator>= (Datum& d) {return s >= d.s;}
  bool     operator<= (Datum& d) {return s <= d.s;}
  };


#if 1
typedef DatumPtrT<Datum> DatumP;
#else

// This facilitates the expansion of the Expandable array in the FileStore.  Essentially The pointers are
// moved from the old version of the array to a new version that is larger.
// Since we are moving the pointers we cannot delete the allocated Datum entity from this class.
// However, the allocated notes should be "deleted" when the dataStore goes out of scope or is deleted.

struct DataP {
Datum* p;

  DataP()             {p = 0;}
  DataP(DataP& dataP) {p = dataP.p;}
 ~DataP()             {p = 0;}

  DataP& operator= (DataP& dataP) {p = dataP.p; return *this;}

  void add(String& s);

  // Requires the following operations for node N* p, N* q, N* s
  //  *p == *q
  //  *p >  *q
  //  *p <= *q
  //  *s = *p

//  bool operator== (DataP& dataP) {return p->get() == dataP.p->get();}
//  bool operator>  (DataP& dataP) {return p->get() >  dataP.p->get();}
//  bool operator<= (DataP& dataP) {return p->get() <= dataP.p->get();}
  bool operator== (DataP& d) {return _tcsicmp(p->get(), d.p->get()) == 0;};
  bool operator>  (DataP& d) {return _tcsicmp(p->get(), d.p->get())  > 0;};
  bool operator<= (DataP& d) {return _tcsicmp(p->get(), d.p->get()) <= 0;};
  };
#endif


// Define the iterator used to look at the data in the datastore.  It is here so that it can be friended

class FileStore;
typedef IterT<FileStore, Datum> FSIter;                        // Iterator for the FileStore


// This is the main store.  I think of it as a permanent home for the data while the program is running.
// The Expandable array deals with the uncertainty of the amount of data as it expands by doubling in
// length each time it has to expand.
// In this example, we provide a way to load it from a file, the details of which are up to the Datum
// class.  The data can be stored in a file, again the details of each record are enclosed in the Datum
// class.  We can add something to the store from the user or some other source (TBD).  In this example
// a sort option is provided to change the order of the data in the array.
// Finally, the destructor returns the allocated Datum records back to the heap (see cpp file).

class FileStore {

ExpandableP<Datum, DatumP, 4> data;

public:

String name;
Date   dt;
int    mssnNo;

  FileStore() : mssnNo(0) { }
 ~FileStore() { }

  void clear();

  void   setName(String& s);
  String date()           {return dt.getDate();}
  String time()           {return dt.getTime();}
  int    missionNo();

  void load(Archive& ar);
  void store(Archive& ar);

  bool isEmpty() {return data.end() == 0;}

  String& operator() (int i);

  void add(String& s);

  void sort();
  void sort(int beg, int end);

  void display(TCchar* fileName);
  void dspLine(String s);

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  Datum* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  // returns number of data items in array
  int   nData()      {return data.end();}

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename FSIter;
  };


extern FileStore fileStore;                                   // Sometimes there only needs to one object

