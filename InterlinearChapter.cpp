/*****************************************************************************
 * FILE NAME    : InterlinearChapter.cpp
 * DATE         : October 17 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "InterlinearChapter.h"
#include "main.h"
#include "Common.h"

/*****************************************************************************!
 * Function : InterlinearChapter
 *****************************************************************************/
InterlinearChapter::InterlinearChapter
(int InBookIndex, int InChapterNumber)
{
  bookIndex = InBookIndex;
  chapterNumber = InChapterNumber;
}

/*****************************************************************************!
 * Function : ~InterlinearChapter
 *****************************************************************************/
InterlinearChapter::~InterlinearChapter
()
{
}


/*****************************************************************************!
 * Function : AddVerse
 *****************************************************************************/
void
InterlinearChapter::AddVerse
(InterlinearVerse* InVerse)
{
  if ( NULL == InVerse ) {
    return;
  }
  verses << InVerse;
}

/*****************************************************************************!
 * Function : GetVerseCount
 *****************************************************************************/
int
InterlinearChapter::GetVerseCount
()
{
  return verses.count();
}

/*****************************************************************************!
 * Function : GetVerseByIndex
 *****************************************************************************/
InterlinearVerse*
InterlinearChapter::GetVerseByIndex
(int InIndex)
{
  if ( InIndex >= verses.count() ) {
    return NULL;
  }

  return verses[InIndex];
}

/*****************************************************************************!
 * Function : GetBookIndex
 *****************************************************************************/
int
InterlinearChapter::GetBookIndex
()
{
  return bookIndex;
}

/*****************************************************************************!
 * Function : GetChapterNumber
 *****************************************************************************/
int
InterlinearChapter::GetChapterNumber
()
{
  return chapterNumber;
}

/*****************************************************************************!
 * Function : FindWordByLocation
 *****************************************************************************/
InterlinearWord*
InterlinearChapter::FindWordByLocation
(QPoint InMouseCursor)
{
  for ( auto verse : verses ) {
    auto word = verse->FindWordByLocation(InMouseCursor);
	if ( word ) {
	  return word;
	}
  }
  return NULL;
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
InterlinearChapter::Read
()
{
  QString                               query;
  int                                   n;

  query = QString("SELECT * FROM VERSE WHERE BOOK_NUMBER is %1 and CHAPTER_NUMBER IS %2;").
    arg(bookIndex).arg(chapterNumber);
  
  n = sqlite3_exec(MainInterlinearDatabase, query.toStdString().c_str(), AddInterlinearChapterCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s\n : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
  }
}

/*****************************************************************************!
 * Function : AddInterlinearChapterCB
 *****************************************************************************/
int
InterlinearChapter::AddInterlinearChapterCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   i;
  int                                   id;
  QString                               columnName;
  QString                               columnValue;
  InterlinearChapter*                   chapter;
  InterlinearVerse*                     verse;
  int                                   verseNumber;
  int                                   bookNumber;
  int                                   chapterNumber;
  
  chapter       = (InterlinearChapter*)InPointer;
  verseNumber   = 0;
  id            = 0;
  bookNumber    = 0;
  chapterNumber = 0;
  
  for (i = 0; i < InColumnCount; i++) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];
    if ( columnName == "ID" ) {
      id = columnValue.toInt();
      continue;
    }

    if ( columnName == "VERSE_NUMBER" ) {
      verseNumber = columnValue.toInt();
      continue;
    }
    if ( columnName == "CHAPTER_NUMBER" ) {
      chapterNumber = columnValue.toInt();
      continue;
    }
    if ( columnName == "BOOK_NUMBER" ) {
      bookNumber = columnValue.toInt();
      continue;
    }
  }
  verse = new InterlinearVerse(bookNumber, chapterNumber, verseNumber, id);
  chapter->AddVerse(verse);
  return 0;
}

/*****************************************************************************!
 * Function : ReadVerses
 *****************************************************************************/
void
InterlinearChapter::ReadVerses
()
{
  int                                   verseCount;
  int                                   i;

  verseCount = GetVerseCount();

  for (i = 0; i < verseCount; i++) {
    verses[i]->Read();
  }
}
