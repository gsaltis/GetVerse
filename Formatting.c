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
#include <StringUtils.h>
#include <MemoryManager.h>
#include <FileUtils.h>

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
(int InBook, int InChapter, int InVerse, FormattingInfoType InType, string InSplitText)
{
  FormattingInfo*                       formatInfo;
  int                                   n;

  n                     = sizeof(FormattingInfo);
  formatInfo            = (FormattingInfo*)GetMemory(n);
  memset(formatInfo, 0x00, n);

  formatInfo->Book      = InBook;
  formatInfo->Chapter   = InChapter;
  formatInfo->Verse     = InVerse;
  formatInfo->Type      = InType;
  if ( InSplitText ) {
    strcpy(formatInfo->SplitText, InSplitText);
  }
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
  list = (FormattingInfoList*)GetMemory(n);
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
string
FormattingInfoApply
(FormattingInfo* InInfo, string InText)
{
  string                                text;
  if ( NULL == InInfo || NULL == InText ) {
    return NULL;
  }
  switch (InInfo->Type) {
    case FormattingInfoTypeNewParagraph : {
      text = StringConcat(InText, "\n\n");
      break;
    }
    case FormattingInfoTypeDone : 
    case FormattingInfoTypeNone : {
      text = StringCopy(InText);
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
  string                                query =
    "SELECT * from Formatting;";
  char*                                 error;
  int                                   n;
  
  n = sqlite3_exec(InDatabase, query, FormattingInfoListReadSQLCB, InList, &error);
  if ( n == SQLITE_OK ) {
    return;
  }
  fprintf(stderr, "%s sqlite3_exec() failed \n%s\n%s\n", __FUNCTION__, query, error);
  
}

/*****************************************************************************!
 * Function : FormattingInfoListReadSQLCB
 *****************************************************************************/
int
FormattingInfoListReadSQLCB
(void* InListP, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  FormattingInfo*                       info;
  int                                   type;
  string                                splitText = "";
  int                                   verse = -1;
  int                                   chapter = -1;
  int                                   book = -1;
  int                                   i;
  FormattingInfoList*                   list = (FormattingInfoList*)InListP;

  for ( i = 0; i < InColumnCount ; i++ ) {
    string                              columnName = InColumnNames[i];
    string                              columnValue = InColumnValues[i];
    
    if ( StringEqual(columnName, "book") ) {
      book = atoi(columnValue);
      continue;
    }

    if ( StringEqual(columnName, "chapter") ) {
      chapter = atoi(columnValue);
      continue;
    }

    if ( StringEqual(columnName, "verse") ) {
      verse = atoi(columnValue);
      continue;
    }

    if ( StringEqual(columnName, "type") ) {
      type = atoi(columnValue);
      continue;
    }

    if ( StringEqual(columnValue, "text") ) {
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

  info = FormattingInfoCreate(book, chapter, verse, type, splitText);
  if ( NULL == info ) {
    return 0;
  }
  
  FormattingInfoListAdd(list, info);
  return 0;
}
  
