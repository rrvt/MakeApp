// MakeAppDoc.cpp : implementation of the MakeAppDoc class


#include "stdafx.h"
#include "MakeAppDoc.h"
#include "FData.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "Guid.h"
#include "MakeApp.h"
#include "NotePad.h"
#include "ProjectName.h"
#include "qsort.h"
#include "SlickEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static TCchar* TestApp     = _T("TestApp");
static TCchar* TestSolDir  = _T("TestApp\\");
static TCchar* TestPrjDir  = _T("TestApp.proj\\");

static TCchar* PrjSection  = _T("Project");
static TCchar* PrjNameKey  = _T("Name");
static TCchar* PrjVisKey   = _T("VisibleName");
static TCchar* PrjDesc     = _T("Description");

// MakeAppDoc

IMPLEMENT_DYNCREATE(MakeAppDoc, CDocument)

BEGIN_MESSAGE_MAP(MakeAppDoc, CDocument)
  ON_COMMAND(ID_NameProject,  &MakeAppDoc::OnNameProject)
  ON_COMMAND(ID_FixSlickEdit, &MakeAppDoc::OnFixSlickEdit)
  ON_COMMAND(ID_FILE_SAVE,    &MakeAppDoc::OnFileSave)
END_MESSAGE_MAP()


// MakeAppDoc construction/destruction

MakeAppDoc::MakeAppDoc() noexcept {
  testSolPath = theApp.basePath + TestSolDir;
  testPrjPath = theApp.basePath + TestPrjDir;

  saveAsTitle = _T("Make App");   defExt = _T("txt");   defFilePat= _T("*.txt");
  }




MakeAppDoc::~MakeAppDoc() { }


BOOL MakeAppDoc::OnNewDocument() {return CDocument::OnNewDocument();}


// MakeAppDoc commands

void MakeAppDoc::OnNameProject() {
ProjectName prjName;
String      path;

    iniFile.readString(PrjSection, PrjNameKey, prjName.name);
    iniFile.readString(PrjSection, PrjVisKey,  prjName.visibleName);
    iniFile.readString(PrjSection, PrjDesc,    prjName.description);

  if (prjName.DoModal() == IDOK) {
    name = prjName.name;   visibleName = prjName.visibleName;   description = prjName.description;

    iniFile.writeString(PrjSection, PrjNameKey, prjName.name);
    iniFile.writeString(PrjSection, PrjVisKey,  prjName.visibleName);
    iniFile.writeString(PrjSection, PrjDesc,    prjName.description);

    if (name.isEmpty()) return;
    if (visibleName.isEmpty()) visibleName = name;
    if (description.isEmpty()) description = visibleName;

    path = baseDir + name;    sltnPath = path + _T('\\') + name;   projPath = sltnPath + _T(".prj");
    resPath = projPath + _T("\\res");

    CreateDirectory(path,     0); CreateDirectory(sltnPath, 0);
    CreateDirectory(projPath, 0); CreateDirectory(resPath,  0);

    sltnPath += _T('\\');  projPath += _T('\\');   resPath +=  _T('\\');

    copySolution();
    copyProject();

    invalidate();
    }
  }


void MakeAppDoc::copySolution() {
String filePath    = testSolPath + TestApp + _T(".sln");
String fileName    = name    + _T(".sln");
String dstFile     = sltnPath + fileName;
int    i;
int    n;

  if (!OnOpenDocument(filePath)) return;   n = fData.end();

  for (i = 0; i < n; i++) {
    String& s = fData[i].line;

    fixGuids(s);   fixProjExt(s);   renamTestApp(s);
    }

  dspData(fileName);

  OnSaveDocument(dstFile);
  }


void MakeAppDoc::fixGuids(String& s) {
String prefix;
String suffix;

  if (!mngGuid.findGuid(s, suffix)) return;

  for (prefix = suffix; mngGuid.findGuid(prefix, suffix); prefix = suffix) s += prefix;

  s += prefix;
  }


void MakeAppDoc::fixProjExt(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(_T("TestApp.proj")); pos >= 0; pos = s.find(_T("TestApp.proj"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+12);

    s = prefix + name + _T(".prj") + suffix;
    }
  }


void MakeAppDoc::copyProject() {
int i;
int n;

  copyVxcproj(); copyVxcprojFilters(); copyVxcprojUser(); copySlickEditVpj();

  n = files.end();

  for (i = 0; i < n; i++) copyFiles(files[i]);
  }


void MakeAppDoc::copyVxcproj() {
String filePath = testPrjPath + TestApp + _T(".vcxproj");
String fileName = name    + _T(".vcxproj");
String dstFile  = projPath + fileName;
int    i;
int    n;

  if (!OnOpenDocument(filePath)) return;   n = fData.end();

  for (i = 0; i < n; i++) {
    String& s = fData[i].line;
    findIncl(s, i);   findCmpl(s, i);   findResCmpl(s, i);   findNoneIncl(s, i);   findImages(s, i);
    }

  getFiles(incl);
  getFiles(cmpl);
  getFiles(res);
  getFiles(none);
  getFiles(image);

  for (i = 0; i < n; i++) {String& s = fData[i].line;   fixGuids(s);   renamTestApp(s);}

  if (incl.isLegal()) {qsort(&fData[incl.beg], &fData[incl.end]); }
  if (cmpl.isLegal()) {qsort(&fData[cmpl.beg], &fData[cmpl.end]); }

  dspData(fileName);

  OnSaveDocument(dstFile);
  }


void MakeAppDoc::copyVxcprojFilters() {
String filePath = testPrjPath + TestApp + _T(".vcxproj.filters");
String fileName = name + _T(".vcxproj.filters");
String dstFile  = projPath + fileName;
int    i;
int    n;

  if (!OnOpenDocument(filePath)) return;   n = fData.end();

  for (i = 0; i < n; i++) {String& s = fData[i].line;   renamTestApp(s);}

  dspData(fileName);

  OnSaveDocument(dstFile);
  }


void MakeAppDoc::copyVxcprojUser() {
String filePath = testPrjPath + TestApp + _T(".vcxproj.user");
String fileName = name + _T(".vcxproj.user");
String dstFile  = projPath + fileName;
int    i;
int    n;

  if (!OnOpenDocument(filePath)) return;   n = fData.end();

  for (i = 0; i < n; i++) {String& s = fData[i].line;   renamTestApp(s);}

  dspData(fileName);

  OnSaveDocument(dstFile);
  }


void MakeAppDoc::copySlickEditVpj() {
String filePath = testPrjPath + TestApp + _T(".vpj");
String fileName = name + _T(".vpj");
String dstFile  = projPath + fileName;
int    i;
int    n;

  if (!OnOpenDocument(filePath)) return;   n = fData.end();

  for (i = 0; i < n; i++) {String& s = fData[i].line;  renamTestApp(s);}

  SlickEdit se;    se.fix();

  dspData(fileName);

  OnSaveDocument(dstFile);
  }


void MakeAppDoc::findIncl(String& s, int i) {if (s.find(_T("ClInclude Include")) >= 0) incl.set(i);}


void MakeAppDoc::findCmpl(String& s, int i) {if (s.find(_T("ClCompile Include")) >= 0) cmpl.set(i);}


void MakeAppDoc::findResCmpl(String& s, int i)
                                            {if (s.find(_T("ResourceCompile Include")) >= 0)
                                              res.set(i);
                                              }

void MakeAppDoc::findNoneIncl(String& s, int i) {if (s.find(_T("None Include")) >= 0) none.set(i);}


void MakeAppDoc::findImages(String& s, int i) {if (s.find(_T("Image Include")) >= 0) image.set(i);}


void MakeAppDoc::getFiles(Bounds& bnds) {
int    i;
String s;
int    pos;

  if (!bnds.isLegal())
    return;

  for (i = bnds.beg; i <= bnds.end; i++) {
    s = fData[i].line;
    pos = s.find(_T("Include=\"")) + 9;   s = s.substr(pos);
    pos = s.find(_T('\"'));               s = s.substr(0, pos);

    if (s[0] == _T('.')) continue;

    files[files.end() ] = s;
    }
  }


void MakeAppDoc::copyFiles(String& fileName) {
String dstName = fileName;                  renamTestApp(dstName);
String srcPath = testPrjPath + fileName;
String dstFile = projPath    + dstName;
int    i;
int    n;

if (fileName.find(_T(".rc")) > 0) {
int x = 1;
}

  if (fileName.find(_T(".bmp")) > 0 || fileName.find(_T(".ico")) > 0)
                                                            {CopyFile(srcPath, dstFile, false); return;}
  if (!OnOpenDocument(srcPath)) return;   n = fData.end();

  for (i = 0; i < n; i++)
                   {String& s = fData[i].line;   renamDesc(s);   renamTestApp(s);   renamVisibleName(s);}

  OnSaveDocument(dstFile);

  dspData(dstName);
  }


void MakeAppDoc::renamDesc(String& s) {
  String prefix;
  String suffix;
  int    pos = s.find(_T("A Template for MFC Applications")); if (pos < 0) return;

  prefix = s.substr(0, pos);  suffix = s.substr(pos+31);

  s = prefix + description + suffix;
  }


void MakeAppDoc::renamTestApp(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(_T("TestApp")); pos >= 0; pos = s.find(_T("TestApp"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+7);

    s = prefix + name + suffix;
    }
  }


void MakeAppDoc::renamVisibleName(String& s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(_T("Test App")); pos >= 0; pos = s.find(_T("Test App"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+8);

    s = prefix + visibleName + suffix;
    }
  }


void MakeAppDoc::OnFixSlickEdit() {
String    path;
String    mainName;
SlickEdit se;

  saveAsTitle = _T("Slickedit Project File");   defExt = _T("vpj");   defFilePat = _T("*.vpj");

  if (!getPathDlg(saveAsTitle, 0, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  if (!OnOpenDocument(path)) return;

  se.fix();

  dspData(getMainName(path));

  invalidate();
  }


void MakeAppDoc::dspData(TCchar* fileName) {
int i;
int n = fData.end();

  notePad << nClrTabs;   for (i = 0; i < 30; i++) notePad << nSetTab(i*2);

  notePad << nCrlf << fileName << nCrlf << nCrlf;

  if (n && fData[0].line[0] != 0xef) dspLine(fData[0].line);

  for (i = 1; i < n; i++) dspLine(fData[i].line);

  notePad << _T("--------------") << nCrlf;
  }


void MakeAppDoc::dspLine(String s) {
String prefix;
String suffix;
int    pos;

  for (pos = s.find(_T("\t")); pos >= 0; pos = s.find(_T("\t"))) {

    prefix = s.substr(0, pos);  suffix = s.substr(pos+1);

    if (!prefix.isEmpty()) notePad << prefix;   notePad << nTab;

    s = suffix;
    }

  if (!s.isEmpty()) notePad << s;

  notePad << nCrlf;
  }



void MakeAppDoc::OnFileSave() {
String path;

  if (!getSaveAsPathDlg(saveAsTitle, defFileName, defExt, defFilePat, path)) return;

  OnSaveDocument(path);
  }


// MakeAppDoc serialization

void MakeAppDoc::serialize(Archive& ar) {
int i;

  if (ar.isStoring()) {
    int n = fData.end();

    for (i = 0; i < n; i++) {ar.write(fData[i].line); ar.crlf();}
    return;
    }

  Tchar  ch;
  String s;

  fData.clr();  i = 0;

  while (ar.read(ch)) {
    if (ch == _T('\n')) {
      fData[i++].line = s;   s.clear();   continue;
      }
    if (ch == _T('\r')) continue;

    s += ch;
    }

  if (!s.isEmpty()) fData[i++].line = s;
  }


// MakeAppDoc diagnostics

#ifdef _DEBUG
void MakeAppDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void MakeAppDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG
