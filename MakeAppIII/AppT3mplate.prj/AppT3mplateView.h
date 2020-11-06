// AppT3mplateView.h : interface of the AppT3mplateView class


#pragma once
#include "CScrView.h"
#include "StoreRpt.h"


class AppT3mplateDoc;


class AppT3mplateView : public CScrView {

StoreRpt dspStore;
StoreRpt prtStore;

protected: // create from serialization only

  AppT3mplateView() noexcept : dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()) { }
  DECLARE_DYNCREATE(AppT3mplateView)

public:

  virtual ~AppT3mplateView() { }

//  void dsplyReport(bool start = true) {displayReport = start;}

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Display& dev, int pageNo);

  AppT3mplateDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

//  DECLARE_MESSAGE_MAP()
public:
  DECLARE_MESSAGE_MAP()
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
  };


#ifndef _DEBUG  // debug version in AppT3mplateView.cpp
inline AppT3mplateDoc* AppT3mplateView::GetDocument() const
   { return reinterpret_cast<AppT3mplateDoc*>(m_pDocument); }
#endif

