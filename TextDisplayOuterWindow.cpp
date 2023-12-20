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

  referenceWindow = new TextDisplayReferenceWindow();
  referenceWindow->setParent(this);
  referenceWindow->hide();

  viewWindow = new TextDisplayViewScrollWindow();
  viewWindow->setParent(this);

  sentenceWindow = new TextDisplaySentenceContainterWindow();
  sentenceWindow->setParent(this);
  sentenceWindow->hide();
  
  controlBar = new TextControlBar();
  controlBar->setParent(this);

  verseWindow = new TextDisplayVerseContainerWindow();
  verseWindow->setParent(this);
  verseWindow->hide();
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
  verseWindow = NULL;
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayOuterWindow::resizeEvent
(QResizeEvent* InEvent)
{
  int                                   verseWindowW;
  int                                   verseWindowH;
  int                                   verseWindowY;
  int                                   verseWindowX;
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
  controlBar->SlotSetChapter(InChapter);
  controlBar->SlotSetChapterSelectMax(InBookInfo->chapters);
  emit SignalBookSelected(InBookInfo);
  emit SignalBookIndexSelected(InBookInfo->GetIndex());
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
  
  connect(controlBar,
          TextControlBar::SignalInterlinearWordChanged,
          viewWindow,
          TextDisplayViewScrollWindow::SlotInterlinearWordSelected);

          connect(viewWindow,
          TextDisplayViewScrollWindow::SignalWindowChange,
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
  
  connect(this,
          TextDisplayOuterWindow::SignalBookSelected,
          sentenceWindow,
          TextDisplaySentenceContainterWindow::SlotBookSet);

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
  sentenceWindow->show();
  emit SignalSetSentenceMode();
}

/*****************************************************************************!
 * Function : SlotSetBlockMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetBlockMode(void)
{
  viewWindow->show();
  verseWindow->hide();
  sentenceWindow->hide();
  emit SignalSetBlockMode();
}

/*****************************************************************************!
 * Function : SlotSetInterlinearMode
 *****************************************************************************/
void
TextDisplayOuterWindow::SlotSetInterlinearMode(void)
{
  viewWindow->show();
  verseWindow->hide();
  sentenceWindow->hide();
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
  sentenceWindow->hide();
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
  verseWindow->hide();
  emit SignalSetEditMode();
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
