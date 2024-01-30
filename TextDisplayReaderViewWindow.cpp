/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewWindow.cpp
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayReaderViewWindow.h"
#include "VerseInfoSet.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayReaderViewWindow
 *****************************************************************************/
TextDisplayReaderViewWindow::TextDisplayReaderViewWindow
() : QTextEdit()
{
  QPalette                              pal;

  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 0, 0)));
  setPalette(pal);
  Initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayReaderViewWindow
 *****************************************************************************/
TextDisplayReaderViewWindow::~TextDisplayReaderViewWindow
()
{
  
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
TextDisplayReaderViewWindow::Initialize()
{
  setReadOnly(false);
  setAlignment(Qt::AlignJustify);
  setLineWidth(0);
  setFrameShape(QFrame::NoFrame);
  setFont(QFont(MainSystemSettings->GetReaderViewFontName(),
                MainSystemSettings->GetReaderViewFontSize(),
                QFont::Normal));
  Book = NULL;
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotBookSelected
(BookInfo* InBook)
{
  int                                   blockCount;
  QTextDocument*                        doc;
  int                                   n;
  VerseInfo*                            verseInfo;
  int                                   i;
  QString                               text;
  QString                               verseText;
  VerseInfoSet*                         verseSet;
  int                                   verseCount;
  QTextBlockFormat                      textBlockFormat;
  QTextCursor                           cursor;

  //! 
  Book = InBook;
  verseSet = Book->GetVerses();

  //! 
  doc = document();
  cursor = QTextCursor(doc);
  cursor.setPosition(0);
  setPlainText("");
  
  //! 
  textBlockFormat.setAlignment(Qt::AlignJustify);
  textBlockFormat.setLeftMargin(25);
  textBlockFormat.setRightMargin(25);
  textBlockFormat.setBackground(QBrush(QColor(255, 0, 0, 32)));
  cursor.setBlockFormat(textBlockFormat);

  //! 
  verseCount = verseSet->GetVerseCount();
  for (i = 0 ; i < verseCount; i++) {
    verseInfo = verseSet->GetVerseByIndex(i);
    if ( verseInfo->GetChapter() == 2 && verseInfo->GetVerse() == 1 ) {
      cursor.insertText(text);
      text = "";
      CreateNewBlock(cursor);
    }
    text += verseInfo->GetText() + QString(" ");
  }
  cursor.insertText(text);
  blockCount = doc->blockCount();
  CurrentText = text;
  delete verseSet;
  n = CurrentText.length();

  CurrentTextStart = 0;
  for ( i = 0 ; i < n ; i++ ) {
    if ( CurrentText[i].isPunct() ) {
      i++;
      break;
    }
  }

  CurrentTextEnd = i;
  setFocus();
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotChapterSelected
(int)
{
}

/*****************************************************************************!
 * Function : SetVerseText
 *****************************************************************************/
void
TextDisplayReaderViewWindow::CreateNewBlock
(QTextCursor& InCursor)
{
  QTextBlockFormat                      textBlockFormat;
  textBlockFormat.setAlignment(Qt::AlignJustify);
  textBlockFormat.setLeftMargin(50);
  textBlockFormat.setRightMargin(50);
  textBlockFormat.setBackground(QBrush(QColor(0, 0, 255, 32)));
  InCursor.insertBlock(textBlockFormat);
}
