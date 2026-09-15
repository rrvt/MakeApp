// Main Dialog Box


#pragma once
#include "DialogEx.h"
#include "MyToolBar.h"
#include "NotePad.h"
#include "PrintNtPd.h"
#include "Resource.h"
#include "WinPos.h"



// Dialog4ppDlg dialog

class Dialog4ppDlg : public DialogEx {

DECLARE_DYNAMIC(Dialog4ppDlg)

String    helpPath;

MyToolBar toolBar;
bool      isInitialized;
NotePad   np;                 // Used for output to printer and ???
String    docName;

public:

                   Dialog4ppDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual         ~Dialog4ppDlg();

  virtual BOOL     OnInitDialog();

  virtual bool     onPreparePrinter(PrinterInfo& info);     // Called to update printer attributes
  virtual NotePad& onPreparePrinting();                     // Called to create a Notepad with the
                                                            // text to put on the printer
  virtual void     setHeader(PrintNtPd& prntNp);
  virtual void     setFooter(PrintNtPd& prntNp);
  static HdrFtrFn  getHdr;
  static HdrFtrFn  getFtr;

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Dialog4pp };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnOK();

  DECLARE_MESSAGE_MAP()

private:

  void            setupToolBar();
  int             findNextBrk(String& line);

public:

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);

  afx_msg void    onSetupPrinter()     {printerSetup();}
  afx_msg void    onFilePrintPreview() { }
  afx_msg void    onPrintFile()        {printFile(true);}

  afx_msg void    onAppAbout();
  afx_msg void    onHelp();

  afx_msg void    OnMove(int x, int y);
#ifdef DialogSizable
  afx_msg void    OnSize(UINT nType, int cx, int cy);
#endif
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void    onSaveHist();

#ifdef Examples
  afx_msg void    changeReady();

  afx_msg void    onTBChange(NMHDR* pNMHDR, LRESULT* pResult);

  afx_msg void    onDispatch();
  afx_msg void    onOption00();
  afx_msg void    onOption01();
  afx_msg void    onOption02();
  afx_msg void    onDispatch1();
  afx_msg void    onOption11();
  afx_msg void    onOption12();

  afx_msg void    onDispatch2() {toolBar.dispatch(ID_Options);}

  afx_msg void    onX();
  afx_msg void    onCboBxChange();
  afx_msg void    onCboBx1Change();

  afx_msg void    onTBEditBox();
#endif

private:



enum EleType {NilEle, WordEle, WhiteEle};

struct ElementX {
EleType typ{NilEle};
String  word;

  ElementX() { }

  void clear() {typ = NilEle;   word.clear();}
  };

  bool findNextBrk(String& line, ElementX& ele);
  bool findWhite(  String& line, ElementX& ele);
  };

