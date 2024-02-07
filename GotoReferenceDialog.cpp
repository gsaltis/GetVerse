/*****************************************************************************
 * FILE NAME    : GotoReferenceDialog.cpp
 * DATE         : February 06 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <trace_winnetqt.h>
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "GotoReferenceDialog.h"
#include "Common.h"

/*****************************************************************************!
 * Function : GotoReferenceDialog
 *****************************************************************************/
GotoReferenceDialog::GotoReferenceDialog
(BookInfo* InBook, int InChapter) : QDialog()
{
  book = InBook;
  chapter = InChapter;
  setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  Initialize();
}

/*****************************************************************************!
 * Function : ~GotoReferenceDialog
 *****************************************************************************/
GotoReferenceDialog::~GotoReferenceDialog
()
{
}

/*****************************************************************************!
 * Function : Initialize
 *****************************************************************************/
void
GotoReferenceDialog::Initialize(void)
{
  QPalette                              pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(128, 128, 128)));
  setPalette(pal);
  CreateSubWindows();  
  CreateConnections();
  resize(GOTO_REFERENCE_DIALOG_WIDTH, GOTO_REFERENCE_DIALOG_HEIGHT);
}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
GotoReferenceDialog::CreateConnections(void)
{
  connect(OKButton, SIGNAL(pressed()), this, SLOT(SlotOKButtonPressed()));  
  connect(CancelButton, SIGNAL(pressed()), this, SLOT(SlotCancelButtonPressed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
GotoReferenceDialog::CreateSubWindows(void)
{
  int                                   bookComboHeight;
  int                                   bookComboWidth;
  int                                   bookComboX;
  int                                   bookComboY;

  int                                   buttonGap;

  int                                   cancelButtonWidth;
  int                                   cancelButtonHeight;
  int                                   cancelButtonX;
  int                                   cancelButtonY;

  int                                   chapterComboX;
  int                                   chapterComboY;
  int                                   chapterComboWidth;
  int                                   chapterComboHeight;

  int                                   elementHeight;
  int                                   elementX;
  int                                   elementY;

  int                                   okButtonWidth;
  int                                   okButtonHeight;
  int                                   okButtonX;
  int                                   okButtonY;

  buttonGap     = 5;
  elementHeight = 20;
  elementY      = 5;
  elementX      = 5;
  
  okButtonWidth         = 40;
  cancelButtonWidth     = 60;
  bookComboWidth        = 120;
  chapterComboWidth     = 50;

  bookComboHeight       = elementHeight;
  bookComboX            = elementX;
  bookComboY            = elementY;
  elementX              += bookComboWidth + buttonGap;
  
  chapterComboHeight    = elementHeight;
  chapterComboY         = elementY;
  chapterComboX         = elementX;
  elementX              += chapterComboWidth + buttonGap;

  okButtonHeight        = elementHeight;
  okButtonX             = elementX;
  okButtonY             = elementY;
  elementX              += okButtonWidth + buttonGap;

  cancelButtonHeight    = elementHeight;
  cancelButtonX         = elementX;
  cancelButtonY         = elementY;
  
  //! 
  OKButton = new QPushButton("OK", this);
  OKButton->move(okButtonX, okButtonY);
  OKButton->resize(okButtonWidth, okButtonHeight);
  
  CancelButton = new QPushButton("Cancel", this);
  CancelButton->move(cancelButtonX, cancelButtonY);
  CancelButton->resize(cancelButtonWidth, cancelButtonHeight);

  //! 
  BookComboBox = new QComboBox(this);
  BookComboBox->move(bookComboX, bookComboY);
  BookComboBox->resize(bookComboWidth, bookComboHeight);

  connect(BookComboBox,
          QComboBox::currentIndexChanged,
          this,
          GotoReferenceDialog::SlotBookComboIndexChanged);

  //! 
  ChapterComboBox = new QComboBox(this);
  ChapterComboBox->move(chapterComboX, chapterComboY);
  ChapterComboBox->resize(chapterComboWidth, chapterComboHeight);

  PopulateBookCombo();
}

/*****************************************************************************!
 * Function : SlotOKButtonPressed
 *****************************************************************************/
void
GotoReferenceDialog::SlotOKButtonPressed()
{
  accept();
}

/*****************************************************************************!
 * Function : SlotCancelButtonPressed
 *****************************************************************************/
void
GotoReferenceDialog::SlotCancelButtonPressed()
{
  reject();
}

/*****************************************************************************!
 * Function : PopulateBookCombo
 *****************************************************************************/
void
GotoReferenceDialog::PopulateBookCombo(void)
{
  BookInfo*                             bookInfo;
  int                                   i;
  int                                   n;
  int                                   index;
  int                                   bookComboIndex;
  BookInfo*                             lastBook;

  lastBook = book;

  MainBookInfo->PopulateBookNameCombo(BookComboBox);
#if 0
  n = MainBookInfo->GetBookCount();
  for (i = 0; i < n; i++) {
    bookInfo = MainBookInfo->GetByIndex(i);
    BookComboBox->addItem(bookInfo->GetCapitalizedBookName(), bookInfo->GetIndex());
  }
#endif
  book = lastBook;
  book->PopulateChapterComboBox(ChapterComboBox);
  index = book->GetIndex();
  bookComboIndex = BookComboBox->findData(index);
  
  BookComboBox->setCurrentIndex(bookComboIndex);
  
  ChapterComboBox->setCurrentIndex(ChapterComboBox->findData(chapter));
}

/*****************************************************************************!
 * Function : GetBook
 *****************************************************************************/
BookInfo*
GotoReferenceDialog::GetBook(void)
{
  BookInfo*                             book;
  int                                   bookIndex;

  bookIndex = BookComboBox->currentData().toInt();
  book = MainBookInfo->GetBookByIndex(bookIndex);
  return book;
}

/*****************************************************************************!
 * Function : GetChapter
 *****************************************************************************/
int
GotoReferenceDialog::GetChapter(void)
{
  int                                   chapter;

  chapter = ChapterComboBox->currentData().toInt();
  return chapter;
}

/*****************************************************************************!
 * Function : SlotBookComboIndexChanged
 *****************************************************************************/
void
GotoReferenceDialog::SlotBookComboIndexChanged
(int )
{
  int                                   bookIndex;
  bookIndex = BookComboBox->currentData().toInt();
  book = MainBookInfo->GetBookByIndex(bookIndex);
  book->PopulateChapterComboBox(ChapterComboBox);
}
