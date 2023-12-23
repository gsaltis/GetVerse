/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearScrollWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearscrollwindow_h_
#define _textdisplayinterlinearscrollwindow_h_

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
#include "TextDisplayInterlinearWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_INTERLINEAR_SCROLL_WINDOW_X 200
#define TEXT_DISPLAY_INTERLINEAR_SCROLL_WINDOW_Y 200
#define TEXT_DISPLAY_INTERLINEAR_SCROLL_WINDOW_WIDTH 200
#define TEXT_DISPLAY_INTERLINEAR_SCROLL_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearScrollWindow
 *****************************************************************************/
class TextDisplayInterlinearScrollWindow : public QScrollArea
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayInterlinearScrollWindow  ();

 //! Destructor
 public :
  ~TextDisplayInterlinearScrollWindow ();

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
  TextDisplayInterlinearWindow* verseWindow;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);
  void                          SlotChapterSelected     (int InChapter);
  void                          SlotWindowChange        (int InNewWindow);
  void                          SlotSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SlotChapterArrowSelected (int InChapter);

 //! Public Signals
 signals :
  void                          SignalBookSelected      (BookInfo* InBook);
  void                          SignalChapterSelected   (int InChapter);
  void                          SignalWindowChange      (int InNewWindow);
  void                          SignalSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SignalChapterArrowSelected (int InChapter);

 //! Public Actions
 public :

};

#endif /* _textdisplayinterlinearscrollwindow_h_*/
