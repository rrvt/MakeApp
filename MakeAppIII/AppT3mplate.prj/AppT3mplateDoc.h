// AppT3mplateDoc.h : interface of the AppT3mplateDoc class


#pragma once
#include "CDoc.h"


class AppT3mplateDoc : public CDoc {

String saveAsTitle;                                            // Save As Parameters, examples:
String defFileName;                                            // _T("mumble.txt")
String defExt;                                                 // _T("txt")
String defFilePat;                                             // _T("*.txt")

protected: // create from serialization only

  AppT3mplateDoc() noexcept;
  DECLARE_DYNCREATE(AppT3mplateDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
  virtual BOOL OnNewDocument();

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~AppT3mplateDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnTest();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  };
