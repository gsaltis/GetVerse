/*****************************************************************************
 * FILE NAME    : MainDisplayWindow.cpp
 * DATE         : September 10 2023
 * PROJECT      : GetVerse
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
#include "MainDisplayWindow.h"

/*****************************************************************************!
 * Function : MainDisplayWindow
 *****************************************************************************/
MainDisplayWindow::MainDisplayWindow
() : QWidget()
{
  QPalette				pal;

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
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
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
  displayWindow = new TextDisplayOuterWindow();
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
