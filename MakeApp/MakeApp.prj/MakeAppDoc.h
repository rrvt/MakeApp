// MakeAppDoc.h : interface of the MakeAppDoc class


#pragma once
#include "CDoc.h"


enum DataSource {NotePadSrc, FontSrc};


class MakeAppDoc : public CDoc {

DataSource dataSource;

#if 1
PathDlgDsc  pathDlgDsc;
#else
String     saveAsTitle;                                      // Save As Parameters, examples:
String     defFileName;                                      // _T("mumble.txt")
String     defExt;                                           // _T("txt")
String     defFilePat;                                       // _T("*.txt")
#endif

protected: // create from serialization only

  MakeAppDoc() noexcept;
  DECLARE_DYNCREATE(MakeAppDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       resetDataSrc() {dataSource = NotePadSrc;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~MakeAppDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testLine(int n);


// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnNameProject();
  afx_msg void OnFixSlickEdit();
  afx_msg void OnTest();
  afx_msg void OnCalibDspPrt();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  afx_msg void OnFontRptOpt();
  };

