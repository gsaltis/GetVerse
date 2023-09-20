/*****************************************************************************
 * FILE NAME    : TextDisplayFormattingItem.cpp
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
#include <QScreen>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayFormattingItem.h"

/*****************************************************************************!
 * Function : TextDisplayFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem::TextDisplayFormattingItem
(int InBook, QString InBookName, int InChapter, int InVerse, int InFormatting) :
  TextDisplayItem(InBook, InChapter, InVerse, QString())
{
  Foreground    = QColor(0, 0, 0);
  Background    = QColor(240, 240, 240);
  BookName      = InBookName;
  Type          = FormattingType;
  Formatting    = InFormatting;
  Font = QFont("Arial", 14, QFont::Normal);
}

/*****************************************************************************!
 * Function : ~TextDisplayFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem::~TextDisplayFormattingItem
()
{
}

/*****************************************************************************!
 * Function : Draw
 *****************************************************************************/
void
TextDisplayFormattingItem::Draw
(QPainter* InPainter)
{
  int                                   xd;
  int                                   yd;
  int                                   y;
  int                                   x;
  QString                               st;
  QFontMetrics                          fm(Font);
  QSize                                 si = fm.size(0, st);

  x = Location.x();
  y = Location.y();

  switch ( Formatting ) {
    case 1 : {
      st = QChar(0x25BC);
      xd = Size.width() - si.width();
      xd /= 4;
      x += xd;
      break;
    }
    case 2 : {
      st = QChar(0x25B2);
      xd = Size.width() - si.width();
      xd /= 4;
      x += xd;
      break;
    }
  }
  yd = Size.height() + si.height();
  yd /= 2;
  y += (yd - 3);

  InPainter->setFont(Font);
  InPainter->setPen(QPen(Foreground));
  InPainter->setBrush(QBrush(Background));
  InPainter->drawRect(QRect(Location, Size));
  InPainter->drawText(QPoint(x, y), st);
}

