// My ToolBar


#pragma once
#include "ExamplesDef.h"


#ifdef Examples
#include "TBButton.h"
#include "TBEditBox.h"
#include "TBCbxMenu.h"
#include "TBCboBx.h"
#endif
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

#ifdef Examples

TBButton  button;
TBEditBox editBox;
TBCbxMenu cbxMenu;
TBCbxMenu cbxMenu1;
TBCboBx   cboBx;
TBCboBx   cboBx1;

#endif

public:

  MyToolBar();
 ~MyToolBar() { }

#ifdef Examples

  bool    addButton( uint id, TCchar* caption);

  bool    addEditBox(uint id, int     noChars);
  CString getText(uint id);

  bool    addMenu(   uint id, int     idr, TCchar* caption);
  bool    addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
  void    dispatch(uint id);

  bool    addCBx(    uint id);
  bool    addCBx(    uint id, int     idr, TCchar* caption);
  bool    addCbxItem(uint id, TCchar* txt, int data = 0);
  bool    addCBx(    uint id, CbxItem cbxItem[], int n, TCchar* caption);
  bool    addCbxItemSorted(uint id, TCchar* txt, int data = 0);
  void    setCaption(uint id, TCchar* caption);
  void    setWidth(  uint id);
  void    setHeight( uint id);
  bool    getCurSel( uint id, String& s, int& data);
#endif
  };

