


#include "pch.h"
#include "FixFilter.h"


static TCchar* ClInclude = _T("</ClInclude");
static TCchar* OneLine   = _T("/>");


bool FixFilter::operator() (String& s) {

  if (xmplHdrSeen) {

    if (s.find(ClInclude) >= 0)
      xmplHdrSeen = false;

    return false;
    }

  if (ctx.xcldExample(s, _T("ExamplesDef.h"))) {

    if (s.find(OneLine) < 0)
      xmplHdrSeen = true;

    return false;
    }

  renameAppName(s);   return true;
  }

