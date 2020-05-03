// MakeAppView.h : interface of the MakeAppView class


#pragma once
#include "DisplayView.h"

class MakeAppDoc;


class MakeAppView : public CScrollView {

protected: // create from serialization only

  MakeAppView() noexcept;
  DECLARE_DYNCREATE(MakeAppView)

// Attributes

DisplayView dspView;
DisplayView prtView;

String      author;
String      font;

public:

  MakeAppDoc* GetDocument() const;

// Operations
public:

          void setAuthor(TCchar* a) {author = a;}
          void setFont(  TCchar* f) {font   = f;}

// Overrides
public:
  virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* sb);
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

  virtual void OnInitialUpdate(); // called first time after construct
  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

  virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void OnPrint(        CDC* pDC, CPrintInfo* pInfo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

          void printFooter();

private:
          void setScrollSize(DisplayView& dv);

// Implementation
public:
  virtual ~MakeAppView();
#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MakeAppView.cpp
inline MakeAppDoc* MakeAppView::GetDocument() const
   { return reinterpret_cast<MakeAppDoc*>(m_pDocument); }
#endif

