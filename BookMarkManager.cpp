/*****************************************************************************
 * FILE NAME    : BookMarkManager.cpp
 * DATE         : December 16 2023
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
#include "BookMarkManager.h"

/*****************************************************************************!
 * Function : BookMarkManager
 *****************************************************************************/
BookMarkManager::BookMarkManager
(QString InOrgName, QString InAppName) : QWidget()
{
  int                                   n;
  int                                   i;

  settings = new QSettings(InOrgName, InAppName);
  n = BOOK_MARK_MANAGER_MAX_COUNT + 1;
  for (i = 0; i < n; i++) {
    bookMarks[i] = NULL;
  }
}

/*****************************************************************************!
 * Function : ~BookMarkManager
 *****************************************************************************/
BookMarkManager::~BookMarkManager
()
{
}

/*****************************************************************************!
 * Function : AddBookMark
 *****************************************************************************/
void
BookMarkManager::AddBookMark
(BookMark* InBookMark)
{
  int                                   n;
  int                                   i;

  n = BOOK_MARK_MANAGER_MAX_COUNT;
  for ( i = 0; i < n; i++ ) {
    bookMarks[i + 1] = bookMarks[i];
  }
  bookMarks[0] = InBookMark;
}

/*****************************************************************************!
 * Function : GetBookMark
 *****************************************************************************/
BookMark*
BookMarkManager::GetBookMark
(int InIndex)
{
  if ( InIndex > BOOK_MARK_MANAGER_MAX_COUNT ) {
    return NULL;
  }
  return bookMarks[InIndex];
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
BookMarkManager::Read
()
{
  BookMark*                             bookMark;
  int                                   n;
  int                                   i;

  n = BOOK_MARK_MANAGER_MAX_COUNT;
  for (i = 0; i < n; i++) {
    bookMark = new BookMark(i+1);
    bookMark->Read(settings);
    bookMarks[i] = bookMark;
  }
}

/*****************************************************************************!
 * Function : SetBookMark
 *****************************************************************************/
void
BookMarkManager::SetBookMark
(int InBook, int InChapter, int InVerse, int)
{
  int                                   n;
  int                                   i;
  ShiftBookMarks();
  bookMarks[0]->Set(InBook, InChapter, InVerse);

  n = BOOK_MARK_MANAGER_MAX_COUNT;
  for (i = 0; i < n; i++) {
    bookMarks[i]->Save(settings);
  }
}

/*****************************************************************************!
 * Function : ShiftBookMarks
 *****************************************************************************/
void
BookMarkManager::ShiftBookMarks(void)
{
  int                                   n;
  int                                   i;

  n = BOOK_MARK_MANAGER_MAX_COUNT - 1;
  for (i = n-1; i > 0; i--) {
    bookMarks[i]->Set(bookMarks[i-1]->GetBook(),
                      bookMarks[i-1]->GetChapter(),                        
                      bookMarks[i-1]->GetVerse());
    bookMarks[i]->Save(settings);
  }
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
BookMarkManager::Clear(void)
{
  int                                   n;
  int                                   i;

  n = BOOK_MARK_MANAGER_MAX_COUNT;
  for (i = 0; i < n; i++) {
    bookMarks[i]->Clear(settings);
  }
}

/*****************************************************************************!
 * Function : SlotSetBookmark
 *****************************************************************************/
void
BookMarkManager::SlotSetBookmark
(int InBook, int InChapter, int InVerse, int InWordIndex)
{
  SetBookMark(InBook, InChapter, InVerse, InWordIndex);
}
