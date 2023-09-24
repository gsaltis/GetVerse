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
#include "TextDisplayFormattingItem.h"
#include "TextDisplayReferenceItem.h"
#include "TextDisplayWordItem.h"

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
    EditMode,
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
  void                          mousePressEvent         (QMouseEvent* InEvent);
  void                          resizeEvent             (QResizeEvent* InEvent);
  void                          mouseMoveEvent          (QMouseEvent* InEvent);

 //! Protected Data
 protected :

 //! Private Methods
 private :
  void                          initialize              ();
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          SetBook                 ();
  static int                    SetBookCB               (void* InThisPointer, int InColumnCount, char** InColumnValues, char** InColumnNames);
  void                          AddLineText             (int InChapter, int InVerse, QString InVerseText);
  QSize                         ComputeSize             ();
  void                          GetMaxReferenceWidth    ();
  int                           GetVerseCount           ();
  
  TextDisplayFormattingItem::FormatType
                                GetFormattingByReference        (int InBook, int InChapter, int InVerse);
  TextDisplayFormattingItem::FormatType
                                GetWordFormattingByReference    (int InBook, int InChapter, int InVerse, int InWord);
  TextDisplayFormattingItem::FormatType
                                GetWordFormattingByReference    (TextDisplayWordItem* InItem);
    
  void                          PaintReferenceMode      (QPainter* InPainter, QRect InRect);
  void                          PaintSentenceMode       (QPainter* InPainter, QRect InRect);
  void                          PaintBlockMode          (QPainter* InPainter, QRect InRect);
  void                          PaintEditMode          (QPainter* InPainter, QRect InRect);

  void                          ArrangeItems            ();
  int                           ArrangeItemsReference   (int InX, int InY, int InWindowWidth);
  int                           ArrangeItemsBlock       (int InX, int InY, int InWindowWidth);
  int                           ArrangeItemsEdit        (int InX, int InY, int InWindowWidth);
  int                           ArrangeItemsSentence    (int InX, int InY, int InWindowWidth);
  TextDisplayFormattingItem*    FindReferenceFormattingItem (int InBook, int InChapter, int InVerse);
  TextDisplayFormattingItem*    FindWordFormattingItem  (int InBook, int InChapter, int InVerse, int InWord);
  void                          LineJustify             (int InWindowWidth, int InLineEnd, int InLineStartIndex, int InLineEndIndex);
  int                           LineJustifyPunctuation  (int InLineRemaining, int InLineStartIndex, int InLineEndIndex);
  void                          LineJustifyWords        (int InLineRemaining, int InLineStartIndex, int InLineEndIndex);
  inline bool                   WordEndsInPunctuation   (QString InWord);
  void                          EditModeMouseMove       (QPoint InLocation);
  void                          EditModeMousePress      (QPoint InLocation);
  void                          EditModeReferenceMouseSelect    (TextDisplayReferenceItem* InItem);
  void                          EditModeWordMouseSelect (TextDisplayWordItem* InItem);
  void                          AddFormatting           (int InBook, int InChapter, int InVerse, int InWord, int InFormatting);

  TextDisplayItem*              FindSelectedItem        (QPoint InLocation);
  BookInfo*                     FindBookInfoByIndex     (int InBookIndex);
  TextDisplayReferenceItem*     FindDisplayReferenceByChapterVerse      (int InChapter, int InVerse);

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
  int                           tableWidth;
  int                           verseCount;
  int                           tmpVerseCount;
  int                           tmpSentenceCount;
  int                           wordCount;
  DisplayMode                   mode;
  TextDisplayItem*              lastSelectedItem;
  QSize                         tableSize;
  std::vector<TextDisplayItem*> textItems;
  std::vector<TextDisplayFormattingItem*>       formattingItems;
  
  QSize                         windowSize;  
  int                           sentenceIndent;
  int                           EditViewReferenceIndent;
  
  int                           BlockLeftMargin;
  int                           BlockRightMargin;
  int                           DotsPerInchX;

  int                           EndOfSentencePadding;
  int                           EndOfPhrasePadding;

  bool                          BlockLinesAreJustified;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected                (BookInfo* InBookInfo);
  void                          SlotSetSentenceMode             (void);
  void                          SlotSetBlockMode                (void);
  void                          SlotSetReferenceMode            (void);
  void                          SlotSetEditMode                 (void);
  void                          SlotVerticalScrolled            (void);
  void                          SlotSelectChapter       (int InChapter);
  
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
  void                          SignalSetViewMode               (void);

  void                          SignalVerseCountChanged         (int InVerseCount);
  void                          SignalSentenceCountChanged      (int InSentenceCount);
  void                          SignalSetMessage                (QString InMessage);
  void                          SignalLocationSelected  (QPoint InLocation);

 //! Public Actions
 public :

};

#endif /* _textdisplayviewwindow_h_*/
