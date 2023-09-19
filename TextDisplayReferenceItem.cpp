/*****************************************************************************
 * FILE NAME    : TextDisplayReferenceItem.cpp
 * DATE         : September 16 2023
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
#include "TextDisplayReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayReferenceItem
 *****************************************************************************/
TextDisplayReferenceItem::TextDisplayReferenceItem
(int InBook, QString InBookName, int InChapter, int InVerse) :
  TextDisplayItem(InBook, InChapter, InVerse, QString())
{
  Text = QString("%2:%3").arg(InChapter).arg(InVerse); 
  Foreground = QColor(192, 0, 0);
  Background = QColor(255, 255, 255);
  BookName = InBookName;
  Font = QFont("Arial", 10, QFont::Normal);
  Type = ReferenceType;
}

/*****************************************************************************!
 * Function : ~TextDisplayReferenceItem
 *****************************************************************************/
TextDisplayReferenceItem::~TextDisplayReferenceItem
()
{
}

/*****************************************************************************!
 * Function : Draw
 *****************************************************************************/
void
TextDisplayReferenceItem::Draw
(QPainter* InPainter)
{
  int                                   d;
  QFontMetrics                          fm(Font);
  QSize                                 s;
  int                                   textWidth;
  int                                   x;

  s = fm.size(0, Text);
  textWidth = s.width();
  x = Location.x();
  
  d = Size.width() - textWidth;
  if ( d > 0 ) {
    x += d;
  }
  InPainter->setFont(Font);
  InPainter->setPen(QPen(Foreground));
  InPainter->drawText(QPoint(x, Location.y() + Size.height()), Text);
}

