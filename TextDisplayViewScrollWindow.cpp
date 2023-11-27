/*****************************************************************************
 * FILE NAME    : TextDisplayViewScrollWindow.cpp
 * DATE         : September 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnet.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QScrollBar>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewScrollWindow.h"

/*****************************************************************************!
 * Function : TextDisplayViewScrollWindow
 *****************************************************************************/
TextDisplayViewScrollWindow::TextDisplayViewScrollWindow
() : QScrollArea()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayViewScrollWindow
 *****************************************************************************/
TextDisplayViewScrollWindow::~TextDisplayViewScrollWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayViewScrollWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  verticalBar = verticalScrollBar();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollWindow::CreateSubWindows()
{
  viewWindow = new TextDisplayViewWindow();
  setWidget(viewWindow);

  VScrollBar = new TextDisplayViewScrollBar();
  setVerticalScrollBar(VScrollBar);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayViewScrollWindow::InitializeSubWindows()
{
  viewWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayViewScrollWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   viewWindowH;
  QSize					size;  
  int					width;

  size = InEvent->size();
  width = size.width();
  viewWindowH = viewWindow->GetTableHeight();
  if ( viewWindow ) {
    viewWindow->resize(width, viewWindowH);
  }
}

/*****************************************************************************!
 * Function : ClearText
 *****************************************************************************/
void
TextDisplayViewScrollWindow::ClearText(void)
{
  viewWindow->ClearText();
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QScrollBar*                           vBar;

  VScrollBar->SetChapterCount(InBookInfo->chapters);
  vBar = verticalScrollBar();
  vBar->setValue(0);
  emit SignalBookSelected(InBookInfo);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayViewScrollWindow::CreateConnections(void)
{
  connect(viewWindow,
          TextDisplayViewWindow::SignalWindowChange,
          this,
          TextDisplayViewScrollWindow::SlotWindowChange);
  
  connect(viewWindow,
          TextDisplayViewWindow::SignalChapterArrowSelected,
          this,
          TextDisplayViewScrollWindow::SlotChapterArrowSelected);
          
  connect(this,
          SIGNAL(SignalSetFormattingType(TextDisplayFormattingItem::FormatType)),
          viewWindow,
          SLOT(SlotSetFormattingType(TextDisplayFormattingItem::FormatType)));
  
  connect(VScrollBar,
          SIGNAL(SignalChapterSelected(int)),
          this,
          SLOT(SlotChapterSelected(int)));

  connect(VScrollBar,
          SIGNAL(SignalChapterSelected(int)),
          viewWindow,
          SLOT(SlotSelectChapter(int)));

  connect(VScrollBar,
          SIGNAL(SignalChapterScrolled(int)),
          this,
          SLOT(SlotChapterScrolled(int)));

  connect(viewWindow,
          SIGNAL(SignalLocationSelected(QPoint)),
          this,
          SLOT(SlotLocationSelected(QPoint)));
  
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          viewWindow,
          SLOT(SlotBookSelected(BookInfo*)));

  connect(viewWindow,
          SIGNAL(SignalSetMessage(QString)),
          this,
          SLOT(SlotSetMessage(QString)));

  connect(viewWindow,
          SIGNAL(SignalHideProgressBar()),
          this,
          SLOT(SlotHideProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalShowProgressBar()),
          this,
          SLOT(SlotShowProgressBar()));
  
  connect(viewWindow,
          SIGNAL(SignalSetProgressBar(int, int)),
          this,
          SLOT(SlotSetProgressBar(int, int)));
  
  connect(viewWindow,
          SIGNAL(SignalUpdateProgressBar(int)),
          this,
          SLOT(SlotUpdateProgressBar(int)));

  connect(viewWindow,
          SIGNAL(SignalWordCountChanged(int)),
          this,
          SLOT(SlotWordCountChanged(int)));

  connect(viewWindow,
          SIGNAL(SignalSentenceCountChanged(int)),
          this,
          SLOT(SlotSentenceCountChanged(int)));

  connect(viewWindow,
          SIGNAL(SignalVerseCountChanged(int)),
          this,
          SLOT(SlotVerseCountChanged(int)));

  connect(this,
          SIGNAL(SignalSetSentenceMode()),
          viewWindow,
          SLOT(SlotSetSentenceMode()));
  connect(this,
          SIGNAL(SignalSetEditMode()),
          viewWindow,
          SLOT(SlotSetEditMode()));
  connect(this,
          SIGNAL(SignalSetReferenceMode()),
          viewWindow,
          SLOT(SlotSetReferenceMode()));
  connect(this,
          SIGNAL(SignalSetBlockMode()),
          viewWindow,
          SLOT(SlotSetBlockMode()));

  connect(this,
          SIGNAL(SignalSetInterlinearMode()),
          viewWindow,
          SLOT(SlotSetInterlinearMode()));

  connect(verticalBar,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(SlotVerticalScrolled(int)));

  connect(this,
          SIGNAL(SignalVerticalScrolled()),
          viewWindow,
          SLOT(SlotVerticalScrolled()));

  connect(this,
          SIGNAL(SignalChapterChanged(int)),
          viewWindow,
          SLOT(SlotChapterChanged(int)));
}

/*****************************************************************************!
 * Function : SlotHideProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotHideProgressBar(void)
{
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : SlotShowProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotShowProgressBar(void)
{
  emit SignalShowProgressBar();
}

/*****************************************************************************!
 * Function : SlotUpdateProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotUpdateProgressBar
(int InValue)
{
  emit SignalUpdateProgressBar(InValue);
}

/*****************************************************************************!
 * Function : SlotSetProgressBar
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetProgressBar
(int InMin, int InMax)
{
  emit SignalSetProgressBar(InMin, InMax);
}

/*****************************************************************************!
 * Function : SlotWordCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotWordCountChanged
(int InWordCount)
{
  emit SignalWordCountChanged(InWordCount);
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetSentenceMode(void)
{
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetBlockMode(void)
{
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSetInterlinearMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetInterlinearMode(void)
{
  emit SignalSetInterlinearMode();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetReferenceMode(void)
{
  emit SignalSetReferenceMode();
}

/*****************************************************************************!
 * Function : SlotSetEditMode
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetEditMode(void)
{
  emit SignalSetEditMode();
}

/*****************************************************************************!
 * Function : SlotVerseCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotVerseCountChanged
(int InVerseCount)
{
  emit SignalVerseCountChanged(InVerseCount);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}

/*****************************************************************************!
 * Function : SlotVerticalScrolled
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotVerticalScrolled
(int)
{
  emit SignalVerticalScrolled();
}

/*****************************************************************************!
 * Function : SlotSetMessage
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetMessage
(QString InMessage)
{
  emit SignalSetMessage(InMessage);
}

/*****************************************************************************!
 * Function : SlotChapterScrolled
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotChapterSelected
(int InChapter)
{
  emit SignalChapterSelected(InChapter);
}

/*****************************************************************************!
 * Function : SlotChapterScrolled
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotChapterScrolled
(int InChapter)
{
  emit SignalChapterScrolled(InChapter);
}

/*****************************************************************************!
 * Function : SlotLocationSelected
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotLocationSelected
(QPoint InLocation)
{
  VScrollBar->setValue(InLocation.y());
}

/*****************************************************************************!
 * Function : SlotSetFormattingType
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotSetFormattingType
(TextDisplayFormattingItem::FormatType InFormattingType)
{
  emit SignalSetFormattingType(InFormattingType);
}

/*****************************************************************************!
 * Function : SlotChapterChanged
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotChapterChanged
(int InNewChapter)
{
  emit SignalChapterChanged(InNewChapter); 
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotChapterArrowSelected
(int InNewChapter)
{
  emit SignalChapterArrowSelected(InNewChapter);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplayViewScrollWindow::SlotWindowChange
(int InType)
{
  emit SignalWindowChange(InType);
}

/*****************************************************************************!
 * Function : keyPressEvent
 *****************************************************************************/
void
TextDisplayViewScrollWindow::keyPressEvent
(QKeyEvent* InEvent)
{
  int                                   key;
  Qt::KeyboardModifiers                 mods;

  key = InEvent->key();
  mods = InEvent->modifiers();

  if ( viewWindow->KeyPress(key, mods) ) {
    return;
  }

  QScrollArea::keyPressEvent(InEvent);
}

/*****************************************************************************!
 * Function : enterEvent
 *****************************************************************************/
void
TextDisplayViewScrollWindow::enterEvent
(QEnterEvent*)
{
  setFocus();
}

