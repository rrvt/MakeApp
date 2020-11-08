// AppT3mplateView.h : interface of the AppT3mplateView class


#pragma once
#include "CScrView.h"
#include "NoteRpt.h"
#include "StoreRpt.h"


class AppT3mplateDoc;


class AppT3mplateView : public CScrView {

NoteRptB dspNote;
NoteRptB prtNote;
StoreRpt dspStore;
StoreRpt prtStore;

protected: // create from serialization only

  AppT3mplateView() noexcept;
//                               dspStore(dMgr.getNotePad()), prtStore(pMgr.getNotePad()) { }

  DECLARE_DYNCREATE(AppT3mplateView)

public:

  virtual ~AppT3mplateView() { }

    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool isNotePad, bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Display& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  AppT3mplateDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in AppT3mplateView.cpp
inline AppT3mplateDoc* AppT3mplateView::GetDocument() const
   { return reinterpret_cast<AppT3mplateDoc*>(m_pDocument); }
#endif

