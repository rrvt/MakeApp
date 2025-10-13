// Rename App



#pragma once
#include "Context.h"


class RenameApp {

Context& ctx;
String&  targetName;

public:

  RenameApp(Context& context);
 ~RenameApp() { }

  void operator() (String& s);

private:

  RenameApp() : ctx(*(Context*)0), targetName(*(String*)0) { }
  };




////////-----------------
#if 0
String& name;
String& dialogName;
#endif

