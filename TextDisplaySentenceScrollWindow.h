/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceScrollWindow.h
 * DATE         : November 24 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplaysentencescrollwindow_h_
#define _textdisplaysentencescrollwindow_h_

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
#include "TextDisplaySentenceWindow.h"
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_SENTENCE_SCROLL_WINDOW_X 200
#define TEXT_DISPLAY_SENTENCE_SCROLL_WINDOW_Y 200
#define TEXT_DISPLAY_SENTENCE_SCROLL_WINDOW_WIDTH 200
#define TEXT_DISPLAY_SENTENCE_SCROLL_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplaySentenceScrollWindow
 *****************************************************************************/
class TextDisplaySentenceScrollWindow : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplaySentenceScrollWindow ();

 //! Destructor
 public :
  ~TextDisplaySentenceScrollWindow ();

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
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          keyPressEvent           (QKeyEvent* InEvent);
  
 //! Private Data
 private :
  TextDisplaySentenceWindow*    sentenceWindow;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBookInfo);
  void                          SlotChapterChanged      (int InChapter);
  void                          SlotSentenceCountChanged        (int InSentenceCount);
  void                          SlotChapterArrowSelected        (int InChapter);
  void                          SlotWindowChange        (int InType);
  
 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBookInfo);
  void                          SignalChapterChanged    (int InChapter);
  void                          SignalSentenceCountChanged      (int InSentenceCount);
  void                          SignalChapterArrowSelected      (int InChapter);
  void                          SignalWindowChange      (int InType);
  
 //! Public Actions
 public :

};

#endif /* _textdisplaysentencescrollwindow_h_*/
