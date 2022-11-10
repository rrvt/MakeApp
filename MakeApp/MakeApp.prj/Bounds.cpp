// Bounds in files to process further


#include "pch.h"
#include "Bounds.h"
#include "FileList.h"
#include "FileStore.h"


static TCchar* IncTarget  = _T("Include=\"");
static int     NIncTarget = _tcslen(IncTarget);


// Scan a file between the bounds and store the file names found in FileList

void Bounds::getFiles() {
int    i;
String s;
int    pos;

  if (!isLegal()) return;

  for (i = beg; i <= this->end; i++) {
    s = fileStore(i);
    pos = s.find(IncTarget);    if (pos < 0) continue;

    pos += NIncTarget;   s = s.substr(pos);

    pos = s.find(_T('\"'));     if (pos < 0) pos = s.find(_T("\">"));   if (pos < 0) continue;

    s = s.substr(0, pos);       if (s[0] == _T('.')) continue;

    fileList.add(s);
    }
  }

