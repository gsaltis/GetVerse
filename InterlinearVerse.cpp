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
#include "main.h"
#include "Common.h"

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

/*****************************************************************************!
 * Function : FindWordByLocation
 *****************************************************************************/
InterlinearWord*
InterlinearVerse::FindWordByLocation
(QPoint InMouseCursor)
{
  for ( auto word : words ) {
	if ( word->ContainsPoint(InMouseCursor) ) {
	  return word;
	}
  }
  return NULL; 
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
InterlinearVerse::Read(void)
{
  QString                               query;
  int                                   n;

  query = QString("SELECT * FROM INTERLINEAR_WORD WHERE VERSE_ID is %1 ORDER BY ID;").arg(GetVerseID());
  n = sqlite3_exec(MainInterlinearDatabase, query.toStdString().c_str(), AddInterlinearVerseCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s\n : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
  }  
}

/*****************************************************************************!
 * Function : AddInterlinearVerseCB
 *****************************************************************************/
int
InterlinearVerse::AddInterlinearVerseCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               columnName;
  QString                               columnValue;
  int                                   verseID;
  QString                               contextualForm ;
  QString                               transliteratedContextualForm;
  QString                               morphologyID;
  QString                               strongsWordID;
  QString                               english;
  InterlinearVerse*                     verse;
  InterlinearWord*                      word;
  
  verse  = (InterlinearVerse*)InPointer;
  verseID = 0;
  for (int i = 0 ; i < InColumnCount; i++) {

    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "VERSE_ID" ) {
      verseID = columnValue.toInt();
      continue;
    }
    
    if ( columnName == "CONTEXTUAL_FORM" ) {
      contextualForm = columnValue;
      continue;
    }
    
    if ( columnName == "TRANSLITERATED_CONTEXTUAL_FORM" ) {
      transliteratedContextualForm = columnValue;
      continue;
    }
    
    if ( columnName == "MORPHOLOGY_ID" ) {
      morphologyID = columnValue;
      continue;
    }
    
    if ( columnName == "STRONGS_WORD_ID" ) {
      strongsWordID = columnValue;
      continue;
    }
    
    if ( columnName == "ENGLISH" ) {
      english = columnValue;
      continue;
    }
  }

  word = new InterlinearWord(verse->GetBookIndex(), verse->GetChapterNumber(), verse->GetVerseNumber(), verseID);
  word->SetContextualForm(contextualForm);
  word->SetTransliteratedContextualForm(transliteratedContextualForm);
  word->SetMorphologyID(morphologyID);
  word->SetStrongsWordID(strongsWordID);
  word->SetEnglish(english);

  verse->AddWord(word);
  return 0;
}

