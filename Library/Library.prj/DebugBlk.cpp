

#include "pch.h"
#include "DebugBlk.h"


DebugBlk dbgBlk;


void DebugBlk::hex(void* blk, int n) {
Byte*  p = (Byte*) blk;
int    i;
String s;

  for (i = 0; i < n; i++) {
    if (i) fio.write(_T(' '));

    s.format(_T("%02x"), p[i]);  fio.write(s);
    }
  }


#if 0

dbgBlk.label(_T("Tab"));   dbgBlk.hex(&tab, sizeof(tab));  dbgBlk.crlf();

#endif
