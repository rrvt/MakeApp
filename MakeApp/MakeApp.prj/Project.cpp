// Project Management -- Make changes and copy


#include "pch.h"
#include "Project.h"
#include "filename.h"
#include "filesrch.h"
#include "FileStore.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "MkAppUtilities.h"
#include "NotePad.h"
#include "SlickEdit.h"

#include "MessageBox.h"   //debug


Project project;


static TCchar* MakeTarget  = _T("MakeApp\\");

static TCchar* MakeAppSect = _T("MakeApp");
static TCchar* BaseDirKey  = _T("BaseDir");
static TCchar* AppT3mplate = _T("AppT3mplate");
static TCchar* DialogApp   = _T("Dialog4pp");


static TCchar* TestSolDir  = _T("AppT3mplate\\");
static TCchar* TestPrjDir  = _T("AppT3mplate.prj\\");
static TCchar* TestHlpDir  = _T("AppT3mplate.hlp\\");


void Project::getBaseDir() {

  iniFile.readString(MakeAppSect, BaseDirKey, dstRoot);   appRoot = dstRoot;

  notePad << _T("Base Directory: ") << dstRoot << nCrlf;
  }


void Project::getBaseDirUser() {
String path;
int    lng;
Tchar  ch;

  if (!getDirPathDlg(_T("Make App"), path)) return;

  lng = path.length();  ch = path[lng-1];  if (ch != _T('\\')) path += _T('\\');

  appRoot = dstRoot = path;

  iniFile.writeString(MakeAppSect, BaseDirKey, dstRoot);

  notePad.clear();

  notePad << _T("Base Directory: ") << dstRoot << nCrlf;
  }



void Project::determineBasePath(TCchar* helpPath) {
String   s = helpPath;
int      pos;
FileSrch dirs;
String   t;
String   tgt = AppT3mplate;  tgt += _T(".wix");
String   path;
bool     rslt;

  pos = s.findLastOf(_T('\\'));   if (pos < 0) return;

  t = s.substr(0, pos);

  loop {

    for (rslt = dirs.findSubDirs(t, tgt); !rslt; rslt = dirs.findSubDirs(t, tgt)) {
      pos = t.findLastOf(_T('\\'));   if (pos < 0) return;;

      t = t.substr(0, pos);
      }

    pos = t.find(_T("\\.."));  if (pos <= 0) break;

    t = t.substr(0, pos);
    }

  if (rslt) srcRoot = t + _T('\\');
  }


bool Project::operator() (ProjectNameDlg& dlg) {
String t;
String s;

  appType = (AppType) dlg.appType;

  notePad << _T("App Type: ") << appType << _T(" -- ");

  switch (appType) {
    case DocViewType : notePad << _T("Doc/View"); break;
    case DialogType  : notePad << _T("Dialog");   break;
    default          : notePad << _T("Unknown") << nCrlf; return false;
    }
  notePad << nCrlf;

  name = dlg.name; visible = dlg.visibleName; description = dlg.description;

  switch (appType) {
    case DocViewType : targetName = AppT3mplate; break;
    case DialogType  : targetName = DialogApp; dialogName = name + _T("Dlg"); break;
    }

  if (name.isEmpty())        return false;
  if (visible.isEmpty())     visible     = name;
  if (description.isEmpty()) description = visible;

  appRoot = dstRoot;   addSegment(appRoot, name);

  mngGuid.clear();

  copyGlobal(_T("README-Template.md"), _T("README.md"));

  copyFiles(targetName);

  s = t =  targetName + _T(".hlp"); copyFiles(t);

  t += _T("\\Templates");           copyFiles(t);
  s += _T("\\Images");              copyFiles(s);

  t =  targetName + _T(".prj");     copyFiles(t);

  t += _T("\\res");                 copyFiles(t);

  t =  targetName + _T(".wix");     copyFiles(t);

  return true;
  }


void Project::copyFiles(TCchar* srcDirName) {
FileSrch files;
String   path;

  preparePath(srcDirName);

  for (files.findAllFiles(srcPath); files.getName(path);) copyFixable(path);
  }


void Project::copyGlobal(TCchar* srcName, TCchar* dstName) {
String srcFilePath = srcRoot + srcName;
String dstFilePath = appRoot;

  createDir(dstFilePath);   dstFilePath += dstName;

  CopyFile(srcFilePath, dstFilePath, false);
  }


void Project::copyFixable(TCchar* path) {
String   fileName;
FileType fileType;

  fileName = removePath(path);   if (!mustCopy(fileName, fileType)) return;

  switch (fileType) {
    case NilType: copyFile(fileName);         break;
    case PrjType: copyFile(fileName, PrjFix); break;
    case SlnType: copyFile(fileName, SlnFix); break;
    case SrcType: copyFile(fileName, SrcFix); break;
    case SEType : copyFile(fileName, SEFix);  break;
    case VxcType: fileList.clear(); incl.clear(); cmpl.clear();
                  res.clear();      none.clear(); image.clear();
                  copyFile(fileName, VxcFix); break;
    case WxsType: copyFile(fileName, WxsFix); break;
    case WxdType: copyFile(fileName, WxdFix); break;
    default     : break;
    }
  }


bool Project::mustCopy(String& fileName, FileType& fileType) {
String ext = getExtension(fileName);

  if (ext == _T("h"))             {fileType = SrcType; return true;}
  if (ext == _T("cpp"))           {fileType = SrcType; return true;}
  if (ext == _T("rc"))            {fileType = SrcType; return true;}
  if (ext == _T("rc2"))           {fileType = SrcType; return true;}
  if (ext == _T("sln"))           {fileType = SlnType; return true;}
  if (ext == _T("vcxproj"))       {fileType = VxcType; return true;}
  if (ext == _T("filters"))       {fileType = PrjType; return true;}
  if (ext == _T("user"))          {fileType = PrjType; return true;}
  if (ext == _T("vpj"))           {fileType = SEType;  return true;}
  if (ext == _T("bmp"))           {fileType = NilType; return true;}
  if (ext == _T("ico"))           {fileType = NilType; return true;}
  if (ext == _T("wxd"))           {fileType = WxdType; return true;}
  if (ext == _T("wxs"))           {fileType = WxsType; return true;}
  if (ext == _T("wxl"))           {fileType = NilType; return true;}
  if (ext == _T("wixproj"))       {fileType = WxsType; return true;}
  if (ext == _T("dwt"))           {fileType = NilType; return true;}
  if (ext == _T("css"))           {fileType = NilType; return true;}
  if (ext == _T("hhc"))           {fileType = SrcType; return true;}
  if (ext == _T("hhp"))           {fileType = SrcType; return true;}
  if (ext == _T("bat"))           {fileType = SrcType; return true;}
  if (ext == _T("htm"))           {fileType = SrcType; return true;}
  if (ext == _T("jpg"))           {fileType = NilType; return true;}
  if (ext == _T("rtf"))           {fileType = NilType; return true;}
  if (ext == _T("md"))            {fileType = NilType; return true;}
  if (fileName == _T("makefile")) {fileType = SrcType; return true;}

  return false;
  }


void Project::preparePath(TCchar* pathName, TCchar* segment) {

  srcPath = srcRoot;   if (segment)  addSegment(srcPath, segment);
                       if (pathName) addSegment(srcPath, pathName);

  dstPath = appRoot;   if (segment)  addSegment(dstPath, segment);
                       if (pathName) dstPath += pathName;

  renameAppName(dstPath);   createDir(dstPath);  dstPath += _T('\\');
  }


bool Project::createDir(TCchar* path) {
String s;

  if (!path || !*path) return false;

  if (CreateDirectory(path, 0) || GetLastError() == ERROR_ALREADY_EXISTS) return true;

  s = getPath(path);

  if (createDir(s)) return CreateDirectory(path, 0) || GetLastError() == ERROR_ALREADY_EXISTS;

  return false;
  }


void Project::copyFile(String& srcName) {
String srcFilePath = srcPath + srcName;
String dstName     = srcName;  renameAppName(dstName);
String dstFilePath = dstPath + dstName;

  CopyFile(srcFilePath, dstFilePath, false);
  }


void Project::copyFile(TCchar* srcName, FixIt fixIt) {
String dstName     = srcName;                  renameAppName(dstName);
String srcFilePath = srcPath + srcName;
String dstFilePath = dstPath + dstName;
FSIter iter(fileStore);
Datum* d;

  if (!doc()->OnOpenDocument(srcFilePath)) return;

  if (fixIt == VxcFix) getFiles();

  for (d = iter(); d; d = iter++) {
    String& s = d->get();

    switch(fixIt) {
      case SlnFix : renameAppName(s); mngGuid.fixBraceGuids(s); break;
      case VxcFix : mngGuid.fixBraceGuids(s);   fixReadMe(s);
      case SEFix  :
      case PrjFix : renameAppName(s);   break;
      case SrcFix : renameAppName(s);   renamDesc(s);   renamVisibleName(s); break;
      case WxsFix : mngGuid.fixWxsGuid(s); renameAppName(s); break;
      case WxdFix : mngGuid.fixWxdGuid(s); renameAppName(s);  fixPath(srcRoot, appRoot, s);
                    renameMakeApp(s); break;
      }
    }

  if (fixIt == SEFix)  {SlickEdit se;    se.fix();}
  if (fixIt == VxcFix) {fileStore.sort(incl.beg, incl.end);  fileStore.sort(cmpl.beg, cmpl.end);}

  fileStore.display(dstName);   invalidate();

  doc()->OnSaveDocument(dstFilePath);
  }


void Project::getFiles() {
FSIter iter(fileStore);
Datum* d;
int    i;

  for (d = iter(), i = 0; d; d = iter++, i++) {
    String& s = d->get();
     incl.find(_T("ClInclude Include"),       s, i);
     cmpl.find(_T("ClCompile Include"),       s, i);
      res.find(_T("ResourceCompile Include"), s, i);
     none.find(_T("None Include"),            s, i);
    image.find(_T("Image Include"),           s, i);
    }

  incl.getFiles(); cmpl.getFiles(); res.getFiles(); none.getFiles(); image.getFiles();
  }


static TCchar* ReadMeTgt = _T("README-Template.md");
static TCchar* ReadMeRpl = _T("README.md");

void Project::fixReadMe(String& s) {
int pos;

  for (pos = s.find(ReadMeTgt); pos >= 0; pos = s.find(ReadMeTgt)) replace(s, pos, pos + 18, ReadMeRpl);
  }


static TCchar* DialogDlg = _T("Dialog4ppDlg");

void Project::renameAppName(String& s) {
int pos;

  for (pos = s.find(targetName); pos >= 0; pos = s.find(targetName))
                                                  replace(s, pos, pos + targetName.length(), name);

  if (appType == DialogType)
    for (pos = s.find(DialogDlg); pos >= 0; pos = s.find(DialogDlg))
                                                  replace(s, pos, pos + 9, dialogName);
  }


static TCchar* AppLine  = _T("< Description >");
static int     NAppLine = _tcslen(AppLine);


void Project::renamDesc(String& s) {
int pos = s.find(AppLine);   if (pos < 0) return;

  replace(s, pos, pos + NAppLine, description);
  }


static TCchar* TitleTarget  = _T("< Title >");
static int     NTitleTarget = _tcslen(TitleTarget);


void Project::renamVisibleName(String& s) {
int    pos = s.find(TitleTarget);   if (pos < 0) return;

  replace(s, pos, pos + NTitleTarget, visible);
  }


void Project::fixPath(String& srcRoot, String& dstRoot, String& s) {
int lng = srcRoot.length();
int pos = s.find(srcRoot);

  if (pos >= 0) replace(s, pos, pos+lng, dstRoot);
  }


void Project::renameMakeApp(String& s) {
int pos = s.find(_T("MakeApp"));

  if (pos >= 0)
    replace(s, pos, pos+7, name);
  }

