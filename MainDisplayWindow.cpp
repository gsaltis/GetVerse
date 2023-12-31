/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
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
#include "MainDisplayWindow.h"
#include "main.h"
#include "Common.h"

/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
(QString InBookName) : QWidget()
{
  QPalette				pal;

  BookName = InBookName;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(160, 160, 192)));
  setPalette(pal);
  setAutoFillBackground(true);

  Initialize();
}

/*****************************************************************************!
 * Function : ~MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::~MainDisplayWindow
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
MainDisplayWindow::Initialize()
{
  int                                   book;
  int                                   chapter;
  int                                   verse;

  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
  MainGetStartLocation(book, chapter, verse);

  emit SignalMoveToBookChapter(book, chapter, verse);
  displayWindow->SlotChapterSelected(chapter);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
MainDisplayWindow::InitializeSubWindows()
{
  bookNameWindow = NULL;  
  messageWindow = NULL;
  displayWindow = NULL;
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
MainDisplayWindow::CreateSubWindows()
{
  bookNameWindow = new BookNameWindow();  
  bookNameWindow->setParent(this);
  messageWindow = new MainMessageWindow();
  messageWindow->setParent(this);
  displayWindow = new TextDisplayOuterWindow(BookName);
  displayWindow->setParent(this);
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
MainDisplayWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   displayWindowH;
  int                                   displayWindowW;
  int                                   displayWindowY;
  int                                   displayWindowX;

  int                                   messageWindowX;
  int                                   messageWindowY;
  int                                   messageWindowH;
  int                                   messageWindowW;

  int                                   bookNameWindowH;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  messageWindowX = 0;
  messageWindowY = height - MAIN_MESSAGE_WINDOW_HEIGHT;
  messageWindowH = MAIN_MESSAGE_WINDOW_HEIGHT;
  messageWindowW = width;

  displayWindowX = BOOK_NAME_WINDOW_WIDTH;
  displayWindowY = 0;
  displayWindowW = width - BOOK_NAME_WINDOW_WIDTH;
  displayWindowH = height - MAIN_MESSAGE_WINDOW_HEIGHT;;
  
  bookNameWindowH = height - MAIN_MESSAGE_WINDOW_HEIGHT;
  (void)height;
  (void)width;
  if ( bookNameWindow ) {
    bookNameWindow->move(0, 0);
    bookNameWindow->resize(BOOK_NAME_WINDOW_WIDTH, bookNameWindowH);
  }
  if ( messageWindow ) {
    messageWindow->move(messageWindowX, messageWindowY);
    messageWindow->resize(messageWindowW, messageWindowH);
  }
  if ( displayWindow ) {
    displayWindow->move(displayWindowX, displayWindowY);
    displayWindow->resize(displayWindowW, displayWindowH);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
MainDisplayWindow::CreateConnections(void)
{
  connect(this,
          MainDisplayWindow::SignalDisplayBookMarks,
          displayWindow,
          TextDisplayOuterWindow::SlotDisplayBookMarks);
  
  connect(this,
          MainDisplayWindow::SignalClearBookMarks,
          displayWindow,
          TextDisplayOuterWindow::SlotClearBookMarks);
  
  connect(displayWindow,
          TextDisplayOuterWindow::SignalSetStartupBookmarkInfo,
          this,
          MainDisplayWindow::SlotSetStartupBookmarkInfo);
  
  connect(displayWindow,
          TextDisplayOuterWindow::SignalSetBookMark,
          this,
          MainDisplayWindow::SlotSetBookMark);
  
  connect(this,
          MainDisplayWindow::SignalMoveToBookChapter,
          bookNameWindow,
          BookNameWindow::SlotMoveToBookChapter);
  
  connect(displayWindow,
          TextDisplayOuterWindow::SignalSetStartupBookmark,
          this,
          MainDisplayWindow::SlotSetStartupBookmark);
  
  connect(bookNameWindow,
          SIGNAL(SignalBookSelected(int)),
          displayWindow,
          SLOT(SlotBookSelected(int)));
  
  connect(displayWindow,
          SIGNAL(SignalShowProgressBar()),
          this,
          SLOT(SlotShowProgressBar()));

  connect(displayWindow,
          SIGNAL(SignalHideProgressBar()),
          this,
          SLOT(SlotHideProgressBar()));

  connect(displayWindow,
          SIGNAL(SignalSetMessage(QString)),
          messageWindow,
          SLOT(SlotSetMessageNormal(QString)));
  
  connect(displayWindow,
          SIGNAL(SignalSetProgressBar(int, int)),
          this,
          SLOT(SlotSetProgressBar(int, int)));
  connect(displayWindow,
          SIGNAL(SignalUpdateProgressBar(int)),
          this,
          SLOT(SlotUpdateProgressBar(int)));
  connect(this,
          SIGNAL(SignalHideProgressBar()),
          messageWindow,
          SLOT(SlotProgressBarHide()));
  connect(this,
          SIGNAL(SignalShowProgressBar()),
          messageWindow,
          SLOT(SlotProgressBarShow()));
  connect(this,
          SIGNAL(SignalUpdateProgressBar(int)),
          messageWindow,
          SLOT(SlotProgressBarUpdate(int)));
  connect(this,
          SIGNAL(SignalSetProgressBar(int, int)),
          messageWindow,
          SLOT(SlotProgressBarSet(int, int)));
}

/*****************************************************************************!
 * Function : SlotShowProgressBar
 *****************************************************************************/
void
MainDisplayWindow::SlotShowProgressBar(void)
{
  emit SignalShowProgressBar();
}

/*****************************************************************************!
 * Function : SlotHideProgressBar
 *****************************************************************************/
void
MainDisplayWindow::SlotHideProgressBar(void)
{
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : SlotUpdateProgressBar
 *****************************************************************************/
void
MainDisplayWindow::SlotUpdateProgressBar
(int InValue)
{
  emit SignalUpdateProgressBar(InValue);
}

/*****************************************************************************!
 * Function : SlotSetProgressBar
 *****************************************************************************/
void
MainDisplayWindow::SlotSetProgressBar
(int InMin, int InMax)
{
  emit SignalSetProgressBar(InMin, InMax);
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmark
 *****************************************************************************/
void
MainDisplayWindow::SlotSetStartupBookmark
(int InBook, int InChapter, int InVerse)
{
  BookInfo*                             bookInfo;

  bookInfo = MainBookInfo->FindBookByIndex(InBook);
  
  MainSetStartLocation(InBook, InChapter, InVerse);
  messageWindow->SlotSetMessageNormal(QString("Saving Bookmark : %1 %2").arg(bookInfo->name).arg(InChapter));
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
MainDisplayWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  SlotSetStartupBookmark(InBookInfo->index, InChapter, 1);
}

/*****************************************************************************!
 * Function : SlotSetBookMark
 *****************************************************************************/
void
MainDisplayWindow::SlotSetBookMark
(BookInfo* InBookInfo, int InChapter, int InVerse, int InWord)
{
  MainBookMarks->SetBookMark(InBookInfo->index, InChapter, InVerse, InWord);
  emit SignalDisplayBookMarks();
}

/*****************************************************************************!
 * Function : SlotClearBookMarks
 *****************************************************************************/
void
MainDisplayWindow::SlotClearBookMarks(void)
{
  emit SignalClearBookMarks();  
}

/*****************************************************************************!
 * Function : SetViewMode
 *****************************************************************************/
void
MainDisplayWindow::SetViewMode
(QString InMode)
{
  if ( NULL == displayWindow ) {
    return;
  }
  displayWindow->SetViewMode(InMode);
}
