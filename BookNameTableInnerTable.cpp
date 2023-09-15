/*****************************************************************************
 * FILE NAME    : BookNameTableInnerTable.cpp
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
#include "BookNameTableInnerTable.h"
#include "Common.h"
#include "Trace.h"

/*****************************************************************************!
 * Function : BookNameTableInnerTable
 *****************************************************************************/
BookNameTableInnerTable::BookNameTableInnerTable
() : QWidget()
{
  QPalette pal;
  topMargin = 0;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~BookNameTableInnerTable
 *****************************************************************************/
BookNameTableInnerTable::~BookNameTableInnerTable
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
BookNameTableInnerTable::initialize()
{
  tableHeight = BOOK_NAME_TABLE_ITEM_HEIGHT * MainBookInfo.size() + topMargin;
  resize(BOOK_NAME_TABLE_ITEM_WIDTH, tableHeight);
  InitializeSubWindows();  
  CreateSubWindows();
  Populate();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
BookNameTableInnerTable::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
BookNameTableInnerTable::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
BookNameTableInnerTable::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;

  size = InEvent->size();
  width = size.width();
  for ( auto item : items ) {
    item->resize(width, BOOK_NAME_TABLE_ITEM_HEIGHT);
  }
  resize(width, tableHeight);
}

/*****************************************************************************!
 * Function : Populate
 *****************************************************************************/
void
BookNameTableInnerTable::Populate(void)
{
  int                                   n;
  QString                               name;
  BookNameTableItem*                    tableItem;
  int                                   y;


  y = topMargin;
  n = 1;
  for ( BookInfo* bookInfo : MainBookInfo) {
    name = bookInfo->GetCapitalizedBookName();
    tableItem = new BookNameTableItem(n, name);
    tableItem->move(0, y);
    tableItem->setParent(this);
    items.push_back(tableItem);
    y += BOOK_NAME_TABLE_ITEM_HEIGHT;
    n++;
    connect(tableItem,
            SIGNAL(SignalBookSelected(int)),
            this,
            SLOT(SlotBookSelected(int)));
  }
  tableHeight = y;
}

/*****************************************************************************!
 * Function : GetTableHeight 
 *****************************************************************************/
int
BookNameTableInnerTable::GetTableHeight
()
{
  return tableHeight;
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
BookNameTableInnerTable::SlotBookSelected
(int InBookIndex)
{
  emit SignalBookSelected(InBookIndex);
}

