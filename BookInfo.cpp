/*****************************************************************************
 * FILE NAME    : BookInfo.cpp
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Function : BookInfo
 *****************************************************************************/
BookInfo::BookInfo
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BookInfo
 *****************************************************************************/
BookInfo::~BookInfo
()
{
}

/*****************************************************************************!
 * Function : GetCapitalizedBookName
 *****************************************************************************/
QString
BookInfo::GetCapitalizedBookName
()
{
  QChar                                 ch;
  int                                   i;
  int                                   n = name.length();
  QString                               returnBookName;

  returnBookName = name;
  for (i = 0; i < n; i++) {
    if ( i == 0 || returnBookName[i-1].isSpace() ) {
      ch = returnBookName[i];
      returnBookName[i] = ch.toUpper();
      continue;
    }
  }
  return returnBookName;
}

  

