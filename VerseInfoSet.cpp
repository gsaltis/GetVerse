/*****************************************************************************
 * FILE NAME    : VerseInfoSet.cpp
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
#include "VerseInfoSet.h"

/*****************************************************************************!
 * Function : VerseInfoSet
 *****************************************************************************/
VerseInfoSet::VerseInfoSet
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : VerseInfoSet
 *****************************************************************************/
VerseInfoSet::VerseInfoSet
(int InBook) : QWidget()
{
  Initialize();
  Book = InBook;
}

/*****************************************************************************!
 * Function : ~VerseInfoSet
 *****************************************************************************/
VerseInfoSet::~VerseInfoSet
()
{
  VerseInfo*                            verse;
  while ( ! Verses.isEmpty() ) {
    verse = Verses.first();
    Verses.pop_front();
    delete verse;
  }
}

/*****************************************************************************!
 * Function : ReadDB
 *****************************************************************************/
void
VerseInfoSet::ReadDB
(sqlite3* InDatabase)
{

  QString                               selectStatement =
    QString("SELECT * From Verses WHERE book is %1;").arg(Book);
  
  if ( 0 == Book ) {
    return;
  }
  
  sqlite3_exec(InDatabase, selectStatement.toStdString().c_str(), ReadDBCB, this, NULL);
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
VerseInfoSet::Initialize(void)
{
  Book = 0;
}

/*****************************************************************************!
 * Function : ReadDBCB
 *****************************************************************************/
int
VerseInfoSet::ReadDBCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  VerseInfo*                            verseInfo;
  QString                               text;
  int                                   verse;
  int                                   book;
  int                                   chapter;
  QString                               columnValue;
  QString                               columnName;
  int                                   i;
  VerseInfoSet*                         verseSet;

  book = 0;
  chapter = 0;
  verse = 0;
  verseSet = (VerseInfoSet*)InPointer;

  for (i = 0; i < InColumnCount; i++) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

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
    if ( columnName == "text" ) {
      text = columnValue;
      continue;
    }
  }

  if ( book == 0 || chapter == 0 || verse == 0 ) {
    return 0;
  }
  
  verseInfo = new VerseInfo(book, chapter, verse, text);
  verseSet->AddVerse(verseInfo);
  return 0;
}

/*****************************************************************************!
 * Function : AddVerse
 *****************************************************************************/
void
VerseInfoSet::AddVerse
(VerseInfo* InVerse)
{
  if ( NULL == InVerse ) {
    return;
  }
  Verses << InVerse;
}

/*****************************************************************************!
 * Function : GetVerseCount
 *****************************************************************************/
int
VerseInfoSet::GetVerseCount(void)
{
  return Verses.size();
}

/*****************************************************************************!
 * Function : GetVerseByIndex
 *****************************************************************************/
VerseInfo*
VerseInfoSet::GetVerseByIndex
(int InIndex)
{
  if ( InIndex >= Verses.size() ) {
    return NULL;
  }
  return Verses[InIndex];
}
