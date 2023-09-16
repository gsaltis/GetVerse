/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindowReferenceItem.h
 * DATE         : September 13 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewwindowreferenceitem_h_
#define _textdisplayviewwindowreferenceitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayViewWindowItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VIEW_WINDOW_REFERENCE_ITEM_X 200
#define TEXT_DISPLAY_VIEW_WINDOW_REFERENCE_ITEM_Y 200
#define TEXT_DISPLAY_VIEW_WINDOW_REFERENCE_ITEM_WIDTH 200
#define TEXT_DISPLAY_VIEW_WINDOW_REFERENCE_ITEM_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewWindowReferenceItem
 *****************************************************************************/
class TextDisplayViewWindowReferenceItem : public TextDisplayViewWindowItem
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewWindowReferenceItem (QString InText, int InBookIndex, int InChapter, int InVerse,
                                      int InX, int InY, QSize InSize);

 //! Destructor
 public :
  ~TextDisplayViewWindowReferenceItem ();

 //! Public Methods
 public :
  int                           GetWordCount            (void);
  void                          SetWordCount            (int InWordCount);
  int                           GetVerse                ();
  int                           GetChapter              ();
  int                           GetBookIndex            ();

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
  void                          enterEvent              (QEnterEvent* InEvent);
  void                          leaveEvent              (QEvent* InEvent);
  void                          mousePressEvent         (QMouseEvent* InEvent);

 //! Private Data
 private :
  int                           WordCount;
  int                           BookIndex;
  int                           Chapter;
  int                           Verse;
  
 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayviewwindowreferenceitem_h_*/
