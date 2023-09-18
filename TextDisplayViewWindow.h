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
#include "TextDisplayItem.h"

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

 //! Public Types
 public :
  enum DisplayMode {
    NoneMode                   = 0,
    ReferenceMode,
    BlockMode,
    SentenceMode
  };
    
 //! Public Methods
 public :
  void                          ClearText               ();
  int                           GetTableHeight          ();
  
 //! Public Data
 public :

 //! Protected Methods
 protected :
  void                          paintEvent              (QPaintEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          mouseMoveEvent          (QMouseEvent* InEvent);
  void                          SetBook                 ();
  static int                    SetBookCB               (void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  void                          AddLineText             (int InChapter, int InVerse, QString InVerseText);
  QSize                         ComputeSize             ();
  void                          GetMaxReferenceWidth    ();
  int                           GetVerseCount           ();
  int                           GetFormattingByReference(int InBook, int InChapter, int InVerse);
  void                          PaintReferenceMode      (QPainter* InPainter, QRect InRect);
  void                          PaintSentenceMode       (QPainter* InPainter, QRect InRect);
  void                          PaintBlockMode          (QPainter* InPainter, QRect InRect);
  void                          ArrangeItems            ();
  int                           ArrangeItemsReference   (int InX, int InY, int InWindowWidth);
  int                           ArrangeItemsBlock       (int InX, int InY, int InWindowWidth);
  int                           ArrangeItemsSentence    (int InX, int InY, int InWindowWidth);

 //! Private Data
 private :
  BookInfo*                     bookInfo;
  int                           textX;
  int                           textY;
  int                           InterLineSkip;
  int                           InterWordSkip;
  int                           InterParagraphSkip;
  int                           rightMargin;
  int                           leftMargin;
  int                           bottomMargin;
  int                           topMargin;
  int                           lineCount;
  QFont                         displayFont;
  int                           referenceWidth;
  int                           tableHeight;
  int                           verseCount;
  int                           tmpVerseCount;
  int                           tmpSentenceCount;
  int                           wordCount;
  DisplayMode                   mode;
  TextDisplayItem*              lastSelectedItem;
  bool                          repaintOnlySelected;
  QSize                         tableSize;
  std::vector<TextDisplayItem*> textItems;
  QSize                         windowSize;  
  int                           sentenceIndent;

 //! Public Slots
 public slots :
  void                          SlotBookSelected                (BookInfo* InBookInfo);
  void                          SlotSetSentenceMode             (void);
  void                          SlotSetBlockMode                (void);
  void                          SlotSetReferenceMode            (void);
  void                          SlotVerticalScrolled            (void);
  
 //! Public Signals
 signals :
  void                          SignalHideProgressBar           (void);
  void                          SignalShowProgressBar           (void);
  void                          SignalSetProgressBar            (int InMin, int InMax);
  void                          SignalUpdateProgressBar         (int InValue);
  void                          SignalWordCountChanged          (int InWordCount);
  void                          SignalSetSentenceMode           (void);
  void                          SignalSetReferenceMode          (void);
  void                          SignalSetBlockMode              (void);
  void                          SignalVerseCountChanged         (int InVerseCount);
  void                          SignalSentenceCountChanged      (int InSentenceCount);

 //! Public Actions
 public :

};

#endif /* _textdisplayviewwindow_h_*/
