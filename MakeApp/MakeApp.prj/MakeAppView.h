// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "CScrView.h"
#include "FontRpt.h"
#include "NotePadRpt.h"


class MakeAppDoc;


class MakeAppView : public CScrView {

NotePadRpt dspNote;
NotePadRpt prtNote;
FontRpt    dspFonts;
FontRpt    prtFonts;

protected:              // create from serialization only

  MakeAppView() noexcept;
  DECLARE_DYNCREATE(MakeAppView)

public:

              ~MakeAppView() { }
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void OnPrepareDC(CDC* dc, CPrintInfo* info = 0);                // Display/Printer Override

  virtual void printFooter(DevBase& dev, int pageNo);
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
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const {return reinterpret_cast<MakeAppDoc*>(m_pDocument);}
#endif




//  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
//  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//  afx_msg void onSetupPrinter();

