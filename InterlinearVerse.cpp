/*****************************************************************************
 * FILE NAME    : InterlinearVerse.cpp
 * DATE         : October 15 2023
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
#include "InterlinearVerse.h"

/*****************************************************************************!
 * Function : InterlinearVerse
 *****************************************************************************/
InterlinearVerse::InterlinearVerse
(int InBookIndex, int InChapterNumber, int InVerseNumber, int InVerseID)
{
  bookIndex     = InBookIndex;
  chapterNumber = InChapterNumber;
  verseNumber   = InVerseNumber;
  verseID       = InVerseID;
}

/*****************************************************************************!
 * Function : ~InterlinearVerse
 *****************************************************************************/
InterlinearVerse::~InterlinearVerse
()
{
}

/*****************************************************************************!
 * Function : AddWord
 *****************************************************************************/
void
InterlinearVerse::AddWord
(InterlinearWord* InWord)
{
  if ( NULL == InWord ) {
    return;
  }
  
  words << InWord;
}

/*****************************************************************************!
 * Function : GetWordCount
 *****************************************************************************/
int
InterlinearVerse::GetWordCount
()
{
  return (int)words.count();
}

/*****************************************************************************!
 * Function : GetWordByIndex
 *****************************************************************************/
InterlinearWord*
InterlinearVerse::GetWordByIndex
(int InIndex)
{
  if ( InIndex >= words.count() ) {
    return NULL;
  }

  return words[InIndex];
}

/*****************************************************************************!
 * Function ; GetWordByID
 *****************************************************************************/
InterlinearWord*
InterlinearVerse::GetWordByID
(int InID)
{
  for ( auto i = words.begin(); i != words.end(); i++ ) {
    InterlinearWord*                    word = *i;

    if ( word->GetID() == InID ) {
      return word;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetVerseID
 *****************************************************************************/
int
InterlinearVerse::GetVerseID
()
{
  return verseID;
}

/*****************************************************************************!
 * Function : GetVerseNumber
 *****************************************************************************/
int
InterlinearVerse::GetVerseNumber
()
{
  return verseNumber;
}

/*****************************************************************************!
 * Function : GetChapterNumber
 *****************************************************************************/
int
InterlinearVerse::GetChapterNumber
()
{
  return chapterNumber;
}

/*****************************************************************************!
 * Function : GetBookIndex
 *****************************************************************************/
int
InterlinearVerse::GetBookIndex
()
{
  return bookIndex;
}

