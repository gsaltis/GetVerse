/*****************************************************************************
 * FILE NAME    : TextDisplayVerseContainerWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayversecontainerwindow_h_
#define _textdisplayversecontainerwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayVerseScrollWindow.h"
#include "ChapterHeaderWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_X 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_Y 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_VERSE_CONTAINER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayVerseContainerWindow
 *****************************************************************************/
class TextDisplayVerseContainerWindow : public QWidget
{
  Q_OBJECT;

  //! Constructors
public :
  TextDisplayVerseContainerWindow ();

  //! Destructor
public :
  ~TextDisplayVerseContainerWindow ();

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
  TextDisplayVerseScrollWindow* verseWindow;
  ChapterHeaderWindow*          header;
  BookInfo*                     Book;

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
  void                          SignalTotalChaptersChanged (int InTotalChapters);
  void                          SignalGotoBookChapter   (BookInfo* InBook, int InChapter);

  //! Public Actions
public :

};

#endif /* _textdisplayversecontainerwindow_h_*/
