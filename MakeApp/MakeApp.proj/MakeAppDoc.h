// MakeAppDoc.h : interface of the MakeAppDoc class


#pragma once
#include "CDoc.h"
#include "ManageGuid.h"


struct Bounds {
int beg;
int end;

  Bounds() {beg = end = -1;}

  void set(int i) {if (beg < 0) beg = i;   end = i;}

  bool isLegal() {return beg >= 0;}
  };


class MakeAppDoc : public CDoc {

  String                  saveAsTitle;                          // Save As Parameters, examples:
  String                  defFileName;                          // _T("mumble.txt")
  String                  defExt;                               // _T("txt")
  String                  defFilePat;                           // _T("*.txt")

protected: // create from serialization only

  MakeAppDoc() noexcept;
  DECLARE_DYNCREATE(MakeAppDoc)

public:

String                  baseDir;
String                  name;
String                  visibleName;
String                  description;
ManageGuid              mngGuid;

String                  testSolPath;
String                  testPrjPath;

String                  sltnPath;
String                  projPath;
String                  resPath;

Expandable<String, 128> files;

Bounds                  incl;
Bounds                  cmpl;
Bounds                  res;
Bounds                  none;
Bounds                  image;

  virtual BOOL OnNewDocument();

          void copySolution();
          void fixGuids(String& s);
          void fixProjExt(String& s);

          void copyProject();
          void copyVxcproj();
          void copyVxcprojFilters();
          void copyVxcprojUser();
          void copySlickEditVpj();

          void findIncl(    String& s, int i);
          void findCmpl(    String& s, int i);
          void findResCmpl( String& s, int i);
          void findNoneIncl(String& s, int i);
          void findImages(  String& s, int i);
          void getFiles(Bounds& bnds);

          void copyFiles(String& fileName);
          void renamDesc(String& s);
          void renamTestApp(String& s);
          void renamVisibleName(String& s);

          void dspData(TCchar* fileName);
          void dspLine(String s);

          void OnFileSave();

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~MakeAppDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnNameProject();
  afx_msg void OnFixSlickEdit();
  };