// Utilities -- Little functions that may be used anywhere


#include "pch.h"
#include "MkAppUtilities.h"


void replace(String& s, int pos, int endPos, TCchar* repl) {
String prefix;
String suffix;

  prefix = s.substr(0, pos);  suffix = s.substr(endPos);

  s = prefix + repl + suffix;
  }

