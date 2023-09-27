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
#include "Trace.h"

/*****************************************************************************!
 * Function : TextDisplayFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem::TextDisplayFormattingItem
(int InBook, QString InBookName, int InChapter, int InVerse,
 TextDisplayFormattingItem::FormatType InFormatting) :
  TextDisplayItem(InBook, InChapter, InVerse, QString())
{
  Foreground    = QColor(0, 0, 0);
  Background    = QColor(240, 240, 240);
  BookName      = InBookName;
  Type          = FormattingVerseType;
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
    case FormatTypePreVerse : {
      st = QChar(0x25BC);
      xd = Size.width() - si.width();
      xd /= 4;
      x += xd;
      break;
    }
    case FormatTypePostVerse : {
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
    
  InPainter->setPen(QPen(Foreground));
  InPainter->drawText(QPoint(x, y), st);
}


/*****************************************************************************!
 * Function : GetFormattingType
 *****************************************************************************/
TextDisplayFormattingItem::FormatType
TextDisplayFormattingItem::GetFormattingType
()
{
  return (TextDisplayFormattingItem::FormatType)Formatting;
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayFormattingItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

