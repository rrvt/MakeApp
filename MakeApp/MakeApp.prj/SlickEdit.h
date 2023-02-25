// Fix SlickEdit Property Operations


#pragma once
#include "Expandable.h"
#include "FileStore.h"


class Operation {
public:
String                  name;
bool                    clearAllSeen;
bool                    clearAngleBrkt;
Expandable<String,  16> descrip;

  Operation() {clear();}
 ~Operation() {clear();}

  void clear() {name.clear();   clearAllSeen = false;   clearAngleBrkt = false;   descrip.clear();}

  Operation& operator= (Operation& op);

  void       get(int& lineNo, Datum*& d, FSIter& iter);
  void       fixSaveOption(String& s);
  void       fixClearBuffer(String& s);
  };


class SlickEdit {

FSIter iter;
Datum* d;
int    lineNo;


Expandable<String,   512> data;
Expandable<Operation,  2> operators;

public:

  SlickEdit() : iter(fileStore), d(0) {clear();}
 ~SlickEdit() {clear();}

  void fix();

private:

  void fixAmenu(Datum*& d);
  void addToData(TCchar* name);
  void copyOperToData(Operation& op);
  void clear() {lineNo = 0; data.clear(); operators.clear();}
  };

