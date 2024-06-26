// MakeAppDoc.h : interface of the MakeAppDoc class


#pragma once
#include "CDoc.h"


enum DataSource {NotePadSrc, FontSrc};


class MakeAppDoc : public CDoc {

DataSource  dataSource;
PathDlgDsc  pathDlgDsc;

protected: // create from serialization only

  MakeAppDoc() noexcept;
  DECLARE_DYNCREATE(MakeAppDoc)

public:

  virtual     ~MakeAppDoc();

  virtual BOOL OnNewDocument();

  DataSource   dataSrc() {return dataSource;}
  void         resetDataSrc() {dataSource = NotePadSrc;}
  void         display(DataSource ds);

  virtual void serialize(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void testLine(int n);

protected:
  DECLARE_MESSAGE_MAP()

public:
  afx_msg void OnNameProject();
  afx_msg void OnFixSlickEdit();
  afx_msg void OnTest();
  afx_msg void OnCalibDspPrt();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnFontRptOpt();
  };


