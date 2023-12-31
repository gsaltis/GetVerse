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
  Font = QFont("Arial", 12, QFont::Normal);
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

/*****************************************************************************!
 * Function : DrawSelected
 *****************************************************************************/
void
TextDisplayReferenceItem::DrawSelected
(QPainter* InPainter)
{
  int                                   x;
  QRect                                 r;
  QRect                                 r2;
  int                                   h;
  int                                   w;
  int                                   y;
  QFontMetrics                          fm(Font);
  QSize                                 s;
  int                                   textWidth;

  s = fm.size(0, Text);
  textWidth = s.width();
  
  InPainter->setFont(Font);
  InPainter->setPen(QPen(QColor(160, 160, 160)));
  InPainter->setBrush(QBrush(QColor(224, 224, 224)));

  r = GetBoundingRect();

  x = Location.x() + (Size.width() - s.width());
  y = r.top() + 0;
  w = textWidth + 8;
  h = r.height() + 6;

  r2 = QRect(QPoint(x-3, y), QSize(w, h));
  InPainter->drawRoundedRect(r2, 20, 20);

  InPainter->setPen(QPen(QColor(128, 0, 0)));
  InPainter->drawText(QPoint(x, Location.y() + Size.height()), Text);
}

