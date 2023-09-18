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
#include "sqlite3.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/
extern std::vector<BookInfo*>
MainBookInfo;

extern sqlite3*
MainDatabase;

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/

#endif /* _common_h_*/