// Project Management -- Make changes and copy


#pragma once
#include "Bounds.h"
#include "FileList.h"
#include "ManageGuid.h"
#include "ProjectNameDlg.h"

class MakeAppDoc;


class Project {

enum FileType {NilType, SlnType, VxcType, PrjType, SrcType, SEType, WxsType, WxdType};
enum FixIt    {         SlnFix,  VxcFix,  PrjFix,  SrcFix,  SEFix,  WxsFix,  WxdFix};


AppType    appType;
String     name;
String     visible;
String     description;

String     srcRoot;                             // Base Path where MakeApp resides
String     srcPath;                             // Current Source Path

String     dstRoot;                             // Destiantion base Direcotry
String     appRoot;                             // application base directory
String     dstPath;                             // Current destination directory

String     targetName;
String     dialogName;

String     defFileName;

ManageGuid mngGuid;

Bounds     incl;
Bounds     cmpl;
Bounds     res;
Bounds     none;
Bounds     image;

public:

  Project() { }
 ~Project() { }

  void getBaseDir();
  void getBaseDirUser();

  void determineBasePath(TCchar* helpPath);

  bool operator() (ProjectNameDlg& dlg);

private:

       // if Segment not zero, then path includes it
       // returns source path in src, destination path as return value

  void preparePath(TCchar* pathName, TCchar* segment = 0);
  void addSegment(String& s, TCchar* segment) {s += segment;  s += _T('\\');}

  void copyFiles(TCchar* srcDirName);
  void copyGlobal(TCchar* srcName, TCchar* dstName);
  void copyFixable(TCchar* path);
  bool mustCopy(String& fileName, FileType& fileType);
  bool createDir(TCchar* path);

  void copyFile(TCchar* dstName, FixIt fixIt);
  void copyFile(String& srcName);

  void getFiles();

  void fixReadMe(String& s);
  void renameAppName(String& s);
  void renamVisibleName(String& s);
  void renamDesc(String& s);
  void fixPath(String& srcPath, String& dstPath, String& s);
  void renameMakeApp(String& s);
  };


extern Project project;

