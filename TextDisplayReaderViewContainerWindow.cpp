/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewContainerWindow.cpp
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
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
  readerWindow = new TextDisplayReaderViewWindow();  
  readerWindow->setParent(this);
  readerWindow->show();
  header = new ChapterHeaderWindow("Chapter", this);
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
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayReaderViewContainerWindow::resizeEvent
(QResizeEvent* InEvent)
{
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

  readerWindowX = 0;
  readerWindowY = CHAPTER_HEADER_WINDOW_HEIGHT;
  readerWindowW = width;
  readerWindowH = height - CHAPTER_HEADER_WINDOW_HEIGHT;
  readerWindow->move(readerWindowX, readerWindowY);
  readerWindow->resize(readerWindowW, readerWindowH);

  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = CHAPTER_HEADER_WINDOW_HEIGHT;
  header->move(headerX, headerY);
  header->resize(headerW, headerH);
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
  header->SetText(name);
  emit SignalBookSelected(InBookInfo);  
}

