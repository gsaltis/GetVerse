/*****************************************************************************
 * FILE NAME    : TextDisplayVerseScrollWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayversescrollwindow_h_
#define _textdisplayversescrollwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QScrollArea>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayVerseWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VERSE_SCROLL_WINDOW_X 200
#define TEXT_DISPLAY_VERSE_SCROLL_WINDOW_Y 200
#define TEXT_DISPLAY_VERSE_SCROLL_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VERSE_SCROLL_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayVerseScrollWindow
 *****************************************************************************/
class TextDisplayVerseScrollWindow : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayVerseScrollWindow  ();

 //! Destructor
 public :
  ~TextDisplayVerseScrollWindow ();

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
  TextDisplayVerseWindow*       verseWindow;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);
  void                          SlotChapterSelected     (int InChapter);
  void                          SlotWindowChange        (int InNewWindow);
  void                          SlotSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SlotChapterArrowSelected (int InChapter);
  void                          SlotSetBookmark         (int InBook, int InChapter, int InVerse, int InWordIndex);
  void                          SlotGotoBookChapter     (BookInfo* InBook, int InChapter);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBook);
  void                          SignalChapterSelected   (int InChapter);
  void                          SignalWindowChange      (int InNewWindow);
  void                          SignalSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SignalChapterArrowSelected (int InChapter);
  void                          SignalSetBookmark       (int InBook, int InChapter, int InVerse, int InWordIndex);
  void                          SignalGotoBookChapter   (BookInfo* InBook, int InChapter);

 //! Public Actions
 public :

};

#endif /* _textdisplayversescrollwindow_h_*/
