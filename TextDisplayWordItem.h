/*****************************************************************************
 * FILE NAME    : TextDisplayWordItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayworditem_h_
#define _textdisplayworditem_h_

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
#include "TextDisplayWordFormattingItem.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/

/*****************************************************************************!
 * Exported Class : TextDisplayWordItem
 *****************************************************************************/
class TextDisplayWordItem : public TextDisplayItem
{
 //! Constructors
 public :
  TextDisplayWordItem           (int InBook, int InChapter, int InVerse, QString InWord, int InWordIndex);

 //! Destructor
 public :
  ~TextDisplayWordItem          ();

 //! Public Methods
 public :
  int                           GetWordIndex            (void);
  void                          SetWordIndex            (int InWordIndex);
  void                          DrawFormatted           (QPainter* InPainter, TextDisplayWordFormattingItem* InFormatting);
  virtual void                  Draw                    (QPainter* InPainter);
  virtual void                  DrawSelected            (QPainter* InPainter);
  virtual void                  SetFont                 (QFont InFont);
  virtual bool                  Contains                (QPoint InPaint);
  virtual QString               GetText                 (void);
  virtual bool                  IsReference             (const int InBook, const int InChapter, const int InVerse, const int InWord);
  QString                       GetWord                 (void);
  void                          SetWord                 (QString InWord);
  
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
  
  int                           WordIndex;
  QString                       Word;

};

#endif /* _textdisplayworditem_h_*/
