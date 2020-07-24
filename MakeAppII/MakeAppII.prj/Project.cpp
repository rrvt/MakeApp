// Project Management -- Make changes and copy


#include "stdafx.h"
#include "Project.h"
#include "filename.h"
#include "FileStore.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MakeAppII.h"
#include "MakeAppIIDoc.h"
#include "NotePad.h"
#include "SlickEdit.h"



Project project;


static TCchar* MakeTarget  = _T("MakeAppII\\");

static TCchar* MakeAppSect = _T("MakeApp");
static TCchar* BaseDirKey  = _T("BaseDir");
static TCchar* TestApp     = _T("TestApp");
static TCchar* TestSolDir  = _T("TestApp\\");
static TCchar* TestPrjDir  = _T("TestApp.prj\\");
static TCchar* TestHlpDir  = _T("TestApp.hlp\\");


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


void Project::determineBasePath(TCchar* helpPath) {
String s = helpPath;
int    pos;

  pos = s.find(MakeTarget);   if (pos < 0) return;

  basePath = s.substr(0, pos + _tcslen(MakeTarget));
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
String  srcName = TestApp;  srcName += _T(".vcxproj");
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

  copyVxcproj(testHlpPath, helpPath, _T("TestAppHelp.vcxproj"));
  copyHelpPrj(_T("TestAppHelp.vcxproj.filters"), PrjFix);
  copyHelpPrj(_T("TestAppHelp.vcxproj.user"),    PrjFix);
  copyHelpPrj(_T("TestAppHelp.vpj"),             SEFix);

  for (p = iter(); p; p = iter++) copyFile(testHlpPath, helpPath, *p);
  }


void Project::copyFile(String& srcPath, String& dstPath, String& srcName) {
String dstName;
String srcFilePath;
String dstFilePath;

  if (srcName.find(_T(".bmp")) > 0 || srcName.find(_T(".ico")) > 0) {
    srcFilePath = srcPath + srcName;
    dstName     = srcName;  renamTestApp(dstName);
    dstFilePath = dstPath + dstName;

    CopyFile(srcFilePath, dstFilePath, false); return;
    }

  copyFile(srcPath, dstPath, srcName, SrcFix);
  }



void Project::copySolution()
  {String srcName  = TestApp; srcName += _T(".sln");   copyFile(testSolPath, sltnPath, srcName, SlnFix);}


void Project::copyVxcproj(String& srcPath, String& dstPath, TCchar* srcName) {

  fileList.clear(); incl.clear(); cmpl.clear(); res.clear(); none.clear(); image.clear();

  copyFile(srcPath, dstPath, srcName, VxcFix);
  }


void Project::copyProj(TCchar* suffix, FixIt fixIt)
       {String srcName = TestApp; srcName += suffix;   copyFile(testPrjPath, projPath, srcName, fixIt);}
void Project::copyHelpPrj(TCchar* srcName, FixIt fixIt)
                                                      {copyFile(testHlpPath, helpPath, srcName, fixIt);}


void Project::copyFile(String& srcPath, String& dstPath, TCchar* srcName, FixIt fixIt) {
String dstName     = srcName;                  renamTestApp(dstName);
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
      case PrjFix : renamTestApp(s);   break;
      case SrcFix : renamTestApp(s);   renamDesc(s);   renamVisibleName(s); break;
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


static TCchar* PrjTarget  = _T("TestApp.prj");
static int     NPrjTarget = _tcslen(PrjTarget);


void Project::fixProjExt(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(PrjTarget); pos >= 0; pos = s.find(_T("TestApp.prj"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos + NPrjTarget);

    s = prefix + name + _T(".prj") + suffix;
    }
  }


static TCchar* NameTarget  = _T("TestApp");
static int     NNameTarget = _tcslen(NameTarget);


void Project::renamTestApp(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(NameTarget); pos >= 0; pos = s.find(NameTarget)) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+NNameTarget);

    s = prefix + name + suffix;
    }
  }


static TCchar* TitleTarget  = _T("Test App");
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

