// Context of the Project Construction


#pragma once
#include "ProjectNameDlg.h"


extern TCchar* AppTemplate;


class Context {
public:

bool    inclExmpls;
AppType appType;
String  name;
String  targetName;
String  dialogName;
String  visible;
String  description;

String  dstRoot;                              // Destination base directory
String  appRoot;                              // application base directory

  Context() : inclExmpls(false) { }
 ~Context() { }

  void setBaseDir();
  void getBaseDir();

  bool operator() (ProjectNameDlg& dlg);

  bool xcldExample(String& s, TCchar* stg) {return !inclExmpls && s.find(stg) >= 0;}


private:

  void dspBaseDir();
  };

