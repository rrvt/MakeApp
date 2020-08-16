// Fix SlickEdit Property Operations


#include "stdafx.h"
#include "SlickEdit.h"
#include "FileStore.h"
#include "MessageBox.h"


static TCchar* tgtTable[] = {_T("Build Solution"),
                             _T("Clean Solution"),
                             _T("Rebuild"),
                             _T("Build"),
                             _T("Clean Project"),
                             _T("Compile"),
                             _T("Debug"),
                             _T("DebugVisualStudio"),
                             _T("Execute")
                            };


void SlickEdit::fix() {
int i;
int n;

  for (d = iter(), lineNo = 0; d; d = iter++, lineNo++) {
    String& s = d->get();

    if (s.find(_T("<Target")) > 0) {fixAmenu(d); continue;}

    data[data.end()] = s;
    }

  fileStore.clear();

  for (i = 0, n = data.end(); i < n; i++) fileStore.add(data[i]);
  }


void SlickEdit::fixAmenu(Data*& d) {
int i;
int n;

  operators.clr();

  for ( ; d; d = iter++, lineNo++) {
    String& s = d->get();

    if (s.find(_T("</Menu>")) > 0) break;
    if (s.find(_T("<Target")) > 0) {operators[operators.end()].get(lineNo, d, iter); continue;}

    messageBox(_T("Whoops!")); break;
    }

  n = noElements(tgtTable);

  for (i = 0; i < n; i++) addToData(tgtTable[i]);

  data[data.end()] = fileStore(lineNo);                             // save </Menu>
  }


void Operation::get(int& lineNo, Data*& d, FSIter& iter) {
int begX;
int endX;

  clear();

  for ( ; d; d = iter++, lineNo++) {
    String& s = d->get();

    begX = s.find(_T("Name=\""));

    if (begX > 0) {
      begX += 6;  endX = s.find(_T('"'), begX);  name = s.substr(begX, endX-begX);
      }

    fixSaveOption(s);   fixClearBuffer(s);
    descrip[descrip.end()] = s;

    if (s.find(_T("</Target>")) >= 0) break;
    }
  }



//SaveOption="SaveAll"

void Operation::fixSaveOption(String& s) {
String prefix;
String suffix;
int    pos;

  if (s.find(_T("SaveOption=\"")) < 0) return;

  pos = s.find(_T('\"'))+1;     prefix = s.substr(0, pos);

  pos = s.find(_T('\"'), pos);  suffix = s.substr(pos);

  s = prefix + _T("SaveAll") + suffix;
  }


// ClearProcessBuffer="1">
// <Exec

void Operation::fixClearBuffer(String& s) {
bool   lineIsClearBuf = s.find(_T("ClearProcessBuffer=\"")) >= 0;
String prefix;
String suffix;
int    pos;

  if (!clearAllSeen) {

    if (!lineIsClearBuf && !clearAngleBrkt)
                {pos = s.find(_T('>'));   if (pos >= 0) {s = s.substr(0, pos);  clearAngleBrkt = true;}}

    if (s.find(_T("<Exec")) >= 0)
              {descrip[descrip.end()] = _T("        ClearProcessBuffer=\"1\">");   clearAllSeen = true;}
    }

  if (!lineIsClearBuf) return;

  pos = s.find(_T('\"'))+1;     prefix = s.substr(0, pos);

  pos = s.find(_T('\"'), pos);  suffix = s.substr(pos);

  s = prefix + _T("1") + suffix;    clearAllSeen = true;
  }



void SlickEdit::addToData(TCchar* name) {
int i;
int n = operators.end();

  for (i = 0; i < n; i++) {
    Operation& op = operators[i];

    if (op.name == name) {copyOperToData(op); return;}
    }
  }


void SlickEdit::copyOperToData(Operation& op) {
int i;
int n = op.descrip.end();

  for (i = 0; i < n; i++) data[data.end()] = op.descrip[i];
  }


Operation& Operation::operator= (Operation& op) {
int i;
int n = op.descrip.end();

  name = op.name;   for (i = 0; i < n; i++) descrip[i] = op.descrip[i];

  return *this;
  }

