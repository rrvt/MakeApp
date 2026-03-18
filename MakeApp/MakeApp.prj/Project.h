// Project Management -- Make changes and copy


#pragma once
#include "Bounds.h"
#include "Context.h"
#include "FileList.h"
#include "FixFilter.h"
#include "ManageGuid.h"
#include "ProjectNameDlg.h"
#include "RenameApp.h"

class MakeAppDoc;


class Project {

enum FileType {NilType, SlnType, PrjType, FltType, SrcType, SEType, WxsType, WxdType};
enum FixIt    {         SlnFix,  PrjFix,  FltFix,  SrcFix,  SEFix,  WxsFix,  WxdFix};


Context    ctx;
AppType&   appType;
String&    name;
String&    targetName;
String&    dialogName;
String&    visible;
String&    description;
String&    appRoot;

String     srcRoot;                             // Base Path where MakeApp resides
String     srcPath;                             // Current Source Path
String     dstPath;                             // Current destination directory
String     defFileName;

RenameApp  renameAppName;
FixFilter  fixFilter;
ManageGuid mngGuid;

Bounds     incl;
Bounds     cmpl;
Bounds     res;
Bounds     none;
Bounds     image;

public:

  Project() : ctx(),                targetName(ctx.targetName),   dialogName(ctx.dialogName),
              appRoot(ctx.appRoot), name(ctx.name),               appType(ctx.appType),
              visible(ctx.visible), description(ctx.description), renameAppName(ctx),
              fixFilter(ctx) { }
 ~Project() { }

  void setSourcePath(TCchar* helpPath);
  void setBaseDir() {ctx.setBaseDir();}
  void getBaseDir() {ctx.getBaseDir();}

  bool operator() (ProjectNameDlg& dlg);

private:

  // if Segment not zero, then path includes it
  // returns source path in src, destination path as return value

  void preparePath(TCchar* pathName, TCchar* segment = 0);

  void copyFiles(TCchar* srcDirName);
  void copyGlobal(TCchar* srcName, TCchar* dstName);
  void copyFixable(TCchar* path);
  bool mustCopy(String& fileName, FileType& fileType);
  bool createDir(TCchar* path);

  void copyFile(TCchar* dstName, FixIt fixIt);
  void copyFile(String& srcName);

  void copyDir(TCchar* srcDirName);             // Copy directory (and files) and rename files
  void renameSubDirFiles(TCchar* path);         // Rename files in dstPath and subdirectories
  void renameFiles(TCchar* path);               // Rename files at path

  void getFiles();

  void fixReadMe(String& s);
  bool fixProject(String& s);
//  bool fixFilter(String& s);
  bool fixSource(String& s);
  void renamDesc(String& s);
  void renamVisibleName(String& s);
  void fixPath(String& srcPath, String& dstPath, String& s);
  void renameMakeApp(String& s);

  bool xcldExample(String& s, TCchar* stg) {return ctx.xcldExample(s, stg);}
  };


extern Project project;



//////-----------------

//  void renameAppName(String& s);
//  void getBaseDirUser();

//  void determineBasePath(TCchar* helpPath);
#if 0
bool       inclExmpls;
AppType    appType;
String     name;
String     visible;
String     description;

String     dstRoot;                             // Destiantion base Direcotry
String     appRoot;                             // application base directory

String     targetName;
String     dialogName;
#endif

