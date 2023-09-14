/*****************************************************************************
 * FILE NAME    : TextDisplayViewScrollWindow.h
 * DATE         : September 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewscrollwindow_h_
#define _textdisplayviewscrollwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QScrollArea>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VIEW_SCROLL_WINDOW_X 200
#define TEXT_DISPLAY_VIEW_SCROLL_WINDOW_Y 200
#define TEXT_DISPLAY_VIEW_SCROLL_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VIEW_SCROLL_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewScrollWindow
 *****************************************************************************/
class TextDisplayViewScrollWindow : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewScrollWindow   ();

 //! Destructor
 public :
  ~TextDisplayViewScrollWindow  ();

 //! Public Methods
 public :
  void                          ClearText               (void);

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
  TextDisplayViewWindow*        viewWindow;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBookInfo);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBookInfo);

 //! Public Actions
 public :

};

#endif /* _textdisplayviewscrollwindow_h_*/
