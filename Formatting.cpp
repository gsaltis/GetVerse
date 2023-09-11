/*****************************************************************************
 * FILE NAME    : Formatting.c
 * DATE         : September 10 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "Formatting.h"

/*****************************************************************************!
 * Local Macros
 *****************************************************************************/

/*****************************************************************************!
 * Local Data
 *****************************************************************************/

/*****************************************************************************!
 * Local Functions
 *****************************************************************************/
int
FormattingInfoListReadSQLCB
(void* InListP, int InColumnCount, char** InColumnValues, char** InColumnNames);

/*****************************************************************************!
 * Function : FormattingInfoCreate
 *****************************************************************************/
FormattingInfo*
FormattingInfoCreate
(int InBook, int InChapter, int InVerse, FormattingInfoType InType, QString InSplitText)
{
  FormattingInfo*                       formatInfo;

  formatInfo            = new FormattingInfo();

  formatInfo->Book      = InBook;
  formatInfo->Chapter   = InChapter;
  formatInfo->Verse     = InVerse;
  formatInfo->Type      = InType;
  formatInfo->SplitText = InSplitText;

  return formatInfo;
}

/*****************************************************************************!
 * Function : FormattingInfoListCreate
 *****************************************************************************/
FormattingInfoList*
FormattingInfoListCreate
(void)
{
  FormattingInfoList*                   list;
  int                                   n;

  n = sizeof(FormattingInfoList);
  list = new FormattingInfoList();
  memset(list, 0x00, n);
  return list;
}

/*****************************************************************************!
 * Function : FormattingInfoListAdd
 *****************************************************************************/
void
FormattingInfoListAdd
(FormattingInfoList* InList, FormattingInfo* InInfo)
{
  if ( NULL == InList || NULL == InInfo ) {
    return;
  }
  if ( InList->Head ) {
    InList->Tail->Next = InInfo;
    InList->Tail = InInfo;
    return;
  }
  InList->Head = InInfo;
  InList->Tail = InInfo;
}

/*****************************************************************************!
 * Function : FormattingInfoListFindType
 *****************************************************************************/
int
FormattingInfoListFindType
(FormattingInfoList* InList, int InBook, int InChapter, int InVerse)
{
  FormattingInfo*                       info;

  info = FormattingInfoListFind(InList, InBook, InChapter, InVerse);
  if ( NULL == info ) {
    return 0;
  }
  return info->Type;
}

/*****************************************************************************!
 * Function : FormattingInfoListFind
 *****************************************************************************/
FormattingInfo*
FormattingInfoListFind
(FormattingInfoList* InList, int InBook, int InChapter, int InVerse)
{
  FormattingInfo*                       info;
  if ( NULL == InList ) {
    return NULL;
  }

  for ( info = InList->Head ; info ; info = info->Next ) {
    if ( info->Book == InBook && info->Chapter == InChapter && info->Verse == InVerse ) {
      return info;
    }
  }
  return 0;
}

/*****************************************************************************!
 * Function : FormattingInfoApply
 *****************************************************************************/
QString
FormattingInfoApply
(FormattingInfo* InInfo, QString InText)
{
  QString                               text;
  if ( NULL == InInfo || InText.isEmpty() ) {
    return NULL;
  }
  switch (InInfo->Type) {
    case FormattingInfoTypeNewParagraph : {
      text = InText + QString("\n\n");
      break;
    }
    case FormattingInfoTypeDone : 
    case FormattingInfoTypeNone : {
      text = QString(InText) + " ";
      break;
    }
  }
  return text;
}

/*****************************************************************************!
 * Function : FunctionInfoListReadSQL
 *****************************************************************************/
void
FormattingInfoListReadSQL
(FormattingInfoList* InList, sqlite3* InDatabase)
{
  QString                               query =
    "SELECT * from Formatting;";
  char*                                 error;
  int                                   n;
  
  n = sqlite3_exec(InDatabase, query.toStdString().c_str(), FormattingInfoListReadSQLCB, InList, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__,
          query.toStdString().c_str(), sqlite3_errstr(n));
  
}

/*****************************************************************************!
 * Function : FormattingInfoListReadSQLCB
 *****************************************************************************/
int
FormattingInfoListReadSQLCB
(void* InListP, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  FormattingInfo*                       info;
  int                                   type = 0;
  QString                               splitText = QString();
  int                                   verse = -1;
  int                                   chapter = -1;
  int                                   book = -1;
  int                                   i;
  FormattingInfoList*                   list = (FormattingInfoList*)InListP;

  for ( i = 0; i < InColumnCount ; i++ ) {
    QString                             columnName = InColumnNames[i];
    QString                             columnValue = InColumnValues[i];
    
    if ( columnName == "book" ) {
      book = columnValue.toInt();
      continue;
    }

    if ( columnName == "chapter" ) {
      chapter = columnValue.toInt();
      continue;
    }

    if ( columnName == "verse" ) {
      verse = columnValue.toInt();
      continue;
    }

    if ( columnName == "type" ) {
      type = columnValue.toInt();
      continue;
    }

    if ( columnValue == "text" ) {
      splitText = columnValue;
      continue;
    }
  }
  if ( book    == -1 ||
       chapter == -1 ||
       verse   == -1 || 
       (type < 0 || type >= (int)FormattingInfoTypeDone) ) { 
    return 0;
  }

  info = FormattingInfoCreate(book, chapter, verse, (FormattingInfoType)type, splitText);
  if ( NULL == info ) {
    return 0;
  }
  
  FormattingInfoListAdd(list, info);
  return 0;
}
  
