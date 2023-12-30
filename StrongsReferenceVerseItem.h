/*****************************************************************************
 * FILE NAME    : StrongsReferenceVerseItem.h
 * DATE         : December 28 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _strongsreferenceverseitem_h_
#define _strongsreferenceverseitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QTableWidgetItem>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/
#include "BookInfo.h"

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define STRONGS_REFERENCE_VERSE_ITEM_X  200
#define STRONGS_REFERENCE_VERSE_ITEM_Y  200
#define STRONGS_REFERENCE_VERSE_ITEM_WIDTH 200
#define STRONGS_REFERENCE_VERSE_ITEM_HEIGHT 200

/*****************************************************************************!
 * Exported Class : StrongsReferenceVerseItem
 *****************************************************************************/
class StrongsReferenceVerseItem : public QTableWidgetItem
{
 //! Constructors
 public :
  StrongsReferenceVerseItem     (int InBookNumber, int InChapterNumber, int InVerseNumber);

 //! Destructor
 public :
  ~StrongsReferenceVerseItem    ();

 //! Public Methods
 public :
  void                          GetReference            (int &InBookNumber, int &InChapterNumber, int &InVerseNumber);

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
  int                           BookNumber;
  int                           ChapterNumber;
  int                           VerseNumber;
  BookInfo*                     bookInfo;

};

#endif /* _strongsreferenceverseitem_h_*/
