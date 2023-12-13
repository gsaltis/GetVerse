/*****************************************************************************
 * FILE NAME    : BookMarkSet.cpp
 * DATE         : December 10 2023
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
#include "BookMarkSet.h"
#include "main.h"

/*****************************************************************************!
 * Function : BookMarkSet
 *****************************************************************************/
BookMarkSet::BookMarkSet
() : QWidget()
{
}

/*****************************************************************************!
 * Function : ~BookMarkSet
 *****************************************************************************/
BookMarkSet::~BookMarkSet
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
BookMarkSet::Initialize(void)
{
  int                                   i;
  for ( i = 1 ; i <= BOOKMARK_SET_MAX_COUNT ; i++ ) {
    BookMark*                           bookmark;

    bookmark = new BookMark(i);
    Bookmarks[i] = bookmark;
  }
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
BookMarkSet::Read(void)
{
  BookMark*                             bookmark;
  int                                   i;
  QSettings                             settings(MAIN_ORG_NAME, MAIN_APP_NAME); 

  for ( i = 1 ; i <= BOOKMARK_SET_MAX_COUNT ; i++ ) {
    bookmark = Bookmarks[i];
    bookmark->Read(&settings);
  }
}

/*****************************************************************************!
 * Function : FindByIndex
 * Purpose  : Return by index (1 Based)
 *****************************************************************************/
BookMark*
BookMarkSet::FindByIndex
(int InIndex)
{
  if ( InIndex > BOOKMARK_SET_MAX_COUNT ) {
    return NULL;
  }
  return Bookmarks[InIndex];
}

/*****************************************************************************!
 * Function : SetBookMark
 *****************************************************************************/
void
BookMarkSet::SetBookMark
(int InIndex, int InBook, int InChapter, int InVerse)
{
  BookMark*                             bookmark;
  if ( InIndex > BOOKMARK_SET_MAX_COUNT ) {
    return;
  }

  bookmark = Bookmarks[InIndex];
  bookmark->Set(InBook, InChapter, InVerse);
}

/*****************************************************************************!
 * Function : AddBookMark
 *****************************************************************************/
void
BookMarkSet::AddBookMark
(int InBook, int InChapter, int InVerse)
{
  int                                   index;

  index = FindNextAvailableIndex();
  SetBookMark(index, InBook, InChapter, InVerse);
}

/*****************************************************************************!
 * Function : FindNextAvailableIndex
 *****************************************************************************/
int
BookMarkSet::FindNextAvailableIndex(void)
{
  BookMark*                             bookmarkSource;
  BookMark*                             bookmarkTarget;
  int                                   i;
  
  for ( i = 2 ; i <= BOOKMARK_SET_MAX_COUNT ; i++ ) {
    bookmarkTarget = Bookmarks[i];
    bookmarkSource = Bookmarks[i-1];
    bookmarkTarget->Set(bookmarkSource->GetBook(), bookmarkSource->GetChapter(), bookmarkSource->GetVerse());
  }
  return i;
}
