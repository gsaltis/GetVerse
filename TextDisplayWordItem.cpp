/*****************************************************************************
 * FILE NAME    : TextDisplayWordItem.cpp
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
#include "TextDisplayWordItem.h"
#include "Trace.h"

/*****************************************************************************!
 * Function : TextDisplayWordItem
 *****************************************************************************/
TextDisplayWordItem::TextDisplayWordItem
(int InBook, int InChapter, int InVerse, QString InWord, int InWordIndex) :
  TextDisplayItem(InBook, InChapter, InVerse, QString())
{
  Text = QString("%2:%3").arg(InChapter).arg(InVerse); 
  Foreground = QColor(64, 64, 64);
  Background = QColor(255, 255, 255);
  Font = QFont("Arial", 10, QFont::Normal);
  Type = WordType;
  WordIndex = InWordIndex;
  Word = InWord;
}

/*****************************************************************************!
 * Function : ~TextDisplayWordItem
 *****************************************************************************/
TextDisplayWordItem::~TextDisplayWordItem
()
{
}

/*****************************************************************************!
 * Function : GetWordIndex
 *****************************************************************************/
int
TextDisplayWordItem::GetWordIndex(void)
{
  return WordIndex;  
}

/*****************************************************************************!
 * Function : SetWordIndex
 *****************************************************************************/
void
TextDisplayWordItem::SetWordIndex
(int InWordIndex)
{
  WordIndex = InWordIndex;  
}

/*****************************************************************************!
 * Function : Draw
 *****************************************************************************/
void
TextDisplayWordItem::Draw
(QPainter* InPainter)
{
  InPainter->setFont(Font);
  InPainter->setPen(QPen(Foreground));
  InPainter->setBrush(QBrush(Background));
  InPainter->drawText(QPoint(Location.x(), Location.y() + Size.height()),
                      Word);
}

/*****************************************************************************!
 * Function : DrawFormatted
 *****************************************************************************/
void
TextDisplayWordItem::DrawFormatted
(QPainter* InPainter, TextDisplayWordFormattingItem* InFormatting) 
{
  QColor                                        color;
  TextDisplayFormattingItem::FormatType         formatType;

  color = Foreground;
  formatType = InFormatting->GetFormattingType();
  TRACE_FUNCTION_INT(formatType);
  if ( formatType == TextDisplayWordFormattingItem::FormatTypeWordHighlight ) {
    color = QColor(255, 0, 0);
  }
  InPainter->setFont(Font);
  InPainter->setPen(QPen(color));
  InPainter->setBrush(QBrush(Background));
  InPainter->drawText(QPoint(Location.x(), Location.y() + Size.height()),
                      Word);
}

/*****************************************************************************!
 * Function : DrawSelected
 *****************************************************************************/
void
TextDisplayWordItem::DrawSelected
(QPainter* InPainter)
{
  int                                   l, t, h, w;
  QRect                                 r, r2;

  InPainter->setFont(Font);
  InPainter->setPen(QPen(QColor(32, 32, 32)));
  InPainter->setBrush(QBrush(QColor(32, 32, 32)));
  r = GetBoundingRect();

  h = r.height() + 6;
  w = r.width() + 6;

  l = r.left() - 3;
  t = r.top() + 0;

  r2 = QRect(QPoint(l, t), QSize(w, h));
  InPainter->drawRoundedRect(r2, 20, 20);
  
  InPainter->setPen(QPen(QColor(255, 255, 255)));
  InPainter->drawText(QPoint(Location.x(), Location.y() + Size.height()), Word);
}

/*****************************************************************************!
 * Function : GetWord
 *****************************************************************************/
QString
TextDisplayWordItem::GetWord(void)
{
  return Word;  
}

/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
TextDisplayWordItem::GetText(void)
{
  return Word;  
}

/*****************************************************************************!
 * Function : SetWord
 *****************************************************************************/
void
TextDisplayWordItem::SetWord
(QString InWord)
{
  Word = InWord;
}

/*****************************************************************************!
 * Function : SetFont
 *****************************************************************************/
void
TextDisplayWordItem::SetFont
(QFont InFont)
{
  QFontMetrics                          fm(InFont);
  Font = QFont(InFont);
  Size = fm.size(0, Word);
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayWordItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : IsReference
 *****************************************************************************/
bool
TextDisplayWordItem::IsReference
(const int InBook, const int InChapter, const int InVerse, const int InWord)
{
  if ( InBook == Book && InChapter == Chapter && InVerse == Verse && InWord == WordIndex ) {
    return true;
  }
  return false;
}

