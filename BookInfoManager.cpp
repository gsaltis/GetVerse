/*****************************************************************************
 * FILE NAME    : BookInfoManager.cpp
 * DATE         : December 17 2023
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
#include "BookInfoManager.h"

/*****************************************************************************!
 * Function : BookInfoManager
 *****************************************************************************/
BookInfoManager::BookInfoManager
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BookInfoManager
 *****************************************************************************/
BookInfoManager::~BookInfoManager
()
{
}

/*****************************************************************************!
 * Function : VerifyBookName
 *****************************************************************************/
int
BookInfoManager::VerifyBookName
(QString InBookName)
{
  QString                               bookName;
  QString                               name;
  BookInfo*                             candidate = NULL;

  bookName = InBookName.toLower();

  for (BookInfo* bookInfo : Books) {
    name = bookInfo->name.toLower();
    if ( name.startsWith(bookName) ) {
      if ( candidate ) {
        return DUPLICATE_BOOK;
      }
      candidate = bookInfo;
    }
  }
  return  ( candidate == NULL ) ? BOOK_NOT_FOUND : BOOK_FOUND;
}

/*****************************************************************************!
 * Function : AddBookInfo
 *****************************************************************************/
void
BookInfoManager::AddBookInfo
(BookInfo* InBook)
{
  Books << InBook;
}

/*****************************************************************************!
 * Function : FindBookByIndex
 *****************************************************************************/
BookInfo*
BookInfoManager::FindBookByIndex
(int InIndex)
{
  for ( auto book : Books ) {
    if ( book->GetIndex() == InIndex ) {
      return book;
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : GetSearchableBookName
 *****************************************************************************/
BookInfo*
BookInfoManager::GetSearchableBookName
(QString InBookName)
{
  QString                               bookName;
  QString                               name;
  BookInfo*                             candidate = NULL;

  bookName = InBookName.toLower();
  for (BookInfo* bookInfo : Books) {
    name = bookInfo->name.toLower();
    if ( name.startsWith(bookName) ) {
      if ( candidate ) {
        return NULL;
      }
      candidate = bookInfo;
    }
  }
  return candidate;
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
int
BookInfoManager::GetSize(void)
{
  return Books.size();
}

/*****************************************************************************!
 * Function : GetByIndex
 *****************************************************************************/
BookInfo*
BookInfoManager::GetByIndex
(int InIndex)
{
  if ( InIndex >= Books.size() ) {
    return NULL;
  }
  return Books[InIndex];
}

/*****************************************************************************!
 * Function : GetBookByName
 *****************************************************************************/
BookInfo*
BookInfoManager::GetBookByName
(QString InBookName, bool InUseAbbrev)
{
  QString                               st;

  st = InBookName.toLower();
  for ( auto bookInfo : Books ) {
    if ( bookInfo->name.toLower() == st ) {
      return bookInfo;
    }
    if ( InUseAbbrev ) {
      if ( bookInfo->nameAbbrev.toLower() == InBookName ) {
        return bookInfo;
      }
    }
  }
  return NULL;
}
