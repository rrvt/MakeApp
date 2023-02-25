// font Manager II -- Second attempt at managing fonts in Windows!!!


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class DevCtx;


struct FontAttr {
DevCtx* dvx;
String  face;              // Current Attributes
double  sz;
bool    bold;
bool    italic;
bool    underline;
bool    strikeout;

  FontAttr()               : dvx(0), sz(0), bold(false), italic(false),
                                                                    underline(false), strikeout(false) { }
  FontAttr(DevCtx& devCtx) : dvx(&devCtx), sz(0.0), bold(false), italic(false),
                                                                        underline(false), strikeout(0) { }

 ~FontAttr();

  FontAttr& operator= (FontAttr& d) {copy(d); return *this;}

  void clear();

  void init(DevCtx& devCtx, TCchar* name, double siz);

  void setFace(TCchar* face) {this->face      = face; createFont();}
  void setSize(double  size) {this->sz        = size; createFont();}
  void setBold()             {this->bold      = true; createFont();}
  void setItalic()           {this->italic    = true; createFont();}
  void setUnderLine()        {this->underline = true; createFont();}
  void setStrikeOut()        {this->strikeout = true; createFont();}

  bool createFont();

private:

  void copy(FontAttr& d);
  };


typedef DatumPtrT<FontAttr> FontAttrP;                      // Usually defined just before iterator


class FontMgr {
FontAttr*                           cur;
int                                 stkX;
ExpandableP<FontAttr, FontAttrP, 8> data;

public:

  FontMgr() : stkX(-1), cur(0) { }            //, scale(0.0)
 ~FontMgr();

  FontMgr&  operator= (FontMgr& fm) {copy(fm); return *this;}

  void      setBase(DevCtx& dvx, TCchar* face, double fontSize);
  void      setFace(TCchar* face) {FontAttr& attr = *next();   attr.setFace(face);}
  void      setSize(double  size) {FontAttr& attr = *next();   attr.setSize(size);}
  void      setBold() {            FontAttr& attr = *next();   attr.setBold();}
  void      setItalic() {          FontAttr& attr = *next();   attr.setItalic();}
  void      setUnderLine() {       FontAttr& attr = *next();   attr.setUnderLine();}
  void      setStrikeOut() {       FontAttr& attr = *next();   attr.setStrikeOut();}
  void      pop();
  void      restoreContext() {if (cur) cur->createFont();}

  bool      isFontItalic() {return cur ? cur->italic : false;}

  void      chkData();

private:

  FontAttr* next();

  void      copy(FontMgr& fm);
  FontAttr* getAttr(int i);

  // returns either a pointer to data (or datum) at index i in array or zero

  FontAttr* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int       nData()      {return data.end();}                   // returns number of data items in array

  void      removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}
  };




#if 0
struct FontAttrP {
FontAttr* p;

  FontAttrP()                 {p = 0;}
  FontAttrP(FontAttrP& dataP) {p = dataP.p;}
 ~FontAttrP() { }

  FontAttrP& operator= (FontAttrP& dataP) {
    p = dataP.p;
    return *this;
    }

  FontAttr*  get();
  };
#endif

  //  double    getScale() {return scale;}
  //  void      setScale(double scl) {scale = scl;}
//  bool      createFont(FontAttr& attr);
//  bool      createPointFont(CDC* dc, TCchar* face, double size, CFont& font);
//  bool      select(CFont& font, CDC* dc);

#if 1
#else
  FontAttr* datum(int i) {return 0 <= i && i < nData() ? stk[i].get() : 0;}

  int       nData()      {return stk.end();}

  void      removeDatum(int i) {if (0 <= i && i < nData()) stk.del(i);}
#endif
//class FontMgr;
//typedef IterT<FontMgr, FontAttr> FontIter;

//  friend typename FontIter;
//CDC*   dc;                // Current CDC

//  bool createPointFont(CFont& font);
//  bool select(CFont& font);

//double scale;
//FontAttr& current() {return *cur;}

