/*****************************************************************************
 * FILE NAME    : ReaderViewFormatSet.cpp
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
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
#include "ReaderViewFormatSet.h"
#include "Common.h"

/*****************************************************************************!
 * Function : ReaderViewFormatSet
 *****************************************************************************/
ReaderViewFormatSet::ReaderViewFormatSet
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~ReaderViewFormatSet
 *****************************************************************************/
ReaderViewFormatSet::~ReaderViewFormatSet
()
{
}

/*****************************************************************************!
 * Function : FindFormat
 *****************************************************************************/
ReaderViewFormat*
ReaderViewFormatSet::FindFormat
(int InBook, int InChapter, int InVerse, int InWordIndex)
{
  for ( auto format : Formats ) {
    if ( format->IsEqual(InBook, InChapter, InVerse, InWordIndex) ) {
      return format;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : ReadDB
 *****************************************************************************/
void
ReaderViewFormatSet::ReadDB
(sqlite3* InDatabase)
{
  QString                               selectStatement =
    "SELECT * FROM ReaderViewFormat;";

  sqlite3_exec(InDatabase, selectStatement.toStdString().c_str(),
               ReadDBCB, this, NULL);
}

/*****************************************************************************!
 * Function : ReadDBCB
 *****************************************************************************/
int
ReaderViewFormatSet::ReadDBCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  BookInfo*                             bookInfo;
  int                                   i;
  QColor                                color;
  ReaderViewFormat*                     viewFormat;
  QString                               title;
  QString                               colorString;
  int                                   format;
  int                                   wordIndex;
  int                                   verse;
  int                                   chapter;
  int                                   bookIndex;
  QString                               columnValue;
  QString                               columnName;
  ReaderViewFormatSet*                  formatSet;

  bookIndex = 0;
  chapter = 0;
  verse = 0;
  wordIndex = 0;
  format = 0;

  formatSet = (ReaderViewFormatSet*)InPointer;

  for (i = 0; i < InColumnCount; i++) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "Book" ) {
      bookIndex = columnValue.toInt();
      continue;
    }

    if ( columnName == "Chapter" ) {
      chapter = columnValue.toInt();
      continue;
    }

    if ( columnName == "Verse" ) {
      verse = columnValue.toInt();
      continue;
    }

    if ( columnName == "WordIndex" ) {
      wordIndex = columnValue.toInt();
      continue;
    }

    if ( columnName == "Format" ) {
      format = columnValue.toInt();
      continue;
    }

    if ( columnName == "Color" ) {
      color = QColor(columnValue);
      continue;
    }

    if ( columnName == "Title" ) {
      title = columnValue;
      continue;
    }
  }

  //!
  do {
    bookInfo = MainBookInfo->FindBookByIndex(bookIndex);
    if ( bookInfo == NULL ) {
      break;
    }
    viewFormat = new ReaderViewFormat(bookInfo, chapter, verse, wordIndex);
    viewFormat->SetFormat(format);
    viewFormat->SetColor(color);
    viewFormat->SetTitle(title);
    formatSet->AddFormat(viewFormat);
  } while (false);

  return 0;
}

/*****************************************************************************!
 * Function : AddFormat
 *****************************************************************************/
void
ReaderViewFormatSet::AddFormat
(ReaderViewFormat* InFormat)
{
  if ( NULL == InFormat ) {
    return;
  }
  
  Formats << InFormat;
}

/*****************************************************************************!
 * Function : GetFormatCount
 *****************************************************************************/
int
ReaderViewFormatSet::GetFormatCount(void)
{
  return Formats.size();
}
