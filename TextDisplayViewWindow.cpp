/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindow.cpp
 * DATE         : September 12 2023
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
#include <QThread>
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewWindow.h"
#include "Common.h"
#include "TextDisplayViewWindowItem.h"
#include "TextDisplayViewWindowReferenceItem.h"
#include "TextDisplayReferenceItem.h"
#include "TextDisplayWordFormattingItem.h"
#include "TextDisplayWordItem.h"
#include "SQLStatement.h"
#include "InterlinearChapter.h"
#include "InterlinearDisplayElementSelectDialog.h"
#include "StrongsReferenceDisplayDialog.h"

/*****************************************************************************!
 * Local Type : ThisChapter
 *****************************************************************************/
struct _ThisChapter {
  TextDisplayViewWindow*                thisPointer;
  InterlinearChapter*                   chapter;
};
typedef struct _ThisChapter ThisChapter;

/*****************************************************************************!
 * Function : TextDisplayViewWindow
 *****************************************************************************/
TextDisplayViewWindow::TextDisplayViewWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  bookInfo = NULL;
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
  setFont(displayFont);
  setMouseTracking(true);
  lastSelectedItem = NULL;
  currentSelectedInterlinearWord = NULL;
  FormattingType = TextDisplayFormattingItem::FormatTypeWordBreak;
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
  currentSelectedChapter        = 1;
  EditViewReferenceIndent       = 40;
  InterLineSkip                 = 6;
  SentenceInterLineSkip         = 3;
  InterlinearWord::SetLineskip(1);
  InterParagraphSkip            = 20;
  InterWordSkip                 = 8;
  BlockInterlineSkip            = 2;
  InterInterlinearWordSkip      = 12;
  bottomMargin                  = 10;
  leftMargin                    = 10;
  rightMargin                   = 30;
  sentenceIndent                = 30;
  tableSize                     = QSize();
  topMargin                     = 10;
  DotsPerInchX                  = (int)screen()->logicalDotsPerInch();
  BlockLeftMargin               = 100;
  BlockRightMargin              = 100;
  EndOfSentencePadding          = 3;
  EndOfPhrasePadding            = 2;
  BlockLinesAreJustified        = false;
  WordBreakIndent               = 50;
  FormattingType                = TextDisplayFormattingItem::FormatTypeWordBreak;
  interlinearVerse              = NULL;
  
  if ( DotsPerInchX ) {
    BlockLeftMargin             = DotsPerInchX;
    BlockRightMargin            = DotsPerInchX;
  }
  
  mode                          = ReferenceMode;
  displayFont                   = MainSystemConfig->GetWordItemFont();
  currentInterlinearChapter     = NULL;
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
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QSize                                 s;

  TRACE_FUNCTION_START();
  emit SignalShowProgressBar();
  bookInfo = InBookInfo;
  verseCount = GetVerseCount();
  maxChapters = bookInfo->chapters;
  if ( mode == ReferenceMode ) {
    emit SignalVerseCountChanged(verseCount);
  }
  emit SignalSetProgressBar(0, verseCount);
  GetMaxReferenceWidth();
  SetBook();
  ItemsArranged = false;

  ArrangeItems();
  ComputeSize();
  ItemsArranged = true;
  resize(tableSize);
  ItemsArranged = false;
  repaint();
  s = size();
  emit SignalHideProgressBar();
  TRACE_FUNCTION_END();
}

/*****************************************************************************!
 * Function : ArrangeItems
 *****************************************************************************/
void
TextDisplayViewWindow::ArrangeItems
()
{
  int                                   height;
  int                                   x;
  int                                   y;
  int                                   windowWidth;

  y             = topMargin;
  x             = leftMargin;  
  height        = 0;
  windowWidth   = tableWidth - (leftMargin + rightMargin);

  if ( bookInfo == NULL ) {
    return;
  }
  switch (mode) {
    case NoneMode : {
      break;
    }
    case ReferenceMode : {
      height = ArrangeItemsReference(x, y, windowWidth);
      emit SignalVerseCountChanged(GetVerseCount());
      break;
    }
    case InterlinearMode : {
      height = ArrangeItemsInterlinear(y, windowWidth);
      emit SignalVerseCountChanged(GetVerseCount());
      break;
    }
    case BlockMode : {
      windowWidth = tableWidth - (BlockLeftMargin + BlockRightMargin);
      height = ArrangeItemsBlock(BlockLeftMargin, y, windowWidth);
      break;
    }
    case EditMode : {
      height = ArrangeItemsEdit(x, y, windowWidth);
      break;
    }
    case SentenceMode : {
#if 0
      height = ArrangeItemsSentence(x, y, windowWidth);
      emit SignalSentenceCountChanged(tmpSentenceCount);
#endif      
      break;
    }
  }
  windowSize = QSize(tableWidth, height);
  resize(windowSize);
}

/*****************************************************************************!
 * Function : ArrangeItemsSentence
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsSentence
(int InX, int InY, int InWindowWidth)
{  
  QString                               ending;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   k;
  QSize                                 s;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  int                                   i;
  int                                   n;
  TextDisplayItem*                      item;

  x             = InX ;
  y             = InY + 30;
  windowHeight  = 0;

  n = textItems.size();
  for ( i = 0 ; i < n ; i++ ) {
    item = textItems[i];
    if ( item->GetChapter() != currentSelectedChapter ) {
      continue;
    }
    s = item->GetSize();
    itemWidth = s.width();
    itemHeight = s.height();
    itemText = item->GetText();
    ending = itemText.right(1);

    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }

    if ( itemWidth + x >= InWindowWidth ) {
      x = InX + sentenceIndent;
      y += itemHeight;
      windowHeight = y + itemHeight;
    }
    item->SetLocation(QPoint(x, y));
    x += s.width() + InterWordSkip;
    if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
      k = itemText.length() - 2;
      ending = itemText.sliced(k, 1);
    }
    if ( ending == "." || ending == "?" || ending == "!" ) {
      tmpSentenceCount ++;
      y += itemHeight + SentenceInterLineSkip;
      x = InX;
      windowHeight = y + itemHeight;
    }
  }
  windowHeight += bottomMargin;
  return windowHeight;
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
 * Function : SetBook
 *****************************************************************************/
void
TextDisplayViewWindow::SetBook
()
{
  QString                               columnName;
  int                                   n;
  QString                               query;
  
  tmpVerseCount = 0;
  wordCount = 0;
  ClearText();
  query = QString("SELECT * from Verses where book is %1;\n").arg(bookInfo->index);
  tmpVerseCount = 0;
  tmpSentenceCount = 0;
  n = sqlite3_exec(MainDatabase, query.toStdString().c_str(), SetBookCB, this, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
    return;
  }

  if ( currentInterlinearChapter ) {
    delete currentInterlinearChapter;
  }
  currentInterlinearChapter = AddInterlinearChapter(bookInfo->index, 1);
  emit SignalWordCountChanged(wordCount);
}

/*****************************************************************************!
 * Function : SetBookCB
 *****************************************************************************/
int
TextDisplayViewWindow::SetBookCB
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

  window->AddLineText(chapter, verse, verseText);
  return 0;
}

/*****************************************************************************!
 * Function : AddLineText
 *****************************************************************************/
void
TextDisplayViewWindow::AddLineText
(int InChapter, int InVerse, QString InVerseText)
{
  int                                   formatting;
  int                                   i;
  int                                   n;
  QStringList                           words;
  TextDisplayItem*                      item;
  TextDisplayReferenceItem*             refItem;
  TextDisplayFormattingItem*            formattingItem;
  QString                               referenceText;

  refItem = new TextDisplayReferenceItem(bookInfo->index,
                                         bookInfo->GetCapitalizedBookName(),
                                         InChapter, InVerse);

  formatting = GetFormattingByReference(bookInfo->index, InChapter, InVerse);
  if ( formatting ) {
    formattingItem = new TextDisplayFormattingItem(bookInfo->index,
                                                   bookInfo->GetCapitalizedBookName(),
                                                   InChapter,
                                                   InVerse,
                                                   (TextDisplayFormattingItem::FormatType)formatting);
    formattingItems.push_back(formattingItem);
  }
  refItem->SetFont(displayFont);
  refItem->SetSize(QSize(referenceWidth, refItem->GetSize().height()));
  textItems.push_back(refItem);
  words = InVerseText.split(" ");
  n = words.size();

  for ( i = 0; i < n; i++ ) {
    TextDisplayWordFormattingItem*              formattingItem;
    int                                         word;
    word = i + 1;
    item = new TextDisplayWordItem(bookInfo->index, InChapter, InVerse, words[i], word);
    item->SetFont(displayFont);
    textItems.push_back(item);
    formatting = GetWordFormattingByReference(bookInfo->index, InChapter, InVerse, word);
    if ( formatting ) {
      formattingItem = new TextDisplayWordFormattingItem(bookInfo->index,
                                                         bookInfo->GetCapitalizedBookName(),
                                                         InChapter,
                                                         InVerse,
                                                         word,
                                                         (TextDisplayFormattingItem::FormatType)formatting);
      formattingItems.push_back(formattingItem);
    }
    
    tmpVerseCount++;
    wordCount++;
    emit SignalUpdateProgressBar(tmpVerseCount);
    QCoreApplication::processEvents();
  }    
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
  formattingItems.clear();
  textItems.clear();
  textY = topMargin;
}

/*****************************************************************************!
 * Function : ComputeSize
 *****************************************************************************/
QSize
TextDisplayViewWindow::ComputeSize
()
{
  int                                   height;
  int                                   h1;
  QPoint                                p;
  QSize                                 s;

  height = 0;
  for ( auto item : textItems ) {
    s = item->GetSize();
    p = item->GetLocation();

    h1 = s.height() + p.y();
    if ( height < h1 ) {
      height = h1;
    }
  }
  height += (topMargin  + bottomMargin);
  return QSize(size().width(), height);
}

/*****************************************************************************!
 * Function : GetTableHeight
 *****************************************************************************/
int
TextDisplayViewWindow::GetTableHeight
()
{
  return windowSize.height();
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
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetBlockMode(void)
{
  mode = BlockMode;
  setFocus();
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetReferenceMode(void)
{
  mode = ReferenceMode;
  setFocus();
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetEditMode(void)
{
  mode = EditMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : GetFormattingByReference
 *****************************************************************************/
TextDisplayFormattingItem::FormatType
TextDisplayViewWindow::GetFormattingByReference
(int InBook, int InChapter, int InVerse)
{
  int                                   type;
  int                                   n;
  int                                   retryCount;
  sqlite3_stmt*                         statement;
  QString                               query;
  
  query = QString("SELECT type FROM Formatting WHERE book is %1 and chapter is %2 and verse is %3 and word is 0;\n").
    arg(InBook).arg(InChapter).arg(InVerse);

  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(),
                         query.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "sqlite3_prepare_v2() %s failed\n  %s\n  %s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return TextDisplayFormattingItem::FormatTypeNone;
  }
  type = 0;
  retryCount = 0;
  do {
    n = sqlite3_step(statement);
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
      type = sqlite3_column_int(statement, 0);
      break;
    }
  } while (true);
  sqlite3_finalize(statement);
  return (TextDisplayFormattingItem::FormatType)type;
}

/*****************************************************************************!
 * Function : GetWordFormattingByReference
 *****************************************************************************/
TextDisplayFormattingItem::FormatType
TextDisplayViewWindow::GetWordFormattingByReference
(TextDisplayWordItem* InItem)
{
  int                                   verse;
  int                                   chapter;
  int                                   book;
  int                                   word;

  word          = InItem->GetWordIndex();
  book          = InItem->GetBook();
  chapter       = InItem->GetChapter();
  verse         = InItem->GetVerse();

  return GetWordFormattingByReference(book, chapter, verse, word);
}

/*****************************************************************************!
 * Function : GetWordFormattingByReference
 *****************************************************************************/
TextDisplayFormattingItem::FormatType
TextDisplayViewWindow::GetWordFormattingByReference
(int InBook, int InChapter, int InVerse, int InWord)
{
  int                                   type;
  int                                   n;
  int                                   retryCount;
  sqlite3_stmt*                         statement;
  QString                               query;
  
  query = QString("SELECT type FROM Formatting WHERE book is %1 and chapter is %2 and verse is %3 and word is %4;\n").
    arg(InBook).arg(InChapter).arg(InVerse).arg(InWord);

  n = sqlite3_prepare_v2(MainDatabase, query.toStdString().c_str(),
                         query.length(), &statement, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "sqlite3_prepare_v2() %s failed\n  %s\n  %s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return TextDisplayFormattingItem::FormatTypeNone;
  }
  type = 0;
  retryCount = 0;
  do {
    n = sqlite3_step(statement);
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
      type = sqlite3_column_int(statement, 0);
      break;
    }
  } while (true);
  sqlite3_finalize(statement);
  return (TextDisplayFormattingItem::FormatType)type;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewWindow::resizeEvent
(QResizeEvent* InEvent)
{
  QSize                                 s;
  s = InEvent->size();
  tableWidth = s.width();
  if ( ! ItemsArranged ) {
    ArrangeItems();
  }
  repaint();
}

/*****************************************************************************!
 * Function : paintEvent
 *****************************************************************************/
void
TextDisplayViewWindow::paintEvent
(QPaintEvent* InEvent)
{
  QPainter                              painter(this);
  QRect                                 rect = InEvent->rect();

  painter.setRenderHints(QPainter::Antialiasing);
  switch (mode) {
    case ReferenceMode : {
      PaintReferenceMode(&painter, rect);
      break;
    }
    case SentenceMode : {
      PaintSentenceMode(&painter, rect);
      break;
    }
    case BlockMode : {
      PaintBlockMode(&painter, rect);
      break;
    }
    case InterlinearMode : {
      PaintInterlinearMode(&painter);
      break;
    }
    case EditMode : {
      PaintEditMode(&painter, rect);
      break;
    }
    case NoneMode : {
      break;
    }
  }
  painter.end();
}

/*****************************************************************************!
 * Function : ArrangeItemsReference
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsReference
(int InX, int InY, int InWindowWidth)
{
  QSize                                 s;
  int                                   itemWidth;
  int                                   itemHeight;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  bool                                  isFirst;

  x             = InX;
  y             = InY;
  windowHeight  = 0;
  
  do {
    isFirst = true;
    for ( auto item : textItems ) {
      if ( item->GetChapter() != currentSelectedChapter ) {
        continue;
      }
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      
      if ( !isFirst && item->GetType() == TextDisplayItem::ReferenceType ) {
        x = leftMargin;
        y += InterLineSkip + itemHeight;
        windowHeight = y + itemHeight;
      }
      if ( itemWidth + x >= InWindowWidth ) {
        x = leftMargin + referenceWidth + InterWordSkip;
        y += InterLineSkip + itemHeight;
        windowHeight = y + itemHeight;
      }
      isFirst = false;
      item->SetLocation(QPoint(x, y));
      x += s.width() + InterWordSkip;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : PaintReferenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintReferenceMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;

  for ( auto item : textItems ) {
    if ( item->GetChapter() != currentSelectedChapter ) {
      item->SetIsVisible(false);
      continue;
    }
    itemR = QRect(item->GetBoundingRect());

    if ( InRect.contains(itemR) ) {
      item->SetIsVisible(true);
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        item->Draw(InPainter);
      }
    }
  } while (false);
}

/*****************************************************************************!
 * Function : ArrangeItemsEdit
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsEdit
(int InX, int InY, int InWindowWidth)
{
  int                                   formattingWidth;
  TextDisplayFormattingItem*            formattingItem;
  bool                                  isFirst;
  int                                   itemHeight;
  int                                   itemWidth;
  QSize                                 s;
  int                                   windowHeight;
  int                                   wordSkip;
  int                                   x;
  int                                   y;
  int                                   i;
  int                                   n;
  TextDisplayItem*                      item;
  
  x             = InX;
  y             = InY;
  windowHeight  = 0;

  n = textItems.size();
  isFirst = false;
  do {
    for ( i = 0 ; i < n; i++ ) {
      item = textItems[i];
      wordSkip = InterWordSkip;
      
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();

      //!
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        x = leftMargin + EditViewReferenceIndent;
        if ( isFirst ) {
          y += InterLineSkip + itemHeight;
        }
        formattingItem = FindReferenceFormattingItem(item->GetBook(), item->GetChapter(), item->GetVerse());
        if ( formattingItem ) {
          formattingItem->SetLocation(QPoint(leftMargin, y + InterLineSkip));
          formattingItem->SetSize(QSize(EditViewReferenceIndent - leftMargin, itemHeight));
        }
        isFirst = true;
        windowHeight = y + itemHeight;
        item->SetLocation(QPoint(x, y));
        x += s.width() + wordSkip;
        continue;
      }

      //!
      if ( item->GetType() == TextDisplayItem::WordType ) {
        TextDisplayWordItem*                    wordItem = (TextDisplayWordItem*)item;
        formattingItem = FindWordFormattingItem(wordItem->GetBook(), wordItem->GetChapter(), wordItem->GetVerse(),
                                                wordItem->GetWordIndex());
        formattingWidth = 0;
        if ( formattingItem ) {
          formattingWidth = 4;
        }
        if ( itemWidth + x + formattingWidth >= InWindowWidth ) {
          x = leftMargin + referenceWidth + InterWordSkip + EditViewReferenceIndent;
          y += InterLineSkip + itemHeight;
          windowHeight = y + itemHeight;
        }
        if ( formattingItem ) {
          formattingItem->SetLocation(QPoint(x, y + InterLineSkip));
          formattingItem->SetHeight(itemHeight);
          x += formattingItem->GetWidth();
        }
        
        item->SetLocation(QPoint(x, y));
        x += s.width() + formattingWidth + wordSkip;
        continue;
      }
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : PaintEditMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintEditMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;

  QPoint                                TL;
  QPoint                                BR;
  TextDisplayFormattingItem*            formattingItem;

  TL = InRect.topLeft();
  BR = InRect.bottomRight();

  for ( auto item : textItems ) {
    itemR = QRect(item->GetBoundingRect());
    if ( ! InRect.contains(itemR) ) {
      continue;
    }
    if ( lastSelectedItem == item ) {
      item->DrawSelected(InPainter);
    } else {
      TextDisplayWordItem*                      wordItem = (TextDisplayWordItem*)item;
      TextDisplayFormattingItem*                wordItemFormatting;
      
      wordItemFormatting = FindWordFormattingItem(wordItem);
      if ( wordItemFormatting ) {
        wordItem->DrawFormatted(InPainter, (TextDisplayWordFormattingItem*)wordItemFormatting);
      } else {
        item->Draw(InPainter);
      }
    }
  }
  for ( auto item : formattingItems ) {
    TextDisplayWordFormattingItem*      wordFormattingItem;
    
    formattingItem = (TextDisplayFormattingItem*)item;
    auto formatting = formattingItem->GetFormattingType();
    itemR = QRect(item->GetBoundingRect());

    if ( InRect.contains(itemR) ) {
      if ( formatting == TextDisplayFormattingItem::FormatTypeWordBreak ||
           formatting == TextDisplayFormattingItem::FormatTypeWordBreakIndent ) {
        wordFormattingItem = (TextDisplayWordFormattingItem*)item;
        wordFormattingItem->Draw(InPainter);
      } else {
        item->Draw(InPainter);
      } 
    }
  }
}

/*****************************************************************************!
 * Function : PaintSentenceMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintSentenceMode
(QPainter* InPainter, QRect InRect)
{
  QRect                                 itemR;
  
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }
    if ( item->GetChapter() != currentSelectedChapter ) {
      continue;
    }
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        item->Draw(InPainter);
      }
    }
  } while (false);
}

/*****************************************************************************!
 * Function : ArrangeItemsBlock
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsBlock
(int InX, int InY, int InWindowWidth)
{
  int                                   k;
  TextDisplayItem*                      item2;
  int                                   book;
  bool                                  breakAfter;
  int                                   chapter;
  QString                               ending;
  TextDisplayFormattingItem::FormatType formatting;
  int                                   i;
  TextDisplayItem*                      item;
  int                                   itemHeight;
  QString                               itemText;
  int                                   itemWidth;
  int                                   n;
  TextDisplayReferenceItem*             referenceItem;
  QSize                                 s;
  int                                   verse;
  int                                   windowHeight;
  int                                   x;
  int                                   y;
  int                                   lineEnd;
  int                                   lineStartIndex;
  int                                   lineEndIndex;
  QPoint                                location;
  TextDisplayItem::ParagraphPosition    paragraphPosition;

  //!
  lineEnd       = InX;
  x             = InX;
  y             = InY;
  windowHeight  = 0;
  breakAfter = false;
  lineStartIndex = 1;
  lineEndIndex = 0;
  n = textItems.size();
  paragraphPosition = TextDisplayItem::MidParagraph;

  //!
  do {
    for (i = 0; i < n; i++) {
      item = textItems[i];
      s = item->GetSize();
      itemWidth = s.width();
      itemHeight = s.height();
      itemText = item->GetText();
      ending = itemText.right(1);
      
      //!
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        if ( breakAfter ) {
          x = InX;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          breakAfter = false;
          paragraphPosition = TextDisplayItem::StartOfParagraph;
          k = i - 1;
          while ( k > 1 ) {
            item2 = textItems[k];
            if ( item2->GetType() == TextDisplayItem::TextType ) {
              item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
              break;
            }
            k--;
          }
        }
        referenceItem = (TextDisplayReferenceItem*)item;
        verse = referenceItem->GetVerse();
        chapter = referenceItem->GetChapter();
        book = bookInfo->index;
        formatting = GetFormattingByReference(book, chapter, verse);
        if ( formatting == TextDisplayFormattingItem::FormatTypePostVerse ) {
          breakAfter = true;
          continue;
        }

        //!
        if ( formatting == TextDisplayFormattingItem::FormatTypePreVerse ) {
          k = i - 1;
          while ( k > 1 ) {
            item2 = textItems[k];
            if ( item2->GetType() == TextDisplayItem::TextType ) {
              item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
              break;
            }
            k--;
          }
          x = InX;
          y += itemHeight + InterParagraphSkip;
          windowHeight = y + itemHeight;
          paragraphPosition = TextDisplayItem::StartOfParagraph;
          continue;
        }
        continue;
      }

      //! Word level formatting
      formatting = GetWordFormattingByReference((TextDisplayWordItem*)item);
      if ( formatting == TextDisplayFormattingItem::FormatTypeWordBreak ) {
        k = i - 1;
        while ( k > 1 ) {
          item2 = textItems[k];
          if ( item2->GetType() == TextDisplayItem::TextType ) {
            item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
            break;
          }
          k--;
        }
        x = InX;
        y += itemHeight + InterParagraphSkip/2;
        location = QPoint(x, y);
        item->SetLocation(location);
        item->SetParagraphPosition(paragraphPosition);
        windowHeight = y + itemHeight;
        paragraphPosition = TextDisplayItem::MidParagraph;
        x += itemWidth + InterWordSkip;
        continue;
      }
      
      //!
      if ( formatting == TextDisplayFormattingItem::FormatTypeWordBreakIndent ) {
        k = i - 1;
        while ( k > 1 ) {
          item2 = textItems[k];
          if ( item2->GetType() == TextDisplayItem::TextType ) {
            item2->SetParagraphPosition(TextDisplayItem::EndOfParagraph);
            break;
          }
          k--;
        }
        x = InX + WordBreakIndent;
        y += itemHeight + InterParagraphSkip/2;
        location = QPoint(x, y);
        item->SetLocation(location);
        item->SetParagraphPosition(paragraphPosition);
        windowHeight = y + itemHeight;
        paragraphPosition = TextDisplayItem::MidParagraph;
        x += itemWidth + InterWordSkip;
        continue;
      }
      
      //!
      if ( itemWidth + x >= InWindowWidth ) {
        if ( BlockLinesAreJustified ) {
          LineJustify(InWindowWidth, lineEnd, lineStartIndex, lineEndIndex);
        }
        x = InX;
        lineEnd = x;
        y += itemHeight + BlockInterlineSkip;
        windowHeight = y + itemHeight;
        lineStartIndex = i;
        location = QPoint(x, y);
        item->SetLocation(QPoint(x, y));
        x += itemWidth + InterWordSkip;
        lineEnd = x - InterWordSkip;
        lineEndIndex = i;
        continue;
      }

      //!
      location = QPoint(x, y);
      item->SetLocation(location);
      item->SetParagraphPosition(paragraphPosition);
      x += itemWidth + InterWordSkip;
      lineEnd = x - InterWordSkip;
      lineEndIndex = i;
      paragraphPosition = TextDisplayItem::MidParagraph;
    }
  } while (false);
  windowHeight += bottomMargin;
  return windowHeight;
}

/*****************************************************************************!
 * Function : PaintBlockMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintBlockMode
(QPainter* InPainter, QRect InRect)
{
  TextDisplayFormattingItem*            formatType;
  QRect                                 itemR;

  QBrush                                brush = QBrush(MainSystemConfig->GetBlockWindowBackgroundColor());
  QSize                                 s = size();
  InPainter->setBrush(brush);
  InPainter->drawRect(QRect(QPoint(0, 0), s));
  
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      continue;
    }
    TextDisplayWordItem*                    wordItem = (TextDisplayWordItem*)item;
    formatType = FindWordFormattingItem(wordItem);
    itemR = QRect(item->GetBoundingRect());
    if ( InRect.contains(itemR) ) {
      if ( lastSelectedItem == item ) {
        item->DrawSelected(InPainter);
      } else {
        if ( formatType ) {
          wordItem->DrawFormatted(InPainter, (TextDisplayWordFormattingItem*)formatType);
        } else {
          wordItem->Draw(InPainter);
        }
      }
    }
  } while (false);
}

/*****************************************************************************!
 * Function : mousePressEvent
 *****************************************************************************/
void
TextDisplayViewWindow::mousePressEvent
(QMouseEvent* InEvent)
{
  QPoint                                p = InEvent->position().toPoint();
  if ( mode == EditMode ) {
    EditModeMousePress(p);
    return;
  }
  if ( mode == ReferenceMode ) {
    ReferenceModeMousePress(InEvent);
  }
  if ( mode == InterlinearMode ) {
    InterlinearModeMousePress(InEvent);
    return;
  }
}

/*****************************************************************************!
 * Function : EditModeMousePress
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeMousePress
(QPoint InPoint)
{
  TextDisplayItem*                      item;
  TextDisplayItem::DisplayType          type;

  item = FindSelectedItem(InPoint);
  if ( NULL == item ) {
    return;
  }
  type = item->GetType();

  if ( type == TextDisplayItem::FormattingVerseType ) {
    EditModeReferenceFormattingMouseSelect((TextDisplayFormattingItem*)item);
    return;
  }
  
  if ( type == TextDisplayItem::ReferenceType ) {
    EditModeReferenceMouseSelect((TextDisplayReferenceItem*)item);
    return;
  }
  if ( type == TextDisplayItem::WordType ) {
    EditModeWordMouseSelect((TextDisplayWordItem*)item);
    return;
  }

  if ( type == TextDisplayItem::FormattingWordType ) {
    EditModeFormattingMouseSelect((TextDisplayWordFormattingItem*)item);
    return;
  }
}

/*****************************************************************************!
 * Function : EditModeFormattingMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeFormattingMouseSelect
(TextDisplayWordFormattingItem* InItem)
{
  RemoveWordFormattingItem(InItem);
}

/*****************************************************************************!
 * Function : EditModeReferenceMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeReferenceFormattingMouseSelect
(TextDisplayFormattingItem* InItem)
{
  RemoveVerseFormattingItem(InItem);
}

/*****************************************************************************!
 * Function : RemoveWordFormattingItem
 *****************************************************************************/
void
TextDisplayViewWindow::RemoveWordFormattingItem
(TextDisplayWordFormattingItem* InItem)
{
  int                                   m;
  int                                   book;
  int                                   chapter;
  int                                   verse;
  int                                   word;
  int                                   type;
  char                                  sqlstatement[1024];
  
  book          = InItem->GetBook();
  chapter       = InItem->GetChapter();
  verse         = InItem->GetVerse();
  word          = InItem->GetWordIndex();
  type          = (int)InItem->GetFormattingType();

  sprintf(sqlstatement,
          SQLStatement::GetWordFormattingDelete().toStdString().c_str(),
          book,
          chapter,
          verse,
          word,
          type);
  m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, NULL);
  if ( m != SQLITE_OK ) {
    fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
    return;
  }

  for ( auto i = formattingItems.begin() ; i != formattingItems.end(); i++ ) {
    if (*i == (TextDisplayFormattingItem*)InItem ) {
      formattingItems.erase(i);
      break;
    }
  }
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : RemoveVerseFormattingItem
 *****************************************************************************/
void
TextDisplayViewWindow::RemoveVerseFormattingItem
(TextDisplayFormattingItem* InItem)
{
  int                                   m;
  int                                   book;
  int                                   chapter;
  int                                   verse;
  int                                   type;
  char                                  sqlstatement[1024];
  
  book          = InItem->GetBook();
  chapter       = InItem->GetChapter();
  verse         = InItem->GetVerse();
  type          = (int)InItem->GetFormattingType();

  sprintf(sqlstatement,
          SQLStatement::GetVerseFormattingDelete().toStdString().c_str(),
          book,
          chapter,
          verse,
          type);
  m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, NULL);
  if ( m != SQLITE_OK ) {
    fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
    return;
  }

  for ( auto i = formattingItems.begin() ; i != formattingItems.end(); i++ ) {
    if (*i == (TextDisplayFormattingItem*)InItem ) {
      formattingItems.erase(i);
      break;
    }
  }
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : FindSelectedItem
 *****************************************************************************/
TextDisplayItem*
TextDisplayViewWindow::FindSelectedItem
(QPoint InLocation)
{
  for ( auto item : textItems ) {
    if ( item->Contains(InLocation) ) {
      return item;
    }
  }
  for ( auto item : formattingItems ) {
    if ( item->Contains(InLocation) ) {
      return item;
    }
  }
  return NULL;
}
    
/*****************************************************************************!
 * Function : EditModeReferenceMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeReferenceMouseSelect
(TextDisplayReferenceItem* InItem)
{
  int                                   verse;
  int                                   chapter;
  int                                   book;
  QString                               itemText;

  itemText = InItem->GetText();
  book = InItem->GetBook();
  chapter = InItem->GetChapter();
  verse = InItem->GetVerse();

  AddFormatting(book, chapter, verse, 0, TextDisplayFormattingItem::FormatTypePreVerse);
}

/*****************************************************************************!
 * Function : AddFormatting
 *****************************************************************************/
void
TextDisplayViewWindow::AddFormatting
(int InBook, int InChapter, int InVerse, int InWord, int InFormatting)
{
  int                                   m;
  char                                  sqlstatement[1024];
  QString                               insertStatment;
  
  insertStatment = SQLStatement::GetFormattingInsert();
  sprintf(sqlstatement,
          insertStatment.toStdString().c_str(),
          InBook,
          InChapter,
          InVerse,
          InWord,
          QString(),
          InFormatting);
  m  = sqlite3_exec(MainDatabase, sqlstatement, NULL, NULL, NULL);
  if ( m != SQLITE_OK ) {
    fprintf(stderr, "sqlite_exec() failed\n %s\n %d : %s\n", sqlstatement, m, sqlite3_errstr(m));
    return;
  }
  bookInfo = FindBookInfoByIndex(InBook);
  if ( bookInfo == NULL ) {
    return;
  }

  if ( InWord == 0 ) {
    TextDisplayFormattingItem*          formattingItem;
    formattingItem = new TextDisplayFormattingItem(InBook, bookInfo->name, InChapter, InVerse,
                                                   (TextDisplayFormattingItem::FormatType)InFormatting);
    formattingItems.push_back(formattingItem);
  } else {
    TextDisplayWordFormattingItem*      formattingItem;
    formattingItem = new TextDisplayWordFormattingItem(InBook, bookInfo->name, InChapter, InVerse, InWord,
                                                       (TextDisplayFormattingItem::FormatType)InFormatting);
    formattingItems.push_back(formattingItem);
  }
  ArrangeItems();
  repaint();
  return;
}

/*****************************************************************************!
 * Function : EditModeWordMouseSelect
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeWordMouseSelect
(TextDisplayWordItem* InItem)
{
  QString                               st;
  QString                               word;
  int                                   wordIndex;

  AddFormatting(InItem->GetBook(), InItem->GetChapter(), InItem->GetVerse(), InItem->GetWordIndex(),
                FormattingType);
  word = InItem->GetWord();
  wordIndex = InItem->GetWordIndex();
  st = QString("%1:%2").arg(word).arg(wordIndex);
  ArrangeItems();
  repaint();
  emit SignalSetMessage(st);
}
  
/*****************************************************************************!
 * Function : mouseMoveEvent
 *****************************************************************************/
void
TextDisplayViewWindow::mouseMoveEvent
(QMouseEvent* InEvent)
{
  QString                               itemText;
  QPoint                                location;
  QString                               text;
  QPoint                                p = InEvent->position().toPoint();

  setFocus();
  if ( mode == InterlinearMode ) {
    InterlinearModeMouseMove(p);
    return;
  }

  if ( mode == EditMode ) {
    EditModeMouseMove(p);
    return;
  }
  if ( lastSelectedItem && lastSelectedItem->Contains(p) ) {
    return;
  }

  lastSelectedItem = NULL;
  for ( auto item : textItems ) {
    if ( item->Contains(p) ) {
      if ( item->GetType() == TextDisplayItem::ReferenceType ) {
        continue;
      }
      location = item->GetLocation();
      itemText = item->GetText();
      text = item->GetText();
      if ( item != lastSelectedItem ) {
        lastSelectedItem = item;
        break;
      }
    }
  }
  repaint();
}

/*****************************************************************************!
 * Function : EditModeMouseMove
 *****************************************************************************/
void
TextDisplayViewWindow::EditModeMouseMove
(QPoint InLocation)
{
  QPoint                                location;

  if ( lastSelectedItem && lastSelectedItem->Contains(InLocation) ) {
    return;
  }

  lastSelectedItem = NULL;
  for ( auto item : textItems ) {
    if ( item->Contains(InLocation) ) {
      location = item->GetLocation();
      if ( item != lastSelectedItem ) {
        lastSelectedItem = item;
        break;
      }
    }
  }
  repaint();
}

/*****************************************************************************!
 * Function : SlotVerticalScrolled
 *****************************************************************************/
void
TextDisplayViewWindow::SlotVerticalScrolled(void)
{
  lastSelectedItem = NULL;
  repaint();
}

/*****************************************************************************!
 * Function : FindWordFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem*
TextDisplayViewWindow::FindWordFormattingItem
(TextDisplayWordItem* InItem)
{
  return FindWordFormattingItem(InItem->GetBook(),
                                InItem->GetChapter(),
                                InItem->GetVerse(),
                                InItem->GetWordIndex());
}

/*****************************************************************************!
 * Function : FindWordFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem*
TextDisplayViewWindow::FindWordFormattingItem
(int InBook, int InChapter, int InVerse, int InWord)
{
  TextDisplayFormattingItem::FormatType         formattingType;
  TextDisplayWordFormattingItem*                f;

  for ( auto item : formattingItems ) {
    f = (TextDisplayWordFormattingItem*)item;
    if ( f->IsReferenceWord(InBook, InChapter, InVerse, InWord) ) {
      formattingType = f->GetFormattingType();
      if ( formattingType == TextDisplayFormattingItem::FormatTypeWordBreak ||
           formattingType == TextDisplayFormattingItem::FormatTypeWordBreakIndent ||
           formattingType == TextDisplayFormattingItem::FormatTypeWordHighlight ) {
        return f;
      }
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : FindReferenceFormattingItem
 *****************************************************************************/
TextDisplayFormattingItem*
TextDisplayViewWindow::FindReferenceFormattingItem
(int InBook, int InChapter, int InVerse)
{
  TextDisplayFormattingItem::FormatType         formattingType;
  
  for ( auto item : formattingItems ) {
    if ( item->IsReference(InBook, InChapter, InVerse, 0) ) {
      formattingType = item->GetFormattingType();
      if ( formattingType == TextDisplayFormattingItem::FormatTypePostVerse ||
           formattingType == TextDisplayFormattingItem::FormatTypePreVerse ) {
        return item;
      }
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : LineJustify
 *****************************************************************************/
void
TextDisplayViewWindow::LineJustify
(int InWindowWidth, int InLineEnd, int InLineStartIndex, int InLineEndIndex)
{
  int                                   lineRemaining;

  lineRemaining = InWindowWidth - InLineEnd;
  lineRemaining = LineJustifyPunctuation(lineRemaining, InLineStartIndex, InLineEndIndex);
  LineJustifyWords(lineRemaining, InLineStartIndex, InLineEndIndex);
}

/*****************************************************************************!
 * Function : LineJustifyPunctuation
 *****************************************************************************/
int
TextDisplayViewWindow::LineJustifyPunctuation
(int InLineRemaining, int InLineStartIndex, int InLineEndIndex)
{
  QPoint                                Location;
  QString                               ending;
  TextDisplayItem*                      item;
  QString                               itemText;
  int                                   k;
  int                                   lineRemaining;

  //!
  lineRemaining = InLineRemaining;
  for ( int i = InLineStartIndex ; lineRemaining > 0 && i < InLineEndIndex ; i++ ) {
    item = textItems[i];
    itemText = item->GetText();
    if ( item->GetParagraphPosition() == TextDisplayItem::EndOfParagraph ) {
      continue;
    }
    ending = itemText.right(1);
    Location = item->GetLocation();
    if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ) {
      k = itemText.length() - 2;
      ending = itemText.sliced(k, 1);

      //!
      if ( ending == "." || ending == "?" || ending == "!" ) {
        for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
          TextDisplayItem*              item1 = textItems[j];
          if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
            continue;
          }
          Location = item1->GetLocation();
          Location += QPoint(EndOfSentencePadding, 0);
          item1->SetLocation(Location);
        }
        lineRemaining -= EndOfSentencePadding;
        continue;
      }

      //!
      if ( ending == ":" || ending == ";" || ending == "," ) {
        for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
          TextDisplayItem*              item1 = textItems[j];
          if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
            continue;
          }
          Location = item1->GetLocation();
          Location += QPoint(EndOfPhrasePadding, 0);
          item1->SetLocation(Location);
        }
        lineRemaining -= EndOfPhrasePadding;
        continue;
      }
    }

    //!
    if ( ending == "." || ending == "?" || ending == "!" ) {
      for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location = item1->GetLocation();
        Location += QPoint(EndOfSentencePadding, 0);
        item1->SetLocation(Location);
      }
      lineRemaining -= EndOfSentencePadding;
      continue;
    }

    //!
    if ( ending == ":" || ending == ";" || ending == "," ) {
      for ( int j = i + 1 ; j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        Location = item1->GetLocation();
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location += QPoint(EndOfPhrasePadding, 0);
        item1->SetLocation(Location);
      }
      lineRemaining -= EndOfPhrasePadding;
      continue;
    }
  }
  return lineRemaining;
}

/*****************************************************************************!
 * Function : LineJustifyWords
 *****************************************************************************/
void
TextDisplayViewWindow::LineJustifyWords
(int InLineRemaining, int InLineStartIndex, int InLineEndIndex)
{
  QSize                                 Size;
  QPoint                                Location;
  QString                               itemText;
  int                                   lineRemaining;
  TextDisplayItem*                      item;
  QString                               ending;

  lineRemaining = InLineRemaining;
  wordCount = InLineEndIndex - InLineStartIndex;
  while ( lineRemaining > 0 ) {
    for ( int i = InLineStartIndex ;  lineRemaining > 0 && i < InLineEndIndex ; i++ ) {
      item = textItems[i];
      itemText = item->GetText();
      ending = itemText.right(1);
      
      if ( WordEndsInPunctuation(itemText) ) {
        continue;
      }
      for ( int j = i + 1 ; lineRemaining > 0 && j <= InLineEndIndex ; j++ ) {
        TextDisplayItem*              item1 = textItems[j];
        if ( item1->GetParagraphPosition() == TextDisplayItem::StartOfParagraph ) {
          continue;
        }
        Location = item1->GetLocation();
        itemText = item1->GetText();
        Location += QPoint(1, 0);
        Size = item1->GetSize();
        item1->SetLocation(Location);
      }
      lineRemaining--;
    }
  }
}

/*****************************************************************************!
 * Function : WordEndsInPunctuation
 *****************************************************************************/
bool
TextDisplayViewWindow::WordEndsInPunctuation
(QString InWord)
{
  QString ending =                      InWord.right(1);

  if ( ending == "'" || ending == "`" || ending == "]" || ending == ")" ||
       ending == ":" || ending == ";" || ending == "," ||
       ending == "." || ending == "?" || ending == "!" ) {
    return true;
  }
  return false;
}

/*****************************************************************************!
 * Function : FindBookInfoByIndex
 *****************************************************************************/
BookInfo*
TextDisplayViewWindow::FindBookInfoByIndex
(int InBookIndex)
{
  return MainBookInfo->GetByIndex(InBookIndex);
}

/*****************************************************************************!
 * Function : SlotSelectChapter
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSelectChapter
(int InChapter)
{
  QPoint                                loc;
  TextDisplayReferenceItem*             item;

  item = FindDisplayReferenceByChapterVerse(InChapter, 1);
  if ( NULL == item ) {
    return;
  }

  loc = item->GetLocation();
  emit SignalLocationSelected(loc);
}

/*****************************************************************************!
 * Function : FindDisplayReferenceByChapterVerse
 *****************************************************************************/
TextDisplayReferenceItem*
TextDisplayViewWindow::FindDisplayReferenceByChapterVerse
(int InChapter, int InVerse)
{
  for ( auto item : textItems ) {
    if ( item->GetType() == TextDisplayItem::ReferenceType ) {
      if ( item->GetChapter() == InChapter && item->GetVerse() == InVerse ) {
        return (TextDisplayReferenceItem*)item;
      }
    }
  }
  return NULL;
}

/*****************************************************************************!
 * Function : SlotSetFormattingType
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetFormattingType
(TextDisplayFormattingItem::FormatType InFormattingType)
{
  FormattingType = InFormattingType;
}

/*****************************************************************************!
 * Function : GetWordCount
 *****************************************************************************/
int
TextDisplayViewWindow::GetWordCount
()
{
  return wordCount;
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplayViewWindow::SlotChapterChanged
(int InChapter)
{
  currentSelectedChapter = InChapter;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplayViewWindow::keyPressEvent
(QKeyEvent* InEvent)
{
  int                                   key;
  Qt::KeyboardModifiers                 mods;
  
  key = InEvent->key();
  mods = InEvent->modifiers();
  
  if ( mode == InterlinearMode || mode == ReferenceMode ) {
    if ( KeyPress(key, mods) ) {
      return;
    }
  }

  QWidget::keyPressEvent(InEvent);
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayViewWindow::enterEvent
(QEnterEvent*)
{
  setFocus();
}

/*****************************************************************************!
 * Function : KeyPress
 *****************************************************************************/
bool
TextDisplayViewWindow::KeyPress
(int InKey, Qt::KeyboardModifiers InModifiers)
{
  int                                   newChapter;
  if ( maxChapters == 0 ) {
    return false;
  }

  if ( InModifiers != Qt::NoModifier ) {
    return false;
  }
  
  if ( InKey == Qt::Key_I ) {
    emit SignalWindowChange(5);
    return true;
  }

  if ( InKey == Qt::Key_B ) {
    emit SignalWindowChange(2);
    return true;
  }

  if ( InKey == Qt::Key_E ) {
    emit SignalWindowChange(3);
    return true;
  }

  if ( InKey == Qt::Key_0 ) {
    emit SignalSetStartupBookmark(bookInfo, currentSelectedChapter);
    return true;
  }

  if ( InKey == Qt::Key_S ) {
    emit SignalWindowChange(4);
    return true;
  }

  if ( InKey == Qt::Key_M ) {
    SetBookMark();
    return true;
  }
  if ( InKey == Qt::Key_V ) {
    emit SignalWindowChange(1);
    return true;
  }
    
  if ( InKey == Qt::Key_Home && InModifiers == Qt::NoModifier ) {
    newChapter = 1;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }
  
  if ( InKey == Qt::Key_End && InModifiers == Qt::NoModifier ) {
    newChapter = maxChapters;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }
  
  if ( InKey == Qt::Key_Left && InModifiers == Qt::NoModifier ) {
    if ( currentSelectedChapter <= 1 ) {
      return true;
    }
    newChapter = currentSelectedChapter - 1;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  if ( InKey == Qt::Key_Right && InModifiers == Qt::NoModifier ) {
    if ( currentSelectedChapter >= maxChapters ) {
      return true;
    }

    if( currentSelectedChapter >= maxChapters ) {
      return true;
    }

    newChapter = currentSelectedChapter+1;
    SlotChapterChanged(newChapter);
    emit SignalChapterArrowSelected(newChapter);
    return true;
  }

  return false;
}

/*****************************************************************************!
 *****************************************************************************
 * Interlinear Functions
 *****************************************************************************
 *****************************************************************************/

/*****************************************************************************!
 * Function : SlotSetInterlinearMode
 *****************************************************************************/
void
TextDisplayViewWindow::SlotSetInterlinearMode(void)
{
  currentSelectedInterlinearWord = NULL;
  mode = InterlinearMode;
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : AddInterlinearChapter
 *****************************************************************************/
InterlinearChapter*
TextDisplayViewWindow::AddInterlinearChapter
(int InBookIndex, int InChapterNumber)
{
  QString                               query;
  int                                   n;
  InterlinearChapter*                   chapter;
  ThisChapter                           thisChapter;

  chapter = new InterlinearChapter(InBookIndex, InChapterNumber);
  thisChapter.thisPointer = this;
  thisChapter.chapter = chapter;

  query = QString("SELECT * FROM VERSE WHERE BOOK_NUMBER is %1 and CHAPTER_NUMBER IS %2;").
    arg(InBookIndex).arg(InChapterNumber);
  
  n = sqlite3_exec(MainInterlinearDatabase, query.toStdString().c_str(), AddInterlinearChapterCB, &thisChapter, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s\n : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
  }
  return chapter;
}

/*****************************************************************************!
 * Function : AddInterlinearChapterCB
 *****************************************************************************/
int
TextDisplayViewWindow::AddInterlinearChapterCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  int                                   i;
  int                                   id;
  QString                               columnName;
  QString                               columnValue;
  InterlinearChapter*                   chapter;
  InterlinearVerse*                     verse;
  int                                   verseNumber;
  TextDisplayViewWindow*                thisPointer;
  ThisChapter*                          thisChapter;
  
  thisChapter   = (ThisChapter*)InPointer;
  thisPointer   = thisChapter->thisPointer;
  chapter       = thisChapter->chapter;
  verseNumber   = 0;
  id            = 0;
  
  for (i = 0; i < InColumnCount; i++) {
    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];
    if ( columnName == "ID" ) {
      id = columnValue.toInt();
      continue;
    }

    if ( columnName == "VERSE_NUMBER" ) {
      verseNumber = columnValue.toInt();
      continue;
    }
  }
  verse = new InterlinearVerse(chapter->GetBookIndex(), chapter->GetChapterNumber(), verseNumber, id);
  chapter->AddVerse(verse);
  thisPointer->AddInterlinearVerse(verse);
  return 0;
}

/*****************************************************************************!
 * Function: AddInterlinearVerse
 *****************************************************************************/
void
TextDisplayViewWindow::AddInterlinearVerse
(InterlinearVerse* InVerse)
{
  QString                               query;
  int                                   n;

  query = QString("SELECT * FROM INTERLINEAR_WORD WHERE VERSE_ID is %1 ORDER BY ID;").arg(InVerse->GetVerseID());
  n = sqlite3_exec(MainInterlinearDatabase, query.toStdString().c_str(), AddInterlinearVerseCB, InVerse, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s\n : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
  }
}

/*****************************************************************************!
 * Function : AddInterlinearVerseCB
 *****************************************************************************/
int
TextDisplayViewWindow::AddInterlinearVerseCB
(void* InPointer, int InColumnCount, char** InColumnValues, char** InColumnNames)
{
  QString                               columnName;
  QString                               columnValue;
  int                                   verseID;
  QString                               contextualForm ;
  QString                               transliteratedContextualForm;
  QString                               morphologyID;
  QString                               strongsWordID;
  QString                               english;
  InterlinearVerse*                     verse;
  InterlinearWord*                      word;
  
  verse  = (InterlinearVerse*)InPointer;
  verseID = 0;
  for (int i = 0 ; i < InColumnCount; i++) {

    columnName = InColumnNames[i];
    columnValue = InColumnValues[i];

    if ( columnName == "VERSE_ID" ) {
      verseID = columnValue.toInt();
      continue;
    }
    
    if ( columnName == "CONTEXTUAL_FORM" ) {
      contextualForm = columnValue;
      continue;
    }
    
    if ( columnName == "TRANSLITERATED_CONTEXTUAL_FORM" ) {
      transliteratedContextualForm = columnValue;
      continue;
    }
    
    if ( columnName == "MORPHOLOGY_ID" ) {
      morphologyID = columnValue;
      continue;
    }
    
    if ( columnName == "STRONGS_WORD_ID" ) {
      strongsWordID = columnValue;
      continue;
    }
    
    if ( columnName == "ENGLISH" ) {
      english = columnValue;
      continue;
    }
  }

  word = new InterlinearWord(verse->GetBookIndex(), verse->GetChapterNumber(), verse->GetVerseNumber(), verseID);
  word->SetContextualForm(contextualForm);
  word->SetTransliteratedContextualForm(transliteratedContextualForm);
  word->SetMorphologyID(morphologyID);
  word->SetStrongsWordID(strongsWordID);
  word->SetEnglish(english);

  verse->AddWord(word);
  return 0;
}

/*****************************************************************************!
 * Function : GetInterlinearVerse
 *****************************************************************************/
InterlinearVerse*
TextDisplayViewWindow::GetInterlinearVerse
(int InID)
{
  (void)InID;
#if 0  
  QString                               query;
  int                                   n;
  InterlinearVerse*                     verse;

  verse = new InterlinearVerse();
  query = QString("SELECT * from INTERLINEAR_WORD WHERE VERSE_ID is %1 ORDER BY ID;\n").arg(InID);
  n = sqlite3_exec(MainInterlinearDatabase, query.toStdString().c_str(), GetInterlinearVerseCB, verse, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s : sqlite3_exec()\n%s\n%s\n",
            __FUNCTION__, query.toStdString().c_str(),
            sqlite3_errstr(n));
    return NULL;
  }

  return verse;
#endif
  return NULL;
}

/*****************************************************************************!
 * Function : GetInterlinearVerseNumber
 *****************************************************************************/
int
TextDisplayViewWindow::GetInterlinearVerseNumber
(int InBookNumber, int InChapterNumber, int InVerseNumber)
{
  QString                               query;
  int                                   n;
  sqlite3_stmt*                         sqlstmt;
  int                                   retryCount;
  int                                   verseID;
  int                                   len;
  
  query = QString("SELECT ID FROM VERSE WHERE BOOK_NUMBER IS %1 AND CHAPTER_NUMBER IS %2 AND VERSE_NUMBER IS %3;")
    .arg(InBookNumber)
    .arg(InChapterNumber)
    .arg(InVerseNumber);
  len = query.length();
  
  n = sqlite3_prepare_v2(MainInterlinearDatabase, query.toStdString().c_str(), len, &sqlstmt, NULL);
  if ( n != SQLITE_OK ) {
    fprintf(stderr, "%s sqlite3_prepare_v2()\n%s\n%s\n",
            __FUNCTION__,
            query.toStdString().c_str(),
            sqlite3_errstr(n));
    return 0;
  }
  retryCount = 0;
  verseID = 0;
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
      verseID = sqlite3_column_int(sqlstmt, 0);
    }
  } while (true);
  sqlite3_finalize(sqlstmt);
  return verseID;
}

/*****************************************************************************!
 * Function : ArrangeItemsInterlinear
 *****************************************************************************/
int
TextDisplayViewWindow::ArrangeItemsInterlinear
(int InY, int InWindowWidth)
{
  int                                   i;
  int                                   n;
  int                                   x;
  int                                   y;
  int                                   m;
  int                                   j;
  InterlinearVerse*                     verse;
  InterlinearWord*                      word;
  QSize                                 wordSize;
  QString                               contextualForm;
  QString                               english;
  QSize                                 ws;
  int                                   wordHeight;

  if ( currentInterlinearChapter ) {
    delete currentInterlinearChapter;
  }
  currentInterlinearChapter = AddInterlinearChapter(bookInfo->index, currentSelectedChapter);
  n = currentInterlinearChapter->GetVerseCount();
  y = InY;
  for ( i = 0 ; i < n ; i++ ) {
    verse = currentInterlinearChapter->GetVerseByIndex(i);
    x = InWindowWidth;
    m = verse->GetWordCount();
    wordHeight = 0;
    for ( j = 0 ; j < m ; j++ ) {
      word = verse->GetWordByIndex(j);
      wordSize = word->GetSize();
      if ( x - wordSize.width() < rightMargin ) {
        y += wordHeight;
        x = InWindowWidth;
      } 
      x -= wordSize.width();
      x -= InterInterlinearWordSkip;
      word->SetX(x);
      word->SetY(y);
      wordHeight = wordSize.height();
    }
    y += wordHeight + InterLineSkip * 2;
    x = InWindowWidth;

  }
  y += bottomMargin;
  return y;
}

/*****************************************************************************!
 * Function : PaintInterlinearMode
 *****************************************************************************/
void
TextDisplayViewWindow::PaintInterlinearMode
(QPainter* InPainter)
{
  QString                               ref;
  int                                   x2;
  int                                   w2;
  int                                   x;
  int                                   n;
  int                                   i;
  int                                   m;
  int                                   j;
  QSize					wordSize;
  int                                   y;
  int                                   y2;
  QBrush				brush = QBrush(QColor(240, 240, 240));
  QSize                                 s = size();

  y = 0;
  InPainter->setBrush(brush);
  InPainter->drawRect(QRect(QPoint(0, 0), s));
 
  if ( currentInterlinearChapter == NULL ) {
    return;
  }

  n = currentInterlinearChapter->GetVerseCount();
  for ( i = 0 ; i < n ; i++ ) {
    InterlinearWord*                    word;
    InterlinearVerse*                   verse;

    verse = currentInterlinearChapter->GetVerseByIndex(i);
    m = verse->GetWordCount();
    word = verse->GetWordByIndex(0);
    x = word->GetX();
    w2 = word->GetSize().width();

    x2 = x + w2 + 5;
    ref = QString("%1:%2").arg(verse->GetChapterNumber()).arg(verse->GetVerseNumber());
    for ( j = 0 ; j < m ; j++ ) {
      word = verse->GetWordByIndex(j);
      word->Paint(InPainter);
      wordSize = word->GetSize();
      y = word->GetY();
    }
    InPainter->setBrush(QBrush(QColor(192, 0, 0)));
    InPainter->setFont(QFont("Arial", 12, QFont::Normal));
    InPainter->drawText(x2, y+18, ref);

    y2 = y + wordSize.height() + InterLineSkip;

    InPainter->setPen(QColor(240, 240, 240));
    InPainter->drawLine(0, y2, s.width(), y2);
  }
  if ( currentSelectedInterlinearWord ) {
    currentSelectedInterlinearWord->PaintSelected(InPainter);
  }
}
  
/*****************************************************************************!
 * Function : InterlinearModeMousePress
 *****************************************************************************/
void
TextDisplayViewWindow::InterlinearModeMousePress
(QMouseEvent* InEvent)
{
  Qt::MouseButton                       button;
  Qt::KeyboardModifiers                 modifiers;

  button = InEvent->button();
  modifiers = InEvent->modifiers();

  if ( button == Qt::LeftButton && modifiers == Qt::NoModifier ) {
    InterlinearWord*                    word;
    word = currentInterlinearChapter->FindWordByLocation(InEvent->pos());
    if ( word ) {
      InterlinearModeDisplayElementViewDialog(InEvent->globalPosition().toPoint(), word);
    }
    return;
  }
}

/*****************************************************************************!
 * Function : InterlinearModeDisplayElementViewDialog
 *****************************************************************************/
void
TextDisplayViewWindow::InterlinearModeDisplayElementViewDialog
(QPoint InPosition, InterlinearWord* InWord)
{
  StrongsReferenceDisplayDialog*                dialog;
  QString                                       s;

  s = InWord->GetStrongsWordID();
  dialog = new StrongsReferenceDisplayDialog(InWord);
  dialog->move(InPosition);
  dialog->exec();
  delete dialog;
}

/*****************************************************************************!
 * Function : InterlinearModeMouseMove
 *****************************************************************************/
void
TextDisplayViewWindow::InterlinearModeMouseMove
(QPoint InMouseCursor)
{
  InterlinearWord*                      word;
  QString 				englishWord;

  word = currentInterlinearChapter->FindWordByLocation(InMouseCursor);
  if ( word == NULL ) {
    currentSelectedInterlinearWord = NULL;
    repaint();
    return;
  }
  if ( currentSelectedInterlinearWord == word ) {
    return;
  }
  currentSelectedInterlinearWord = word;
  englishWord = currentSelectedInterlinearWord->GetEnglish();
  repaint();
}

/*****************************************************************************!
 * Function : AddInterlinearItem
 *****************************************************************************/
void
TextDisplayViewWindow::AddInterlinearItem
(TextDisplayInterlinearItem* InItem)
{
  if ( NULL == InItem ) {
    return;
  }
  interlinearItems.push_back(InItem);
}

/*****************************************************************************!
 * Function : SlotInterlinearWordSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotInterlinearWordSelected
(int InWord, bool InSelected)
{
  switch (InWord) {
    case INTERLINEAR_WORD_CONTEXTUAL_INDEX : {
      InterlinearWord::contextualFormDisplay = InSelected;
      break;
    }

    case INTERLINEAR_WORD_MORPHOLOGY_INDEX : {
      InterlinearWord::morphologyDisplay = InSelected ;     
      break;
    }

    case INTERLINEAR_WORD_TRANSLITERATE_INDEX : {
      InterlinearWord::transliterateDisplay = InSelected;            
      break;
    }

    case INTERLINEAR_WORD_STRONGS_INDEX : {
      InterlinearWord::strongsDisplay = InSelected;                  
      break;
    }

    case INTERLINEAR_WORD_ENGLISH_INDEX : {
      InterlinearWord::englishDisplay = InSelected;                        
      break;
    }
  }
  InterlinearWord::SetValues();
  ArrangeItems();
  repaint();
}

/*****************************************************************************!
 * Function : SetBookMark
 *****************************************************************************/
void
TextDisplayViewWindow::SetBookMark(void)
{
  if ( mode == ReferenceMode ) {
    SetBookMarkReference();
    return;
  }
}
 
/*****************************************************************************!
 * Function : SetBookMarkReference
 *****************************************************************************/
void
TextDisplayViewWindow::SetBookMarkReference(void)
{
  BookInfo*                             bookInfo;
  int                                   verse;
  int                                   chapter;
  int                                   book;
  TextDisplayItem::DisplayType          type;
  TextDisplayItem*                      textItem;
  int                                   i;
  int                                   n;

  n = textItems.size();
  for (i = 0; i < n; i++) {
    textItem = textItems[i];
    type = textItem->GetType();
    if ( type != TextDisplayItem::WordType ) {
      continue;
    }
    if ( textItem->GetIsVisible() ) {
      break;
    }
  }
  if ( i >= n ) {
    return;
  }
  book = textItem->GetBook();
  chapter = textItem->GetChapter();
  verse = textItem->GetVerse();

  bookInfo = MainBookInfo->FindBookByIndex(book);
  emit SignalSetBookMark(bookInfo, chapter, verse, 0);
}

/*****************************************************************************!
 * Function : ReferenceModeMousePress
 *****************************************************************************/
void
TextDisplayViewWindow::ReferenceModeMousePress
(QMouseEvent* )
{
}

/*****************************************************************************!
 * Function : SlotBookmarkSelected
 *****************************************************************************/
void
TextDisplayViewWindow::SlotBookmarkSelected
(BookInfo* InBook, int InChapter, int)
{
  SlotBookSelected(InBook);
  SlotSelectChapter(InChapter);
}
