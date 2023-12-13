/*****************************************************************************
 * FILE NAME    : BookMark.cpp
 * DATE         : December 09 2023
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
#include "BookMark.h"
#include "BookmarkButton.h"

/*****************************************************************************!
 * Function : BookMark
 *****************************************************************************/
BookMark::BookMark
(int InIndex) : QWidget()
{
  Initialize();
  Index = InIndex;
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
  book = InBook;
  chapter = InChapter;
  verse = InVerse;

  button->Set(book, chapter, verse);
    
}
