// Project Management -- Make changes and copy


#pragma once
#include "Bounds.h"
#include "FileList.h"
#include "ManageGuid.h"

class MakeAppDoc;



class Project {

enum FixIt {SlnFix, VxcFix, PrjFix, SrcFix, SEFix};

String        name;
String        visible;
String        description;

String        basePath;                            // Base Path where MakeApp resides
String        testSolPath;                         // Source directories
String        testPrjPath;
String        testHlpPath;


String        baseDir;                             // Destination base directory
String        sltnPath;                            // Destination directories
String        projPath;
String        resPath;
String        helpPath;
String        tmplPath;

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


  bool operator() (TCchar* nam, TCchar* vis, TCchar* desc);

private:

  void preparePaths();
  void copyProject();
  void copyHelp();

  void copySolution();
  void copyVxcproj(String& srcPath, String& dstPath, TCchar* srcName);
  void copyProj(TCchar* suffix, FixIt fixIt);
  void copyHelpPrj(TCchar* srcName, FixIt fixIt);
  void copyFile(String& srcPath, String& dstPath, String& srcName);

  void copyFile(String& srcPath, String& dstPath, TCchar* dstName, FixIt fixIt);

  void getFiles();
  void fixGuids(String& s);
  void fixProjExt(String& s);

  void renamAppT3mplate(String& s);
  void renamVisibleName(String& s);
  void renamDesc(String& s);
  };


extern Project project;



//  void copyVxcprojFilters(String& srcFilePath, String& dstPath, TCchar* dstFileName);
//  void copyVxcprojUser(String& srcFilePath, String& dstPath, TCchar* dstFileName);
//  void getFiles(Bounds& bnds);
//  void copySlickEditVpj(String& srcFilePath, String& dstPath, TCchar* dstFileName);
//  void copyPrjFiles(String& fileName);
//  void copyHlpFiles(String& fileName);
//  void copyHlpVxcprojFilters();
//  void copyHlpVxcprojUser();
//  void copyHlpSlickEditVpj();
//  void copyHlpVxcproj();
//  void copyPrjVxcprojFilters();
//  void copyPrjVxcprojUser();
//  void copyPrjSlickEditVpj();
//  void copyPrjVxcproj();

