/*****************************************************************************
 * FILE NAME    : TextDisplayInterlinearItem.h
 * DATE         : October 16 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Vertiv Company
 *****************************************************************************/
#ifndef _textdisplayinterlinearitem_h_
#define _textdisplayinterlinearitem_h_

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
#define TEXT_DISPLAY_INTERLINEAR_ITEM_X 200
#define TEXT_DISPLAY_INTERLINEAR_ITEM_Y 200
#define TEXT_DISPLAY_INTERLINEAR_ITEM_WIDTH 200
#define TEXT_DISPLAY_INTERLINEAR_ITEM_HEIGHT 200

/*****************************************************************************!
 * Exported Class : TextDisplayInterlinearItem
 *****************************************************************************/
class TextDisplayInterlinearItem : public TextDisplayItem
{
 //! Constructors
 public :
  TextDisplayInterlinearItem    (int InBook, int InChapter, int InVerse, QString InText,
                                 QString InEnglish, QString InMorphology, QString InStrongsReference);

 //! Destructor
 public :
  ~TextDisplayInterlinearItem   ();

 //! Public Types
 public :
  
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
  void                          initialize              ();

 //! Private Data
 private :
  QString                       English;
  QString                       Morphology;
  QString                       StrongsReference;
  
};

#endif /* _textdisplayinterlinearitem_h_*/
