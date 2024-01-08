/*****************************************************************************
 * FILE NAME    : TextDisplayOuterWindow.cpp
 * DATE         : September 12 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayOuterWindow.h"
#include "Common.h"

/*****************************************************************************!
 * Function : TextDisplayOuterWindow
 *****************************************************************************/
TextDisplayOuterWindow::TextDisplayOuterWindow
(QString InBookName) : QFrame()
{
  QPalette pal;
  BookInfo*                     bookInfo;

  BookInfoIndex = -1;
  BookName = InBookName;
  if ( !BookName.isEmpty() ) {
    bookInfo = FindBookInfoByName(InBookName);
    if ( bookInfo ) {
      BookInfoIndex = bookInfo->index;
    }
  }
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(224, 224, 224)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShadow(QFrame::Sunken);
  setFrameStyle(QFrame::Panel);
  initialize();
  if ( BookInfoIndex > -1 ) {
    SlotBookSelected(BookInfoIndex);
  }
}

/*****************************************************************************!
 * Function : ~TextDisplayOuterWindow
 *****************************************************************************/
TextDisplayOuterWindow::~TextDisplayOuterWindow
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayOuterWindow::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayOuterWindow::CreateSubWindows()
{
  header = new SectionHeader();
  header->SetText("----");
  header->setParent(this);

  controlBar = new TextControlBar();
  controlBar->setParent(this);

  referenceWindow = new TextDisplayReferenceWindow();
  referenceWindow->setParent(this);
  referenceWindow->hide();

  viewWindow = new TextDisplayViewScrollWindow();
  viewWindow->setParent(this);
  viewWindow->hide();
  
  sentenceWindow = new TextDisplaySentenceContainterWindow();
  sentenceWindow->setParent(this);
  sentenceWindow->hide();
  
  verseWindow = new TextDisplayVerseContainerWindow();
  verseWindow->setParent(this);
  verseWindow->show();

  interlinearWindow = new TextDisplayInterlinearContainerWindow();
  interlinearWindow->setParent(this);
  interlinearWindow->hide();

  readerWindow = new TextDisplayReaderViewContainerWindow();
  readerWindow->setParent(this);
  readerWindow->hide();
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayOuterWindow::InitializeSubWindows()
{
  header                = NULL;
  referenceWindow       = NULL;
  sentenceWindow        = NULL;
  viewWindow            = NULL;
  controlBar            = NULL;
  verseWindow           = NULL;
  interlinearWindow     = NULL;
  readerWindow          = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayOuterWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   readerWindowW;
  int                                   readerWindowH;
  int                                   readerWindowY;
  int                                   readerWindowX;
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
  int                                   interlinearWindowW;
  int                                   interlinearWindowH;
  int                                   interlinearWindowY;
  int                                   interlinearWindowX;
  int                                   headerH;
  int                                   headerW;
  int                                   headerY;
  int                                   headerX;
  int                                   referenceWindowX;
  int                                   referenceWindowY;
  int                                   referenceWindowW;
  int                                   referenceWindowH;
  int                                   viewWindowX;
  int                                   viewWindowY;
  int                                   viewWindowW;
  int                                   viewWindowH;
  QSize					size;  
  int					width;
  int					height;
  int                                   controlBarX;
  int                                   controlBarY;
  int                                   controlBarW;
  int                                   controlBarH;
  int                                   sentenceWindowX;
  int                                   sentenceWindowY;
  int                                   sentenceWindowW;
  int                                   sentenceWindowH;
  
  size = InEvent->size();
  width = size.width();
  height = size.height();

  //!
  headerX = 0;
  headerY = 0;
  headerW = width;
  headerH = SECTION_HEADER_HEIGHT;
  
  //!
  controlBarX = 0;
  controlBarY = SECTION_HEADER_HEIGHT;
  controlBarH = TEXT_CONTROL_BAR_HEIGHT;
  controlBarW = width;

  //!
  referenceWindowX = 0;
  referenceWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  referenceWindowW = width;
  referenceWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);

  //!
  viewWindowX = 0;
  viewWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  viewWindowW = width;
  viewWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);

  //!
  sentenceWindowX = 0;
  sentenceWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  sentenceWindowW = width;
  sentenceWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);

  verseWindowX = 0;
  verseWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  verseWindowW = width;
  verseWindowH = height - (SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT);
  
  interlinearWindowX = 0;
  interlinearWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  interlinearWindowW = width;
  interlinearWindowH = height - (SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT);

  readerWindowX = 0;
  readerWindowY = SECTION_HEADER_HEIGHT + TEXT_CONTROL_BAR_HEIGHT;
  readerWindowW = width;
  readerWindowH = height - (TEXT_CONTROL_BAR_HEIGHT + SECTION_HEADER_HEIGHT);
    
  //!
  if ( header ) {
    header->move(headerX, headerY);
    header->resize(headerW, headerH);
  }

  if ( referenceWindow ) {
    referenceWindow->move(referenceWindowX, referenceWindowY);
    referenceWindow->resize(referenceWindowW, referenceWindowH);
  }
  if ( viewWindow ) {
    viewWindow->move(viewWindowX, viewWindowY);
    viewWindow->resize(viewWindowW, viewWindowH);
  }
  if ( sentenceWindow ) {
    sentenceWindow->move(sentenceWindowX, sentenceWindowY);
    sentenceWindow->resize(sentenceWindowW, sentenceWindowH);
  }
  if ( controlBar ) {
    controlBar->move(controlBarX, controlBarY);
    controlBar->resize(controlBarW, controlBarH);
  }
  
  verseWindow->move(verseWindowX, verseWindowY);
  verseWindow->resize(verseWindowW, verseWindowH);

  interlinearWindow->move(interlinearWindowX, interlinearWindowY);
  interlinearWindow->resize(interlinearWindowW, interlinearWindowH);

  readerWindow->move(readerWindowX, readerWindowY);
  readerWindow->resize(readerWindowW, readerWindowH);
}

/*****************************************************************************!
 * Function : SlotBookSelected
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotBookSelected
(int InBookIndex)
{
  BookInfo*                             bookInfo;

  bookInfo = MainBookInfo->FindBookByIndex(InBookIndex);
  if ( NULL == bookInfo ) {
    return;
  }
  BookSelected(bookInfo, 1);
}

/*****************************************************************************!
 * Function : BookSelected
 *****************************************************************************/
void
TextDisplayOuterWindow::BookSelected
(BookInfo* InBookInfo, int InChapter)
{
  InBookInfo->ReadVerses();
  header->SetText(InBookInfo->GetCapitalizedBookName());
  viewWindow->ClearText();

  emit SignalBookIndexSelected(InBookInfo->GetIndex());

  emit SignalBookSelected(InBookInfo);
  if ( InChapter > 0 ) {
    controlBar->SlotSetChapter(InChapter);
  }
  controlBar->SlotSetChapterSelectMax(InBookInfo->chapters);
  if ( InChapter > 0 ) {
    emit SignalChapterSelected(InChapter);
  }
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayOuterWindow::CreateConnections(void)
{
  connect(controlBar,
          TextControlBar::SignalBookmarkSelected,
          this,
          TextDisplayOuterWindow::SlotBookmarkSelected);

  connect(this,
          TextDisplayOuterWindow::SignalBookmarkSelected,
          viewWindow,
          TextDisplayViewScrollWindow::SlotBookmarkSelected);
  
  connect(this,
          TextDisplayOuterWindow::SignalDisplayBookMarks,
          controlBar,
          TextControlBar::SlotDisplayBookMarks);
  
  connect(this,
          TextDisplayOuterWindow::SignalClearBookMarks,
          controlBar,
          TextControlBar::SlotClearBookMarks);
  
  connect(viewWindow,
          TextDisplayViewScrollWindow::SignalSetBookMark,
          this,
          TextDisplayOuterWindow::SlotSetBookMark);
  
  connect(viewWindow,
          TextDisplayViewScrollWindow::SignalSetStartupBookmark,
          this,
          TextDisplayOuterWindow::SlotSetStartupBookmarkInfo);
  
  connect(sentenceWindow,
          TextDisplaySentenceContainterWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayOuterWindow::SlotSetStartupBookmarkInfo);
  
  connect(verseWindow,
          TextDisplayVerseContainerWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayOuterWindow::SlotSetStartupBookmarkInfo);
  
  connect(verseWindow,
          TextDisplayVerseContainerWindow::SignalChapterArrowSelected,
          this,
          TextDisplayOuterWindow::SlotChapterArrowSelected);
  
  connect(controlBar,
          TextControlBar::SignalInterlinearWordChanged,
          viewWindow,
          TextDisplayViewScrollWindow::SlotInterlinearWordSelected);

  connect(viewWindow,
          TextDisplayViewScrollWindow::SignalWindowChange,
          this,
          TextDisplayOuterWindow::SlotWindowChange);

  connect(verseWindow,
          TextDisplayVerseContainerWindow::SignalWindowChange,
          this,
          TextDisplayOuterWindow::SlotWindowChange);

  connect(this,
          TextDisplayOuterWindow::SignalWindowChange,
          controlBar,
          TextControlBar::SlotWindowChange);
          
  connect(sentenceWindow,
          TextDisplaySentenceContainterWindow::SignalWindowChange,
          this,
          TextDisplayOuterWindow::SlotWindowChange);
  
  connect(controlBar,
          TextControlBar::SignalSetStartupBookmark,
          this,
          TextDisplayOuterWindow::SlotSetStartupBookmark);

  connect(sentenceWindow,
          TextDisplaySentenceContainterWindow::SignalChapterArrowSelected,
          this,
          TextDisplayOuterWindow::SlotChapterArrowSelected);
  
  connect(viewWindow,
          TextDisplayViewScrollWindow::SignalChapterArrowSelected,
          this,
          TextDisplayOuterWindow::SlotChapterArrowSelected);

  connect(this,
          TextDisplayOuterWindow::SignalBookIndexSelected,
          controlBar,
          TextControlBar::SlotBookSelected);
  
  connect(this,
          TextDisplayOuterWindow::SignalChapterArrowSelected,
          controlBar,
          TextControlBar::SlotChapterArrowSelected);
  
  connect(controlBar,
          TextControlBar::SignalChapterChanged,
          sentenceWindow,
          TextDisplaySentenceContainterWindow::SlotChapterSet);

  connect(this,
          TextDisplayOuterWindow::SignalBookSelected,
          verseWindow,
          TextDisplayVerseContainerWindow::SlotBookSelected);

  connect(controlBar,
          TextControlBar::SignalChapterChanged,
          verseWindow,
          TextDisplayVerseContainerWindow::SlotChapterSelected);

  connect(this,
          TextDisplayOuterWindow::SignalBookSelected,
          sentenceWindow,
          TextDisplaySentenceContainterWindow::SlotBookSet);

  connect(this,
          TextDisplayOuterWindow::SignalBookSelected,
          readerWindow,
          TextDisplayReaderViewContainerWindow::SlotBookSelected);

  connect(controlBar,
          SIGNAL(SignalSetFormattingType(TextDisplayFormattingItem::FormatType)),
          viewWindow,
          SLOT(SlotSetFormattingType(TextDisplayFormattingItem::FormatType)));
  
  connect(viewWindow,
          SIGNAL(SignalChapterSelected(int)),
          this,          
          SLOT(SlotChapterSelected(int)));
  
  connect(viewWindow,
          SIGNAL(SignalChapterScrolled(int)),
          this,
          SLOT(SlotChapterScrolled(int)));

  connect(this,
          SIGNAL(SignalChapterScrolled(int)),
          controlBar,
          SLOT(SlotSetChapter(int)));
  
  connect(this,
          SIGNAL(SignalChapterSelected(int)),
          controlBar,
          SLOT(SlotSetChapter(int)));
#if 0
  connect(this,
          TextDisplayOuterWindow::SignalChapterSelected,
          sentenceWindow,
          TextDisplaySentenceContainterWindow::SlotChapterSet);
#endif  
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          referenceWindow,
          SLOT(SlotBookSelected(BookInfo*)));
  connect(this,
          SIGNAL(SignalBookSelected(BookInfo*)),
          viewWindow,
          SLOT(SlotBookSelected(BookInfo*)));
  connect(viewWindow,
          SIGNAL(SignalSetMessage(QString)),
          this,
          SLOT(SlotSetMessage(QString)));
  connect(viewWindow,
          SIGNAL(SignalShowProgressBar()),
          this,
          SLOT(SlotShowProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalHideProgressBar()),
          this,
          SLOT(SlotHideProgressBar()));
  connect(viewWindow,
          SIGNAL(SignalUpdateProgressBar(int)),
          this,
          SLOT(SlotUpdateProgressBar(int)));
  connect(viewWindow,
          SIGNAL(SignalSetProgressBar(int, int)),
          this,
          SLOT(SlotSetProgressBar(int, int)));

  connect(viewWindow,
          SIGNAL(SignalWordCountChanged(int)),
          this,
          SLOT(SlotWordCountChanged(int)));
  connect(this,
          SIGNAL(SignalWordCountChanged(int)),
          controlBar,
          SLOT(SlotWordCountChanged(int)));
  
  connect(viewWindow,
          SIGNAL(SignalVerseCountChanged(int)),
          this,
          SLOT(SlotVerseCountChanged(int)));
  connect(this,
          SIGNAL(SignalVerseCountChanged(int)),
          controlBar,
          SLOT(SlotVerseCountChanged(int)));

#if 0
  connect(viewWindow,
          SIGNAL(SignalSentenceCountChanged(int)),
          this,
          SLOT(SlotSentenceCountChanged(int)));
#endif
  
  connect(sentenceWindow,
          TextDisplaySentenceContainterWindow::SignalSentenceCountChanged,
          this,
          TextDisplayOuterWindow::SlotSentenceCountChanged);
  
  connect(this,
          SIGNAL(SignalSentenceCountChanged(int)),
          controlBar,
          SLOT(SlotSentenceCountChanged(int)));
  
  connect(controlBar,
          SIGNAL(SignalSetSentenceMode()),
          this,
          SLOT(SlotSetSentenceMode()));

  connect(controlBar,
          SIGNAL(SignalSetReaderMode()),
          this,
          SLOT(SlotSetReaderMode()));

  connect(controlBar,
          SIGNAL(SignalSetReferenceMode()),
          this,
          SLOT(SlotSetReferenceMode()));

  connect(controlBar,
          SIGNAL(SignalSetEditMode()),
          this,
          SLOT(SlotSetEditMode()));

  connect(controlBar,
          SIGNAL(SignalSetBlockMode()),
          this,
          SLOT(SlotSetBlockMode()));

  connect(controlBar,
          SIGNAL(SignalSetInterlinearMode()),
          this,
          SLOT(SlotSetInterlinearMode()));

  connect(this,
          SIGNAL(SignalSetSentenceMode()),
          viewWindow,
          SLOT(SlotSetSentenceMode()));
  connect(this,
          SIGNAL(SignalSetReferenceMode()),
          viewWindow,
          SLOT(SlotSetReferenceMode()));
  connect(this,
          SIGNAL(SignalSetEditMode()),
          viewWindow,
          SLOT(SlotSetEditMode()));
  connect(this,
          SIGNAL(SignalSetBlockMode()),
          viewWindow,
          SLOT(SlotSetBlockMode()));
  connect(this,
          SIGNAL(SignalSetInterlinearMode()),
          viewWindow,
          SLOT(SlotSetInterlinearMode()));

  connect(controlBar,
          SIGNAL(SignalChapterChanged(int)),
          viewWindow,
          SLOT(SlotChapterChanged(int)));

  //!
  connect(interlinearWindow,
          TextDisplayInterlinearContainerWindow::SignalSetStartupBookmarkInfo,
          this,
          TextDisplayOuterWindow::SlotSetStartupBookmarkInfo);
  
  connect(interlinearWindow,
          TextDisplayInterlinearContainerWindow::SignalChapterArrowSelected,
          this,
          TextDisplayOuterWindow::SlotChapterArrowSelected);
  
  connect(interlinearWindow,
          TextDisplayInterlinearContainerWindow::SignalWindowChange,
          this,
          TextDisplayOuterWindow::SlotWindowChange);

  connect(this,
          TextDisplayOuterWindow::SignalBookSelected,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotBookSelected);

  connect(controlBar,
          TextControlBar::SignalChapterChanged,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotChapterSelected);
  
  connect(this,
          TextDisplayOuterWindow::SignalEnglishChanged,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotEnglishChanged);
  
  connect(controlBar,
          TextControlBar::SignalEnglishChanged,
          this,
          TextDisplayOuterWindow::SlotEnglishChanged);

  connect(this,
          TextDisplayOuterWindow::SignalTransliterateChanged,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotTransliterateChanged);

  connect(controlBar,
          TextControlBar::SignalTransliterateChanged,
          this,
          TextDisplayOuterWindow::SlotTransliterateChanged);

  connect(this,
          TextDisplayOuterWindow::SignalStrongsChanged,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotStrongsChanged);
  
  connect(controlBar,
          TextControlBar::SignalStrongsChanged,
          this,
          TextDisplayOuterWindow::SlotStrongsChanged);

  connect(this,
          TextDisplayOuterWindow::SignalMorphologyChanged,
          interlinearWindow,
          TextDisplayInterlinearContainerWindow::SlotMorphologyChanged);
  connect(controlBar,
          TextControlBar::SignalMorphologyChanged,
          this,
          TextDisplayOuterWindow::SlotMorphologyChanged);
}

/*****************************************************************************!
 * Function : SlotShowProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotShowProgressBar(void)
{
  emit SignalShowProgressBar();
}

/*****************************************************************************!
 * Function : SlotHideProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotHideProgressBar(void)
{
  emit SignalHideProgressBar();
}

/*****************************************************************************!
 * Function : SlotUpdateProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotUpdateProgressBar
(int InValue)
{
  emit SignalUpdateProgressBar(InValue);
}

/*****************************************************************************!
 * Function : SlotSetProgressBar
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetProgressBar
(int InMin, int InMax)
{
  emit SignalSetProgressBar(InMin, InMax);
}

/*****************************************************************************!
 * Function : SlotWordCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotWordCountChanged
(int InWordCount)
{
  emit SignalWordCountChanged(InWordCount);
}

/*****************************************************************************!
 * Function : SlotSetSentenceMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetSentenceMode(void)
{
  viewWindow->hide();
  verseWindow->hide();
  interlinearWindow->hide();
  sentenceWindow->show();
  readerWindow->hide();
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetBlockMode(void)
{
  viewWindow->show();
  interlinearWindow->hide();
  verseWindow->hide();
  sentenceWindow->hide();
  readerWindow->hide();
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSetInterlinearMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetInterlinearMode(void)
{
  viewWindow->hide();
  interlinearWindow->show();
  verseWindow->hide();
  sentenceWindow->hide();
  readerWindow->hide();
  emit SignalSetInterlinearMode();
}

/*****************************************************************************!
 * Function : SlotSetReferenceMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetReferenceMode(void)
{
  viewWindow->hide();
  verseWindow->show();
  interlinearWindow->hide();
  sentenceWindow->hide();
  readerWindow->hide();
  emit SignalSetReferenceMode();
}

/*****************************************************************************!
 * Function : SlotSetEditMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetEditMode(void)
{
  viewWindow->show();
  sentenceWindow->hide();
  interlinearWindow->hide();
  verseWindow->hide();
  readerWindow->hide();
  emit SignalSetEditMode();
}

/*****************************************************************************!
 * Function : SlotSetReaderMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetReaderMode(void)
{
  viewWindow->hide();
  sentenceWindow->hide();
  interlinearWindow->hide();
  verseWindow->hide();
  readerWindow->show();
  emit SignalSetReaderMode();
}

/*****************************************************************************!
 * Function : SlotVerseCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotVerseCountChanged
(int InVerseCount)
{
  emit SignalVerseCountChanged(InVerseCount);
}

/*****************************************************************************!
 * Function : SlotSentenceCountChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSentenceCountChanged
(int InSentenceCount)
{
  emit SignalSentenceCountChanged(InSentenceCount);
}

/*****************************************************************************!
 * Function : FindBookInfoByName
 *****************************************************************************/
BookInfo*
TextDisplayOuterWindow::FindBookInfoByName
(QString InBookName)
{
  return MainBookInfo->GetBookByName(InBookName);
}

/*****************************************************************************!
 * Function : SlotSetMessage
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetMessage
(QString InMessage)
{
  emit SignalSetMessage(InMessage);
}

/*****************************************************************************!
 * Function : SlotChapterScrolled
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotChapterSelected
(int InChapter)
{
  emit SignalChapterSelected(InChapter);
}

/*****************************************************************************!
 * Function : SlotChapterScrolled
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotChapterScrolled
(int InChapter)
{
  emit SignalChapterScrolled(InChapter);
}

/*****************************************************************************!
 * Function : SlotSetFormattingType
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetFormattingType
(TextDisplayFormattingItem::FormatType InFormattingType)
{
  emit SignalSetFormattingType(InFormattingType);
}

/*****************************************************************************!
 * Function : SlotChapterArrowSelected
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotChapterArrowSelected
(int InNewChapter)
{
  emit SignalChapterArrowSelected(InNewChapter);
}

/*****************************************************************************!
 * Function : SlotSetSartupBookmark
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetStartupBookmark
(int InBook, int InChapter, int InVerse)
{
  emit SignalSetStartupBookmark(InBook, InChapter, InVerse);
}

/*****************************************************************************!
 * Function : SlotWindowChange
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotWindowChange
(int InType)
{
  emit SignalWindowChange(InType);
}

/*****************************************************************************!
 * Function : SlotSetStartupBookmarkInfo
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetStartupBookmarkInfo
(BookInfo* InBookInfo, int InChapter)
{
  emit SignalSetStartupBookmarkInfo(InBookInfo, InChapter);
}

/*****************************************************************************!
 * Function : SlotSetBookMark
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetBookMark
(BookInfo* InBookInfo, int InChapter, int InVerse, int InWord)
{
  emit SignalSetBookMark(InBookInfo, InChapter, InVerse, InWord);  
}

/*****************************************************************************!
 * Function : SlotClearBookMarks
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotClearBookMarks(void)
{
  emit SignalClearBookMarks();  
}

/*****************************************************************************!
 * Function : SlotDisplayBookMarks
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotDisplayBookMarks(void)
{
  emit SignalDisplayBookMarks();  
}

/*****************************************************************************!
 * Function : SlotBookmarkSelected
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotBookmarkSelected
(BookInfo* InBook, int InChapter, int, int)
{
  BookSelected(InBook, InChapter);
  emit SignalChapterSelected(InChapter);
}

/*****************************************************************************!
 * Function : SlotEnglishChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotEnglishChanged
(bool InSet)
{
  emit SignalEnglishChanged(InSet);
}

/*****************************************************************************!
 * Function : SlotTransliterateChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotTransliterateChanged
(bool InSet)
{
  emit SignalTransliterateChanged(InSet);  
}

/*****************************************************************************!
 * Function : SlotMorphologyChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotMorphologyChanged
(bool InSet)
{
  emit SignalMorphologyChanged(InSet);  
}

/*****************************************************************************!
 * Function : SlotStrongsChanged
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotStrongsChanged
(bool InSet)
{
  emit SignalStrongsChanged(InSet);  
}

/*****************************************************************************!
 * Function : SetViewMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SetViewMode
(QString InMode)
{
  if ( InMode == "verse" ) {
    SlotSetReferenceMode();
    return;
  }
  if ( InMode == "sentence" ) {
    SlotSetSentenceMode();
    return;
  }
  if ( InMode == "reader" ) {
    SlotSetReaderMode();
    return;
  }
  if ( InMode == "interlinear" ) {
    SlotSetInterlinearMode();
    return;
  }
}
