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
  Initialize();
  setReadOnly(true);
  Book = NULL;
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
  setReadOnly(true);
  setAlignment(Qt::AlignJustify);
  setLineWidth(0);
  setFrameShape(QFrame::NoFrame);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotBookSelected
(BookInfo* InBook)
{
  int                                   n;
  VerseInfo*                            verseInfo;
  int                                   i;
  QString                               text;
  QString                               verseText;
  VerseInfoSet*                         verseSet;
  int                                   verseCount;
  
  Book = InBook;
  verseSet = Book->GetVerses();

  verseCount = verseSet->GetVerseCount();

  for (i = 0; i < verseCount; i++) {
    verseInfo = verseSet->GetVerseByIndex(i);
    verseText = verseInfo->GetText();
    text += verseText + QString(" ");
  }
  setPlainText(text);
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

  QTextCursor                           textC(document());
  QTextCharFormat                       fmt;

  fmt = textC.charFormat();
  fmt.setForeground(Qt::red);
  textC.setCharFormat(fmt);
  textC.setPosition(0);
  textC.setPosition(i, QTextCursor::KeepAnchor);
  setTextCursor(textC);
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
