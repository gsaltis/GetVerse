/*****************************************************************************
 * FILE NAME    : TextDisplayReaderViewWindow.h
 * DATE         : January 01 2024
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2024 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreaderviewwindow_h_
#define _textdisplayreaderviewwindow_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_READER_VIEW_WINDOW_X 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_Y 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_WIDTH 200
#define TEXT_DISPLAY_READER_VIEW_WINDOW_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayReaderViewWindow
 *****************************************************************************/
class TextDisplayReaderViewWindow : public QTextEdit
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayReaderViewWindow   (QWidget* InParent);

 //! Destructor
 public :
  ~TextDisplayReaderViewWindow  ();

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
  void                          Initialize                      ();
  void                          CreateParagraphBlock            (QTextCursor& InCursor, uint32_t InPosition, int InLeftIndent, int InRightIndent, int InTopIndent, int InBottomIndent);
  void                          CreateCharBlock                 (QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QColor InColor);
  void                          CreateChapterBlock              (QTextCursor& InCursor, uint32_t InIndent);
  void                          CreateCharFontBlock             (QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QFont InFont);
  void                          CreateCharBackgroundBlock       (QTextCursor& InCursor, uint32_t InStart, uint32_t InEnd, QColor InColor);
  void                          CreateConnections               (void);
  int                           FindWordIndexAtPosition         (int InCursorPosition);

 //! Private Data
 private :
  BookInfo*                     Book;
  int                           Chapter;
  QString                       CurrentText;
  int                           CurrentTextStart;
  int                           CurrentTextEnd;
  
  int                           selectionStart;
  int                           selectionEnd;
  int                           selectionStartWord;
  int                           selectionEndWord;
 
  int                           currentCursorIndex;

 //! Public Slots
 public slots :
  void                          SlotBookSelected                (BookInfo* InBook);
  void                          SlotChapterSelected             (int InChapter);
  void                          SlotCursorPositionChanged       (void);
  void                          SlotTextColorSet                (QColor InTextColor);
  void                          SlotTextFontSet                 (QFont InFont);
  void                          SlotTextBackgroundColorSet      (QColor InTextBackgroundColor);
  void                          SlotParagraphSet                (int InLeftIndent, int InRightIndent, int InTopIndent, int InBottomIndent);
  void                          SlotExtraPushed                 ();

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayreaderviewwindow_h_*/
