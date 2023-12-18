/*****************************************************************************
 * FILE NAME    : BookmarkButton.cpp
 * DATE         : December 09 2023
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
#include "BookmarkButton.h"
#include "Common.h"

/*****************************************************************************!
 * Function : BookmarkButton
 *****************************************************************************/
BookmarkButton::BookmarkButton
(QWidget* InParent) : QPushButton(InParent)
{
  initialize();
}

/*****************************************************************************!
 * Function : BookmarkButton
 *****************************************************************************/
BookmarkButton::BookmarkButton
(QWidget* InParent, BookMark* InBookMark) : QPushButton(InParent)
{
  int                                   n;
  BookInfo*                             b;
  initialize();

  bookMark = InBookMark;
  if ( bookMark->GetChapter() == 0 ) {
    return;
  }
  n = InBookMark->GetBook();
  TRACE_FUNCTION_INT(n);
  b = MainBookInfo->FindBookByIndex(n);
  Set(b, bookMark->GetChapter(), bookMark->GetVerse());
}

/*****************************************************************************!
 * Function : BookmarkButton
 *****************************************************************************/
BookmarkButton::BookmarkButton
(QWidget* InParent, BookInfo* InBook, int InChapter, int InVerse) : QPushButton(InParent)
{
  initialize();
  resize(BOOKMARK_BUTTON_WIDTH, BOOKMARK_BUTTON_HEIGHT);
  Set(InBook, InChapter, InVerse);
}

/*****************************************************************************!
 * Function : ~BookmarkButton
 *****************************************************************************/
BookmarkButton::~BookmarkButton
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookmarkButton::initialize()
{
  Book          = NULL;
  Chapter       = 0;
  Verse         = 0;
  CreateConnections();
}

/*****************************************************************************!
 * Function : Set
 *****************************************************************************/
void
BookmarkButton::Set
(BookInfo* InBook, int InChapter, int InVerse)
{
  QString                               st;
  Book          = InBook;
  Chapter       = InChapter;
  Verse         = InVerse;

  st = QString("%1 %2:%3").arg(Book->nameAbbrev).arg(Chapter).arg(Verse);
  setText(st);
  show();
}

/*****************************************************************************!
 * Function : SlotPushed
 *****************************************************************************/
void
BookmarkButton::SlotPushed(void)
{
  TRACE_FUNCTION_START();
  emit SignalBookmarkSelected(Book, Chapter, Verse, 0);
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
BookmarkButton::CreateConnections(void)
{
  connect(this,
          QPushButton::pressed,
          this,
          BookmarkButton::SlotPushed);
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
BookmarkButton::Clear(void)
{
  Book = NULL;
  Chapter = 0;
  Verse = 0;
  bookMark = NULL;
}

/*****************************************************************************!
 * Function : Display
 *****************************************************************************/
void
BookmarkButton::Display(void)
{
  BookInfo*                             bookInfo;
  bookInfo = MainBookInfo->FindBookByIndex(bookMark->GetBook());
  if ( bookInfo ) {
    Set(bookInfo, bookMark->GetChapter(), bookMark->GetVerse());
  } 
}
