/*****************************************************************************
 * FILE NAME    : TextDisplayOuterWindow.cpp
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
#include "TextDisplayOuterWindow.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayOuterWindow
 *****************************************************************************/
TextDisplayOuterWindow::TextDisplayOuterWindow
() : QFrame()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(224, 224, 224)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameStyle(QFrame::Panel);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayOuterWindow
 *****************************************************************************/
TextDisplayOuterWindow::~TextDisplayOuterWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayOuterWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayOuterWindow::CreateSubWindows()
{
  header = new SectionHeader();
  header->SetText("----");
  header->setParent(this);

  referenceWindow = new TextDisplayReferenceWindow();
  referenceWindow->setParent(this);
  referenceWindow->hide();

  viewWindow = new TextDisplayViewScrollWindow();
  viewWindow->setParent(this);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayOuterWindow::InitializeSubWindows()
{
  header = NULL;
  referenceWindow = NULL;
  viewWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayOuterWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   referenceWindowX;
  int                                   referenceWindowY;
  int                                   referenceWindowW;
  int                                   referenceWindowH;
  int                                   viewWindowX;
  int                                   viewWindowY;
  int                                   viewWindowW;
  int                                   viewWindowH;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  referenceWindowX = 0;
  referenceWindowY = SECTION_HEADER_HEIGHT;
  referenceWindowW = width;
  referenceWindowH = height;

  viewWindowX = 0;
  viewWindowY = SECTION_HEADER_HEIGHT;
  viewWindowW = width;
  viewWindowH = height;

  if ( header ) {
    header->move(0, 0);
    header->resize(width, SECTION_HEADER_HEIGHT);
  }
  if ( referenceWindow ) {
    referenceWindow->move(referenceWindowX, referenceWindowY);
    referenceWindow->resize(referenceWindowW, referenceWindowH);
  }
  if ( viewWindow ) {
    viewWindow->move(viewWindowX, viewWindowY);
    viewWindow->resize(viewWindowW, viewWindowH);
  }
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotBookSelected
(int InBookIndex)
{
  QString                               name;
  BookInfo*                             bookInfo;

  bookInfo = NULL;
  for ( auto b : MainBookInfo ) {
    if ( b->index == InBookIndex ) {
      bookInfo = b;
      break;
    }
  }
  if ( NULL == bookInfo ) {
    return;
  }
  header->SetText(bookInfo->GetCapitalizedBookName());
  viewWindow->ClearText();
  emit SignalBookSelected(bookInfo);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayOuterWindow::CreateConnections(void)
{
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          referenceWindow,
          SLOT(SlotBookSelected(BookInfo*)));
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          viewWindow,
          SLOT(SlotBookSelected(BookInfo*)));
}
