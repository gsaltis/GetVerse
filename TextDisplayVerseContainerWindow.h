/*****************************************************************************
 * FILE NAME    : TextDisplayVerseContainerWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayversecontainerwindow_h_
#define _textdisplayversecontainerwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayVerseScrollWindow.h"
#include "ChapterHeaderWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_X 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_Y 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayVerseContainerWindow
 *****************************************************************************/
class TextDisplayVerseContainerWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayVerseContainerWindow ();

 //! Destructor
 public :
  ~TextDisplayVerseContainerWindow ();

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
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          CreateConnections       (void);

 //! Private Data
 private :
  TextDisplayVerseScrollWindow* verseWindow;
  ChapterHeaderWindow*          header;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBook);

 //! Public Actions
 public :

};

#endif /* _textdisplayversecontainerwindow_h_*/
