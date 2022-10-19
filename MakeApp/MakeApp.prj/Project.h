// Project Management -- Make changes and copy


#pragma once
#include "Bounds.h"
#include "FileList.h"
#include "ManageGuid.h"

class MakeAppDoc;
class ProjectNameDlg;


class Project {

enum FileType {NilType, SlnType, VxcType, PrjType, SrcType, SEType, WxsType, WxdType};
enum FixIt    {         SlnFix,  VxcFix,  PrjFix,  SrcFix,  SEFix,  WxsFix,  WxdFix};

String        name;
String        visible;
String        description;

String        srcBase;                            // Base Path where MakeApp resides
String        srcPath;                            // Current Source Path

String        dstBase;                            // Destiantion base Direcotry
String        appBase;                            // application base directory
String        dstPath;                            // Current destination directory

String        targetName;

String        defFileName;

ManageGuid    mngGuid;

Bounds        incl;
Bounds        cmpl;
Bounds        res;
Bounds        none;
Bounds        image;

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

  void    preparePath(TCchar* pathName, TCchar* segment = 0);
  void    addSegment(String& s, TCchar* segment) {s += segment;  s += _T('\\');}

  void    copyFiles(TCchar* srcDirName);
  bool    mustCopy(String& fileName, FileType& fileType);
  bool    createDir(TCchar* path);

  void    copyFile(String& srcPath, String& dstPath, TCchar* dstName, FixIt fixIt);
  void    copyFile(TCchar* srcPath, TCchar* dstPath, String& srcName);

  void    getFiles();

  void    renameAppName(String& s);
  void    renamVisibleName(String& s);
  void    renamDesc(String& s);
  void    fixPath(String& srcPath, String& dstPath, String& s);
  void    renameMakeApp(String& s);
  };


extern Project project;

