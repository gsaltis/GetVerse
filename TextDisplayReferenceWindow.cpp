/*****************************************************************************
 * FILE NAME    : TextDisplayReferenceWindow.cpp
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
#include "TextDisplayReferenceWindow.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayReferenceWindow
 *****************************************************************************/
TextDisplayReferenceWindow::TextDisplayReferenceWindow
() : QSvgWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayReferenceWindow
 *****************************************************************************/
TextDisplayReferenceWindow::~TextDisplayReferenceWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayReferenceWindow::initialize()
{
  bookInfo = NULL;
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayReferenceWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayReferenceWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayReferenceWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextDisplayReferenceWindow::paintEvent
(QPaintEvent* InEvent)
{
  (void)InEvent;
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayReferenceWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QString                               name;

  bookInfo = InBookInfo;
  name = InBookInfo->GetCapitalizedBookName();
  GetChapter(1);
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
void
TextDisplayReferenceWindow::GetChapter
(int InChapter)
{
  QString                               columnName;
  int                                   n;
  QString                               sqlstmt;

  sqlstmt = QString("SELECT * from Verses where book is %1 and chapter is %2;\n").
    arg(bookInfo->index).
    arg(InChapter);

  n = sqlite3_exec(MainDatabase, sqlstmt.toStdString().c_str(), GetChapterCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, sqlstmt.toStdString().c_str(),
            sqlite3_errstr(n));
    return;
  }
}

/*****************************************************************************!
 * Function : GetChapterCB
 *****************************************************************************/
int
TextDisplayReferenceWindow::GetChapterCB
(void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               columnValue;
  QString                               columnName;
  QString                               verseText;
  QString                               reference;

  (void)InThisPointer;
  for ( int i = 0 ; i < InColumnCount ; i++ ) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "key" ) {
      reference = columnValue;
      continue;
    }

    if ( columnName == "text" ) {
      verseText = columnValue;
      continue;
    }
  }

  return 0;
}
