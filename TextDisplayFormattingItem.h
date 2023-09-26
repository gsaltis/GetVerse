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
    FormatTypeWordBreakIndent,
    FormatTypeSection,
    FormatTypeWordBreak,
    FormatTypeWordLower,
    FormatTypeWordUpper,
    FormatTypeWordCaptilize,
    FormatTypeWordHighlight
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
  virtual void                  Draw                    (QPainter* InPainter) override;
  FormatType                    GetFormattingType       ();
  
 //! Public Data
 public :

 //! Protected Methods
 protected :

 //! Protected Data
 protected :
  QString                       BookName;
  int                           Formatting;

 //! Private Methods
 private :

 //! Private Data
 private :
  
};

#endif /* _textdisplayformattingitem_h_*/
