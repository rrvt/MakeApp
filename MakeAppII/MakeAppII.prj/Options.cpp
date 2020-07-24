// Global Options


#include "stdafx.h"
#include "Options.h"
#include "IniFile.h"


static TCchar* Section        = _T("Options");
static TCchar* TopMarginKey   = _T("TopMargin");
static TCchar* LeftMarginKey  = _T("LeftMargin");
static TCchar* RightMarginKey = _T("RightMargin");
static TCchar* BotMarginKey   = _T("BotMargin");

Options options;


void Options::load() {
String excel;

  iniFile.readString(Section, TopMarginKey,   topMargin,   _T("2.0"));
  iniFile.readString(Section, LeftMarginKey,  leftMargin,  _T("5.0"));
  iniFile.readString(Section, RightMarginKey, rightMargin, _T("3.0"));
  iniFile.readString(Section, BotMarginKey,   botMargin,   _T("2.7"));
  }


void Options::store() {

  iniFile.writeString(Section, TopMarginKey,   topMargin);
  iniFile.writeString(Section, LeftMarginKey,  leftMargin);
  iniFile.writeString(Section, RightMarginKey, rightMargin);
  iniFile.writeString(Section, BotMarginKey,   botMargin);
  }

