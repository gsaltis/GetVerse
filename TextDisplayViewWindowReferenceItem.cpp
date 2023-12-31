/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindowReferenceItem.cpp
 * DATE         : September 13 2023
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
#include "TextDisplayViewWindowReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayViewWindowReferenceItem
 *****************************************************************************/
TextDisplayViewWindowReferenceItem::TextDisplayViewWindowReferenceItem
(QString InText, int InBookIndex, int InChapter, int InVerse, int InX, int InY, QSize InSize) :
  TextDisplayViewWindowItem(InText, InX, InY, InSize)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::WindowText, QBrush(QColor(192, 0, 0)));
  setPalette(pal);
  setAutoFillBackground(true);
  setCursor(Qt::PointingHandCursor);
  setAlignment(Qt::AlignRight);

  BookIndex = InBookIndex;
  Chapter = InChapter;
  Verse = InVerse;

  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayViewWindowReferenceItem
 *****************************************************************************/
TextDisplayViewWindowReferenceItem::~TextDisplayViewWindowReferenceItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::enterEvent
(QEnterEvent* InEvent)
{
  (void)InEvent;
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::leaveEvent
(QEvent* InEvent)
{
  (void)InEvent;
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::mousePressEvent
(QMouseEvent* )
{
}

/*****************************************************************************!
 * Function : GetWordCount
 *****************************************************************************/
int
TextDisplayViewWindowReferenceItem::GetWordCount(void)
{
  return WordCount;  
}

/*****************************************************************************!
 * Function : SetWordCount
 *****************************************************************************/
void
TextDisplayViewWindowReferenceItem::SetWordCount
(int InWordCount)
{
  WordCount = InWordCount;  
}

/*****************************************************************************!
 * Function : GetBookIndex
 *****************************************************************************/
int
TextDisplayViewWindowReferenceItem::GetBookIndex
()
{
  return BookIndex;
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
int
TextDisplayViewWindowReferenceItem::GetChapter
()
{
  return Chapter;
}

/*****************************************************************************!
 * Function : GetVerse
 *****************************************************************************/
int
TextDisplayViewWindowReferenceItem::GetVerse
()
{
  return Verse;
}

