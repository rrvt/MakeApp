// Fix <Project Name>.vcxproj.filters file


#pragma once
//#include "Context.h"
#include "RenameApp.h"


class FixFilter {

Context&  ctx;
RenameApp renameAppName;
bool      xmplHdrSeen;

public:

  FixFilter(Context& context) : ctx(context), renameAppName(context), xmplHdrSeen(false) { }
 ~FixFilter() { }

  bool operator() (String& s);

private:

  FixFilter() : ctx(*(Context*)0), renameAppName(*(RenameApp*)0) { }
  };

