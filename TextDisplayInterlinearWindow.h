/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearWindow.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayinterlinearwindow_h_
#define _textdisplayinterlinearwindow_h_

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
#include "TextDisplayInterlinearItem.h"
#include "TextDisplayInterlinearReferenceItem.h"
#include "InterlinearChapter.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_INTERLINEAR_WINDOW_X     200
#define TEXT_DISPLAY_INTERLINEAR_WINDOW_Y     200
#define TEXT_DISPLAY_INTERLINEAR_WINDOW_WIDTH 200
#define TEXT_DISPLAY_INTERLINEAR_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearWindow
 *****************************************************************************/
class TextDisplayInterlinearWindow : public QWidget
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayInterlinearWindow        ();

 //! Destructor
 public :
  ~TextDisplayInterlinearWindow       ();

 //! Public Methods
 public :
  int                           ArrangeItems            ();
  int                           ArrangeItems            (int InWidth);
  int                           ArrangeItemsRightToLeft (int InWidth);
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
  TextDisplayInterlinearReferenceItem* FindReferenceByVerseNumber (int InVerseNumber);
  bool                          KeyPress                (int InKey, Qt::KeyboardModifiers InModifiers);

 //! Private Data
 private :
  int                           Chapter;
  BookInfo*                     Book;
  QList<TextDisplayInterlinearItem*>  DisplayItems;
  QColor                        DisplayColor;
  QColor                        ReferenceColor;
  QColor                        BackgroundColor;
  int                           LeftMargin;
  int                           LeftIndent;
  int                           TopMargin;
  int                           RightMargin;
  int                           HorizontalSkip;
  QList<TextDisplayInterlinearReferenceItem*> ReferenceItems;
  int                           maxChapters;
  InterlinearChapter*           interlinearChapter;
  
  int                           VerticalSkip;
  int                           VerticalSkipSmall;

 //! Public Slots
 public slots :
  void                          SlotBookSelected        (BookInfo* InBook);
  void                          SlotChapterSelected     (int InChapter);
  void                          SlotReferenceSelected   (int InVerseNumber);
  void                          SlotSelectStrongsWord   (QString InStrongsWord);

 //! Public Signals
 signals :
  void                          SignalWindowChange      (int InNewWindow);
  void                          SignalSetStartupBookmarkInfo (BookInfo* InBookInfo, int InChapter);
  void                          SignalChapterArrowSelected (int InChapter);
  void                          SignalSelectStrongsWord (QString InStrongsWord);

 //! Public Actions
 public :

};

#endif /* _textdisplayinterlinearwindow_h_*/
