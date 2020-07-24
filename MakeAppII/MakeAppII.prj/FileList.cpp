// File List


#include "stdafx.h"
#include "FileList.h"
#include "Bounds.h"
#include "FileStore.h"



static TCchar* IncTarget  = _T("Include=\"");
static int     NIncTarget = _tcslen(IncTarget);


FileList fileList;

