// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "CScrView.h"

class MakeAppDoc;


class MakeAppView : public CScrView {

protected: // create from serialization only

  MakeAppView() noexcept { }
  DECLARE_DYNCREATE(MakeAppView)

public:

  virtual ~MakeAppView() { }

  MakeAppDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

  DECLARE_MESSAGE_MAP()
  };

#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const
   { return reinterpret_cast<MakeAppDoc*>(m_pDocument); }
#endif

