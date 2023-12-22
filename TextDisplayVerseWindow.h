/*****************************************************************************
 * FILE NAME    : TextDisplayVerseWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayversewindow_h_
#define _textdisplayversewindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"
#include "TextDisplayVerseItem.h"
#include "TextDisplayVerseReferenceItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VERSE_WINDOW_X     200
#define TEXT_DISPLAY_VERSE_WINDOW_Y     200
#define TEXT_DISPLAY_VERSE_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VERSE_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayVerseWindow
 *****************************************************************************/
class TextDisplayVerseWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayVerseWindow        ();

 //! Destructor
 public :
  ~TextDisplayVerseWindow       ();

 //! Public Methods
 public :
  int                           ArrangeItems            ();
  int                           ArrangeItems            (int InWidth);
  void                          ClearDisplayItems       ();

 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          keyPressEvent           (QKeyEvent* InEvent);
  void                          mouseMoveEvent          (QMouseEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          CreateConnections       ();
  void                          InitializeSubWindows    ();
  void                          CreateDisplayItems      ();
  TextDisplayVerseReferenceItem* FindReferenceByVerseNumber (int InVerseNumber);
  bool                          KeyPress                (int InKey, Qt::KeyboardModifiers InModifiers);

 //! Private Data
 private :
  int                           Chapter;
  BookInfo*                     Book;
  QFont                         DisplayFont;
  QList<TextDisplayVerseItem*>  DisplayItems;
  QFont                         ReferenceFont;
  QColor                        DisplayColor;
  QColor                        ReferenceColor;
  QColor                        BackgroundColor;
  int                           LeftMargin;
  int                           LeftIndent;
  int                           TopMargin;
  int                           RightMargin;
  int                           HorizontalSkip;
  QList<TextDisplayVerseReferenceItem*> ReferenceItems;
  int                           maxChapters;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);
  void                          SlotChapterSelected     (int InChapter);
  void                          SlotReferenceSelected   (int InVerseNumber);

 //! Public Signals
 signals :
  void                          SignalWindowChange      (int InNewWindow);
  void                          SignalSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SignalChapterArrowSelected (int InChapter);

 //! Public Actions
 public :

};

#endif /* _textdisplayversewindow_h_*/
