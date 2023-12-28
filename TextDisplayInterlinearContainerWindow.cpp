/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearContainerWindow.cpp
 * DATE         : December 18 2023
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

  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  interlinearWindowX = 0;
  interlinearWindowY = CHAPTER_HEADER_WINDOW_HEIGHT;
  interlinearWindowW = width - TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_WIDTH;
  interlinearWindowH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  interlinearWindow->move(interlinearWindowX, interlinearWindowY);
  interlinearWindow->resize(interlinearWindowW, interlinearWindowH);

  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = CHAPTER_HEADER_WINDOW_HEIGHT;
  header->move(headerX, headerY);
  header->resize(headerW, headerH);

  wordSelectX = interlinearWindowW;
  wordSelectY = 0;
  wordSelectW = TEXT_DISPLAY_INTERLINEAR_WORD_SELECT_WIDTH;
  wordSelectH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  wordSelect->move(wordSelectX, wordSelectY);
  wordSelect->resize(wordSelectW, wordSelectH);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayInterlinearContainerWindow::CreateConnections(void)
{
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

  chapterText = QString("Chapter %1").arg(InChapter);
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
