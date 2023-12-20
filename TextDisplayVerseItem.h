/*****************************************************************************
 * FILE NAME    : TextDisplayVerseItem.h
 * DATE         : December 18 2023
 * PROJECT      : 
 * COPYRIGHT    : Copyright (C) 2023 by Gregory R Saltis
 *****************************************************************************/
#ifndef _textdisplayverseitem_h_
#define _textdisplayverseitem_h_

/*****************************************************************************!
 * Global Headers
 *****************************************************************************/
#include <QtCore>
#include <QtGui>
#include <QLabel>
#include <QWidget>

/*****************************************************************************!
 * Local Headers
 *****************************************************************************/

/*****************************************************************************!
 * Exported Macros
 *****************************************************************************/
#define TEXT_DISPLAY_VERSE_ITEM_X       200
#define TEXT_DISPLAY_VERSE_ITEM_Y       200
#define TEXT_DISPLAY_VERSE_ITEM_WIDTH   200
#define TEXT_DISPLAY_VERSE_ITEM_HEIGHT  200

/*****************************************************************************!
 * Exported Class : TextDisplayVerseItem
 *****************************************************************************/
class TextDisplayVerseItem : public QLabel
{
  Q_OBJECT;

 //! Constructors
 public :
  TextDisplayVerseItem          ();

 //! Destructor
 public :
  ~TextDisplayVerseItem         ();

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
  void                          CreateSubWindows        ();
  void                          InitializeSubWindows    ();
  void                          resizeEvent             (QResizeEvent* InEvent);

 //! Private Data
 private :

 //! Public Slots
 public slots :

 //! Public Signals
 signals :

 //! Public Actions
 public :

};

#endif /* _textdisplayverseitem_h_*/
