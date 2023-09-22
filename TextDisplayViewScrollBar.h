/*****************************************************************************
 * FILE NAME    : TextDisplayViewScrollBar.h
 * DATE         : September 21 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewscrollbar_h_
#define _textdisplayviewscrollbar_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QScrollBar>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VIEW_SCROLL_BAR_X  200
#define TEXT_DISPLAY_VIEW_SCROLL_BAR_Y  200
#define TEXT_DISPLAY_VIEW_SCROLL_BAR_WIDTH 200
#define TEXT_DISPLAY_VIEW_SCROLL_BAR_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewScrollBar
 *****************************************************************************/
class TextDisplayViewScrollBar : public QScrollBar
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewScrollBar      ();

 //! Destructor
 public :
  ~TextDisplayViewScrollBar     ();

 //! Public Methods
 public :
  int                           GetChapterCount         (void);
  void                          SetChapterCount         (int InChapterCount);

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          mousePressEvent         (QMouseEvent* InEvent);
  void                          mouseMoveEvent          (QMouseEvent* InEvent);
  void                          resizeEvent             (QResizeEvent* InEvent);
  
 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          MouseChapterSelect      (QPoint InPoint);
  
 //! Private Data
 private :
  int                           ChapterCount;

 //! Public Slots
 public slots :

 //! Public Signals
 signals :
  void                          SignalChapterSelected   (int InCurrentChapter);
  void                          SignalChapterScrolled   (int InCurrentChapter);
  
 //! Public Actions
 public :

};

#endif /* _textdisplayviewscrollbar_h_*/
