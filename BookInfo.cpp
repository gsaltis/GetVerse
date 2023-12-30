/*****************************************************************************
 * FILE NAME    : BookInfo.cpp
 * DATE         : September 11 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
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
#include "BookInfo.h"
#include "sqlite3.h"
#include "Common.h"

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

/*****************************************************************************!
 * Function : GetVerseCount
 *****************************************************************************/
int
BookInfo::GetVerseCount
()
{
  int                                   verseCount;
  sqlite3_stmt*                         sqlstmt;
  int                                   n;
  int                                   len;
  QString                               query;
  int                                   retryCount = 0;
  
  query = QString("SELECT COUNT(*) FROM Verses WHERE book is %1;\n").arg(index);
  len = query.length();
  
  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(), len, &sqlstmt, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s sqlite3_prepare_v2()\n%s\n%s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return 0;
  }
  retryCount = 0;
  verseCount = 0;
  do {
    n = sqlite3_step(sqlstmt);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      verseCount = sqlite3_column_int(sqlstmt, 0);
    }
  } while (true);

  sqlite3_finalize(sqlstmt);
  return verseCount;
}

/*****************************************************************************!
 * Function : ReadVerses
 *****************************************************************************/
void
BookInfo::ReadVerses
()
{
  QString                               columnName;
  int                                   n;
  QString                               query;

  if ( wordItems.size() > 0 ) {
    return;
  }
  query = QString("SELECT * from Verses where book is %1 ORDER by book, chapter, verse;\n").arg(index);
  n = sqlite3_exec(MainDatabase, query.toStdString().c_str(), BookInfo::ReadVersesCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
    return;
  }
}

/*****************************************************************************!
 * Function : ReadVersesCB
 *****************************************************************************/
int
BookInfo::ReadVersesCB
(void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   chapter = 0;
  int                                   verse = 0;
  QString                               columnValue;
  QString                               columnName;
  QString                               verseText;
  QString                               reference;
  QString                               s;
  BookInfo*                             bookInfo;
  
  bookInfo = (BookInfo*)InThisPointer;
  
  for ( int i = 0 ; i < InColumnCount ; i++ ) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "key" ) {
      reference = columnValue;
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
      verseText = columnValue;
      continue;
    }
  }

  bookInfo->AddLineText(chapter, verse, verseText);
  return 0;
}

/*****************************************************************************!
 * Function : AddLineText
 *****************************************************************************/
void
BookInfo::AddLineText
(int InChapter, int InVerse, QString InVerseText)
{
  QStringList                           words;
  int                                   i;
  int                                   n;
  BookInfoWord*                         wordItem;
  
  words = InVerseText.split(" ");
  n = words.size();

  for ( i = 0; i < n; i++ ) {
    wordItem = new BookInfoWord(index, InChapter, InVerse, i + 1, words[i]);
    wordItems.push_back(wordItem);
  }
}

/*****************************************************************************!
 * Function : GetWord
 *****************************************************************************/
BookInfoWord*
BookInfo::GetWord
(int InChapter, int InVerse, int InWordIndex)
{
  int                                   n;
  int                                   i;
  BookInfoWord*                         wordItem;
  
  n = wordItems.size();

  for (i = 0; i < n; i++) {
    wordItem = wordItems[i];
    if ( wordItem->IsEqual(index, InChapter, InVerse, InWordIndex) ) {
      return wordItem;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetWordCount
 *****************************************************************************/
int
BookInfo::GetWordCount
()
{
  return wordItems.size();
}

/*****************************************************************************!
 * Function : GetChapterWordCount
 *****************************************************************************/
int
BookInfo::GetChapterWordCount
(int InChapter)
{
  BookInfoWord*                         wordItem;
  int                                   i;
  int                                   n;
  int                                   count;

  count = 0;
  n = wordItems.size();

  for (i = 0; i < n; i++) {
    wordItem = wordItems[i];
    if ( wordItem->GetChapter() == InChapter ) {
      count++;
    }
  }
  return count;
}

/*****************************************************************************!
 * Function : GetChapterWordIndices
 *****************************************************************************/
void
BookInfo::GetChapterWordIndices
(int InChapter, int &InStartIndex, int &InEndIndex)
{
  int                                   i;
  BookInfoWord*                         wordItem;
  int                                   n;
  int                                   start;
  int                                   end;

  start = -1;
  end = 0;
  
  n = wordItems.size();

  for (i = 0; i < n; i++) {
    wordItem = wordItems[i];
    if ( wordItem->GetChapter() != InChapter ) {
      continue;
    }
    if ( start == -1 ) {
      start = i;
    }
    end = i;
  }

  InStartIndex = start;
  InEndIndex = end;
}

/*****************************************************************************!
 * Function : GetWordByIndex
 *****************************************************************************/
BookInfoWord*
BookInfo::GetWordByIndex
(int InIndex)
{
  if ( InIndex >= wordItems.size() ) {
    return NULL;
  }
  return wordItems[InIndex];
}

/*****************************************************************************!
 * Function : GetIndex
 *****************************************************************************/
int
BookInfo::GetIndex(void)
{
  return index;
}

/*****************************************************************************!
 * Function : GetChapterCount
 *****************************************************************************/
int
BookInfo::GetChapterCount(void)
{
  return chapters;
}

/*****************************************************************************!
 * Function : GetRightToLeft
 *****************************************************************************/
int
BookInfo::GetRightToLeft(void)
{
  return RightToLeft;  
}

/*****************************************************************************!
 * Function : SetRightToLeft
 *****************************************************************************/
void
BookInfo::SetRightToLeft
(int InRightToLeft)
{
  RightToLeft = InRightToLeft;  
}

/*****************************************************************************!
 * Function : GetName
 *****************************************************************************/
QString
BookInfo::GetName(void)
{
  return name;
}

/*****************************************************************************!
 * Function : GetVerseText
 *****************************************************************************/
QString
BookInfo::GetVerseText
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  int                                   retryCount;
  QString                               verseText;
  sqlite3_stmt*                         sqlStatement;
  int                                   n;
  QString selectStatement =
    QString("SELECT text FROM VERSES "
            "WHERE "
            "book is %1 AND "
            "chapter is %2 AND "
            "verse is %3;").
    arg(InBookNumber).
    arg(InChapterNumber).
    arg(InVerseNumber);

  TRACE_FUNCTION_QSTRING(selectStatement);
  
  n = sqlite3_prepare_v2(MainDatabase, selectStatement.toStdString().c_str(), selectStatement.length(), &sqlStatement, NULL);
  if ( n != SQLITE_OK ) {
    return QString("");
  }
  retryCount = 0;

  do {
    n = sqlite3_step(sqlStatement);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      verseText = QString((char*)sqlite3_column_text(sqlStatement, 0));
    }
  } while (true);

  sqlite3_finalize(sqlStatement);
  return verseText;
  
}
