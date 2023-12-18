/*****************************************************************************
 * FILE NAME    : TextDisplayOuterWindow.h
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayouterwindow_h_
#define _textdisplayouterwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QFrame>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "SectionHeader.h"
#include "TextDisplayReferenceWindow.h"
#include "BookInfo.h"
#include "TextDisplayViewWindow.h"
#include "TextDisplayViewScrollWindow.h"
#include "TextControlBar.h"
#include "TextDisplaySentenceContainterWindow.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_OUTER_WINDOW_X     200
#define TEXT_DISPLAY_OUTER_WINDOW_Y     200
#define TEXT_DISPLAY_OUTER_WINDOW_WIDTH 200
#define TEXT_DISPLAY_OUTER_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayOuterWindow
 *****************************************************************************/
class TextDisplayOuterWindow : public QFrame
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayOuterWindow        (QString InBookName);

 //! Destructor
 public :
  ~TextDisplayOuterWindow       ();

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
  BookInfo*                     FindBookInfoByName      (QString InBookName);

 //! Private Data
 private :
  SectionHeader*                        header;
  TextDisplayReferenceWindow*           referenceWindow;
  TextDisplaySentenceContainterWindow*  sentenceWindow;
  TextDisplayViewScrollWindow*          viewWindow;
  TextControlBar*                       controlBar;
  QString                               BookName;
  int                                   BookInfoIndex;
  
 //! Public Slots
 public slots :
  void                          SlotBookSelected                (int InBookIndex);
  void                          SlotShowProgressBar             (void);
  void                          SlotHideProgressBar             (void);
  void                          SlotUpdateProgressBar           (int InValue);
  void                          SlotSetProgressBar              (int InMin, int InMax);
  void                          SlotWordCountChanged            (int InWordCount);
  void                          SlotVerseCountChanged           (int InWordCount);
  void                          SlotSentenceCountChanged        (int InWordCount);
  void                          SlotSetSentenceMode             (void);
  void                          SlotSetBlockMode                (void);
  void                          SlotSetInterlinearMode          (void);
  void                          SlotSetReferenceMode            (void);
  void                          SlotSetEditMode                 (void);
  void                          SlotSetMessage                  (QString InMessage);
  void                          SlotChapterScrolled             (int InChapter);
  void                          SlotChapterSelected             (int InChapter);
  void                          SlotSetFormattingType           (TextDisplayFormattingItem::FormatType InFormattingType);
  void                          SlotChapterArrowSelected        (int InNewChapter);
  void                          SlotSetStartupBookmark          (int InBook, int InChapter, int InVerse);
  void                          SlotWindowChange                (int InType);
  void                          SlotSetStartupBookmarkInfo      (BookInfo* InBookInfo, int InChapter);
  void                          SlotSetBookMark         (BookInfo* InBookInfo, int InChapter, int InVerse, int InWord);
  void                          SlotClearBookMarks      (void);
  void                          SlotDisplayBookMarks    (void);
  void                          SlotBookmarkSelected    (BookInfo* InBook, int InChapter, int InVerse, int InWord);
  
 //! Public Signals
 signals :
  void                          SignalBookSelected              (BookInfo*);
  void                          SignalBookIndexSelected         (int InBookIndex);
  void                          SignalHideProgressBar           (void);
  void                          SignalShowProgressBar           (void);
  void                          SignalSetProgressBar            (int InMin, int InMax);
  void                          SignalUpdateProgressBar         (int InValue);
  void                          SignalWordCountChanged          (int InWordCount);
  void                          SignalVerseCountChanged         (int InWordCount);
  void                          SignalSentenceCountChanged      (int InWordCount);
  void                          SignalSetSentenceMode           (void);
  void                          SignalSetReferenceMode          (void);
  void                          SignalSetEditMode               (void);
  void                          SignalSetBlockMode              (void);
  void                          SignalSetInterlinearMode        (void);
  void                          SignalSetMessage                (QString InMessage);
  void                          SignalChapterSelected           (int InCurrentChapter);
  void                          SignalChapterScrolled           (int InCurrentChapter);
  void                          SignalSetFormattingType         (TextDisplayFormattingItem::FormatType InFormattingType);
  void                          SignalChapterArrowSelected      (int InNewChapter);
  void                          SignalSetStartupBookmark        (int InBook, int InChapter, int InVerse);
  void                          SignalWindowChange              (int InType);
  void                          SignalSetStartupBookmarkInfo    (BookInfo* InBookInfo, int InChapter);
  void                          SignalSetBookMark       (BookInfo* InBookInfo, int InChapter, int InVerse, int InWord);
  void                          SignalClearBookMarks    (void);
  void                          SignalDisplayBookMarks  (void);
  void                          SignalBookmarkSelected  (BookInfo* InBook, int InChapter, int InVerse, int InWord);
  
 //! Public Actions
 public :

};

#endif /* _textdisplayouterwindow_h_*/
