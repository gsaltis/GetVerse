/*****************************************************************************
 * FILE NAME    : BookInfoWord.cpp
 * DATE         : November 13 2023
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
#include "BookInfoWord.h"

/*****************************************************************************!
 * Function : BookInfoWord
 *****************************************************************************/
BookInfoWord::BookInfoWord
(int InBook, int InChapter, int InVerse, int InWordIndex, QString InWordText) : QWidget()
{
  book          = InBook;
  chapter       = InChapter;
  verse         = InVerse;
  index         = InWordIndex;
  word          = InWordText;
}

/*****************************************************************************!
 * Function : ~BookInfoWord
 *****************************************************************************/
BookInfoWord::~BookInfoWord
()
{
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
int
BookInfoWord::GetBook(void)
{
  return book;
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
int
BookInfoWord::GetChapter(void)
{
  return chapter;
}

/*****************************************************************************!
 * Function : GetVerse
 *****************************************************************************/
int
BookInfoWord::GetVerse(void)
{
  return verse;
}

/*****************************************************************************!
 * Function : GetIndex
 *****************************************************************************/
int
BookInfoWord::GetIndex(void)
{
  return index;
}

/*****************************************************************************!
 * Function : GetWord
 *****************************************************************************/
QString
BookInfoWord::GetWord
()
{
  return word;
}

/*****************************************************************************!
 * Function : IsEqual
 *****************************************************************************/
bool
BookInfoWord::IsEqual
(int InBook, int InChapter, int InVerse, int InIndex)
{
  if ( book != InBook ) {
    return false;
  }
  if ( chapter != InChapter ) {
    return false;
  }
  if ( verse != InVerse ) {
    return false;
      }
  if ( index != InIndex ) {
    return false;
  }
  return true;
}

