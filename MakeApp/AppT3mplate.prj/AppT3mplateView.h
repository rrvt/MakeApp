// AppT3mplateView.h : interface of the AppT3mplateView class


#pragma once
#include "ScrollView.h"
#include "AppT3mplate.h"
#include "AppT3mplateDoc.h"
#include "DisplayNtPd.h"
#include "Printer.h"


class AppT3mplateView : public ScrollView {

CMenu      menu;
CMenu      sub;

protected: // create from serialization only

  AppT3mplateView() noexcept;

  DECLARE_DYNCREATE(AppT3mplateView)

public:

  virtual         ~AppT3mplateView() { }

  virtual BOOL     PreCreateWindow(CREATESTRUCT& cs) {return ScrollView::PreCreateWindow(cs);}
  virtual void     OnInitialUpdate()                 {ScrollView::OnInitialUpdate();}

  virtual void     setHeader(DisplayNtPd& dsplyNp)
                                               {dsplyNp.setHeader(_T("Arial"), 120, &getHeader);}
  virtual void     setFooter(DisplayNtPd& dsplyNp)
                                               {dsplyNp.setFooter(_T("arial"), 120, &getFooter);}
  virtual NotePad& onPrepareOutput() {return doc()->getData();}
                                                        // Create output on a notepad and return it
// Print Data functions

  virtual bool     onPreparePrinter(PrinterInfo& info);
  virtual NotePad& onPreparePrinting() {return doc()->getData();}
  virtual void     setHeader(PrintNtPd& prntNp)
                                              {prntNp.setHeader(_T("Arial"), 120, &getHeader);}
  virtual void     setFooter(PrintNtPd& prntNp)
                                              {prntNp.setFooter(_T("Courier New"), 60, getFooter);}
  static  void     getHeader(NotePad& np, int pageNo, int noPages)
                                                           {doc()->getHeader(np, pageNo, noPages);}
  static  void     getFooter(NotePad& np, int pageNo, int noPages)
                                                           {doc()->getFooter(np, pageNo, noPages);}
  AppT3mplateDoc*  GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()
  afx_msg void onFilePrint();
  afx_msg void onFilePrintPreview();
  afx_msg void onSetupPrinter();

  afx_msg void OnLButtonDown(  UINT nFlags, CPoint point);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

  afx_msg void OnContextMenu(  CWnd* ,      CPoint point);
  afx_msg void onCopy();
  afx_msg void onPup1();
  afx_msg void onPup2();
  };


#ifndef _DEBUG  // debug version in AppT3mplateView.cpp
inline AppT3mplateDoc* AppT3mplateView::GetDocument() const
                                           {return reinterpret_cast<AppT3mplateDoc*>(m_pDocument);}
#endif




//////////-----------------

#if 0
  virtual void       initNoteOrietn();
  virtual void       saveNoteOrietn();
  virtual void       initRptOrietn();
  virtual void       saveRptOrietn();
  virtual PrtrOrient getOrientation() {return prtNote.prtrOrietn;}
#endif
//  virtual void       displayHeader(DevStream& dev);
//  virtual void       displayFooter(DevStream& dev);

