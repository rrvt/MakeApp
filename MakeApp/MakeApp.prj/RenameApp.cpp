// Rename App


#include "pch.h"
#include "RenameApp.h"
#include "MkAppUtilities.h"
#include "ProjectNameDlg.h"


static TCchar* DialogDlg = _T("Dialog4ppDlg");


RenameApp::RenameApp(Context& context) : ctx(context), targetName(ctx.targetName) { }


void RenameApp::operator() (String& s) {
int pos;

  for (pos = s.find(targetName); pos >= 0; pos = s.find(targetName))
                                              replace(s, pos, pos + targetName.length(), ctx.name);

  if (ctx.appType == DialogType)
    for (pos = s.find(DialogDlg); pos >= 0; pos = s.find(DialogDlg))
                                                  replace(s, pos, pos + 9, ctx.dialogName);
  }


