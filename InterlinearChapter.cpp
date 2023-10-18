/*****************************************************************************
 * FILE NAME    : InterlinearChapter.cpp
 * DATE         : October 17 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
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
#include "InterlinearChapter.h"

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

