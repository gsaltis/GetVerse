/*****************************************************************************
 * FILE NAME    : TextDisplayViewContainerWindow.h
 * DATE         : September 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewcontainerwindow_h_
#define _textdisplayviewcontainerwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VIEW_CONTAINER_WINDOW_X 200
#define TEXT_DISPLAY_VIEW_CONTAINER_WINDOW_Y 200
#define TEXT_DISPLAY_VIEW_CONTAINER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VIEW_CONTAINER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewContainerWindow
 *****************************************************************************/
class TextDisplayViewContainerWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewContainerWindow ();

 //! Destructor
 public :
  ~TextDisplayViewContainerWindow ();

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

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayviewcontainerwindow_h_*/
