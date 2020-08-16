// AppT3mplateView.h : interface of the AppT3mplateView class


#pragma once
#include "CScrView.h"


class AppT3mplateDoc;


class AppT3mplateView : public CScrView {

protected: // create from serialization only

  AppT3mplateView() noexcept { }
  DECLARE_DYNCREATE(AppT3mplateView)

public:

  virtual ~AppT3mplateView() { }

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput();

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
  };


#ifndef _DEBUG  // debug version in AppT3mplateView.cpp
inline AppT3mplateDoc* AppT3mplateView::GetDocument() const
   { return reinterpret_cast<AppT3mplateDoc*>(m_pDocument); }
#endif

