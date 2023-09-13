/*****************************************************************************
 * FILE NAME    : TextDisplayReferenceWindow.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreferencewindow_h_
#define _textdisplayreferencewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QSvgWidget>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_REFERENCE_WINDOW_X 200
#define TEXT_DISPLAY_REFERENCE_WINDOW_Y 200
#define TEXT_DISPLAY_REFERENCE_WINDOW_WIDTH 200
#define TEXT_DISPLAY_REFERENCE_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayReferenceWindow
 *****************************************************************************/
class TextDisplayReferenceWindow : public QSvgWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayReferenceWindow    ();

 //! Destructor
 public :
  ~TextDisplayReferenceWindow   ();

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
  void                          paintEvent              (QPaintEvent* InEvent);
  void                          GetChapter              (int InChapter);
  static int                    GetChapterCB            (void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);


 //! Private Data
 private :
  BookInfo*                     bookInfo;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo*);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayreferencewindow_h_*/
