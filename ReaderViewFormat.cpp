/*****************************************************************************
 * FILE NAME    : ReaderViewFormat.cpp
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
#include "ReaderViewFormat.h"

/*****************************************************************************!
 * Function : ReaderViewFormat
 *****************************************************************************/
ReaderViewFormat::ReaderViewFormat
() : QWidget()
{
  Initialize();
}

/*****************************************************************************!
 * Function : ReaderViewFormat
 *****************************************************************************/
ReaderViewFormat::ReaderViewFormat
(BookInfo* InBook, int InChapter, int InVerse, int InWordIndex)
{
  Initialize();
  Book = InBook;
  Chapter = InChapter;
  Verse = InVerse;
  WordIndex = InWordIndex;
}

/*****************************************************************************!
 * Function : ~ReaderViewFormat
 *****************************************************************************/
ReaderViewFormat::~ReaderViewFormat
()
{
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
BookInfo*
ReaderViewFormat::GetBook(void)
{
  return Book;  
}

/*****************************************************************************!
 * Function : SetBook
 *****************************************************************************/
void
ReaderViewFormat::SetBook
(BookInfo* InBook)
{
  Book = InBook;  
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
int
ReaderViewFormat::GetChapter(void)
{
  return Chapter;  
}

/*****************************************************************************!
 * Function : SetChapter
 *****************************************************************************/
void
ReaderViewFormat::SetChapter
(int InChapter)
{
  Chapter = InChapter;  
}

/*****************************************************************************!
 * Function : GetVerse
 *****************************************************************************/
int
ReaderViewFormat::GetVerse(void)
{
  return Verse;  
}

/*****************************************************************************!
 * Function : SetVerse
 *****************************************************************************/
void
ReaderViewFormat::SetVerse
(int InVerse)
{
  Verse = InVerse;  
}

/*****************************************************************************!
 * Function : GetWordIndex
 *****************************************************************************/
int
ReaderViewFormat::GetWordIndex(void)
{
  return WordIndex;  
}

/*****************************************************************************!
 * Function : SetWordIndex
 *****************************************************************************/
void
ReaderViewFormat::SetWordIndex
(int InWordIndex)
{
  WordIndex = InWordIndex;  
}

/*****************************************************************************!
 * Function : GetColor
 *****************************************************************************/
QColor
ReaderViewFormat::GetColor(void)
{
  return Color;  
}

/*****************************************************************************!
 * Function : SetColor
 *****************************************************************************/
void
ReaderViewFormat::SetColor
(QColor InColor)
{
  Color = InColor;  
}

/*****************************************************************************!
 * Function : GetTitle
 *****************************************************************************/
QString
ReaderViewFormat::GetTitle(void)
{
  return Title;  
}

/*****************************************************************************!
 * Function : SetTitle
 *****************************************************************************/
void
ReaderViewFormat::SetTitle
(QString InTitle)
{
  Title = InTitle;  
}

/*****************************************************************************!
 * Function : GetBookIndex
 *****************************************************************************/
int
ReaderViewFormat::GetBookIndex(void)
{
  if ( NULL == Book ) {
    return 0;
  }
  return Book->GetIndex();
}

/*****************************************************************************!
 * Function : IsEqual
 *****************************************************************************/
bool
ReaderViewFormat::IsEqual
(int InBook, int InChapter, int InVerse, int InWordIndex)
{
  if ( InBook != GetBookIndex() ) {
    return false;
  }

  if ( InChapter != Chapter || InVerse != Verse || InWordIndex != WordIndex ) {
    return false;
  }

  return true;
}

/*****************************************************************************!
 * Function : Compare
 *****************************************************************************/
int
ReaderViewFormat::Compare
(int InBook, int InChapter, int InVerse, int InWordIndex)
{
  int                                   b;

  //!
  b = GetBookIndex();
  if ( InBook < b ) {
    return -1;
  }
  if ( InBook > b ) {
    return 1;
  }

  //!
  if ( InChapter < Chapter ) {
    return -1;
  }
  if ( InChapter > Chapter ) {
    return 1;
  }

  //!
  if ( InVerse < Verse ) {
    return -1;
  }
  if ( InVerse > Verse ) {
    return 1;
  }

  //!
  if ( InWordIndex < WordIndex ) {
    return -1;
  }
  if ( InWordIndex > WordIndex ) {
    return 1;
  }

  return 0;
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
ReaderViewFormat::Initialize(void)
{
  Book = NULL;
  Chapter = 0;
  Verse = 0;
  WordIndex = 0;
  Color = QString();
  Title = QString();
}

/*****************************************************************************!
 * Function : GetFormat
 *****************************************************************************/
int
ReaderViewFormat::GetFormat(void)
{
  return Format;  
}

/*****************************************************************************!
 * Function : SetFormat
 *****************************************************************************/
void
ReaderViewFormat::SetFormat
(int InFormat)
{
  Format = InFormat;  
}
