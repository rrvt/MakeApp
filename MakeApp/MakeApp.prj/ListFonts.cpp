// Enum Fonts


#include "pch.h"
#include "ListFonts.h"
#include "NotePad.h"
#include "qsort.h"


/*
This example uses two masks, RASTER_FONTTYPE and TRUETYPE_FONTTYPE, to determine the type of font
being enumerated. If the RASTER_FONTTYPE bit is set, the font is a raster font. If the
TRUETYPE_FONTTYPE bit is set, the font is a TrueType font. If neither bit is set, the font is a
vector font. A third mask, DEVICE_FONTTYPE, is set when a device (for example, a laser printer)
supports downloading TrueType fonts; it is zero if the device is a display adapter, dot-matrix
printer, or other raster device. An application can also use the DEVICE_FONTTYPE mask to
distinguish GDI-supplied raster fonts from device-supplied fonts. The system can simulate bold,
italic, underline, and strikeout attributes for GDI-supplied raster fonts, but not for
device-supplied fonts.

An application can also check bits 1 and 2 in the tmPitchAndFamily member of the NEWTEXTMETRIC
structure to identify a TrueType font. If bit 1 is 0 and bit 2 is 1, the font is a TrueType font.

Vector fonts are categorized as OEM_CHARSET instead of ANSI_CHARSET. Some applications identify
vector fonts by using this information, checking the tmCharSet member of the NEWTEXTMETRIC
structure. This categorization usually prevents the font mapper from choosing vector fonts unless
they are specifically requested. (Most applications no longer use vector fonts because their
strokes are single lines and they take longer to draw than TrueType fonts, which offer many of the
same scaling and rotation features that required vector fonts.)

int EnumFontFamiliesExW(
  HDC           hdc,
  LPLOGFONTW    lpLogfont,
  FONTENUMPROCW lpProc,
  LPARAM        lParam,
  DWORD         dwFlags
);
where:
  hdc       - A handle to the device context from which to enumerate the fonts.

  lpLogfont - A pointer to a LOGFONT structure that contains information about the fonts to
              enumerate.   The function examines the following members.

              Member             Description
              lfCharSet        - If set to DEFAULT_CHARSET, the function enumerates all
                                 uniquely-named fonts in all character sets. (If there are two
                                 fonts with the same name, only one is enumerated.) If set to a
                                 valid character set value, the function enumerates only fonts in
                                 the specified character set.
              lfFaceName       - If set to an empty string, the function enumerates one font in
                                 each available typeface name. If set to a valid typeface name, the
                                 function enumerates all fonts with the specified name.
              lfPitchAndFamily - Must be set to zero for all language versions of the operating
                                 system.

  lpProc    - A pointer to the application defined callback function. For more information, see the
              EnumFontFamExProc function.

  lParam    - An application defined value. The function passes this value to the callback function
              along with font information.

  dwFlags   - This parameter is not used and must be zero.

Return value- The return value is the last value returned by the callback function. This value
              depends on which font families are available for the specified device.


int CALLBACK EnumFontFamExProc(
   const LOGFONT    *lpelfe,
   const TEXTMETRIC *lpntme,
         DWORD      FontType,
         LPARAM     lParam
);

where:

  lpelfe    - A pointer to an LOGFONT structure that contains information about the logical
              attributes of the font. To obtain additional information about the font, you can cast
              the result as an ENUMLOGFONTEX or ENUMLOGFONTEXDV structure.

  lpntme    - A pointer to a structure that contains information about the physical attributes of a
              font.  The function uses the NEWTEXTMETRICEX structure for TrueType fonts; and the
              TEXTMETRIC structure for other fonts.  This can be an ENUMTEXTMETRIC structure.

  FontType  - The type of the font. This parameter can be a combination of these values:

              * DEVICE_FONTTYPE
              * RASTER_FONTTYPE
              * TRUETYPE_FONTTYPE

  lParam    - The application-defined data passed by the EnumFontFamiliesEx function.

  returns   - return value must be a nonzero value to continue enumeration; to stop enumeration,
              the return value must be zero.
*/

ListFonts listFonts;



static BOOL CALLBACK EnumFamCallBack(LOGFONT* lf, NEWTEXTMETRIC* ntm,
                                                                 DWORD FontType, VOID* aFontCount);


bool ListFonts::operator() (CDC* dc) {
bool isPrinting = dc->m_bPrinting;
int  n;

  if (isPrinting == dspFonts && fonts.end()) return true;

  dspFonts = dc->m_bPrinting;

  memset(&lf, 0, sizeof(lf));   lf.lfCharSet = ANSI_CHARSET;

  EnumFontFamiliesEx(dc->m_hDC, &lf, (FONTENUMPROC) EnumFamCallBack, (LPARAM) fontCount, 0);

  n = fonts.end();

  qsort(&fonts[0], &fonts[n-1]);   return true;
  }




// Record the number of raster, TrueType, and vector fonts in the font-count array.

BOOL CALLBACK EnumFamCallBack(LOGFONT* lf, NEWTEXTMETRIC* ntm, DWORD fontType, VOID* fontCount) {
int* count =  (int*) fontCount;

  if      (fontType & RASTER_FONTTYPE)   count[0]++;
  else if (fontType & TRUETYPE_FONTTYPE) count[2]++;
  else                                   count[1]++;

  if (lf) {
    FontAtr fa;  fa.name = lf->lfFaceName;  fa.fType = fontType;

    if (fa.name[0] == _T('@')) return true;

    listFonts.fonts += fa;  return true;
    }

  return false;
  }

