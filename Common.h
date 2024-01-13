/*****************************************************************************
 * FILE NAME    : Common.hpp
 * DATE         : September 11 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _common_h_
#define _common_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vector>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"
#include "BookMark.h"
#include "sqlite3.h"
#include "SystemConfig.h"
#include "BookMarkManager.h"
#include "BookInfoManager.h"
#include "ReaderViewFormatSet.h"
#include "SystemSettings.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern BookInfoManager*
MainBookInfo;

extern sqlite3*
MainDatabase;

extern sqlite3*
MainInterlinearDatabase;

extern SystemConfig*
MainSystemConfig;

extern BookMarkManager*
MainBookMarks;

extern ReaderViewFormatSet*
MainReaderViewFormats;

extern SystemSettings*
MainSystemSettings;

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _common_h_*/
