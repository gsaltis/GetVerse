/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearContainerWindow.cpp
 * DATE         : December 18 2023
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

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayInterlinearContainerWindow.h"

/*****************************************************************************!
 * Function : TextDisplayInterlinearContainerWindow
 *****************************************************************************/
TextDisplayInterlinearContainerWindow::TextDisplayInterlinearContainerWindow
() : QWidget()
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(255, 255, 255)));
  setPalette(pal);
  setAutoFillBackground(true);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayInterlinearContainerWindow
 *****************************************************************************/
TextDisplayInterlinearContainerWindow::~TextDisplayInterlinearContainerWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::initialize()
{
  Book = NULL;
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::CreateSubWindows()
{
  interlinearWindow = new TextDisplayInterlinearScrollWindow();  
  interlinearWindow->setParent(this);
  header = new ChapterHeaderWindow("Chapter", this);
  wordSelect = new TextDisplayInterlinearWordSelect();
  wordSelect->setParent(this);
  wordSelect->hide();
  DisplayWordSelect = false;
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::InitializeSubWindows()
{
  interlinearWindow = NULL;
  header = NULL;
  wordSelect = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::resizeEvent
(QResizeEvent* InEvent)
{
  PerformResize(InEvent->size());
}

/*****************************************************************************!
 * Function : PerformResize
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::PerformResize
(QSize InSize)
{
  int                                   wordSelectW;
  int                                   wordSelectH;
  int                                   wordSelectY;
  int                                   wordSelectX;
  
  int                                   headerW;
  int                                   headerH;
  int                                   headerY;
  int                                   headerX;

  int                                   interlinearWindowW;
  int                                   interlinearWindowH;
  int                                   interlinearWindowY;
  int                                   interlinearWindowX;

  int					width;
  int					height;

  width = InSize.width();
  height = InSize.height();

  interlinearWindowX = 0;
  interlinearWindowY = CHAPTER_HEADER_WINDOW_HEIGHT;

  interlinearWindowW = width;
  if ( DisplayWordSelect ) {
    interlinearWindowW = width - TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_WIDTH;
  }
  interlinearWindowH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  interlinearWindow->move(interlinearWindowX, interlinearWindowY);
  interlinearWindow->resize(interlinearWindowW, interlinearWindowH);

  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = CHAPTER_HEADER_WINDOW_HEIGHT;
  header->move(headerX, headerY);
  header->resize(headerW, headerH);

  if ( DisplayWordSelect ) {
    wordSelectX = interlinearWindowW;
    wordSelectY = CHAPTER_HEADER_WINDOW_HEIGHT;
    wordSelectW = TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_WIDTH;
    wordSelectH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
    wordSelect->move(wordSelectX, wordSelectY);
    wordSelect->resize(wordSelectW, wordSelectH);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::CreateConnections(void)
{
  connect(wordSelect,
          TextDisplayInterlinearWordSelect::SignalCloseStrongsReference,
          this,
          TextDisplayInterlinearContainerWindow::SlotCloseStrongsReference);
  
  connect(interlinearWindow,
          TextDisplayInterlinearScrollWindow::SignalSelectStrongsWord,
          this,
          TextDisplayInterlinearContainerWindow::SlotSelectStrongsWord);

  connect(this,
          TextDisplayInterlinearContainerWindow::SignalSelectStrongsWord,
          wordSelect,
          TextDisplayInterlinearWordSelect::SlotSelectStrongsWord);
  
  connect(this,
          TextDisplayInterlinearContainerWindow::SignalBookSelected,
          interlinearWindow,
          TextDisplayInterlinearScrollWindow::SlotBookSelected);
  connect(this,
          TextDisplayInterlinearContainerWindow::SignalChapterSelected,
          interlinearWindow,
          TextDisplayInterlinearScrollWindow::SlotChapterSelected);
  connect(interlinearWindow,
          TextDisplayInterlinearScrollWindow::SignalWindowChange,
          this,
          TextDisplayInterlinearContainerWindow::SlotWindowChange);
  connect(interlinearWindow,
          TextDisplayInterlinearScrollWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayInterlinearContainerWindow::SlotSetStartupBookmarkInfo);
  connect(interlinearWindow,
          TextDisplayInterlinearScrollWindow::SignalChapterArrowSelected,
          this,
          TextDisplayInterlinearContainerWindow::SlotChapterArrowSelected);

          
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotBookSelected
(BookInfo* InBook)
{
  Book = InBook;
  emit SignalBookSelected(InBook);
  emit SignalChapterSelected(1);
}

/*****************************************************************************!
 * Function : SlotChapterSelected
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotChapterSelected
(int InChapter)
{
  QString                               chapterText;
  QString                               name;

  name = "";
  if ( Book ) {
    name = Book->GetName();
  }
  chapterText = QString("%1 %2").arg(name).arg(InChapter);
  header->SetText(chapterText);
  emit SignalChapterSelected(InChapter);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotWindowChange
(int InNewWindow)
{
  emit SignalWindowChange(InNewWindow);  
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);  
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotChapterArrowSelected
(int InChapter)
{
  emit SignalChapterArrowSelected(InChapter);  
}

/*****************************************************************************!
 * Function : SlotSelectStrongsWord
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotSelectStrongsWord
(QString InStrongsWord)
{
  QSize                                 s = size();
  int                           width = s.width();
  int                           height = s.height();

  DisplayWordSelect = true;
  wordSelect->show();
  resize(width, height-1);
  resize(width, height);
  emit SignalSelectStrongsWord(InStrongsWord);
}

/*****************************************************************************!
 * Function : SlotCloseStrongsReference
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::SlotCloseStrongsReference(void)
{
  QSize                         s = size();
  int                           width = s.width();
  int                           height = s.height();
  
  DisplayWordSelect = false;
  wordSelect->hide();
  resize(width, height-1);
  resize(width, height);
}
