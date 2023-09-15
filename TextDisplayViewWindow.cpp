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
#include <QThread>
#include <stdio.h>
#include <stdlib.h>

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
  setFont(displayFont);
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
  rightMargin   = 30;
  leftMargin    = 10;
  bottomMargin  = 10;
  topMargin     = 10;
  tableHeight   = 0;

  mode = ReferenceMode;
  displayFont = QFont("Arial", 11, QFont::Normal);
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
 * Function : ArrangeElements
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeElements
(int InWidth)
{
  if ( mode == ReferenceMode ) {
    return ArrangeElementsReference(InWidth);
  }
  if ( mode == BlockMode ) {
    return ArrangeElementsBlock(InWidth);
  }

  if ( mode == SentenceMode ) {
    return ArrangeElementsSentence(InWidth);
  }
  return 0;
}

/*****************************************************************************!
 * Function : ArrangeElementsBlock
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeElementsBlock
(int InWidth)
{
  (void)InWidth;
  return 0;
}

/*****************************************************************************!
 * Function : ArrangeElementsSentence
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeElementsSentence
(int InWidth)
{
  int                                   k;
  QString                               ending;
  QString                               itemText;
  int                                   i;
  TextDisplayViewWindowItem*            item;
  int                                   itemHeight;
  int                                   itemWidth;
  int                                   n;
  TextDisplayViewWindowReferenceItem*   ritem;
  QSize                                 s2;
  int                                   textY;
  int                                   verseX;
  int                                   x;

  textY = topMargin;
  n = items.size();
  verseX = leftMargin;
  x = verseX;
  //!
  for (i = 0; i < n; i++) {
    ritem = (TextDisplayViewWindowReferenceItem*)items[i];
    ritem->hide();
    i++;
    while (true) {
      item = items[i];

      s2 = item->size();
      itemWidth = s2.width();
      itemHeight = s2.height();


      if ( x + itemWidth + rightMargin > InWidth ) {
        textY += itemHeight + InterLineSkip;
        x = verseX + 20;
      }
      item->move(x, textY);
      x += itemWidth + InterWordSkip;
      itemText = item->text();
      ending = itemText.right(1);
      if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
        k = itemText.length() - 2;
        ending = itemText.sliced(k, 1);
      }
      if ( ending == "." || ending == "?" || ending == "!" ) {
        textY += itemHeight + InterLineSkip;
        x = verseX;
      }
      if ( item->GetLinePosition() == TextDisplayViewWindowItem::LinePositionEOL ) {
        break;
      }
      i++;
    } 
  }
  ComputeSize();
  return tableHeight;
}

/*****************************************************************************!
 * Function : ArrangeElementsReference
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeElementsReference
(int InWidth)
{
  int                                   i;
  TextDisplayViewWindowItem*            item;
  int                                   itemHeight;
  int                                   itemWidth;
  int                                   n;
  int                                   rItemHeight;
  int                                   rItemWidth;
  TextDisplayViewWindowReferenceItem*   ritem;
  QSize                                 s2;
  int                                   textY;
  int                                   verseX;
  int                                   x;

  textY = topMargin;
  n = items.size();
  //!
  for (i = 0; i < n; i++) {
    x = leftMargin;
    ritem = (TextDisplayViewWindowReferenceItem*)items[i];
    ritem->show();
    ritem->move(x, textY);
    s2 = ritem->size();
    rItemWidth = s2.width();
    rItemHeight = s2.height();
    verseX = rItemWidth + InterWordSkip + leftMargin;
    x = verseX;
    i++;
    while (true) {
      item = items[i];
      s2 = item->size();
      itemWidth = s2.width();
      itemHeight = s2.height();
      if ( x + itemWidth + rightMargin > InWidth ) {
        textY += itemHeight + InterLineSkip;
        x = verseX;
      }
      item->move(x, textY);
      x += itemWidth + InterWordSkip;
      if ( item->GetLinePosition() == TextDisplayViewWindowItem::LinePositionEOL ) {
        break;
      }
      i++;
    } 
    textY += rItemHeight + InterLineSkip;
  }
  ComputeSize();
  return tableHeight;
}
  
/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindow::resizeEvent
(QResizeEvent* InEvent)
{
  (void)InEvent;
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  emit SignalShowProgressBar();
  bookInfo = InBookInfo;
  verseCount = GetVerseCount();
  emit SignalSetProgressBar(0, verseCount);
  GetMaxReferenceWidth();
  GetBook();
  ComputeSize();
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : GetMaxReferenceWidth
 *****************************************************************************/
void
TextDisplayViewWindow::GetMaxReferenceWidth
()
{
  QSize                                 s2;
  QString                               reference;
  int                                   verse;
  int                                   chapter;
  int                                   width;
  int                                   retryCount;
  sqlite3_stmt*                         sqlstmt;
  int                                   n;
  QString                               query;
  QFontMetrics                          fm(displayFont);

  referenceWidth = 0;
  
  query = 
     QString("SELECT chapter, verse FROM Verses WHERE book is %1;\n")
    .arg(bookInfo->index);

  n = sqlite3_prepare_v2(MainDatabase,
                         query.toStdString().c_str(),
                         query.length(),
                         &sqlstmt,
                         NULL);
  if ( n != SQLITE_OK ) {
    return;
  }

  retryCount = 0;
  do {
    n = sqlite3_step(sqlstmt);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      chapter = sqlite3_column_int(sqlstmt, 0);
      verse = sqlite3_column_int(sqlstmt, 1);
      reference = QString("%2:%3").arg(chapter).arg(verse);
      s2 = fm.size(0, reference);
      width = s2.width();
      if ( referenceWidth < width ) {
        referenceWidth = width;
      }
    }
  } while (true);
  sqlite3_finalize(sqlstmt);
}
  
/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
void
TextDisplayViewWindow::GetBook
()
{
  QString                               columnName;
  int                                   n;
  QString                               sqlstmt;

  wordCount = 0;
  sqlstmt = QString("SELECT * from Verses where book is %1;\n").arg(bookInfo->index);
  tmpVerseCount = 0;
  n = sqlite3_exec(MainDatabase, sqlstmt.toStdString().c_str(), GetBookCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, sqlstmt.toStdString().c_str(),
            sqlite3_errstr(n));
    return;
  }
  emit SignalWordCountChanged(wordCount);
  emit SignalVerseCountChanged(tmpVerseCount);
  ComputeSize();
}

/*****************************************************************************!
 * Function : GetBookCB
 *****************************************************************************/
int
TextDisplayViewWindow::GetBookCB
(void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   chapter = 0;
  int                                   verse = 0;
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

    if ( columnName == "chapter" ) {
      chapter = columnValue.toInt();
      continue;
    }
    if ( columnName == "verse" ) {
      verse = columnValue.toInt();
      continue;
    }
    if ( columnName == "text" ) {
      verseText = columnValue;
      continue;
    }
  }

  window->AddLine(chapter, verse, verseText);
  return 0;
}

/*****************************************************************************!
 * Function : AddLine
 *****************************************************************************/
void
TextDisplayViewWindow::AddLine
(int InChapter, int InVerse, QString InVerseText)
{
  QFontMetrics                          fm(font());
  int                                   i;
  TextDisplayViewWindowItem*            item;
  int                                   n;
  QString                               reference;
  TextDisplayViewWindowReferenceItem*   ritem;
  QSize                                 s2;
  QSize                                 s3;
  int                                   verseX;
  int                                   width;
  QString                               word;
  QStringList                           words;
  int                                   x = leftMargin;
  
  s3 = size();
  width = s3.width();

  reference = QString("%2:%3").
    arg(InChapter).
    arg(InVerse);
  
  s2 = fm.size(0, reference);

  s3 = QSize(referenceWidth, s2.height());
  ritem = new TextDisplayViewWindowReferenceItem(reference, x, textY, s3);
  ritem->setParent(this);
  x += referenceWidth + InterWordSkip;
  ritem->show();
  verseX = x;
  words = InVerseText.split(" ");
  n = words.size();
  ritem->SetWordCount(n);
  items.push_back(ritem);
  wordCount += n;
  for (i = 0; i < n; i++) {
    word = words[i];
    s2 = fm.size(0, word);
    if ( x + s2.width() + rightMargin > width ) {
      textY += s2.height() + InterLineSkip;
      lineCount++;
      x = verseX;
    }
    item = new TextDisplayViewWindowItem(word, x, textY, s2);
    item->setParent(this);
    x += s2.width() + InterWordSkip;
    item->show();
    if ( i + 1 == n ) {
      item->SetLinePosition(TextDisplayViewWindowItem::LinePositionEOL);
    }
    items.push_back(item);
  }
  textY += s2.height() + InterLineSkip;
  lineCount++;
  tmpVerseCount++;
  emit SignalUpdateProgressBar(tmpVerseCount);
  QCoreApplication::processEvents();
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
  items.clear();
  textY = topMargin;
}

/*****************************************************************************!
 * Function : ComputeSize
 *****************************************************************************/
void
TextDisplayViewWindow::ComputeSize
()
{
  int                                   width;
  int                                   height;
  int                                   h1;
  QPoint                                p;
  QSize                                 s;

  height = 0;
  for ( auto item : items ) {
    s = item->size();
    p = item->pos();

    h1 = s.height() + p.y();
    if ( height < h1 ) {
      height = h1;
    }
  }
  width = size().width();
  resize(width, height);
  tableHeight = height + topMargin  + bottomMargin;
}

/*****************************************************************************!
 * Function : GetTableHeight
 *****************************************************************************/
int
TextDisplayViewWindow::GetTableHeight
()
{
  return tableHeight;
}

/*****************************************************************************!
 * Function : GetVerseCount
 *****************************************************************************/
int
TextDisplayViewWindow::GetVerseCount
()
{
  int                                   verseCount;
  sqlite3_stmt*                         sqlstmt;
  int                                   n;
  int                                   len;
  QString                               query;
  int                                   retryCount = 0;
  
  query = QString("SELECT COUNT(*) FROM Verses WHERE book is %1;\n").arg(bookInfo->index);
  len = query.length();
  
  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(), len, &sqlstmt, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s sqlite3_prepare_v2()\n%s\n%s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return 0;
  }
  retryCount = 0;
  verseCount = 0;
  do {
    n = sqlite3_step(sqlstmt);
    if ( SQLITE_BUSY == n ) {
      QThread::msleep(30);
      retryCount++;
      if ( retryCount > 10 ) {
        break;
      }
      continue;
    }
    if ( SQLITE_DONE == n ) {
      break;
    }

    if ( SQLITE_ROW == n ) {
      verseCount = sqlite3_column_int(sqlstmt, 0);
    }
  } while (true);

  sqlite3_finalize(sqlstmt);
  return verseCount;
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetSentenceMode(void)
{
  mode = SentenceMode;  
  ArrangeElements(size().width());
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetBlockMode(void)
{
  mode = BlockMode;
  ArrangeElements(size().width());
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetReferenceMode(void)
{
  mode = ReferenceMode;
  ArrangeElements(size().width());
}
