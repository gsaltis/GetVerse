/*****************************************************************************
 * FILE NAME    : TextDisplayViewWindow.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayviewwindow_h_
#define _textdisplayviewwindow_h_

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
#include "TextDisplayViewWindowItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VIEW_WINDOW_X      200
#define TEXT_DISPLAY_VIEW_WINDOW_Y      200
#define TEXT_DISPLAY_VIEW_WINDOW_WIDTH  200
#define TEXT_DISPLAY_VIEW_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayViewWindow
 *****************************************************************************/
class TextDisplayViewWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayViewWindow         ();

 //! Destructor
 public :
  ~TextDisplayViewWindow        ();

 //! Public Methods
 public :
  void                          ClearText               ();
  int                           GetTableHeight          ();
  int                           ArrangeElements         (int InWidth);
  
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
  void                          GetChapter              (int InChapter);
  static int                    GetChapterCB            (void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  void                          AddLine                 (int InChapter, int InVerse, QString InVerseText);
  void                          ComputeSize             ();
  void                          GetMaxReferenceWidth    ();
  
 //! Private Data
 private :
  BookInfo*                     bookInfo;
  int                           textX;
  int                           textY;
  int                           InterLineSkip;
  int                           InterWordSkip;
  int                           rightMargin;
  int                           leftMargin;
  int                           bottomMargin;
  int                           topMargin;
  int                           lineCount;
  QFont                         displayFont;
  int                           referenceWidth;
  int                           tableHeight;
  
  std::vector<TextDisplayViewWindowItem*>       items;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBookInfo);

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayviewwindow_h_*/
