// File List


#pragma once
#include "Expandable.h"
#include "IterT.h"


class FileList;
typedef IterT<FileList, String> FLIter;                        // Iterator for the FileStore



class FileList {

Expandable<String, 128> files;

public:

  FileList() { }
 ~FileList() { }

  void clear() {files.clear();}

  void add(TCchar* name) {files.nextData() = name;}

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  String* datum(int i) {return 0 <= i && i < nData() ? &files[i] : 0;}

  // returns number of data items in array
  int     nData()      {return files.end();}

  friend typename FLIter;
  };



extern FileList fileList;
