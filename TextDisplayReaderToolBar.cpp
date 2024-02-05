/*****************************************************************************
 * FILE NAME    : TextDisplayReaderToolBar.cpp
 * DATE         : February 03 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QColorDialog>
#include <QFontDialog>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayReaderToolBar.h"
#include "CreateParagraphDialog.h"

/*****************************************************************************!
 * Function : TextDisplayReaderToolBar
 *****************************************************************************/
TextDisplayReaderToolBar::TextDisplayReaderToolBar
(QWidget* InParent) : QFrame(InParent)
{
  QPalette pal;
  pal = palette();
  pal.setBrush(QPalette::Window, QBrush(QColor(192, 192, 192)));
  setPalette(pal);
  setAutoFillBackground(true);
  setFrameShape(QFrame::Box);
  setFrameShadow(QFrame::Sunken);
  setLineWidth(1);
  initialize();
}

/*****************************************************************************!
 * Function : ~TextDisplayReaderToolBar
 *****************************************************************************/
TextDisplayReaderToolBar::~TextDisplayReaderToolBar
()
{
}

/*****************************************************************************!
 * Function : initialize
 *****************************************************************************/
void
TextDisplayReaderToolBar::initialize()
{
  InitializeSubWindows();  
  CreateSubWindows();
  CreateConnections();

  TextColor = QColor(0, 0, 0);
  TextBackgroundColor = QColor(255, 255, 255);
  TextFont = QFont("Times New Roman", 10, QFont::Normal);
  
  ActionTextColorPushed = new QAction("TextColorPushed", this);
  connect(ActionTextColorPushed, SIGNAL(triggered()), this, SLOT(SlotTextColorPushed()));
  ActionTextBackgroundColorPushed = new QAction("TextBackgroundColorPushed", this);
  connect(ActionTextBackgroundColorPushed, SIGNAL(triggered()), this, SLOT(SlotTextBackgroundColorPushed()));
  ActionFontPushed = new QAction("FontPushed", this);
  connect(ActionFontPushed, SIGNAL(triggered()), this, SLOT(SlotFontPushed()));
  ActionParagraphPushed = new QAction("ParagraphPushed", this);
  connect(ActionParagraphPushed, SIGNAL(triggered()), this, SLOT(SlotParagraphPushed()));
}

/*****************************************************************************!
 * Function : CreateSubWindows
 *****************************************************************************/
void
TextDisplayReaderToolBar::CreateSubWindows()
{
  int                           x;
  int                           y;

  x = 1;
  y = 1;
  
  //! Create the TextColor button  
  TextColorButton = new QPushButton();
  TextColorButton->setParent(this);
  TextColorButton->setIcon(QIcon(QPixmap(":/Images/TextColor.png")));
  TextColorButton->move(x, y);
  TextColorButton->resize(24,24);
  connect(TextColorButton, SIGNAL(pressed()), this, SLOT(SlotTextColorPushed()));
  y += 25;

  //! Create the TextBackgroundColor button  
  TextBackgroundColorButton = new QPushButton();
  TextBackgroundColorButton->setParent(this);
  TextBackgroundColorButton->setIcon(QIcon(QPixmap(":/Images/TextBackgroundColor.png")));
  TextBackgroundColorButton->move(x, y);
  TextBackgroundColorButton->resize(24,24);
  connect(TextBackgroundColorButton, SIGNAL(pressed()), this, SLOT(SlotTextBackgroundColorPushed()));
  y += 25;
  
  //! Create the Font button  
  FontButton = new QPushButton();
  FontButton->setParent(this);
  FontButton->setIcon(QIcon(QPixmap(":/Images/Font.png")));
  FontButton->move(x, y);
  FontButton->resize(24,24);
  connect(FontButton, SIGNAL(pressed()), this, SLOT(SlotFontPushed()));
  y += 25;
  
  //! Create the Paragraph button  
  ParagraphButton = new QPushButton();
  ParagraphButton->setParent(this);
  ParagraphButton->setIcon(QIcon(QPixmap(":/Images/Paragraph.png")));
  ParagraphButton->move(x, y);
  ParagraphButton->resize(24,24);
  connect(ParagraphButton, SIGNAL(pressed()), this, SLOT(SlotParagraphPushed()));
  y += 25;

  //! Create the Extra button  
  ExtraButton = new QPushButton();
  ExtraButton->setParent(this);
  ExtraButton->setText("E");
  ExtraButton->move(x, y);
  ExtraButton->resize(24,24);
  connect(ExtraButton, SIGNAL(pressed()), this, SLOT(SlotExtraPushed()));
  y += 25;

}

/*****************************************************************************!
 * Function : CreateConnections
 *****************************************************************************/
void
TextDisplayReaderToolBar::CreateConnections()
{
  
}

/*****************************************************************************!
 * Function : InitializeSubWindows
 *****************************************************************************/
void
TextDisplayReaderToolBar::InitializeSubWindows()
{
  
}

/*****************************************************************************!
 * Function : resizeEvent
 *****************************************************************************/
void
TextDisplayReaderToolBar::resizeEvent
(QResizeEvent* InEvent)
{
  QSize					size;  
  int					width;
  int					height;

  size = InEvent->size();
  width = size.width();
  height = size.height();
  (void)height;
  (void)width;
}

/*****************************************************************************!
 * Function : SlotTextColorPushed
 *****************************************************************************/
void
TextDisplayReaderToolBar::SlotTextColorPushed(void)
{
  QColorDialog                  dialog(TextColor);
  dialog.setWindowTitle("Set Text Color");
  dialog.setOptions(QColorDialog::DontUseNativeDialog);
  if ( dialog.exec() ) {
    TextColor = dialog.currentColor();
  }
  emit SignalTextColorSet(TextColor);
}

/*****************************************************************************!
 * Function : SlotTextBackgroundColorPushed
 *****************************************************************************/
void
TextDisplayReaderToolBar::SlotTextBackgroundColorPushed(void)
{
  QColorDialog                  dialog(TextBackgroundColor);
  dialog.setWindowTitle("Set Text Background Color");
  dialog.setOptions(QColorDialog::DontUseNativeDialog);
  if ( dialog.exec() ) {
    TextBackgroundColor = dialog.currentColor();
  }
  emit SignalTextBackgroundColorSet(TextBackgroundColor);
}

/*****************************************************************************!
 * Function : SlotFontPushed
 *****************************************************************************/
void
TextDisplayReaderToolBar::SlotFontPushed(void)
{
  QFontDialog                   dialog(TextFont);
  dialog.setWindowTitle("Text Font");
  if ( dialog.exec() ) {
    TextFont = dialog.currentFont();
  }
  emit SignalTextFontSet(TextFont);
}

/*****************************************************************************!
 * Function : SlotParagraphPushed
 *****************************************************************************/
void
TextDisplayReaderToolBar::SlotParagraphPushed(void)
{
  int                                   bottomIndent;
  int                                   topIndent;
  int                                   rightIndent;
  int                                   leftIndent;
  CreateParagraphDialog                 dialog;

  if ( dialog.exec() ) {
    leftIndent          = dialog.GetLeftIndent();
    rightIndent         = dialog.GetRightIndent();
    topIndent           = dialog.GetTopIndent();
    bottomIndent        = dialog.GetBottomIndent();
  
    emit SignalParagraphSet(leftIndent, rightIndent, topIndent, bottomIndent);
  }
}

/*****************************************************************************!
 * Function : GetTextColor
 *****************************************************************************/
QColor
TextDisplayReaderToolBar::GetTextColor(void)
{
  return TextColor;  
}

/*****************************************************************************!
 * Function : SetTextColor
 *****************************************************************************/
void
TextDisplayReaderToolBar::SetTextColor
(QColor InTextColor)
{
  TextColor = InTextColor;  
}

/*****************************************************************************!
 * Function : GetTextBackgroundColor
 *****************************************************************************/
QColor
TextDisplayReaderToolBar::GetTextBackgroundColor(void)
{
  return TextBackgroundColor;  
}

/*****************************************************************************!
 * Function : SetTextBackgroundColor
 *****************************************************************************/
void
TextDisplayReaderToolBar::SetTextBackgroundColor
(QColor InTextBackgroundColor)
{
  TextBackgroundColor = InTextBackgroundColor;  
}

/*****************************************************************************!
 * Function : GetTextFont
 *****************************************************************************/
QFont
TextDisplayReaderToolBar::GetTextFont(void)
{
  return TextFont;  
}

/*****************************************************************************!
 * Function : SetTextFont
 *****************************************************************************/
void
TextDisplayReaderToolBar::SetTextFont
(QFont InTextFont)
{
  TextFont = InTextFont;  
}

/*****************************************************************************!
 * Function : SlotExtraPushed
 *****************************************************************************/
void
TextDisplayReaderToolBar::SlotExtraPushed(void)
{
  emit SignalExtraPushed();  
}
