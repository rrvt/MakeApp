// MakeAppIIView.h : interface of the MakeAppIIView class


#pragma once
#include "CScrView.h"


class MakeAppIIDoc;


class MakeAppIIView : public CScrView {

protected: // create from serialization only

  MakeAppIIView() noexcept { }
  DECLARE_DYNCREATE(MakeAppIIView)

public:

  virtual ~MakeAppIIView() { }
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);

  MakeAppIIDoc* GetDocument() const;

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


#ifndef _DEBUG  // debug version in MakeAppIIView.cpp
inline MakeAppIIDoc* MakeAppIIView::GetDocument() const
   { return reinterpret_cast<MakeAppIIDoc*>(m_pDocument); }
#endif

