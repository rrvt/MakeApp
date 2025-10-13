// Utilities -- Little functions that may be used anywhere


#pragma once


void replace(String& s, int pos, int endPos, TCchar* repl);


inline void addSegment(String& s, TCchar* segment) {s += segment;  s += _T('\\');}

