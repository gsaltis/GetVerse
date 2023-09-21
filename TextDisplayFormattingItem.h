/*****************************************************************************
 * FILE NAME    : TextDisplayFormattingItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayformattingitem_h_
#define _textdisplayformattingitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayFormattingItem
 *****************************************************************************/
class TextDisplayFormattingItem : public TextDisplayItem
{
 //! Public Types
 public :
  enum FormatType {
    FormatTypeNone          = 0,
    FormatTypePostVerse,
    FormatTypePreVerse,
    FormatTypeMidVerse,
    FormatTypeMidVerseIndent,
    FormatTypeSection,
    FormatTypeWordBreak,
    FormatTypeWordLower,
    FormatTypeWordUpper,
    FormatTypeWordCaptilize,
  };

  
 //! Constructors
 public :
  TextDisplayFormattingItem     (int InBook, QString InBookName, int InChapter, int InVerse,
                                 enum FormatType InFormatting);

 //! Destructor
 public :
  ~TextDisplayFormattingItem    ();

 //! Public Methods
 public :
  virtual void                  Draw                    (QPainter* InPainter);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  QString                       BookName;
  int                           Formatting;
  
};

#endif /* _textdisplayformattingitem_h_*/
