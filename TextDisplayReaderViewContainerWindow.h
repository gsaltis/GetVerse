/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewContainerWindow.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreaderviewcontainerwindow_h_
#define _textdisplayreaderviewcontainerwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayReaderViewWindow.h"
#include "BookInfo.h"
#include "ChapterHeaderWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_READER_VIEW_CONTAINER_WINDOW_X 200
#define TEXT_DISPLAY_READER_VIEW_CONTAINER_WINDOW_Y 200
#define TEXT_DISPLAY_READER_VIEW_CONTAINER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_READER_VIEW_CONTAINER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayReaderViewContainerWindow
 *****************************************************************************/
class TextDisplayReaderViewContainerWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayReaderViewContainerWindow ();

 //! Destructor
 public :
  ~TextDisplayReaderViewContainerWindow ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          CreateConnections       ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :
  TextDisplayReaderViewWindow*  readerWindow;
  int                           Chapter;
  BookInfo*                     Book;
  ChapterHeaderWindow*          header;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBookInfo);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBookInfo);
  void                          SignalTotalChaptersChanged (int InTotalChapters);
  void                          SignalChapterSelected   (int InChapter);

 //! Public Actions
 public :

};

#endif /* _textdisplayreaderviewcontainerwindow_h_*/
