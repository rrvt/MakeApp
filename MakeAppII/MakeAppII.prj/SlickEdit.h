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

  void clear() {name.clear();   clearAllSeen = false;   clearAngleBrkt = false;   descrip.clr();}

  Operation& operator= (Operation& op);

  void       get(int& lineNo, Data*& d, FSIter& iter);
  void       fixSaveOption(String& s);
  void       fixClearBuffer(String& s);
  };


class SlickEdit {

FSIter iter;
Data*  d;
int    lineNo;


Expandable<String,   512> data;
Expandable<Operation,  2> operators;

public:

  SlickEdit() : iter(fileStore), d(0) {clear();}
 ~SlickEdit() {clear();}

  void fix();

private:

  void fixAmenu(Data*& d);
  void addToData(TCchar* name);
  void copyOperToData(Operation& op);
  void clear() {lineNo = 0; data.clr(); operators.clr();}
  };

