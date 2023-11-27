/*****************************************************************************
 * FILE NAME    : TextDisplayWindow.h
 * DATE         : November 26 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplaywindow_h_
#define _textdisplaywindow_h_

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
#define TEXT_DISPLAY_WINDOW_X           200
#define TEXT_DISPLAY_WINDOW_Y           200
#define TEXT_DISPLAY_WINDOW_WIDTH       200
#define TEXT_DISPLAY_WINDOW_HEIGHT      200

/*****************************************************************************!
 * Exported Class : TextDisplayWindow
 *****************************************************************************/
class TextDisplayWindow : public QWidget
{
 //! Constructors
 public :
  TextDisplayWindow             ();

 //! Destructor
 public :
  ~TextDisplayWindow            ();

 //! Public Methods
 public :

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          keyPressEvent           (QKeyEvent* InEvent);
  void                          enterEvent              (QEnterEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  bool                          KeyPress                (int InKey, Qt::KeyboardModifiers InModifiers);

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalWindowChange      (int InType);
  
 //! Public Actions
 public :

};

#endif /* _textdisplaywindow_h_*/
