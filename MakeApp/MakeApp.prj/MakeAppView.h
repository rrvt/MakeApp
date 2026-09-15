// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "ScrollView.h"
#include "DisplayNtPd.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "Printer.h"


class MakeAppDoc;


class MakeAppView : public ScrollView {

protected:              // create from serialization only

  MakeAppView() noexcept;
  DECLARE_DYNCREATE(MakeAppView)

public:

  virtual         ~MakeAppView() { }

  virtual void     OnInitialUpdate() {ScrollView::OnInitialUpdate();}

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
  MakeAppDoc*      GetDocument() const;

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
  };


#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const
                                               {return reinterpret_cast<MakeAppDoc*>(m_pDocument);}
#endif





/////////---------------------
#if 0
          void       initNoteOrietn() { }
          void       saveNoteOrietn() { }
          void       initRptOrietn();
          void       saveRptOrietn();
  virtual PrtrOrient getOrientation() {return NilOrient;}
#endif
#if 0
  virtual void onPreparePrinting(CPrintInfo* info);
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void OnPrepareDC(CDC* dc, CPrintInfo* info = 0);          // Display/Printer Override

  virtual void printFooter(DevStream& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
#endif
//#include "FontRpt.h"
//#include "ReportNtPd.h"

