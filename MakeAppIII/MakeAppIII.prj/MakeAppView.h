// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "CScrView.h"
#include "NoteRpt.h"


class MakeAppDoc;


class MakeAppView : public CScrView {

NoteRptB dspNote;
NoteRptB prtNote;

protected: // create from serialization only

  MakeAppView() noexcept;// : dspNote( nMgr.getNotePad()), prtNote(pMgr.getNotePad()) { }
  DECLARE_DYNCREATE(MakeAppView)

public:

  virtual ~MakeAppView() { }
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool isNotePad, bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Display& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  MakeAppDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

public:
  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const
   { return reinterpret_cast<MakeAppDoc*>(m_pDocument); }
#endif

