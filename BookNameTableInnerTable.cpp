/*****************************************************************************
 * FILE NAME    : BookNameTableInnerTable.cpp
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookNameTableInnerTable.h"
#include "Common.h"

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
  tableHeight = BOOK_NAME_TABLE_ITEM_HEIGHT * MainBookInfo->GetSize() + topMargin;
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
  BookInfo*                             bookInfo;
  int                                   i;
  int                                   n;
  QString                               name;
  BookNameTableItem*                    tableItem;
  int                                   y;

  n = MainBookInfo->GetSize();
  
  y = topMargin;
  for ( i = 0 ; i < n ; i++ ) {
    bookInfo = MainBookInfo->GetByIndex(i);
    name = bookInfo->name;
    tableItem = new BookNameTableItem(bookInfo);
    tableItem->move(0, y);
    tableItem->setParent(this);
    items.push_back(tableItem);
    y += BOOK_NAME_TABLE_ITEM_HEIGHT;
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
  QObjectList                           ch;
  int                                   n;
  
  ch = children();
  n = 0;
  for (auto  item : ch ) {
    BookNameTableItem*                  bookItem = (BookNameTableItem*)item;
    n++;
    if ( InBookIndex  == n ) {
      bookItem->Select();
      continue;
    }
    bookItem->DeSelect();
  }
  emit SignalBookSelected(InBookIndex);
}

/*****************************************************************************!
 * Function : SlotMoveToBookChapter
 *****************************************************************************/
void
BookNameTableInnerTable::SlotMoveToBookChapter
(int InBook, int InChapter, int InVerse)
{
  (void)InChapter;
  (void)InVerse;
  SlotBookSelected(InBook);
}

/*****************************************************************************!
 * Function : FindBookItemByBookNumber
 *****************************************************************************/
BookNameTableItem*
BookNameTableInnerTable::FindBookItemByBookNumber
(int InBookNumber)
{
  for ( auto i : items ) {
    if ( i->GetBookNumber() == InBookNumber ) {
      return i;
    }
  }
  return NULL;
}
