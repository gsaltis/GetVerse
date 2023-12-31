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
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayWordFormattingItem
 *****************************************************************************/
TextDisplayWordFormattingItem::TextDisplayWordFormattingItem
(int InBook, QString InBookName, int InChapter, int InVerse, int InWord, TextDisplayWordFormattingItem::FormatType InWordFormatting) :
  TextDisplayFormattingItem(InBook, InBookName, InChapter, InVerse, InWordFormatting)
{
  Foreground            = QColor(0, 0, 0);
  Background            = QColor(240, 0, 0);
  Type                  = FormattingWordType;
  WordIndex             = InWord;
  Font                  = MainSystemConfig->GetWordItemFont();
  Size                  = QSize(10, 20);
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
  QString                               st = QString("aa");
  QFontMetrics                          fm(Font);
  QSize                                 si = fm.size(0, st);
  QColor                                fore;
  QColor                                back;
  QPolygon                              poly;
  
  x = Location.x();
  y = Location.y();

  Size = QSize(10, Size.height());
  switch ( Formatting ) {
    case FormatTypeWordBreak : {
      xd = Size.width() - si.width();
      x += xd;
      fore = Foreground;
      back = Background;
      break;
    }
    case FormatTypeWordBreakIndent : {
      xd = Size.width() - si.width();
      x += xd;
      fore = QColor(0, 128, 0);
      back = QColor(0, 244, 0);;
      break;
    }
  }
  yd = Size.height() + si.height();
  yd /= 2;
  y += (yd - 3);

  InPainter->setFont(Font);

  poly << QPoint(Location.x(),                Size.height() / 2)
       << QPoint(Location.x() + Size.width(), Location.y())
       << QPoint(Location.x() + Size.width(), Location.y() + Size.height())
       << QPoint(Location.x(),                Size.height() / 2);
  
  InPainter->setPen(QPen(fore));
  InPainter->setBrush(QBrush(back));
  InPainter->drawRect(QRect(Location, Size));
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
