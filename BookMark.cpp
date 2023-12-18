/*****************************************************************************
 * FILE NAME    : BookMark.cpp
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
#include "BookMark.h"
#include "BookmarkButton.h"
#include "Common.h"

/*****************************************************************************!
 * Function : BookMark
 *****************************************************************************/
BookMark::BookMark
(int InIndex) : QWidget()
{
  Initialize();
  Index = InIndex;
  button = NULL;
}

/*****************************************************************************!
 * Function : BookMark
 *****************************************************************************/
BookMark::BookMark
(int InIndex, int InBook, int InChapter, int InVerse) : QWidget()
{
  Initialize();
  Index         = InIndex;
  Book          = InBook;
  Chapter       = InChapter;
  Verse         = InVerse;
  Settings      = NULL;
  button        = NULL;
}

/*****************************************************************************!
 * Function : ~BookMark
 *****************************************************************************/
BookMark::~BookMark
()
{
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
int
BookMark::GetBook(void)
{
  return Book;  
}

/*****************************************************************************!
 * Function : SetBook
 *****************************************************************************/
void
BookMark::SetBook
(int InBook)
{
  Book = InBook;  
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
int
BookMark::GetChapter(void)
{
  return Chapter;  
}

/*****************************************************************************!
 * Function : SetChapter
 *****************************************************************************/
void
BookMark::SetChapter
(int InChapter)
{
  Chapter = InChapter;  
}

/*****************************************************************************!
 * Function : GetVerse
 *****************************************************************************/
int
BookMark::GetVerse(void)
{
  return Verse;  
}

/*****************************************************************************!
 * Function : SetVerse
 *****************************************************************************/
void
BookMark::SetVerse
(int InVerse)
{
  Verse = InVerse;  
}

/*****************************************************************************!
 * Function : GetIndex
 *****************************************************************************/
int
BookMark::GetIndex(void)
{
  return Index;  
}

/*****************************************************************************!
 * Function : SetIndex
 *****************************************************************************/
void
BookMark::SetIndex
(int InIndex)
{
  Index = InIndex;  
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
BookMark::Initialize(void)
{
  Index         = 0;
  Book          = 0;
  Chapter       = 0;
  Verse         = 0;
}

/*****************************************************************************!
 * Function : Read
 *****************************************************************************/
void
BookMark::Read
(QSettings* InSettings)
{
  QString                       settingsBase;
  QString                       settingName;

  Book = 0;
  Chapter = 0;
  Verse = 0;
  settingsBase = QString("Bookmarks/%1").arg(Index);
  Settings = InSettings;
  
  settingName = QString("%1/Book").arg(settingsBase);
  if ( !InSettings->contains(settingName) ) {
    InSettings->setValue(settingName, 0);
    Book = 0;
    InSettings->setValue(settingName, Book);
  } else {
    Book = InSettings->value(settingName).toInt();
  }
  
  settingName = QString("%1/Chapter").arg(settingsBase);
  if ( !InSettings->contains(settingName) ) {
    InSettings->setValue(settingName, 0);
    Chapter = 0;
    InSettings->setValue(settingName, Chapter);
  } else {
    Chapter = InSettings->value(settingName).toInt();
  }
  
  settingName = QString("%1/Verse").arg(settingsBase);
  if ( !InSettings->contains(settingName) ) {
    InSettings->setValue(settingName, 0);
    Verse = 0;
    InSettings->setValue(settingName, Verse);
  } else {
    Verse = InSettings->value(settingName).toInt();
  }  
}

/*****************************************************************************!
 * Function : SetButton
 *****************************************************************************/
void
BookMark::SetButton
(BookmarkButton* InButton)
{
  button = InButton;
}

/*****************************************************************************!
 * Function : Set
 *****************************************************************************/
void
BookMark::Set
(int InBook, int InChapter, int InVerse)
{
  BookInfo*                             bookInfo;
  QString                               bookName;
  
  Book = InBook;
  Chapter = InChapter;
  Verse = InVerse;
  if ( Book > 0 ) {
    bookInfo = MainBookInfo->FindBookByIndex(Book);
    bookName = bookInfo->GetCapitalizedBookName();
    if ( button ) {
      button->Set(bookInfo, Chapter, Verse);
    }
  } else {
    if ( button ) {
      button->Clear();
    }
  }
}

/*****************************************************************************!
 * Function : Save
 *****************************************************************************/
void
BookMark::Save
(QSettings* InSettings)
{
  QString                               settingsVerseName;
  QString                               settingsChapterName;
  QString                               settingsBookName;
  QString                               settingsBase;

  settingsBase = QString("Bookmarks/%1").arg(Index);

  settingsBookName = QString("%1/Book").arg(settingsBase);
  settingsChapterName = QString("%1/Chapter").arg(settingsBase);
  settingsVerseName = QString("%1/Verse").arg(settingsBase);

  InSettings->setValue(settingsBookName, Book);
  InSettings->setValue(settingsChapterName, Chapter);
  InSettings->setValue(settingsVerseName, Verse);
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
BookMark::Clear(void)
{
  Book          = 0;
  Chapter       = 0;
  Verse         = 0;
  if ( button ) {
    button->Set(0, 0, 0);
    button->hide();
  }
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
BookMark::Clear
(QSettings* InSettings)
{
  Clear();
  Save(InSettings);
}
