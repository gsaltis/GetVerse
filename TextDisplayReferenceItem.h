/*****************************************************************************
 * FILE NAME    : TextDisplayReferenceItem.h
 * DATE         : September 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayreferenceitem_h_
#define _textdisplayreferenceitem_h_

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
 * Exported Class : TextDisplayReferenceItem
 *****************************************************************************/
class TextDisplayReferenceItem : public TextDisplayItem
{
 //! Constructors
 public :
  TextDisplayReferenceItem      (int InBook, QString InBookName, int InChapter, int InVerse);

 //! Destructor
 public :
  ~TextDisplayReferenceItem     ();

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
  
};

#endif /* _textdisplayreferenceitem_h_*/
