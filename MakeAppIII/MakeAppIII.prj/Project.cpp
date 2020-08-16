// Project Management -- Make changes and copy


#include "stdafx.h"
#include "Project.h"
#include "filename.h"
#include "filesrch.h"
#include "FileStore.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "NotePad.h"
#include "SlickEdit.h"



Project project;


static TCchar* MakeTarget  = _T("MakeApp\\");

static TCchar* MakeAppSect = _T("MakeApp");
static TCchar* BaseDirKey  = _T("BaseDir");
static TCchar* AppT3mplate = _T("AppT3mplate");
static TCchar* TestSolDir  = _T("AppT3mplate\\");
static TCchar* TestPrjDir  = _T("AppT3mplate.prj\\");
static TCchar* TestHlpDir  = _T("AppT3mplate.hlp\\");


void Project::getBaseDir() {

  iniFile.readString(MakeAppSect, BaseDirKey, baseDir);

  notePad << _T("Base Directory: ") << baseDir << nCrlf;
  }


void Project::getBaseDirUser() {
String path;
int    lng;
Tchar  ch;

  if (!getDirPathDlg(_T("Make App"), path)) return;

  lng = path.length();  ch = path[lng-1];  if (ch != _T('\\')) path += _T('\\');

  baseDir = path;

  iniFile.writeString(MakeAppSect, BaseDirKey, baseDir);

  notePad.clear();

  notePad << _T("Base Directory: ") << baseDir << nCrlf;
  }


//                                    findSubDirs     basePath
//                                    getName


void Project::determineBasePath(TCchar* helpPath) {
String   s = helpPath;
int      pos;
FileSrch dirs;
String   t;
String   tgt = AppT3mplate;  tgt += _T("*.*");
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

  if (rslt) basePath = t + _T('\\');
  }


bool Project::operator() (TCchar* nam, TCchar* vis, TCchar* desc) {

  name = nam; visible = vis; description = desc;
  if (name.isEmpty()) return false;
  if (visible.isEmpty()) visible = name;
  if (description.isEmpty()) description = visible;

  preparePaths();

  copySolution();
  copyProject();
  copyHelp();

  return true;
  }


void Project::preparePaths() {
String path;

  testSolPath = basePath + TestSolDir;                      // Source Paths
  testPrjPath = basePath + TestPrjDir;
  testHlpPath = basePath + TestHlpDir;

  path     = baseDir + name;                                // Destination Paths
  sltnPath = path + _T('\\') + name;
  projPath = sltnPath + _T(".prj");
  resPath  = projPath + _T("\\res");
  helpPath = path     + _T('\\') + name + _T(".hlp");
  tmplPath = helpPath + _T("\\Templates");

  CreateDirectory(path,     0); CreateDirectory(sltnPath, 0);
  CreateDirectory(projPath, 0); CreateDirectory(resPath,  0);
  CreateDirectory(helpPath, 0); CreateDirectory(tmplPath, 0);

  sltnPath += _T('\\');  projPath += _T('\\');   resPath += _T('\\');   helpPath +=  _T('\\');
  }



void Project::copyProject() {
String  srcName = AppT3mplate;  srcName += _T(".vcxproj");
FLIter  iter(fileList);
String* p;

  copyVxcproj(testPrjPath, projPath, srcName);
  copyProj(_T(".vcxproj.filters"), PrjFix);
  copyProj(_T(".vcxproj.user"),    PrjFix);
  copyProj(_T(".vpj"),             SEFix);

  for (p = iter(); p; p = iter++) copyFile(testPrjPath, projPath, *p);
  }


void Project::copyHelp() {
FLIter  iter(fileList);
String* p;

  copyVxcproj(testHlpPath, helpPath, _T("AppT3mplateHelp.vcxproj"));
  copyHelpPrj(_T("AppT3mplateHelp.vcxproj.filters"), PrjFix);
  copyHelpPrj(_T("AppT3mplateHelp.vcxproj.user"),    PrjFix);
  copyHelpPrj(_T("AppT3mplateHelp.vpj"),             SEFix);

  for (p = iter(); p; p = iter++) copyFile(testHlpPath, helpPath, *p);
  }


void Project::copyFile(String& srcPath, String& dstPath, String& srcName) {
String dstName;
String srcFilePath;
String dstFilePath;

  if (srcName.find(_T(".bmp")) > 0 || srcName.find(_T(".ico")) > 0) {
    srcFilePath = srcPath + srcName;
    dstName     = srcName;  renamAppT3mplate(dstName);
    dstFilePath = dstPath + dstName;

    CopyFile(srcFilePath, dstFilePath, false); return;
    }

  copyFile(srcPath, dstPath, srcName, SrcFix);
  }



void Project::copySolution() {
String srcName  = AppT3mplate; srcName += _T(".sln");   copyFile(testSolPath, sltnPath, srcName, SlnFix);
}


void Project::copyVxcproj(String& srcPath, String& dstPath, TCchar* srcName) {

  fileList.clear(); incl.clear(); cmpl.clear(); res.clear(); none.clear(); image.clear();

  copyFile(srcPath, dstPath, srcName, VxcFix);
  }


void Project::copyProj(TCchar* suffix, FixIt fixIt)
       {String srcName = AppT3mplate; srcName += suffix;   copyFile(testPrjPath, projPath, srcName, fixIt);}
void Project::copyHelpPrj(TCchar* srcName, FixIt fixIt)
                                                      {copyFile(testHlpPath, helpPath, srcName, fixIt);}


void Project::copyFile(String& srcPath, String& dstPath, TCchar* srcName, FixIt fixIt) {
String dstName     = srcName;                  renamAppT3mplate(dstName);
String srcFilePath = srcPath + srcName;
String dstFilePath = dstPath + dstName;
FSIter iter(fileStore);
Data*  d;

  if (!doc()->OnOpenDocument(srcFilePath)) return;

  if (fixIt == VxcFix) getFiles();

  for (d = iter(); d; d = iter++) {
    String& s = d->get();

    switch(fixIt) {
      case SlnFix : fixProjExt(s);                      // Fall Thru to perform the rename Fix
      case VxcFix : fixGuids(s);
      case SEFix  :
      case PrjFix : renamAppT3mplate(s);   break;
      case SrcFix : renamAppT3mplate(s);   renamDesc(s);   renamVisibleName(s); break;
      }
    }

  if (fixIt == SEFix)  {SlickEdit se;    se.fix();}
  if (fixIt == VxcFix) {fileStore.sort(incl.beg, incl.end);  fileStore.sort(cmpl.beg, cmpl.end);}

  fileStore.display(dstName);   invalidate();

  doc()->OnSaveDocument(dstFilePath);
  }


void Project::getFiles() {
FSIter iter(fileStore);
Data*  d;
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


void Project::fixGuids(String& s) {
String prefix;
String suffix;

  if (!mngGuid.findGuid(s, suffix)) return;

  for (prefix = suffix; mngGuid.findGuid(prefix, suffix); prefix = suffix) s += prefix;

  s += prefix;
  }


static TCchar* PrjTarget  = _T("AppT3mplate.prj");
static int     NPrjTarget = _tcslen(PrjTarget);


void Project::fixProjExt(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(PrjTarget); pos >= 0; pos = s.find(_T("AppT3mplate.prj"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos + NPrjTarget);

    s = prefix + name + _T(".prj") + suffix;
    }
  }


static TCchar* NameTarget  = _T("AppT3mplate");
static int     NNameTarget = _tcslen(NameTarget);


void Project::renamAppT3mplate(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(NameTarget); pos >= 0; pos = s.find(NameTarget)) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+NNameTarget);

    s = prefix + name + suffix;
    }
  }


static TCchar* TitleTarget  = _T("App Template");
static int     NTitleTarget = _tcslen(TitleTarget);


void Project::renamVisibleName(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(TitleTarget); pos >= 0; pos = s.find(TitleTarget)) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+NTitleTarget);

    s = prefix + visible + suffix;
    }
  }


static TCchar* AppLine  = _T("A Template for MFC Applications");
static int     NAppLine = _tcslen(AppLine);


void Project::renamDesc(String& s) {
String prefix;
String suffix;
int    pos = s.find(AppLine); if (pos < 0) return;

  prefix = s.substr(0, pos);  suffix = s.substr(pos+NAppLine);

  s = prefix + description + suffix;
  }

