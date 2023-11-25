/*****************************************************************************
 * FILE NAME    : TextDisplaySentenceWindow.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplaysentencewindow_h_
#define _textdisplaysentencewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QWidget>
#include <QPlainTextEdit>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"
#include "TextDisplayWordItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplaySentenceWindow
 *****************************************************************************/
class TextDisplaySentenceWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplaySentenceWindow     ();

 //! Destructor
 public :
  ~TextDisplaySentenceWindow    ();

 //! Public Types
 public :
    
 //! Public Methods
 public :
  int                           GetWindowHeight         ();
  void                          CreateDisplayItems      ();
  int                           ArrangeItems            (int InWidth);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          paintEvent              (QPaintEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          mouseMoveEvent          (QMouseEvent* InEvent);
  void                          keyPressEvent           (QKeyEvent* InEvent);
  void                          enterEvent              (QEnterEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          Initialize              ();
  void                          ClearDisplayItems       ();
  bool                          KeyPress                (int InKey, Qt::KeyboardModifiers);

 //! Private Data
 private :
  BookInfo*                     bookInfo;
  int                           currentChapter;
  QList<TextDisplayWordItem*>   displayItems;
  int                           leftMargin;
  int                           rightMargin;
  int                           interWordSkip;
  int                           sentenceInterLineSkip;
  int                           bottomMargin;
  int                           topMargin;
  QFont                         displayFont;
  int                           maxChapters;
  int                           windowHeight;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBookInfo);
  void                          SlotChapterChanged      (int InChapter);
  
 //! Public Signals
 signals :
  void                          SignalSentenceCountChanged      (int InSentenceCount);
  void                          SignalChapterArrowSelected      (int InChapter);
  
 //! Public Actions
 public :

};

#endif /* _textdisplaysentencewindow_h_*/
