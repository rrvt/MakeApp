// MakeAppIIDoc.h : interface of the MakeAppIIDoc class


#pragma once
#include "CDoc.h"


class MakeAppIIDoc : public CDoc {

String saveAsTitle;                                            // Save As Parameters, examples:
String defFileName;                                            // _T("mumble.txt")
String defExt;                                                 // _T("txt")
String defFilePat;                                             // _T("*.txt")

protected: // create from serialization only

  MakeAppIIDoc() noexcept;
  DECLARE_DYNCREATE(MakeAppIIDoc)

public:

  virtual BOOL OnNewDocument();

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~MakeAppIIDoc();
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
  afx_msg void OnTest();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnOptions();
  };

