/*****************************************************************************
 * FILE NAME    : TextDisplayWordFormattingItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplaywordformattingitem_h_
#define _textdisplaywordformattingitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "TextDisplayFormattingItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayWordFormattingItem
 *****************************************************************************/
class TextDisplayWordFormattingItem : public TextDisplayFormattingItem
{
 //! Public Types
 public :
  
 //! Constructors
 public :
  TextDisplayWordFormattingItem     (int InBook, QString InBookName, int InChapter, int InVerse,
                                     int InWord, enum FormatType InWordFormatting);

 //! Destructor
 public :
  ~TextDisplayWordFormattingItem    ();

 //! Public Methods
 public :
  virtual void                  Draw                    (QPainter* InPainter) override;
  int                           GetWordIndex            ();
  virtual bool                  Contains                (QPoint InPaint);
  bool                          IsReferenceWord         (const int InBook, const int InChapter, const int InVerse, const int InWord);
  
 //! Public Data
 public :

 //! Protected Methods
 protected :
  int                           WordIndex;
  
 //! Protected Data
 protected :

 //! Private Methods
 private :

 //! Private Data
 private :
  
};

#endif /* _textdisplaywordformattingitem_h_*/
