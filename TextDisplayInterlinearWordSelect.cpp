/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearWordSelect.cpp
 * DATE         : December 27 2023
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
#include <sqlite3.h>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayInterlinearWordSelect.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearWordSelect
 *****************************************************************************/
TextDisplayInterlinearWordSelect::TextDisplayInterlinearWordSelect
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(240, 240, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearWordSelect
 *****************************************************************************/
TextDisplayInterlinearWordSelect::~TextDisplayInterlinearWordSelect
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::CreateSubWindows()
{
  ReferenceWindow = new StrongsReferenceForm();  
  ReferenceWindow->setParent(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::CreateConnections()
{
  connect(ReferenceWindow,
          StrongsReferenceForm::SignalCloseStrongsReference,
          this,
          TextDisplayInterlinearWordSelect::SlotCloseStrongsReference);

  connect(this,
          TextDisplayInterlinearWordSelect::SignalVerseReferencesStart,
          ReferenceWindow,
          StrongsReferenceForm::SlotVerseReferenceClear);

  connect(this,
          TextDisplayInterlinearWordSelect::SignalVerseReferenceSelected,
          ReferenceWindow,
          StrongsReferenceForm::SlotVerseReferenceSelected);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::InitializeSubWindows()
{
  ReferenceWindow = NULL;  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   ReferenceWindowW;
  int                                   ReferenceWindowH;
  int                                   ReferenceWindowY;
  int                                   ReferenceWindowX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
  ReferenceWindowX = 0;
  ReferenceWindowY = 0;
  ReferenceWindowW = width;
  ReferenceWindowH = height;
  ReferenceWindow->move(ReferenceWindowX, ReferenceWindowY);
  ReferenceWindow->resize(ReferenceWindowW, ReferenceWindowH);
}

/*****************************************************************************!
 * Function : SlotSelectStrongsWord
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::SlotSelectStrongsWord
(QString InStrongsWord)
{
  GetWordReferences(InStrongsWord);
  ReferenceWindow->SetStrongsReference(InStrongsWord);
}

/*****************************************************************************!
 * Function : GetWordReferences
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::GetWordReferences
(QString InStrongsWord)
{
  int                                   verseNumber;
  int                                   chapterNumber;
  int                                   bookNumber;
  int                                   retryTimes;
  sqlite3_stmt*                         statement;
  int                                   n;
  bool                                  finished;

  QString statementTemplate =
    "SELECT VERSE.BOOK_NUMBER, VERSE.CHAPTER_NUMBER, VERSE.VERSE_NUMBER "
    "FROM VERSE "
    "JOIN INTERLINEAR_WORD ON INTERLINEAR_WORD.VERSE_ID = VERSE.ID "
    "WHERE INTERLINEAR_WORD.STRONGS_WORD_ID is '%1';";
  QString selectStatement = QString(statementTemplate).arg(InStrongsWord);

  n = sqlite3_prepare_v2(MainInterlinearDatabase,
                         selectStatement.toStdString().c_str(),
                         selectStatement.length(),
                         &statement,
                         NULL);
  if ( n != SQLITE_OK ) {
    return;
  }

  finished = false;

  emit SignalVerseReferencesStart();
  retryTimes = 0;
  while (!finished) {
    n = sqlite3_step(statement);
    switch (n) {
      case SQLITE_BUSY : {
        retryTimes++;
        if ( retryTimes > 3 ) {
          finished = true;
          break;
        }
        usleep(25000);
        break;
      }

      case SQLITE_DONE : {
        finished = true;
        break;
      }

      //!
      case SQLITE_ROW : {
        bookNumber      = sqlite3_column_int(statement, 0);
        chapterNumber   = sqlite3_column_int(statement, 1);
        verseNumber     = sqlite3_column_int(statement, 2);
        QString st = QString("%1 %2 %3").arg(bookNumber).arg(chapterNumber).arg(verseNumber);

        emit SignalVerseReferenceSelected(bookNumber, chapterNumber, verseNumber);
        break;
      }
      case SQLITE_ERROR : {
        finished = true;
        break;
      }
      case SQLITE_MISUSE : {
        finished = true;
        break;
      }
    }
  }
  sqlite3_finalize(statement);
}


/*****************************************************************************!
 * Function : SlotCloseStrongsReference
 *****************************************************************************/
void
TextDisplayInterlinearWordSelect::SlotCloseStrongsReference(void)
{
  emit SignalCloseStrongsReference();  
}

