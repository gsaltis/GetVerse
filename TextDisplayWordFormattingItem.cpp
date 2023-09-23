 /*****************************************************************************
 * FILE NAME    : TextDisplayWordFormattingItem.cpp
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
#include "TextDisplayWordFormattingItem.h"
#include "Trace.h"

/*****************************************************************************!
 * Function : TextDisplayWordFormattingItem
 *****************************************************************************/
TextDisplayWordFormattingItem::TextDisplayWordFormattingItem
(int InBook, QString InBookName, int InChapter, int InVerse, int InWord, TextDisplayWordFormattingItem::FormatType InWordFormatting) :
  TextDisplayFormattingItem(InBook, InBookName, InChapter, InVerse, InWordFormatting)
{
  Foreground            = QColor(0, 0, 0);
  Background            = QColor(240, 240, 240);
  Type                  = FormattingWordType;
  WordIndex             = InWord;
  Font                  = QFont("Arial", 14, QFont::Normal);
}

/*****************************************************************************!
 * Function : ~TextDisplayWordFormattingItem
 *****************************************************************************/
TextDisplayWordFormattingItem::~TextDisplayWordFormattingItem
()
{
}

/*****************************************************************************!
 * Function : Draw
 *****************************************************************************/
void
TextDisplayWordFormattingItem::Draw
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
    case FormatTypeWordBreak : {
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
 * Function : GetWordIndex
 *****************************************************************************/
int
TextDisplayWordFormattingItem::GetWordIndex
()
{
  return WordIndex;
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayWordFormattingItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : IsReferenceWord
 *****************************************************************************/
bool
TextDisplayWordFormattingItem::IsReferenceWord
(const int InBook, const int InChapter, const int InVerse, const int InWordIndex)
{
  if ( InBook == Book &&
       InChapter == Chapter &&
       InVerse == Verse &&
       WordIndex == InWordIndex) {
    return true;
  }
  return false;
}

