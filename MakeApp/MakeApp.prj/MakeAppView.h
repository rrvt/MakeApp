// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "CScrView.h"
#include "FontRpt.h"
#include "ReportNtPd.h"


class MakeAppDoc;


class MakeAppView : public CScrView {

FontRpt dspFonts;
FontRpt prtFonts;

protected:              // create from serialization only

  MakeAppView() noexcept;
  DECLARE_DYNCREATE(MakeAppView)

public:

              ~MakeAppView() { }

          void       initNoteOrietn() { }
          void       saveNoteOrietn() { }
          void       initRptOrietn();
          void       saveRptOrietn();
  virtual PrtrOrient getOrientation() {return NilOrient;}

  virtual void OnInitialUpdate();

  virtual void onPreparePrinting(CPrintInfo* info);
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void OnPrepareDC(CDC* dc, CPrintInfo* info = 0);          // Display/Printer Override

  virtual void printFooter(DevStream& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  MakeAppDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:
  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const
                                               {return reinterpret_cast<MakeAppDoc*>(m_pDocument);}
#endif

