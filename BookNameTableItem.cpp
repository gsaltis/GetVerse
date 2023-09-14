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
#include "Trace.h"

/*****************************************************************************!
 * Function : BookNameTableItem
 *****************************************************************************/
BookNameTableItem::BookNameTableItem
(int InBookNumber, QString InName) : QWidget()
{
  QColor                                co;
  name = InName;
  bookNumber = InBookNumber;
  index = 0;
  groupEnd = false;
  ReadFormatDB();
  QPalette pal;
  pal = palette();

  co = QColor(textColor);
  pal.setBrush(QPalette::Window, QBrush(co.lighter(250)));
  pal.setBrush(QPalette::WindowText, QBrush(co.darker(100)));

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
  bookName->setText(name);
  bookName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  bookName->setFont(QFont("Arial", 10, QFont::Normal));

  bookNumberLabel = new QLabel();
  bookNumberLabel->setParent(this);
  bookNumberLabel->move(10, 0);
  bookNumberLabel->resize(20, BOOK_NAME_TABLE_ITEM_HEIGHT);
  bookNumberLabel->setText(QString("%1").arg(bookNumber));
  bookNumberLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  bookNumberLabel->setFont(QFont("Arial", 10, QFont::Normal));
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
 * Function : GetName
 *****************************************************************************/
QString
BookNameTableItem::GetName(void)
{
  return name;  
}

/*****************************************************************************!
 * Function : SetName
 *****************************************************************************/
void
BookNameTableItem::SetName
(QString InName)
{
  name = InName;  
}

/*****************************************************************************!
 * Function : ReadFormatDB
 *****************************************************************************/
void
BookNameTableItem::ReadFormatDB
()
{
  int                                   n;
  QString                               sqlstmt;

  sqlstmt = QString("Select * FROM BookFormat where bookIndex is %1;").arg(bookNumber);

  n = sqlite3_exec(MainDatabase, sqlstmt.toStdString().c_str(), BookNameTableItem::ReadFormatDBCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "sqlite3_exec() failure\n%s %s\n%s\n",
            __FUNCTION__, sqlite3_errstr(n),
            sqlstmt.toStdString().c_str());
    return;
  }
}

/*****************************************************************************!
 * Function : ReadFormatDBCB
 *****************************************************************************/
int
BookNameTableItem::ReadFormatDBCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               columnName;
  QString                               columnValue;
  int                                   i;
  QString                               textColor;
  QString                               backgroundColor;
  BookNameTableItem*                    item;

  item = (BookNameTableItem*)InPointer;
  
  for ( i = 0 ; i < InColumnCount ; i++ ) {
    columnName  = QString(InColumnNames[i]);
    columnValue = QString(InColumnValues[i]);
    if ( columnName == "TextColor" ) {
      item->SetTextColor(columnValue);
      continue;
    } 
    if ( columnName == "bookIndex" ) {
      item->SetIndex(columnValue.toInt());
      continue;
    } 
    if ( columnName == "BackgroundColor" ) {
      item->SetBackgroundColor(columnValue);
      continue;
    }
    if ( columnName == "GroupEnd" ) {
      item->SetGroupEnd(columnValue.toInt() ? true : false);
      continue;
    }
  }
  return 0;
}

/*****************************************************************************!
 * Function : SetTextColor
 *****************************************************************************/
void
BookNameTableItem::SetTextColor
(QString InTextColor)
{
  textColorName = InTextColor;
  textColor = QColor(textColorName);
  backgroundColor = QColor(textColorName).lighter(250);

  selectedColor = QColor(textColorName).darker(130);
  selectedTextColor = QColor(textColorName).lighter(250);
}

/*****************************************************************************!
 * Function : SetBackgroundColor
 *****************************************************************************/
void
BookNameTableItem::SetBackgroundColor
(QString InBackgroundColor)
{
  backgroundColorName = InBackgroundColor;
}

/*****************************************************************************!
 * Function : SetGroupEnd
 *****************************************************************************/
void
BookNameTableItem::SetGroupEnd
(bool InGroupEnd)
{
  groupEnd = InGroupEnd;
}

/*****************************************************************************!
 * Function : SetIndex
 *****************************************************************************/
void
BookNameTableItem::SetIndex
(int InIndex)
{
  index = InIndex;
}

/*****************************************************************************!
 * Function : GetIndex
 *****************************************************************************/
int
BookNameTableItem::GetIndex
()
{
  return index;
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

  if ( ! groupEnd ) {
    return;
  }

  QPainter                              painter(this);
  s = size();
  x1 = 0;
  x2 = s.width();
  y1 = s.height() - 2;
  y2 = s.height() - 2;

  pen = QPen(QBrush(QColor(128, 128, 128)), 1);
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

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(selectedColor));
  pal.setBrush(QPalette::WindowText, QBrush(selectedTextColor));
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
  pal.setBrush(QPalette::WindowText, QBrush(textColor));
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
  emit SignalBookSelected(index);
}
