/*****************************************************************************
 * FILE NAME    : BookNameTableItem.cpp
 * DATE         : September 12 2023
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
#include "BookNameTableItem.h"
#include "Common.h"

/*****************************************************************************!
 * Function : BookNameTableItem
 *****************************************************************************/
BookNameTableItem::BookNameTableItem
(BookInfo* InBookInfo) : QWidget()
{
  QPalette pal;
  index = 0;
  pal = palette();
 
  bookInfo = InBookInfo;
  backgroundColor = QColor("#999999").lighter(100 + (bookInfo->bookGroup * 10));
  pal.setBrush(QPalette::Window, QBrush(backgroundColor));
  pal.setBrush(QPalette::WindowText, QBrush(QColor("444")));

  setPalette(pal);
  setAutoFillBackground(true);
  setCursor(Qt::PointingHandCursor);
  initialize();
}

/*****************************************************************************!
 * Function : ~BookNameTableItem
 *****************************************************************************/
BookNameTableItem::~BookNameTableItem
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookNameTableItem::initialize()
{
  normalFont  = QFont("Segoe UI", 10, QFont::Normal);
  selectedFont = QFont("Segoe UI", 12, QFont::Bold); 
  selected = false;
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BookNameTableItem::CreateSubWindows()
{
  //! Create label
  bookName = new QLabel();
  bookName->setParent(this);
  bookName->move(35, 0);
  bookName->resize(100, BOOK_NAME_TABLE_ITEM_HEIGHT);
  bookName->setText(bookInfo->name);
  bookName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  bookName->setFont(normalFont);

  bookNumberLabel = new QLabel();
  bookNumberLabel->setParent(this);
  bookNumberLabel->move(10, 0);
  bookNumberLabel->resize(20, BOOK_NAME_TABLE_ITEM_HEIGHT);
  bookNumberLabel->setText(QString("%1").arg(bookInfo->index));
  bookNumberLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  bookNumberLabel->setFont(normalFont);

  bookNumberLabel->setFont(normalFont);
  bookName->setFont(normalFont);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BookNameTableItem::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BookNameTableItem::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   bookNameY;
  int                                   bookNameX;
  int                                   bookNameH;
  int                                   bookNameW;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
  bookNameX = bookName->pos().x();
  bookNameY = 0;
  bookNameW = width - bookNameX;
  bookNameH = BOOK_NAME_TABLE_ITEM_HEIGHT;

  bookName->resize(bookNameW, bookNameH);
  bookName->move(bookNameX, bookNameY);
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
BookNameTableItem::paintEvent
(QPaintEvent*)
{
  QPen                                  pen;
  int                                   y1;
  int                                   y2;
  int                                   x2;
  int                                   x1;
  QSize                                 s;

  if ( ! bookInfo->groupEnd ) {
    return;
  }

  QPainter                              painter(this);
  s = size();
  x1 = 0;
  x2 = s.width();
  y1 = s.height() - 2;
  y2 = s.height() - 2;

  pen = QPen(QBrush(QColor(64, 64, 64)), 1);
  painter.setPen(pen);

  painter.drawLine(x1, y1, x2, y2);
  
  painter.end();
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
BookNameTableItem::enterEvent
(QEnterEvent* InEvent)
{
  QPalette                              pal;

  QString                               colorName;
  QColor                                co;
  int                                   r, g, b;

  co = QColor(backgroundColor);
  r = co.red() / 2;
  g = co.green() / 2;
  b = co.blue();

  co = QColor(r, g, b, 128);
  colorName = backgroundColor.name();
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(co));
  setPalette(pal);
  (void)InEvent;
}

/*****************************************************************************!
 * Function : leaveEvent
 *****************************************************************************/
void
BookNameTableItem::leaveEvent
(QEvent* InEvent)
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(backgroundColor));
  setPalette(pal);
  (void)InEvent;
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
BookNameTableItem::mousePressEvent
(QMouseEvent* InEvent)
{
  (void)InEvent;
  SetSelected(true);
  emit SignalBookSelected(bookInfo->index);
}

/*****************************************************************************!
 * Function : Select
 *****************************************************************************/
void
BookNameTableItem::Select
()
{
  SetSelected(true);
}

/*****************************************************************************!
 * Function : DeSelect
 *****************************************************************************/
void
BookNameTableItem::DeSelect
()
{
  SetSelected(false);
}

/*****************************************************************************!
 * Function : SetSelected
 *****************************************************************************/
void
BookNameTableItem::SetSelected
(bool InSelected)
{
  QFont                                 font;
  
  selected = InSelected;
  font = selected ? selectedFont : normalFont;
  
  bookNumberLabel->setFont(font);
  bookName->setFont(font);
}

/*****************************************************************************!
 * Function : GetBookNumber
 *****************************************************************************/
int
BookNameTableItem::GetBookNumber
()
{
  return bookNumber;
}
