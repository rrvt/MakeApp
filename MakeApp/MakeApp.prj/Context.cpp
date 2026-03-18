// Context of the Project Construction


#include "pch.h"
#include "Context.h"
#include "GetPathDlg.h"
#include "IniFileEx.h"
#include "MkAppUtilities.h"
#include "NotePad.h"


       TCchar* AppTemplate = _T("AppT3mplate");
static TCchar* DialogApp   = _T("Dialog4pp");
static TCchar* MakeAppSect = _T("MakeApp");
static TCchar* BaseDirKey  = _T("BaseDir");


void Context::setBaseDir() {
String path;
int    lng;
Tchar  ch;

  if (!getDirPathDlg(_T("Make App"), path)) return;

  lng = path.length();  ch = path[lng-1];  if (ch != _T('\\')) path += _T('\\');

  appRoot = dstRoot = path;

  iniFile.writeString(MakeAppSect, BaseDirKey, dstRoot);

  notePad.clear();   dspBaseDir();
  }


void Context::getBaseDir() {

  iniFile.readString(MakeAppSect, BaseDirKey, dstRoot);   appRoot = dstRoot;

  dspBaseDir();
  }


void Context::dspBaseDir() {notePad << _T("Base Directory: ") << dstRoot << nCrlf;}


bool Context::operator() (ProjectNameDlg& dlg) {

  inclExmpls = dlg.inclExmpls;
  appType    = (AppType) dlg.appType;

  notePad << _T("App Type: ") << appType << _T(" -- ");

  switch (appType) {
    case DocViewType : notePad << _T("Doc/View"); break;
    case DialogType  : notePad << _T("Dialog");   break;
    default          : notePad << _T("Unknown") << nCrlf; return false;
    }
  notePad << nCrlf;

  name = dlg.name; visible = dlg.visibleName; description = dlg.description;

  switch (appType) {
    case DocViewType : targetName = AppTemplate; break;
    case DialogType  : targetName = DialogApp; dialogName = name + _T("Dlg"); break;
    }

  if (name.isEmpty())        return false;
  if (visible.isEmpty())     visible     = name;
  if (description.isEmpty()) description = visible;

  iniFile.readString(MakeAppSect, BaseDirKey, dstRoot);   appRoot = dstRoot;

  appRoot = dstRoot;   addSegment(appRoot, name);

  return true;
  }



///////----------------
#if 0
String t;
String s;
  mngGuid.clear();

  copyGlobal(_T("README-Template.md"), _T("README.md"));

  copyFiles(targetName);

  s = t =  targetName + _T(".hlp"); copyFiles(t);

  t += _T("\\Templates");           copyFiles(t);
  s += _T("\\Images");              copyFiles(s);

  t =  targetName + _T(".prj");     copyFiles(t);

  t += _T("\\res");                 copyFiles(t);

  t =  targetName + _T(".wix");     copyFiles(t);
#endif

