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
  
  controlBar = new TextControlBar();
  controlBar->setParent(this);
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
  controlBar = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayOuterWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   headerH;
  int                                   headerW;
  int                                   headerY;
  int                                   headerX;
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
  int                                   controlBarX;
  int                                   controlBarY;
  int                                   controlBarW;
  int                                   controlBarH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = SECTION_HEADER_HEIGHT;
  
  //!
  controlBarX = 0;
  controlBarY = SECTION_HEADER_HEIGHT;
  controlBarH = TEXT_CONTROL_BAR_HEIGHT;
  controlBarW = width;

  //!
  referenceWindowX = 0;
  referenceWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  referenceWindowW = width;
  referenceWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);

  //!
  viewWindowX = 0;
  viewWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  viewWindowW = width;
  viewWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);

  //!
  if ( header ) {
    header->move(headerX, headerY);
    header->resize(headerW, headerH);
  }

  if ( referenceWindow ) {
    referenceWindow->move(referenceWindowX, referenceWindowY);
    referenceWindow->resize(referenceWindowW, referenceWindowH);
  }
  if ( viewWindow ) {
    viewWindow->move(viewWindowX, viewWindowY);
    viewWindow->resize(viewWindowW, viewWindowH);
  }
  if ( controlBar ) {
    controlBar->move(controlBarX, controlBarY);
    controlBar->resize(controlBarW, controlBarH);
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
  connect(viewWindow,
          SIGNAL(SignalShowProgressBar()),
          this,
          SLOT(SlotShowProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalHideProgressBar()),
          this,
          SLOT(SlotHideProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalUpdateProgressBar(int)),
          this,
          SLOT(SlotUpdateProgressBar(int)));
  connect(viewWindow,
          SIGNAL(SignalSetProgressBar(int, int)),
          this,
          SLOT(SlotSetProgressBar(int, int)));

  connect(viewWindow,
          SIGNAL(SignalWordCountChanged(int)),
          this,
          SLOT(SlotWordCountChanged(int)));
  connect(this,
          SIGNAL(SignalWordCountChanged(int)),
          controlBar,
          SLOT(SlotWordCountChanged(int)));
  
  connect(viewWindow,
          SIGNAL(SignalVerseCountChanged(int)),
          this,
          SLOT(SlotVerseCountChanged(int)));
  connect(this,
          SIGNAL(SignalVerseCountChanged(int)),
          controlBar,
          SLOT(SlotVerseCountChanged(int)));
  
  connect(viewWindow,
          SIGNAL(SignalSentenceCountChanged(int)),
          this,
          SLOT(SlotSentenceCountChanged(int)));
  connect(this,
          SIGNAL(SignalSentenceCountChanged(int)),
          controlBar,
          SLOT(SlotSentenceCountChanged(int)));
  
  connect(controlBar,
          SIGNAL(SignalSetSentenceMode()),
          this,
          SLOT(SlotSetSentenceMode()));
  connect(controlBar,
          SIGNAL(SignalSetReferenceMode()),
          this,
          SLOT(SlotSetReferenceMode()));
  connect(controlBar,
          SIGNAL(SignalSetBlockMode()),
          this,
          SLOT(SlotSetBlockMode()));

  connect(this,
          SIGNAL(SignalSetSentenceMode()),
          viewWindow,
          SLOT(SlotSetSentenceMode()));
  connect(this,
          SIGNAL(SignalSetReferenceMode()),
          viewWindow,
          SLOT(SlotSetReferenceMode()));
  connect(this,
          SIGNAL(SignalSetBlockMode()),
          viewWindow,
          SLOT(SlotSetBlockMode()));

}

/*****************************************************************************!
 * Function : SlotShowProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotShowProgressBar(void)
{
  emit SignalShowProgressBar();
}

/*****************************************************************************!
 * Function : SlotHideProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotHideProgressBar(void)
{
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : SlotUpdateProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotUpdateProgressBar
(int InValue)
{
  emit SignalUpdateProgressBar(InValue);
}

/*****************************************************************************!
 * Function : SlotSetProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetProgressBar
(int InMin, int InMax)
{
  emit SignalSetProgressBar(InMin, InMax);
}

/*****************************************************************************!
 * Function : SlotWordCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotWordCountChanged
(int InWordCount)
{
  emit SignalWordCountChanged(InWordCount);
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetSentenceMode(void)
{
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetBlockMode(void)
{
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetReferenceMode(void)
{
  emit SignalSetReferenceMode();
}

/*****************************************************************************!
 * Function : SlotVerseCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotVerseCountChanged
(int InVerseCount)
{
  emit SignalVerseCountChanged(InVerseCount);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}
