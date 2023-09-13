/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindow.cpp
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
#include "TextDisplayViewWindow.h"
#include "Common.h"
#include "Trace.h"
#include "TextDisplayViewWindowItem.h"
#include "TextDisplayViewWindowReferenceItem.h"

/*****************************************************************************!
 * Function : TextDisplayViewWindow
 *****************************************************************************/
TextDisplayViewWindow::TextDisplayViewWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setFont(QFont("Arial", 11, QFont::Normal));
}

/*****************************************************************************!
 * Function : ~TextDisplayViewWindow
 *****************************************************************************/
TextDisplayViewWindow::~TextDisplayViewWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewWindow::initialize()
{
  InterLineSkip = 3;
  InterWordSkip = 4;
  rightMargin = 10;
  
  InitializeSubWindows();  
  CreateSubWindows();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewWindow::CreateSubWindows()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewWindow::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindow::resizeEvent
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
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotBookSelected
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
TextDisplayViewWindow::GetChapter
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
TextDisplayViewWindow::GetChapterCB
(void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               columnValue;
  QString                               columnName;
  QString                               verseText;
  QString                               reference;
  QString                               s;
  TextDisplayViewWindow*                window;
  
  window = (TextDisplayViewWindow*)InThisPointer;
  
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

  window->AddLine(reference, verseText);
  return 0;
}

/*****************************************************************************!
 * Function : AddLine
 *****************************************************************************/
void
TextDisplayViewWindow::AddLine
(QString InReference, QString InVerseText)
{
  QString                               word;
  int                                   i;
  int                                   n;
  QStringList                           words;
  QFontMetrics                          fm(font());
  QSize                                 s2;
  int                                   x = 5;
  int                                   verseX;
  int                                   width;
  QSize                                 s3;
  
  TextDisplayViewWindowItem*            item;
  s3 = size();
  width = s3.width();
  
  s2 = fm.size(0, InReference);
  item = new TextDisplayViewWindowReferenceItem(InReference, x, textY, s2);
  item->setParent(this);
  x += s2.width() + InterWordSkip;
  item->show();
  verseX = x;
  words = InVerseText.split(" ");
  n = words.size();

  for (i = 0; i < n; i++) {
    word = words[i];
    s2 = fm.size(0, word);
    if ( x + s2.width() + rightMargin > width ) {
      textY += s2.height() + InterLineSkip;
      x = verseX;
    }
    item = new TextDisplayViewWindowItem(word, x, textY, s2);
    item->setParent(this);
    x += s2.width() + InterWordSkip;
    item->show();
  }
  textY += s2.height() + InterLineSkip;
}

/*****************************************************************************!
 * Function : ClearText
 *****************************************************************************/
void
TextDisplayViewWindow::ClearText
()
{
  while ( QWidget* w = findChild<QWidget*>() ) {
    delete w;
  }
  textX = 0;
  textY = 0;
}
