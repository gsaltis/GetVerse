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
 * Function : initialize
 *****************************************************************************/
void
TextDisplayReaderViewWindow::initialize()
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
  int                                   formatType;
  ReaderViewFormat*                     formatInfo;
  VerseInfo*                            verseInfo;
  int                                   i;
  QString                               text;
  QString                               verseText;
  VerseInfoSet*                         verseSet;
  int                                   verseCount;

  Book = InBook;
  setStyleSheet("QTextEdit { "
                "  background : #FFFFFF; "
                "  font-size : 14pt "
                "} "
                "H1 {"
                "  font-size : 8pt; "
                "}"
                "div { "
                "  text-align : justify; "
                "  color : red; "
                "  text-justify : inter-word; "
                "}"
                "QFrame { "
                "  margin : 20px; "
                "  margin-right : 100px; "
                "}");
  verseSet = Book->GetVerses();

  verseCount = verseSet->GetVerseCount();
  text += "<p>";
  for (i = 0; i < verseCount; i++) {
    verseInfo = verseSet->GetVerseByIndex(i);
    verseText = verseInfo->GetText();
    formatInfo = MainReaderViewFormats->FindFormat(verseInfo->GetBook(), verseInfo->GetChapter(), verseInfo->GetVerse(), 0);
    if ( NULL == formatInfo ) {
      text += QString(" %1").arg(verseText);
      continue;
    }
    formatType = formatInfo->GetFormat();
    if ( formatType == ReaderViewFormatParagraph ) {
      text += QString("</p><p>") + verseText;
    }
  }
  text += "</p>";
  setHtml(text);
  delete verseSet;
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayReaderViewWindow::SlotChapterSelected
(int)
{
}
