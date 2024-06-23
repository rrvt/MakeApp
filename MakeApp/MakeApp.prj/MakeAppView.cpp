// MakeAppView.cpp : implementation of the MakeAppView class


#include "pch.h"
#include "MakeAppView.h"
#include "IniFile.h"
#include "ListFonts.h"
#include "MakeApp.h"
#include "MakeAppDoc.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "Resources.h"
#include "RptOrientDlgTwo.h"


static TCchar* FontOrietnKey = _T("Font");


// MakeAppView

IMPLEMENT_DYNCREATE(MakeAppView, CScrView)

BEGIN_MESSAGE_MAP(MakeAppView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
END_MESSAGE_MAP()


MakeAppView::MakeAppView() noexcept : dspFonts(dMgr.getNotePad()), prtFonts(pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }



void MakeAppView::OnInitialUpdate() {
  CScrView::OnInitialUpdate();
  }


void MakeAppView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  if (dlg.DoModal() == IDOK) {
    pMgr.setFontScale(printer.scale);
    }
  }


void MakeAppView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Font:");
  dlg.ntpd = printer.toStg(prtNote.prtrOrietn);
  dlg.rpt1 = printer.toStg(prtFonts.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    prtNote.prtrOrietn  = printer.toOrient(dlg.ntpd);
    prtFonts.prtrOrietn = printer.toOrient(dlg.rpt1);
    saveRptOrietn();
    }
  }


void MakeAppView::initRptOrietn()
    {prtFonts.prtrOrietn = (PrtrOrient) iniFile.readInt(RptOrietnSect, FontOrietnKey, PortOrient);}


void MakeAppView::saveRptOrietn()
    {saveNoteOrietn();   iniFile.write(RptOrietnSect, FontOrietnKey,  (int) prtFonts.prtrOrietn);}


void MakeAppView::OnPrepareDC(CDC* dc, CPrintInfo* info) {

  if(doc()->dataSrc() == FontSrc) listFonts(dc);

  CScrView::OnPrepareDC(dc, info);
  }


void MakeAppView::onPreparePrinting(CPrintInfo* info) {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onPreparePrinting(info);     break;
#ifdef Examples
    case FontSrc    : prtFonts.onPreparePrinting(info);    break;
#endif
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void MakeAppView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.onBeginPrinting(*this);  break;
    case FontSrc    : prtFonts.onBeginPrinting(*this); break;
    }
  }


void MakeAppView::onDisplayOutput() {

  switch(doc()->dataSrc()) {
    case NotePadSrc : dspNote.display(*this);  break;
    case FontSrc    : dspFonts.display(*this); break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should
// not be a great hardship to construct a footer.

void MakeAppView::printFooter(DevBase& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc : prtNote.prtFooter(dev, pageNo);  break;
    case FontSrc    : prtFonts.prtFooter(dev, pageNo); break;
    }
  }


void MakeAppView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case FontSrc    : break;
    }
  }


void MakeAppView::OnSetFocus(CWnd* pOldWnd) {

  CScrView::OnSetFocus(pOldWnd);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
    case FontSrc : break;
    }
  }


// MakeAppView diagnostics

#ifdef _DEBUG

void MakeAppView::AssertValid() const          {CScrollView::AssertValid();}
void MakeAppView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                                                    // non-debug version is inline
MakeAppDoc* MakeAppView::GetDocument() const
                    {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(MakeAppDoc))); return (MakeAppDoc*)m_pDocument;}
#endif //_DEBUG


