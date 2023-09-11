/*****************************************************************************
 * FILE NAME    : Formatting.h
 * DATE         : September 10 2023
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _formatting_h_
#define _formatting_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QApplication>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "sqlite3.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Type : FormattingInfoType
 *****************************************************************************/
typedef enum FormattingInfoType
{
  FormattingInfoTypeNone                = 0,
  FormattingInfoTypeNewParagraph,

  FormattingInfoTypeDone
} FormattingInfoType;

/*****************************************************************************!
 * Exported Type : FormattingInfo
 *****************************************************************************/
struct _FormattingInfo
{
  int                                   Book;
  int                                   Chapter;
  int                                   Verse;
  FormattingInfoType                    Type;
  QString                               SplitText;
  struct _FormattingInfo*               Next;
};
typedef struct _FormattingInfo FormattingInfo;

/*****************************************************************************!
 * Exported Type : FormattingInfoList
 *****************************************************************************/
struct _FormattingInfoList
{
  FormattingInfo*                           Head;
  FormattingInfo*                           Tail;
};
typedef struct _FormattingInfoList FormattingInfoList;

/*****************************************************************************!
 * Exported Data
 *****************************************************************************/

/*****************************************************************************!
 * Exported Functions
 *****************************************************************************/
void
FormattingInfoListReadSQL
(FormattingInfoList* InList,sqlite3* InDatabase);

QString
FormattingInfoApply
(FormattingInfo* InInfo, QString InText);

FormattingInfo*
FormattingInfoListFind
(FormattingInfoList* InList, int InBook, int InChapter, int InVerse);

int
FormattingInfoListFindType
(FormattingInfoList* InList, int InBook, int InChapter, int InVerse);

void
FormattingInfoListAdd
(FormattingInfoList* InList, FormattingInfo* InInfo);

FormattingInfoList*
FormattingInfoListCreate
(void);

FormattingInfo*
FormattingInfoCreate
(int InBook, int InChapter, int InVerse, FormattingInfoType InType, QString InSplitText);

#endif /* _formatting_h_*/
