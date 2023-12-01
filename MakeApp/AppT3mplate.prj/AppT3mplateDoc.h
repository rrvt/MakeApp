// AppT3mplateDoc.h : interface of the AppT3mplateDoc class


#pragma once
#include "CDoc.h"
#include "MainFrame.h"


enum DataSource {NotePadSrc, StoreSrc, StrRptSrc, FontSrc};


class AppT3mplateDoc : public CDoc {

PathDlgDsc  pathDlgDsc;

DataSource  dataSource;

protected: // create from serialization only

  AppT3mplateDoc() noexcept;
  DECLARE_DYNCREATE(AppT3mplateDoc)

public:

  virtual BOOL OnNewDocument();

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds = NotePadSrc);

  virtual void serialize(Archive& ar);

// Implementation
public:
  virtual ~AppT3mplateDoc();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void saveFile(TCchar* title, TCchar* suffix, TCchar* fileType);


  void testLine(int n);
  void wholePage();

// Generated message map functions

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onFileOpen();

  afx_msg void onSaveFile();
  afx_msg void onSaveStrRpt();
  afx_msg void onSaveNotePad();

  afx_msg void onEditCopy();

#ifdef Examples
  afx_msg void OnTest();
  afx_msg void displayDataStore();
  afx_msg void myButton();

  afx_msg void OnComboBoxChng();

  afx_msg void OnTBEditBox();
  afx_msg void myButton1();
  afx_msg void onOption11();
  afx_msg void onOption12();
  afx_msg void onOption13();
  afx_msg void onOption21();
  afx_msg void onOption22();
  afx_msg void onOption23();
  afx_msg void OnTestEditBoxes();
#endif
  };
