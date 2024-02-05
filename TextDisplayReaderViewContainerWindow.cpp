/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewContainerWindow.cpp
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
#include "TextDisplayReaderViewContainerWindow.h"

/*****************************************************************************!
 * Function : TextDisplayReaderViewContainerWindow
 *****************************************************************************/
TextDisplayReaderViewContainerWindow::TextDisplayReaderViewContainerWindow
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
 * Function : ~TextDisplayReaderViewContainerWindow
 *****************************************************************************/
TextDisplayReaderViewContainerWindow::~TextDisplayReaderViewContainerWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::CreateSubWindows()
{
  readerWindow = new TextDisplayReaderViewWindow(this);
  header = new ChapterHeaderWindow(this);
  toolBar = new TextDisplayReaderToolBar(this);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::CreateConnections()
{
  connect(this,  
          TextDisplayReaderViewContainerWindow::SignalBookSelected,
          readerWindow,
          TextDisplayReaderViewWindow::SlotBookSelected);
  connect(this,
          TextDisplayReaderViewContainerWindow::SignalTotalChaptersChanged,
          header,
          ChapterHeaderWindow::SlotTotalChaptersChanged);
  connect(this,
          TextDisplayReaderViewContainerWindow::SignalChapterSelected,
          header,
          ChapterHeaderWindow::SlotChapterSelected);

  //! 
  connect(toolBar,
          TextDisplayReaderToolBar::SignalTextColorSet,
          this,
          TextDisplayReaderViewContainerWindow::SlotTextColorSet);

  connect(toolBar,
          TextDisplayReaderToolBar::SignalTextBackgroundColorSet,
          this,
          TextDisplayReaderViewContainerWindow::SlotTextBackgroundColorSet);

  connect(toolBar,
          TextDisplayReaderToolBar::SignalTextFontSet,
          this,
          TextDisplayReaderViewContainerWindow::SlotTextFontSet);

  connect(toolBar,
          TextDisplayReaderToolBar::SignalParagraphSet,
          this,
          TextDisplayReaderViewContainerWindow::SlotParagraphSet);

  connect(toolBar,
          TextDisplayReaderToolBar::SignalExtraPushed,
          this,
          TextDisplayReaderViewContainerWindow::SlotExtraPushed);

  //! 
  connect(this,
          TextDisplayReaderViewContainerWindow::SignalTextColorSet,
          readerWindow,
          TextDisplayReaderViewWindow::SlotTextColorSet);

  connect(this,
          TextDisplayReaderViewContainerWindow::SignalTextBackgroundColorSet,
          readerWindow,
          TextDisplayReaderViewWindow::SlotTextBackgroundColorSet);

  connect(this,
          TextDisplayReaderViewContainerWindow::SignalTextFontSet,
          readerWindow,
          TextDisplayReaderViewWindow::SlotTextFontSet);

  connect(this,
          TextDisplayReaderViewContainerWindow::SignalParagraphSet,
          readerWindow,
          TextDisplayReaderViewWindow::SlotParagraphSet);

  connect(this,
          TextDisplayReaderViewContainerWindow::SignalExtraPushed,
          readerWindow,
          TextDisplayReaderViewWindow::SlotExtraPushed);
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::InitializeSubWindows()
{
  readerWindow  = NULL;  
  header        = NULL;
  Book          = NULL;
  Chapter       = 0;
  toolBar       = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   toolBarW;
  int                                   toolBarH;
  int                                   toolBarY;
  int                                   toolBarX;
  int                                   headerW;
  int                                   headerH;
  int                                   headerY;
  int                                   headerX;
  int                                   readerWindowW;
  int                                   readerWindowH;
  int                                   readerWindowY;
  int                                   readerWindowX;
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();

  readerWindowX = TEXT_DISPLAY_READER_TOOL_BAR_WIDTH;
  readerWindowY = CHAPTER_HEADER_WINDOW_HEIGHT;
  readerWindowW = width - TEXT_DISPLAY_READER_TOOL_BAR_WIDTH;
  readerWindowH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  readerWindow->move(readerWindowX, readerWindowY);
  readerWindow->resize(readerWindowW, readerWindowH);

  headerX = 0;
  headerY = 0;
  headerW = width - TEXT_DISPLAY_READER_TOOL_BAR_WIDTH;
  headerH = CHAPTER_HEADER_WINDOW_HEIGHT;
  header->move(headerX, headerY);
  header->resize(headerW, headerH);

  toolBarX = 0;
  toolBarY = CHAPTER_HEADER_WINDOW_HEIGHT;
  toolBarW = TEXT_DISPLAY_READER_TOOL_BAR_WIDTH;
  toolBarH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  toolBar->move(toolBarX, toolBarY);
  toolBar->resize(toolBarW, toolBarH);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotBookSelected
(BookInfo* InBookInfo)
{
  QString                               name;

  Book = InBookInfo;
  name = Book->GetName();
  emit SignalBookSelected(InBookInfo);
  emit SignalTotalChaptersChanged(InBookInfo->GetChapterCount());
  emit SignalChapterSelected(1);
}

/*****************************************************************************!
 * Function : SlotTextColorSet
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotTextColorSet
(QColor InTextColor)
{
  emit SignalTextColorSet(InTextColor);  
}

/*****************************************************************************!
 * Function : SlotTextBackgroundColorSet
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotTextBackgroundColorSet
(QColor InColor)
{
  emit SignalTextBackgroundColorSet(InColor);  
}

/*****************************************************************************!
 * Function : SlotTextFontSet
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotTextFontSet
(QFont InFont)
{
  emit SignalTextFontSet(InFont);  
}

/*****************************************************************************!
 * Function : SlotParagraphSet
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotParagraphSet
(int InLeftIndent, int InRightIndent, int InTopIndent, int InBottomIndent
)
{
  emit SignalParagraphSet(InLeftIndent, InRightIndent, InTopIndent, InBottomIndent);
}

/*****************************************************************************!
 * Function : SlotExtraPushed
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::SlotExtraPushed
()
{
  emit SignalExtraPushed();  
}
