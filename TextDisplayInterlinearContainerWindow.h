/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearContainerWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearcontainerwindow_h_
#define _textdisplayinterlinearcontainerwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayInterlinearScrollWindow.h"
#include "ChapterHeaderWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_INTERLINEAR_CONTAINER_WINDOW_X 200
#define TEXT_DISPLAY_INTERLINEAR_CONTAINER_WINDOW_Y 200
#define TEXT_DISPLAY_INTERLINEAR_CONTAINER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_INTERLINEAR_CONTAINER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearContainerWindow
 *****************************************************************************/
class TextDisplayInterlinearContainerWindow : public QWidget
{
  Q_OBJECT;

  //! Constructors
public :
  TextDisplayInterlinearContainerWindow ();

  //! Destructor
public :
  ~TextDisplayInterlinearContainerWindow ();

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
  TextDisplayInterlinearScrollWindow* interlinearWindow;
  ChapterHeaderWindow*          header;

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

#endif /* _textdisplayinterlinearcontainerwindow_h_*/