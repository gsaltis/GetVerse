/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewWindow.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreaderviewwindow_h_
#define _textdisplayreaderviewwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_READER_VIEW_WINDOW_X 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_Y 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_WIDTH 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayReaderViewWindow
 *****************************************************************************/
class TextDisplayReaderViewWindow : public QTextEdit
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayReaderViewWindow   ();

 //! Destructor
 public :
  ~TextDisplayReaderViewWindow  ();

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

 //! Private Data
 private :
  BookInfo*                     Book;
  int                           Chapter;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);
  void                          SlotChapterSelected     (int InChapter);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayreaderviewwindow_h_*/
