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
#include "TextDisplayVerseContainerWindow.h"
#include "TextDisplayInterlinearContainerWindow.h"
#include "TextDisplayReaderViewContainerWindow.h"

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
  void                          SetViewMode             (QString InMode);

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
  void                          BookSelected            (BookInfo* InBookInfo, int InChapter);
  
 //! Private Data
 private :
  SectionHeader*                                header;
  TextDisplayReferenceWindow*                   referenceWindow;

  TextDisplaySentenceContainterWindow*          sentenceWindow;
  TextDisplayVerseContainerWindow*              verseWindow;
  TextDisplayInterlinearContainerWindow*        interlinearWindow;

  TextDisplayViewScrollWindow*                  viewWindow;
  TextControlBar*                               controlBar;
  QString                                       BookName;
  int                                           BookInfoIndex;
  
  TextDisplayReaderViewContainerWindow* readerWindow;

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
  void                          SlotSetReaderMode       (void);
  void                          SlotEnglishChanged      (bool InSet);
  void                          SlotTransliterateChanged (bool InSet);
  void                          SlotMorphologyChanged   (bool InSet);
  void                          SlotStrongsChanged      (bool InSet);
  
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
  void                          SignalSetReaderMode     (void);
  void                          SignalEnglishChanged    (bool InSet);
  void                          SignalTransliterateChanged (bool InSet);
  void                          SignalMorphologyChanged (bool InSet);
  void                          SignalStrongsChanged    (bool InSet);
  
 //! Public Actions
 public :

};

#endif /* _textdisplayouterwindow_h_*/
