/*****************************************************************************
 * FILE NAME    : StrongsReferenceVerseWindow.cpp
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QHeaderView>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "StrongsReferenceVerseWindow.h"
#include "StrongsReferenceVerseItem.h"

/*****************************************************************************!
 * Function : StrongsReferenceVerseWindow
 *****************************************************************************/
StrongsReferenceVerseWindow::StrongsReferenceVerseWindow
() : QTableWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setColumnCount(1);
  horizontalHeader()->hide();
  setShowGrid(false);
}

/*****************************************************************************!
 * Function : ~StrongsReferenceVerseWindow
 *****************************************************************************/
StrongsReferenceVerseWindow::~StrongsReferenceVerseWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
StrongsReferenceVerseWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
StrongsReferenceVerseWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
StrongsReferenceVerseWindow::CreateConnections()
{
  connect(this,
          QTableWidget::itemClicked,
          this,
          StrongsReferenceVerseWindow::SlotItemSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
StrongsReferenceVerseWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
StrongsReferenceVerseWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;

  size = InEvent->size();
  width = size.width();

  setColumnWidth(0, width);
}

/*****************************************************************************!
 * Function : SlotVerseReferenceClear
 *****************************************************************************/
void
StrongsReferenceVerseWindow::SlotVerseReferenceClear(void)
{
  Clear();
}

/*****************************************************************************!
 * Function : SlotVerseReferenceSelected
 *****************************************************************************/
void
StrongsReferenceVerseWindow::SlotVerseReferenceSelected
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  int                                   n;
  StrongsReferenceVerseItem*                    item;

  item = new StrongsReferenceVerseItem(InBookNumber, InChapterNumber, InVerseNumber);
  n = rowCount();
  insertRow(n);
  setItem(n, 0, item);
}

/*****************************************************************************!
 * Function : Clear
 *****************************************************************************/
void
StrongsReferenceVerseWindow::Clear(void)
{
  while (rowCount() ) {
    removeRow(0);
  }
}

/*****************************************************************************!
 * Function : SlotItemSelected
 *****************************************************************************/
void
StrongsReferenceVerseWindow::SlotItemSelected
(QTableWidgetItem* InItem)
{
  StrongsReferenceVerseItem*            item;
  int                                   bookNumber;
  int                                   chapterNumber;
  int                                   verseNumber;
  
  item = (StrongsReferenceVerseItem*)InItem;
  item->GetReference(bookNumber, chapterNumber, verseNumber);
  
  emit SignalStrongsReferenceSelected(bookNumber, chapterNumber, verseNumber);
}
