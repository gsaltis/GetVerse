/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceContainterWindow.h
 * DATE         : November 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplaysentencecontainterwindow_h_
#define _textdisplaysentencecontainterwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplaySentenceWindow.h"
#include "ChapterHeaderWindow.h"
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_SENTENCE_CONTAINTER_WINDOW_X 200
#define TEXT_DISPLAY_SENTENCE_CONTAINTER_WINDOW_Y 200
#define TEXT_DISPLAY_SENTENCE_CONTAINTER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_SENTENCE_CONTAINTER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplaySentenceContainterWindow
 *****************************************************************************/
class TextDisplaySentenceContainterWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplaySentenceContainterWindow ();

 //! Destructor
 public :
  ~TextDisplaySentenceContainterWindow ();

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
  TextDisplaySentenceWindow*    sentenceWindow;
  ChapterHeaderWindow*          headerWindow;
  BookInfo*                     bookInfo;
  
 //! Public Slots
 public slots :
  void                          SlotBookSet             (BookInfo* InBookInfo);
  void                          SlotChapterSet          (int InChapter);

 //! Public Signals
 signals :
  void                          SignalBookSet           (BookInfo* InBookInfo);
  void                          SignalChapterSet        (int InChapter);
  void                          SignalChapterTextChanged(QString InChapterText);

 //! Public Actions
 public :

};

#endif /* _textdisplaysentencecontainterwindow_h_*/
