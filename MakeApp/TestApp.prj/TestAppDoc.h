// TestAppDoc.h : interface of the TestAppDoc class


#pragma once
#include "CDoc.h"


class TestAppDoc : public CDoc {

String saveAsTitle;                                            // Save As Parameters, examples:
String defFileName;                                            // _T("mumble.txt")
String defExt;                                                 // _T("txt")
String defFilePat;                                             // _T("*.txt")

protected: // create from serialization only

  TestAppDoc() noexcept;
  DECLARE_DYNCREATE(TestAppDoc)

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
  virtual ~TestAppDoc();
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
};
