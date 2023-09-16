/*****************************************************************************
 * FILE NAME    : TextDisplayItem.cpp
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
#include "TextDisplayItem.h"
#include "Trace.h"

/*****************************************************************************!
 * Function : TextDisplayItem
 *****************************************************************************/
TextDisplayItem::TextDisplayItem
(int InBook, int InChapter, int InVerse, QString InText)
{
  Verse = InVerse;
  Chapter = InChapter;
  Book = InBook;
  Text = QString(InText);
  Foreground = QColor(0, 0, 0);
  Background = QColor(255, 255, 255);
  Font = QFont("Arial", 10, QFont::Normal);
  Type = TextType;
}

/*****************************************************************************!
 * Function : ~TextDisplayItem
 *****************************************************************************/
TextDisplayItem::~TextDisplayItem
()
{
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
int
TextDisplayItem::GetBook(void)
{
  return Book;
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
int
TextDisplayItem::GetVerse(void)
{
  return Verse;
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
int
TextDisplayItem::GetChapter(void)
{
  return Chapter;
}

/*****************************************************************************!
 * Function : GetText
 *****************************************************************************/
QString
TextDisplayItem::GetText(void)
{
  return Text;  
}

/*****************************************************************************!
 * Function : SetText
 *****************************************************************************/
void
TextDisplayItem::SetText
(QString InText)
{
  Text = InText;  
}

/*****************************************************************************!
 * Function : GetSize
 *****************************************************************************/
QSize
TextDisplayItem::GetSize(void)
{
  return Size;  
}

/*****************************************************************************!
 * Function : SetSize
 *****************************************************************************/
void
TextDisplayItem::SetSize
(QSize InSize)
{
  Size = InSize;  
}

/*****************************************************************************!
 * Function : GetLocation
 *****************************************************************************/
QPoint
TextDisplayItem::GetLocation(void)
{
  return Location;  
}

/*****************************************************************************!
 * Function : SetLocation
 *****************************************************************************/
void
TextDisplayItem::SetLocation
(QPoint InLocation)
{
  Location = InLocation;  
}

/*****************************************************************************!
 * Function : Draw
 *****************************************************************************/
void
TextDisplayItem::Draw
(QPainter* InPainter)
{
  InPainter->setFont(Font);
  InPainter->setPen(QPen(Foreground));
  InPainter->setBrush(QBrush(Background));
  InPainter->drawText(QPoint(Location.x(), Location.y() + Size.height()),
                      Text);
}

/*****************************************************************************!
 * Function : DrawSelected
 *****************************************************************************/
void
TextDisplayItem::DrawSelected
(QPainter* InPainter)
{
  int                                   l, t, h, w;
  QRect                                 r, r2;
  
  InPainter->setFont(Font);
  InPainter->setPen(QPen(QColor(160, 160, 160)));
  InPainter->setBrush(QBrush(QColor(224, 224, 224)));
  r = GetBoundingRect();

  h = r.height() + 6;
  w = r.width() + 6;

  l = r.left() - 3;
  t = r.top() + 0;

  r2 = QRect(QPoint(l, t), QSize(w, h));
  InPainter->drawRoundedRect(r2, 3, 3);
  
  InPainter->setPen(QPen(QColor(128, 0, 0)));
  InPainter->drawText(QPoint(Location.x(), Location.y() + Size.height()), Text);
}

/*****************************************************************************!
 * Function : SetFont
 *****************************************************************************/
void
TextDisplayItem::SetFont
(QFont InFont)
{
  QFontMetrics                          fm(InFont);
  Font = QFont(InFont);
  Size = fm.size(0, Text);
}

/*****************************************************************************!
 * Function : GetBackground
 *****************************************************************************/
QColor
TextDisplayItem::GetBackground(void)
{
  return Background;  
}

/*****************************************************************************!
 * Function : SetBackground
 *****************************************************************************/
void
TextDisplayItem::SetBackground
(QColor InBackground)
{
  Background = InBackground;  
}

/*****************************************************************************!
 * Function : GetForeground
 *****************************************************************************/
QColor
TextDisplayItem::GetForeground(void)
{
  return Foreground;  
}

/*****************************************************************************!
 * Function : SetForeground
 *****************************************************************************/
void
TextDisplayItem::SetForeground
(QColor InForeground)
{
  Foreground = InForeground;  
}

/*****************************************************************************!
 * Function : GetType
 *****************************************************************************/
TextDisplayItem::DisplayType
TextDisplayItem::GetType
()
{
  return Type;
}

/*****************************************************************************!
 * Function : Contains
 *****************************************************************************/
bool
TextDisplayItem::Contains
(QPoint InPoint)
{
  QRect                         r = QRect(Location, Size);
  return r.contains(InPoint);
}

/*****************************************************************************!
 * Function : GetBoundingRect
 *****************************************************************************/
QRect
TextDisplayItem::GetBoundingRect
()
{
  return QRect(Location, Size);
}
