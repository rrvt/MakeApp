// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"

#ifdef Examples
static int NoOfButtonControls =  6;
static int NoOfButtons        = 13;
#else
static int NoOfButtonControls =  0;
static int NoOfButtons        =  6;
#endif



MyToolBar::MyToolBar()
#ifdef Examples
                       : button(ID_Button),        editBox(ID_EditBox), cbxMenu(ID_PopupMenu),
                         cbxMenu1(ID_PopupMenu1),  cboBx(ID_CboBx),     cboBx1(ID_CboBx1)
#endif
                        {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}


#ifdef Examples

bool MyToolBar::addButton( uint id, TCchar* caption) {
  if (id == button.getId()) return add(button,  id, caption);

  return false;
  }


bool MyToolBar::addEditBox(uint id, int noChars)              {
  if (id == editBox.getId()) return add(editBox, id, noChars);

  return false;
  }


CString MyToolBar::getText(uint id) {
  if (id == editBox.getId()) {return ToolBarBase::getText(editBox);}

  return _T("");
  }


bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
  if (id == cbxMenu.getId())  return add(cbxMenu,  id, idr, caption);
  if (id == cbxMenu1.getId()) return add(cbxMenu1, id, idr, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  if (id == cbxMenu.getId())   return add(cbxMenu,  id, cbxItem, n, caption);
  if (id == cbxMenu1.getId())  return add(cbxMenu1, id, cbxItem, n, caption);

  return false;
  }


void MyToolBar::dispatch(uint id) {
  if (id == cbxMenu.getId())  ToolBarBase::dispatch(cbxMenu);
  if (id == cbxMenu1.getId()) ToolBarBase::dispatch(cbxMenu1);
  }


bool MyToolBar::addCBx(uint id) {
  if (id == cboBx.getId())  return add(cboBx,  id, 10);
  if (id == cboBx1.getId()) return add(cboBx1, id, 10);

  return false;
  }


bool MyToolBar::addCBx(uint id, int idr, TCchar* caption) {
  if (id == cboBx.getId())   return add(cboBx,  id, idr, caption);
  if (id == cboBx1.getId())  return add(cboBx1, id, idr, caption);

  return false;
  }


bool MyToolBar::addCbxItem(uint id, TCchar* txt, int data) {
  if (id == cboBx.getId())  return addItem(cboBx,  txt, data);
  if (id == cboBx1.getId()) return addItem(cboBx1, txt, data);

  return false;
  }


bool MyToolBar::addCBx(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  if (id == cboBx.getId())  return add(cboBx,  id, cbxItem, n, caption);
  if (id == cboBx1.getId()) return add(cboBx1, id, cbxItem, n, caption);

  return false;
  }


bool MyToolBar::addCbxItemSorted(uint id, TCchar* txt, int data) {
  if (id == cboBx.getId())  return addItemSorted(cboBx,  txt, data);
  if (id == cboBx1.getId()) return addItemSorted(cboBx1, txt, data);

  return false;
  }


void MyToolBar::setCaption(uint id, TCchar* caption) {
  if (id == cboBx.getId())  ToolBarBase::setCaption(cboBx,  caption);
  if (id == cboBx1.getId()) ToolBarBase::setCaption(cboBx1, caption);
  }


void MyToolBar::setWidth(uint id) {
  if (id == cboBx.getId())  ToolBarBase::setWidth(cboBx);
  if (id == cboBx1.getId()) ToolBarBase::setWidth(cboBx1);
  }


void MyToolBar::setHeight( uint id) {
  if (id == cboBx.getId())  ToolBarBase::setHeight(cboBx);
  if (id == cboBx1.getId()) ToolBarBase::setHeight(cboBx1);
  }


bool MyToolBar::getCurSel( uint id, String& s, void*& data) {
  if (id == cboBx.getId())  return ToolBarBase::getCurSel(cboBx,  s, data);
  if (id == cboBx1.getId()) return ToolBarBase::getCurSel(cboBx1, s, data);

  return false;
  }

#endif

